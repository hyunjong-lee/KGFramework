#pragma once

// ���� �Լ��� ������ - AbstractEvent �� ���ؼ�
// ���� ��������� �߰��Ͽ��µ� ���� ���� ���ΰ�? - �̷� �Ϳ� ���� ����� �غ����� ����
#include "KGClientPCH.h"

class CClientEventFactory
{
public:
	CClientEventFactory(void);
	~CClientEventFactory(void);

public:
	//define constants

	// define variables

	// define functions
	CAbstractEvent MakeEvent(/* What parameters are in here? */);
	
private:
	// define constants

	// define variables

	// define functions
};
