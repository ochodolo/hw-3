#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <vector>
#include <string>
#include "wire.h"
#include "gate.h"
#include "heap.h" 
#include "event.h"

class Circuit {
  public:
  Circuit();
  ~Circuit();

  void parse(const std::string &filename);
  void run();
  void test();

  std::vector<Wire*> m_wires;
  std::vector<Gate*> m_gates;
  Heap<Event*, EventLess()> m_pq;

  private:
}

#endif