#pragma once

// ���� �Լ��� ������ - AbstractEvent �� ���ؼ�
// ���� ��������� �߰��Ͽ��µ� ���� ���� ���ΰ�? - �̷� �Ϳ� ���� ����� �غ����� ����
#include "KGClientPCH.h"

class KGClientEventFactory
{
public:
	KGClientEventFactory(void);
	~KGClientEventFactory(void);

public:
	//define constants

	// define variables

	// define functions
	AbstractEvent MakeEvent(/* What parameters are in here? */);
	
private:
	// define constants

	// define variables

	// define functions
};
