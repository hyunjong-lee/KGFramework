#pragma once

// ���� �Լ��� ������ - AbstractEvent �� ���ؼ�
// ���� ��������� �߰��Ͽ��µ� ���� ���� ���ΰ�? - �̷� �Ϳ� ���� ����� �غ����� ����
#include "clientpch.h"

class ClientEventDispatcher
{
public:
	ClientEventDispatcher(void);
	~ClientEventDispatcher(void);

public:
	//define constants

	// define variables

	// define functions
	int DispatchEvent(AbstractEvent event);
	
private:
	// define constants

	// define variables

	// define functions

};
