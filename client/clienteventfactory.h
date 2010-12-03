#pragma once

enum CarMoveDirection {
  CMD_UNKNOWN,
  CMD_UP,
  CMD_DOWN,
  CMD_LEFT,
  CMD_RIGHT,
};

class ClientEventFactory
{
public:
	ClientEventFactory(void);
	~ClientEventFactory(void);

public:
	//define constants

	// define variables

	// define functions
	static std::tr1::shared_ptr<AbstractEvent> MakeCarEvent(CarMoveDirection cmd, double amount);
	static std::tr1::shared_ptr<AbstractEvent> MakeEvent(const std::string &type);
private:
	// define constants

	// define variables

	// define functions
};

struct CarMoveEvent : public AbstractEvent
{
  CarMoveDirection cmd;
  double amount;
};
