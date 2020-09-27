#include "Event.h"

namespace lmw
{
	CEvent::CEvent()
	{
		m_ev = CreateEvent(NULL, FALSE, FALSE, NULL);
	}
	CEvent::~CEvent()
	{
		CloseHandle(m_ev);
	}
	int  CEvent::lock()
	{
		return ResetEvent(m_ev);
	}
	void CEvent::unlock()
	{
		SetEvent(m_ev);
	}
	int  CEvent::wait(TCUQ(long) ms)
	{
		return WaitForSingleObject(m_ev, ms);
	}
	HANDLE CEvent::Event()
	{
		return m_ev;
	}
}





