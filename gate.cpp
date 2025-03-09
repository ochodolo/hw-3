#include "gate.h"

NotGate::NotGate(Wire* input, Wire* output) {
  m_inputs.push_back(input);
  m_output = output;
}

Event* NotGate::update() {
  char inState = m_inputs[0]->getState();
  char newState;
  if(inState = 'X') {
    newState = 'X';
  } else if(inState == '0') {
    newState = '1';
  } else if (inState == '1'){
    newState = '0';
  } else {
    newState = 'X';
  }

  if(m_output->getState() != newState) {
    Event* e = new Event();
    Event* e1 = new Event();
    e->time = 0;
    e->wireID = m_output->getId();
    e->state = newState;
    return e;
  }
  return nullptr;
}