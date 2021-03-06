/**********************************************************************
*	文件功能：LMW库的C语言代码头文件
*	所有者@ ：罗敏
*	编写环境：Windows7 + VS2013
*	编写时间：2020-08-12
*	修改时间：2020-08-12
*
*	内容零	：异常/错误处理
*	内容一	：获取本地时间
*	内容二	：内存池设计实现
*	内容三	：日志文件设计实现
**/
#ifndef _C_LIB_H_
#define _C_LIB_H_

#include "types.h"

namespace lmw
{
	/**********************************************************************
	*	函数功能：根据错误码，获取详细错误信息
	*	参数列表：
	*		参数errCode：错误码(输入)
	*		参数errStr ：错误字符串(输出)
	*	返 回 值：无
	*	修改时间：2020-08-12
	**/
	void GetErrorString(TC(int) errCode, TP(char) errStr);

	/* 定义时间数据类型 */
	struct LIBC_TIME
	{
		TU(short) m_year;
		TU(char) m_month;
		TU(char) m_day;
		TU(char) m_hour;
		TU(char) m_min;
		TU(char) m_sec;
	};
	typedef struct LIBC_TIME lcTime;
	/**********************************************************************
	*	函数功能：获取本地的当前时间
	*	参数列表：
	*		参数：无
	*	返 回 值：返回本地的当前时间结构体
	*	修改时间：2020-08-12
	**/
	lcTime GetLocalTime();

	/* 定义内存池数据类型 */
	struct _Memory_Pool_
	{
		char* pAddr;
		TU(int) size;
	};
	typedef struct _Memory_Pool_ memPool;
	/**********************************************************************
	*	函数功能：初始化内存池
	*	参数列表：
	*		参数pmp ：要初始化的内存池结构(输出)
	*		参数size：初始化内存池的大小(输入)
	*	返 回 值：
	*		0：初始化成功
	*	   !0：失败，使用GetErrorString函数获取详细信息
	*	修改时间：2020-08-12
	**/
	int mp_init(TP(memPool) pmp, TCU(int) size);
	/**********************************************************************
	*	函数功能：分配一段内存空间
	*	参数列表：
	*		参数pmp ：内存池结构指针(输入)
	*		参数size：要分配的内存的大小(输入)
	*	返 回 值：
	*		NULL：分配内存失败，内存池空间已满
	*		!0：内存分配成功
	*	修改时间：2020-08-12
	**/
	TP(void) mp_alloc(TP(memPool) pmp, TCU(int) size);
	/**********************************************************************
	*	函数功能：释放从内存池中分配的内存空间
	*	参数列表：
	*		参数pmp ：内存池结构指针(输入)
	*		参数p：要释放的内存块首地址(输入)
	*	返 回 值：
	*		0：分配释放成功
	*		!0：失败，未知的内存块
	*	修改时间：2020-08-12
	**/
	int mp_free(TP(memPool) pmp, TP(void) p);
	/**********************************************************************
	*	函数功能：释放从内存池的内存空间
	*	参数列表：
	*		参数pmp ：内存池结构指针(输入)
	*	返 回 值：无
	*	修改时间：2020-08-12
	**/
	void mp_close(TP(memPool) pmp);

	/* 定义日志文件类型 */
	struct _Log_File_
	{
		void* pFile; /* C语言文件句柄 */
	};
	typedef struct _Log_File_ logFile;
	/**********************************************************************
	*	函数功能：打开日志文件句柄
	*	参数列表：
	*		参数plf ：日志文件结构体指针
	*		参数filepath ：日志文件的文件路径
	*	返 回 值：
	*		0：文件打开成功
	*		!0：文件打开失败
	*	修改时间：2020-08-12
	**/
	int log_open(TP(logFile) plf, TCP(char) filepath);
	/**********************************************************************
	*	函数功能：向日志文件中写入数据(类似fprintf)
	*	参数列表：
	*		参数plf ：日志文件结构体指针
	*		参数fmt：格式化字符串
	*	返 回 值：
	*		0：文件写入成功
	*		!0：文件写入失败，未打开文件
	*	修改时间：2020-08-12
	**/
	int log_printf(TP(logFile) plf, TCP(char) fmt, ...);
	/**********************************************************************
	*	函数功能：将内存的数据缓冲强制写入文件中
	*	参数列表：
	*		参数plf ：日志文件结构体指针
	*	返 回 值：无
	*	修改时间：2020-08-12
	**/
	void log_fflush(TP(logFile) plf);
	/**********************************************************************
	*	函数功能：关闭日志文件句柄
	*	参数列表：
	*		参数plf ：日志文件结构体指针
	*	返 回 值：无
	*	修改时间：2020-08-12
	**/
	void log_close(TP(logFile) plf);
}

#endif

