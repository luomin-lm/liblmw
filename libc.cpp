#include "libc.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

namespace lmw
{
	void GetErrorString(TC(int) errCode, TP(char) errStr)
	{
		switch (errCode)
		{
		case 0:
			strcpy(errStr, "没有错误");
			break;
		case 1:
			strcpy(errStr, "内存池创建错误：内存不足导致内存分配失败");
			break;
		case 2:
			strcpy(errStr, "内存池释放内存错误：未知的内存");
			break;
		case 3:
			strcpy(errStr, "日志文件打开错误：未知的错误");
			break;
		case 4:
			strcpy(errStr, "日志文件写入错误：文件句柄无效");
			break;
		case 5:
			strcpy(errStr, "内存创建失败：返回NULL");
			break;
		case 6:
			strcpy(errStr, "文件打开失败：返回NULL");
			break;
		default:
			break;
		}
	}

	/* 时间起点：1970-01-01 08:00:00 中国东八区区时*/
#define DEFAULT_YEAR	1970
#define DEFAULT_HOUR	8
	lcTime GetLocalTime()
	{
		lcTime ltret = { 0 };

		time_t t = time(NULL);
		unsigned short days = 365;
		unsigned short tyear = DEFAULT_YEAR;
		unsigned char isr = 1, i;
		int monsday[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		//秒
		ltret.m_sec = t % 60;
		t /= 60;
		//分
		ltret.m_min = t % 60;
		t /= 60;
		//时
		ltret.m_hour = t % 24 + DEFAULT_HOUR;
		ltret.m_hour %= 24;
		t /= 24;

		// 共已过去 t 天
		do
		{
			days = 365;
			if (tyear % 400 == 0)
			{
				days += 1;
				isr = 1;
			}
			else if (tyear % 100 == 0)
			{
				days += 0;
				isr = 0;
			}
			else if (tyear % 4 == 0)
			{
				days += 1;
				isr = 1;
			}
			else
			{
				isr = 0;
			}

			if (t < days)
			{
				break;
			}
			tyear += 1;
			t -= days;
		} while (1);
		ltret.m_year = tyear;

		i = 0;
		while (t > monsday[i])
		{
			if (i == 1){
				t -= isr;
			}
			t -= monsday[i];

			++i;
		}
		ltret.m_month = i + 1;
		ltret.m_day = (unsigned char)t + 1;

		return ltret;

	}

	int mp_init(TP(memPool) pmp, TCU(int) size)
	{
		pmp->pAddr = (char*)malloc(size);
		pmp->size = size;

		if (NULL == pmp->pAddr)
		{
			return 1;
		}

		memset(pmp->pAddr, 0, size);
		return 0;
	}

	void* mp_alloc(TP(memPool) pmp, TCU(int) size)
	{
		char *memp = pmp->pAddr;
		short *v = (short*)memp;
		int i = 0;

		do{
			v = (short*)(memp + i);
			if (*v < 0)
			{
				*v = -*v;
				if (*v == size + 2)
				{
					return memp + i + 2;
				}
			}
			i += *v;
			if (i + size + 2 > pmp->size)
			{
				return NULL;
			}
		} while (*v != 0);

		*v = 2 + size;
		return memp + i + 2;
	}

	int mp_free(TP(memPool) pmp, TP(void) p)
	{
		char* ptmp = (char*)p;
		char* memp = pmp->pAddr;

		if (ptmp < memp)
		{
			return 2;
		}
		else if (ptmp > memp + pmp->size)
		{
			return 2;
		}
		short *v = (short*)((char*)p - 2);
		*v = -*v;

		return 0;
	}

	void mp_close(TP(memPool) pmp)
	{
		if (NULL != pmp->pAddr)
		{
			free(pmp->pAddr);
		}
	}

	int log_open(TP(logFile) plf, TCP(char) filepath)
	{
		FILE* fp = fopen(filepath, "a+b");
		if (NULL == fp)
		{
			return 3;
		}

		plf->pFile = fp;
		return 0;
	}

	int log_printf(TP(logFile) plf, TCP(char) fmt, ...)
	{
		FILE* fp = (FILE*)plf->pFile;
		va_list arg;

		if (fp == NULL)
		{
			return 4;
		}
		va_start(arg, fmt);
		vfprintf(fp, fmt, arg);

		return 0;
	}

	void log_fflush(TP(logFile) plf)
	{
		FILE* fp = (FILE*)plf->pFile;
		fflush(fp);
	}

	void log_close(TP(logFile) plf)
	{
		FILE* fp = (FILE*)plf->pFile;
		fclose(fp);
		plf->pFile = NULL;
	}
}
