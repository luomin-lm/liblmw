/**********************************************************************
*	文件功能：事件内核对象操作类
*	所有者@ ：罗敏
*	编写环境：Win7 + VS2013
*	编写时间：2020-08-19
*	修改时间：2020-08-19
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