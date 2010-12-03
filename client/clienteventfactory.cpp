#include "clientpch.h"
#include "clienteventfactory.h"

ClientEventFactory::ClientEventFactory(void)
{
}

ClientEventFactory::~ClientEventFactory(void)
{
}

boost::shared_ptr<AbstractEvent> ClientEventFactory::MakeEvent(const std::string &type) {
  return boost::shared_ptr<AbstractEvent>(new AbstractEvent(type, 0));
}

boost::shared_ptr<AbstractEvent> ClientEventFactory::MakeCarEvent(CarMoveDirection cmd, double amount) {
  boost::shared_ptr<CarMoveEvent> cme(new CarMoveEvent);
  cme->cmd = cmd;
  cme->amount = amount;
  return cme;
}
