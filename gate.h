#ifndef GATE_H
#define GATE_H
#include <vector>
#include "wire.h"
#include "event.h"

class Gate {
  public:
    virtual ~Gate() {}
    virtual Event* update() = 0;
    protected:
    std::vector<Wire*> m_inputs;
    Wire* m_output;
};

class NotGate : public Gate {
  public:
  NotGate(Wire* input, Wire* output);
  virtual ~NotGate() {}
  virtual Event* update;
};

#endif