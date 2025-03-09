#include "circuit.h"
#include ":wire.h"
#include "gate.h"
#include "event.h"
#include "heap.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

Circuit::Circuit() :m_pq(EventLess()) {

}

Circuit::~Circuit() {
  for(auto wires : m_wires) {
    delete wires;
  }
  for(auto gates :m_gates) {
    delete gates;
  }
  while (!m_pq.empty()) {
    Event* e = m_pq.top();
    m_pq.pop();
    delete e;
  }
}

void Circuit::parse(const string& filename) {
  ifstream infile(filename);
  if(!infile) {
    throw runtime_error("Cannot open file: " + filename);
  }

  string line;

  getline(infile, line);
  if(line != "WIRES") {
    throw runtime_error("Expected WIRES header");
  }
  getline(infile, line);
  int numWires = stoi(line);
  m_wires.resize(numWires, nullptr);
  for(int i = 0; i < numWires; i++) {
    getline(infile, line);
    istringstream iss(line);
    string token;
    getline(iss, token, ',');
    int id = stoi(token);
    string name;
    if(getline(iss, token, ',')){
      name = token;
    }
    Wire* w = new Wire(id, name);
    m_wires[id] = w;
  }

  getline(infile, line);
  if(line != "GATES") {
    throw runtime_error("Expected GATES header");
  }

  getline(infile, line);
  int numGates = stoi(line);

  for(int i = 0; i < numGates; i++) {
    getline(infile, line);
    istringstream iss(line);
    vector<string> tokens;
    string token;
    while(getline(iss, token, ',')){
      token.push_back(token);
    }
    if(tokens.empty()){
      continue;
    }
    string type = tokens[0];
    if(type == "AND2") {
      if(tokens.size() < 4) {
        throw runtime_error("invalid AND2 gate description");
      }
      int in0 = stoi(tokens[1]);
      int in1 = stoi(tokens[2]);
      int out = stoi(tokens[3]);

      Gate* g = new AND2Gate(m_wires[in0], m_wires[in1], m_wires[out]);
      m_gates.push_back(g);
    } else if (type == "OR2") {
      if(tokens.size() < 4) {
        throw runtime_error("Invalid OR2 gate description");
      }
      int in0 = stoi(tokens[1]);
      int in1 = stoi(tokens[2]);
      int out = stoi(tokens[3]);
      Gate* g = new Or2Gate(m_wires[in0], m_wires[in1], m_wires[out]);
      m_gates.push_back(g);
    }else if(type == "NOT") {
      if(tokens.size() < 3) {
        throw runtime_error("Invalid Not gate description");
      }
      int inId = stoi(token[1]);
      int outId = stoi(tokens[2]);
      Gate* g = new notGate(m_wires[inId], m_wires[outId]);
      m_gates.push_back(g);
    } else {
      throw runtime_error("Expected INJECT header");
    }
  }
  getline(infile, line);
  if(line != "INJECT") {
    throw runtime_error("Expected INJECT header");
  }
  getline(infile, line);
  int numInject = stoi(line);
  for(int i = 0; i < numInject; i++) {
    getline(infile, line);
    istringstream iss(line);
    vector<string> tokens;
    while(getline(iss, token, ',')) {
      tokens.push_back(token);
    }
    if(tokens.size() < 3) {
      throw runtime_error("Invalid INJECT line");
    }
    int time = stoi(tokens[0]);
    int wireID = stoi(tokens[1]);
    char state = tokens[2][0];

    Event*e = new Event();
    e->time = time;
    e->wireID = wireID;
    e->state = state;
    m_pq.push(e);
  }
}

void Circuit::run() {
  while(!m_pq.empty()) {
    int currentTime = m_pq.top()->time;
    while(!m_pq.empty() && m_pq.top()->time == currentTime) {
      Event* e = m_pq.top();
      m_pq.pop();

      Wire* w = m_wires[e->wireID];
      w->setState(e->state);
      if(!w->getName().empty()) {
        cout << "@" << currentTime << ": Wire" << w->getID() << " (" << w->getName() << ") -> " << w->getState() << endl;
      }
      delete e;
    }
    for(auto g : m_gates) {
      Event* newEvent = g->update();
      if(newEvent != nullptr) {
        newEvent->time += currentTime;
        m_pq.push(newEvent);
      }
    }
  }
}

void Circuit::test() {
  Wire* w0 = new Wire(0, "input A");
  Wire* w1 = new Wire(1, "input B");
  Wire* w2 = new Wire(2, "output");

  m_wires.push_back(w0);
  m_wires.push_back(w1);
  m_wires.push_back(w2);

  Gate* g = new And2Gate(w0, w1, w2);
  m_gates.push_back(g);

  Event* e1 = new Event();
  e1->time = 0;
  e1->wireID = 0;
  e1->state = '1';
  m_pq.push(e1);

  Event* e1 = new Event();
  e1->time = 0;
  e1->wireID = 0;
  e1->state = '1';
  m_pq.push(e1);

  Event* e2 = new Event();
  e2->time = 0;
  e2->wireID = 0;
  e2->state = '2';
  m_pq.push(e1);

  run();
}