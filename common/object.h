#pragma once
class Object
{
public:
	Object(void);
	~Object(void);

	virtual int initialize() = 0;
	virtual int finalize() = 0;
	virtual int serialize() = 0;
	virtual int deserialize() = 0;
};

