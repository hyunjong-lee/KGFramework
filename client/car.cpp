#include "clientpch.h"
#include "car.h"
#include "clienteventfactory.h"
IMPLEMENT_SINGLETON(Car);

Car::Car()
{
}

Car::~Car()
{
}

int Car::handle(boost::shared_ptr<AbstractEvent> &ae) {
  CarMoveEvent *cme = dynamic_cast<CarMoveEvent *>(ae.get());
 if (cme) {
    if (cme->cmd == CMD_UP)
      pos[1] += cme->amount;
    else if (cme->cmd == CMD_DOWN)
      pos[1] -= cme->amount;
    else if (cme->cmd == CMD_LEFT)
      pos[0] -= cme->amount;
    else if (cme->cmd == CMD_RIGHT)
      pos[0] += cme->amount;
    return 1;
  }
  return 0;
}
