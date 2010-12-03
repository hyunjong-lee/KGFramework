#pragma once

class AbstractEvent;

struct AbstractEventListener
{
  AbstractEventListener() {}
  virtual ~AbstractEventListener() {}
  virtual int handle(std::tr1::shared_ptr<AbstractEvent> &ae) = 0;
};
