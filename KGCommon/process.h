#pragma once
class Process
{
public:
	Process(void);
	~Process(void);

	virtual int run(int argc, char *argv[]) = 0;
};
