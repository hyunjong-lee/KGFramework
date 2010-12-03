#pragma once
#include "character.h"
#include "abstracteventlistener.h"

class Car : public Character, public AbstractEventListener, public Singleton<Car> {
 public:
  Car();
  ~Car();
  int handle(std::tr1::shared_ptr<AbstractEvent> &ae);
};

