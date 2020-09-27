/**********************************************************************
*	�ļ����ܣ��ļ����������
*	������@ ������
*	��д������Win7 + VS2013
*	��дʱ�䣺2020-08-12
*	�޸�ʱ�䣺2020-08-12
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
		/* ���� */
		uint Read(char* buff, TCUQ(int) bufflen);
		uint Write(TCPCH buff, TCUQ(int) bufflen);
		/* ������ */
		void Read(char* buff, TCUQ(int) bufflen, CEvent* pEvent);
		void Write(TCPCH buff, TCUQ(int) bufflen, CEvent* pEvent);
		void Close();
		uint GetFileSize();
		void Flush();
		void Lock();
		void Unlock();
		HANDLE GetHandle();
		/* �ļ�ӳ�� */
		BOOL FileMapToBuffer(TCUQ(int) mapSize = 0);
		char* GetBuffer();

	private:
		HANDLE m_hFile;
		HANDLE m_hMap;
		char * m_buff;
	};

	/* �����ڴ� */
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
		/* ֻ��ɾ����Ŀ¼ */
		BOOL DeleteDir();

	private:
		CStr m_dir;
	};

	/******************************************************************
	*	���ܣ���src�ַ������ܣ����ɼ��ܺ���ַ���
	*	������
	*		src		��Ҫ���ܵ�Դ�ַ���
	*		srclen	Դ�ַ�������
	*		key		�����ַ���
	*	����ֵ����
	**/
	void StrToPassStr(char* src, TCUQ(int) srclen, TCPCH key);
	/******************************************************************
	*	���ܣ���src�ַ������ܣ����ɼ��ܺ���ַ���
	*	������
	*		src		���ܵ�Դ�ַ���
	*		srclen	Դ�ַ�������
	*		key		�����ַ���
	*	����ֵ����
	**/
	void PassStrToStr(char* src, TCUQ(int) srclen, TCPCH key);

}


#endif
