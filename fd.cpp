#include "fd.h"

namespace lmw
{
	/* 基于Win32 API */
	CFile::CFile()
	{
		m_hFile = NULL;
		m_buff = NULL;
		m_hMap = NULL;
	}
	CFile::~CFile()
	{
		Close();
	}
	BOOL CFile::Open(TCPCH filename, BOOL IsCreate, BOOL isEvent)
	{
		DWORD dwFlag = IsCreate == TRUE ? CREATE_ALWAYS : OPEN_EXISTING;
		// CREATE_ALWAYS	覆盖以前的文件
		// OPEN_EXISTING	打开文件，找不到文件，执行失败
		DWORD dwAttr = FILE_ATTRIBUTE_NORMAL;
		if (TRUE == isEvent)
		{
			dwAttr |= FILE_FLAG_OVERLAPPED;
		}

		m_hFile = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
			NULL, dwFlag, dwAttr, NULL);

		if (INVALID_HANDLE_VALUE == m_hFile)
		{
			m_hFile = NULL;
			return FALSE;
		}
		return TRUE;
	}
	uint CFile::Read(char* buff, TCUQ(int) bufflen)
	{
		DWORD len = 0;
		if (NULL != m_hFile)
		{
			ReadFile(m_hFile, buff, bufflen, &len, NULL);
		}
		return len;
	}
	uint CFile::Write(TCPCH buff, TCUQ(int) bufflen)
	{
		DWORD len = 0;
		if (NULL != m_hFile)
		{
			WriteFile(m_hFile, buff, bufflen, &len, NULL);
		}
		return len;
	}
	void CFile::Read(char* buff, TCUQ(int) bufflen, CEvent* pEvent)
	{
		OVERLAPPED over = { 0 };
		over.hEvent = pEvent->Event();
		DWORD plen;

		ReadFile(m_hFile, buff, bufflen, &plen, &over);
	}
	void CFile::Write(TCPCH buff, TCUQ(int) bufflen, CEvent* pEvent)
	{
		OVERLAPPED over = { 0 };
		over.hEvent = pEvent->Event();
		DWORD plen;

		WriteFile(m_hFile, buff, bufflen, &plen, &over);
	}
	void CFile::Close()
	{
		if (m_hMap != NULL)
		{
			UnmapViewOfFile(m_buff);
			CloseHandle(m_hMap);
			m_hMap = NULL;
			m_buff = NULL;
		}
		if (NULL != m_hFile)
		{
			CloseHandle(m_hFile);
			m_hFile = NULL;
		}
	}
	uint CFile::GetFileSize()
	{
		return ::GetFileSize(m_hFile, NULL);
	}
	void CFile::Flush()
	{
		if (NULL != m_hFile)
			FlushFileBuffers(m_hFile);
	}
	void CFile::Lock()
	{
		if (NULL != m_hFile)
			LockFile(m_hFile, 0, 0, GetFileSize(), 0);
	}
	void CFile::Unlock()
	{
		if (NULL != m_hFile)
			UnlockFile(m_hFile, 0, 0, GetFileSize(), 0);
	}
	HANDLE CFile::GetHandle()
	{
		return m_hFile;
	}
	BOOL CFile::FileMapToBuffer(TCUQ(int) mapSize)
	{
		if (NULL == m_hFile)
		{
			return FALSE;
		}
		if (NULL != m_hMap)
		{
			return FALSE;
		}

		m_hMap = CreateFileMapping(m_hFile, NULL,
			PAGE_READWRITE, 0, mapSize, NULL);

		if (NULL == m_hMap)
		{
			return FALSE;
		}
		m_buff = (char*)MapViewOfFile(m_hMap, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);
		return TRUE;
	}
	char* CFile::GetBuffer()
	{
		return m_buff;
	}

	CShareMemory::CShareMemory(const char* name, BOOL isWrite, const uint& size)
	{
		if (isWrite == TRUE)
		{
			m_hfileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, size, name);
		}
		else
		{
			m_hfileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, name);
		}
		if (NULL == m_hfileMap)
		{
			throw "共享内存(创建/打开)失败";
		}
		m_pBuffer = (char*)MapViewOfFile(m_hfileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	}
	CShareMemory::~CShareMemory()
	{
		UnmapViewOfFile(m_pBuffer);
		CloseHandle(m_hfileMap);
	}
	char * CShareMemory::GetBuffer()
	{
		return m_pBuffer;
	}

	CDir::CDir(TCPCH str)
	{
		m_dir = str;
	}
	BOOL CDir::HaveDir()
	{
		if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(m_dir.c_str()))
		{
			return FALSE;
		}
		return TRUE;
	}
	BOOL CDir::Create()
	{
		/* 创建目录 */
		return ::CreateDirectory(m_dir.c_str(), NULL);
	}
	void CDir::SetDir(TCPCH str)
	{
		m_dir = str;
	}
	CStr CDir::GetDir()
	{
		return m_dir;
	}
	BOOL CDir::DeleteDir()
	{
		return RemoveDirectory(m_dir.c_str());
	}

	/******************************************************************
	*	功能：将src字符串加密，生成加密后的字符串
	*	参数：
	*		src		将要加密的源字符串
	*		srclen	源字符串长度
	*		key		密码字符串
	*	返回值：无
	**/
	void StrToPassStr(char* src, TCUQ(int) srclen, TCPCH key)
	{
		size_t keylen = strlen(key);
		size_t i, j;

		for (i = 0; i < srclen; i += keylen)
		{
			for (j = 0; j < keylen; j++)
			{
				if (i + j == srclen)
				{
					break;
				}
				src[i + j] ^= key[j];
				src[i + j] += 0x23;
			}
		}
	}
	/******************************************************************
	*	功能：将src字符串加密，生成加密后的字符串
	*	参数：
	*		src		加密的源字符串
	*		srclen	源字符串长度
	*		key		密码字符串
	*	返回值：无
	**/
	void PassStrToStr(char* src, TCUQ(int) srclen, TCPCH key)
	{
		size_t keylen = strlen(key);
		size_t i, j;

		for (i = 0; i < srclen; i += keylen)
		{
			for (j = 0; j < keylen; j++)
			{
				if (i + j == srclen)
				{
					break;
				}
				src[i + j] -= 0x23;
				src[i + j] ^= key[j];
			}
		}
	}
}











