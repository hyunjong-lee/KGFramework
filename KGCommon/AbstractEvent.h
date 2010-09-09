#pragma once

class KGCOMMON_API CAbstractEvent
{
public:
	CAbstractEvent(void);
	~CAbstractEvent(void);

public:
	//define constants
	enum COMMON_EVENT
	{
	};

	// define variables

	// define functions
	inline std::string	GetType() { return m_type;	}
	inline int			GetSize() { return m_size;	}
	
private:
	// define constants

	// define variables
	std::string		m_type;
	int				m_size;

	// define functions
};
