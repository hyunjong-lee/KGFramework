#include "commonpch.h"
#include "abstractevent.h"

AbstractEvent::AbstractEvent()
{
	m_type = "AbstractEvent";
	m_size = 0;
}

AbstractEvent::AbstractEvent(const std::string &type, int size)
  : m_type(type), m_size(size)
{
}

AbstractEvent::~AbstractEvent(void)
{
}
