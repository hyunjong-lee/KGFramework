#include "clientpch.h"
#include "clienteventfactory.h"

ClientEventFactory::ClientEventFactory(void)
{
}

ClientEventFactory::~ClientEventFactory(void)
{
}

std::tr1::shared_ptr<AbstractEvent> ClientEventFactory::MakeEvent(const std::string &type) {
  return std::tr1::shared_ptr<AbstractEvent>(new AbstractEvent(type, 0));
}

std::tr1::shared_ptr<AbstractEvent> ClientEventFactory::MakeCarEvent(CarMoveDirection cmd, double amount) {
  std::tr1::shared_ptr<CarMoveEvent> cme(new CarMoveEvent);
  cme->cmd = cmd;
  cme->amount = amount;
  return cme;
}
