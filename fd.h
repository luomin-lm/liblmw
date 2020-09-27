/**********************************************************************
*	文件功能：文件对象操作类
*	所有者@ ：罗敏
*	编写环境：Win7 + VS2013
*	编写时间：2020-08-12
*	修改时间：2020-08-12
**/
#ifndef _CPP_FD_H_
#define _CPP_FD_H_

#include "Event.h"
#include "libcpp.h"

namespace lmw
{
	class CFile
	{
	public:
		CFile();
		~CFile();

		BOOL Open(TCPCH filename, BOOL IsCreate, BOOL isEvent = FALSE);
		/* 阻塞 */
		uint Read(char* buff, TCUQ(int) bufflen);
		uint Write(TCPCH buff, TCUQ(int) bufflen);
		/* 非阻塞 */
		void Read(char* buff, TCUQ(int) bufflen, CEvent* pEvent);
		void Write(TCPCH buff, TCUQ(int) bufflen, CEvent* pEvent);
		void Close();
		uint GetFileSize();
		void Flush();
		void Lock();
		void Unlock();
		HANDLE GetHandle();
		/* 文件映射 */
		BOOL FileMapToBuffer(TCUQ(int) mapSize = 0);
		char* GetBuffer();

	private:
		HANDLE m_hFile;
		HANDLE m_hMap;
		char * m_buff;
	};

	/* 共享内存 */
	class CShareMemory
	{
	public:
		CShareMemory(const char* name, BOOL isWrite, const uint& size = 1024);
		~CShareMemory();

		char * GetBuffer();

	private:
		HANDLE m_hfileMap;
		char* m_pBuffer;
	};

	class CDir
	{
	public:
		CDir(TCPCH str = nullptr);
		BOOL HaveDir();
		BOOL Create();
		void SetDir(TCPCH str);
		CStr GetDir();
		/* 只能删除空目录 */
		BOOL DeleteDir();

	private:
		CStr m_dir;
	};

	/******************************************************************
	*	功能：将src字符串加密，生成加密后的字符串
	*	参数：
	*		src		将要加密的源字符串
	*		srclen	源字符串长度
	*		key		密码字符串
	*	返回值：无
	**/
	void StrToPassStr(char* src, TCUQ(int) srclen, TCPCH key);
	/******************************************************************
	*	功能：将src字符串加密，生成加密后的字符串
	*	参数：
	*		src		加密的源字符串
	*		srclen	源字符串长度
	*		key		密码字符串
	*	返回值：无
	**/
	void PassStrToStr(char* src, TCUQ(int) srclen, TCPCH key);

}


#endif
