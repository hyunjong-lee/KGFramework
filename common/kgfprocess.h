#pragma once

class KGCOMMON_API KGFProcess
{
public:
	KGFProcess(void);
	~KGFProcess(void);

	virtual int run(int argc, char *argv[]) = 0;
};
