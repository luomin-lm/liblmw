/**********************************************************************
*	�ļ����ܣ��¼��ں˶��������
*	������@ ������
*	��д������Win7 + VS2013
*	��дʱ�䣺2020-08-19
*	�޸�ʱ�䣺2020-08-19
**/
#ifndef _CPP_EVENT_H_
#define _CPP_EVENT_H_

#include <Windows.h>

namespace lmw
{
#include "types.h"

	class CEvent
	{
	public:
		CEvent();
		~CEvent();

	public:
		int lock();
		void unlock();
		int wait(TCUQ(long) ms);
		HANDLE Event();

	private:
		HANDLE m_ev;
	};
}



#endif