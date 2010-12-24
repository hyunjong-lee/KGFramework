#pragma once

#include <boost/shared_ptr.hpp>

class AbstractEvent;

struct AbstractEventListener
{
  AbstractEventListener() {}
  virtual ~AbstractEventListener() {}
  virtual int handle(boost::shared_ptr<AbstractEvent> &ae) = 0;
};
