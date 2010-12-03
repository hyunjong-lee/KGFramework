#pragma once

#include "actor.h"

class KGCOMMON_API Character : public Actor
{
public:
	Character(void);
	virtual ~Character(void);

	int check();
};
