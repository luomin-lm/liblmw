#include "libcpp.h"
#include <stdio.h>
#include <stdarg.h>

namespace lmw
{
	/********************************************************
	*	成员函数功能：构造函数，初始化对象为nullptr
	*	参数：无
	*	返回：无
	*	时间：2020-08-15
	*/
	CCFile::CCFile()
	{
		m_pFile = nullptr;
		m_size = 0;
	}
	/********************************************************
	*	成员函数功能：析构函数，如果文件未关闭，自动关闭
	*	参数：无
	*	返回：无
	*	时间：2020-08-15
	*/
	CCFile::~CCFile()
	{
		if (m_pFile != nullptr)
		{
			close();
		}
	}
	/********************************************************
	*	成员函数功能：打开文件
	*	参数：
	*		file 文件路径
	*		mode 文件打开模式(r : 读，w : 写，b : 二进制)
	*	返回：无
	*	时间：2020-08-15
	*/
	uint CCFile::open(TCP(char) file, TCP(char) mode)
	{
		FILE * fp = fopen(file, mode);

		if (fp == NULL)
		{
			return 6;
		}

		m_pFile = fp;
		fseek(fp, 0, SEEK_END);
		m_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		return 0;
	}
	/********************************************************
	*	成员函数功能：关闭打开的文件路径
	*	参数：无
	*	返回：无
	*	时间：2020-08-15
	*/
	void CCFile::close()
	{
		fclose((FILE*)m_pFile);
		m_pFile = nullptr;
		m_size = 0;
	}
	/********************************************************
	*	成员函数功能：格式化输出字符串
	*	参数：fmt 格式化字符串
	*	返回：写入字符串个数，失败返回负数-1
	*	时间：2020-08-15
	*/
	int CCFile::printf(TCP(char) fmt, ...)
	{
		va_list arg;

		va_start(arg, fmt);
		return vfprintf((FILE*)m_pFile, fmt, arg);
	}
	/********************************************************
	*	成员函数功能：格式化输入字符串
	*	参数：fmt 格式化字符串
	*	返回：写入字符串个数，失败返回负数-1
	*	时间：2020-08-15
	*/
	int CCFile::scanf(TCP(char) fmt, ...)
	{
		va_list arg;

		va_start(arg, fmt);
		return vfscanf((FILE*)m_pFile, fmt, arg);
	}
	/********************************************************
	*	成员函数功能：读取数组(指针)
	*	参数：	buff  内存首地址
	*			nsize 每个对象内存大小
	*			count 对象数量
	*	返回：读取的对象数量
	*	时间：2020-08-15
	*/
	int CCFile::read(TP(void) buff, TCQ(int) nsize, TCQ(int) count)
	{
		return fread(buff, nsize, count, (FILE*)m_pFile);
	}
	/********************************************************
	*	成员函数功能：读取数组(指针)
	*	参数：	buff  内存首地址，内存不够会报错
	*	返回：无
	*	时间：2020-08-15
	*/
	void CCFile::readAll(TP(char) buff)
	{
		int nread;
		uint sum = 0;

		while (sum < m_size)
		{
			nread = fread(buff + sum, 1, m_size - sum, (FILE*)m_pFile);
			sum += nread;
		}
	}
	/********************************************************
	*	成员函数功能：读取数组(指针)
	*	参数：	buff  内存首地址
	*			nsize 每个对象内存大小
	*			count 对象数量
	*	返回：写入的对象数量
	*	时间：2020-08-15
	*/
	int CCFile::write(TCP(void) buff, TCQ(int) nsize, TCQ(int) count)
	{
		return fwrite(buff, nsize, count, (FILE*)m_pFile);
	}
	/********************************************************
	*	成员函数功能：设置文件指针
	*	参数：	offset 偏移
	*			sek 起点
	*	返回：写入的对象数量
	*	时间：2020-08-15
	*/
	void CCFile::seek(TCUQ(int) offset, TCQ(Seek) sek)
	{
		switch (sek)
		{
		case seek_current:
			fseek((FILE*)m_pFile, offset, SEEK_CUR);
			break;
		case seek_end:
			fseek((FILE*)m_pFile, offset, SEEK_END);
			break;
		case seek_start:
			fseek((FILE*)m_pFile, offset, SEEK_SET);
			break;
		default:
			break;
		}
	}
	/********************************************************
	*	成员函数功能：获取文件大小
	*	参数：无
	*	返回：文件大小
	*	时间：2020-08-15
	*/
	TU(int) CCFile::size()
	{
		return m_size;
	}
}
