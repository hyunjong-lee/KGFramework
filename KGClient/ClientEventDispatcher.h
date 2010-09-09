#pragma once

// 밑의 함수가 에러남 - AbstractEvent 에 의해서
// 따라서 헤더파일을 추가하였는데 과연 옳은 일인가? - 이런 것에 대한 고민을 해본적이 없음
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
