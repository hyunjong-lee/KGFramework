#pragma once

// ���� �Լ��� ������ - AbstractEvent �� ���ؼ�
// ���� ��������� �߰��Ͽ��µ� ���� ���� ���ΰ�? - �̷� �Ϳ� ���� ����� �غ����� ����
#include "clientpch.h"

class ClientEventFactory
{
public:
	ClientEventFactory(void);
	~ClientEventFactory(void);

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
