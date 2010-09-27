#pragma once

class CClientEventHandler
{
public:
	CClientEventHandler(void);
	~CClientEventHandler(void);

  int handle(int event);
};
