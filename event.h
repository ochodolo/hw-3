#ifndef EVENT_H
#define EVENT_H

struct Event {
  int time;
  int wireID;
  char state;
}

struct EventLess {
  bool opertor()(const Event* a, const Event* b) const {
    return a->time < b->time;
  }
};

#endif