#pragma once

// ���� �Լ��� ������ - AbstractEvent �� ���ؼ�
// ���� ��������� �߰��Ͽ��µ� ���� ���� ���ΰ�? - �̷� �Ϳ� ���� ����� �غ����� ����
#include "KGClientPCH.h"

class CClientEventDispatcher
{
public:
	CClientEventDispatcher(void);
	~CClientEventDispatcher(void);

public:
	//define constants

	// define variables

	// define functions
	int DispatchEvent(CAbstractEvent event);
	
private:
	// define constants

	// define variables

	// define functions

};
