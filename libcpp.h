/**********************************************************************
*	文件功能：LMW库的C++代码头文件
*	所有者@ ：罗敏
*	编写环境：Windows7 + VS2013
*	编写时间：2020-08-12
*	修改时间：2020-08-12
*
*	内容0001：CStr字符串类
*	内容0002：CCFile基于C语言Stdio的文件类
*	内容0003：CMemoryPool基于C的内存池类
**/
#ifndef _CPP_LIB_H_
#define _CPP_LIB_H_

#include <Windows.h>

namespace lmw
{
#include "types.h"

	/********************************************************
	*	类名：CStr
	*	功能：字符串类，基于string.h
	*	时间：2020-08-13
	*/
	class CStr
	{
	public:
		/********************************************************
		*	成员函数功能：构造函数，初始化对象
		*	参数：str 初始化字符串
		*	返回：无
		*	时间：2020-08-13
		*/
		CStr(TCP(char) str = nullptr);
		/********************************************************
		*	成员函数功能：拷贝构造函数，初始化对象
		*	参数：obj 拷贝对象
		*	返回：无
		*	时间：2020-08-13
		*/
		CStr(TCQ(CStr) obj);
		/********************************************************
		*	静态成员变量：用于设置类的Format函数的最大内存
		*/
		static TU(int) m_fmtmaxsize;

	public:
		/********************************************************
		*	成员函数功能：重载=操作符，赋值
		*	参数：obj 拷贝对象
		*	返回：obj 拷贝对象的常引用
		*	时间：2020-08-13
		*/
		TCQ(CStr) operator=(TCQ(CStr) obj);
		/********************************************************
		*	成员函数功能：重载=操作符，赋值
		*	参数：str 拷贝字符串
		*	返回：*this对象的常引用
		*	时间：2020-08-13
		*/
		TCQ(CStr) operator=(TCP(char) str);
		/********************************************************
		*	成员函数功能：返回字符串中的字符个数
		*	参数：无
		*	返回：字符串中的字符个数
		*	时间：2020-08-13
		*/
		TU(int) size();
		/********************************************************
		*	成员函数功能：返回字符串
		*	参数：无
		*	返回：内存buff的常首地址
		*	时间：2020-08-13
		*/
		TCP(char) c_str();
		/********************************************************
		*	成员函数功能：返回字符串
		*	参数：len : 内存的新长度
		*	返回：内存buff的首地址
		*	时间：2020-08-13
		*/
		TP(char) get_buffer_set_length(TCQ(int) len);
		/********************************************************
		*	成员函数功能：重载+
		*	参数：obj 另一个字符串对象
		*	返回：两个字符串连接后的字符串对象
		*	时间：2020-08-13
		*/
		CStr operator+(TCQ(CStr) obj);
		/********************************************************
		*	成员函数功能：重载+=
		*	参数：obj 另一个字符串对象
		*	返回：两个字符串连接后的字符串对象
		*	时间：2020-08-13
		*/
		CStr operator+=(TCQ(CStr) obj);
		/********************************************************
		*	成员函数功能：重载==
		*	参数：obj 另一个字符串对象
		*	返回：是否相同
		*	时间：2020-09-01
		*/
		BOOL operator==(TCQ(CStr) obj);
		/********************************************************
		*	成员函数功能：重载!=
		*	参数：obj 另一个字符串对象
		*	返回：是否不相同
		*	时间：2020-09-01
		*/
		BOOL operator!=(TCQ(CStr) obj);
		/********************************************************
		*	成员函数功能：格式化字符串,printf类似
		*	参数：fmt 格式化字符串
		*	参数：... 其他参数
		*	返回：无
		*	时间：2020-08-13
		*/
		void Format(TCP(char) fmt, ...);
		/********************************************************
		*	成员函数功能：替换字符串
		*	参数：
		*		src 字符串中的原有子字符串
		*		dst 替换后的字符串
		*	返回：
		*		1 -> 替换成功，替换了其中一个
		*		0 -> 替换失败，没有可以替换的了
		*	时间：2020-08-28
		*/
		uint Replace(const CStr& src, const CStr& dst);
		/********************************************************
		*	成员函数功能：转换为double数字
		*	参数：转换后的数
		*	返回：无
		*	时间：2020-08-28
		*/
		static double ToDouble(const char* str);
		/********************************************************
		*	功能：编码类型转换
		*	时间：2020-08-28
		*/
		CStr AscllToUtf8(const char* src, const uint& len);
		CStr Utf8ToAscll(const char* src, const uint& len);

	private:
		char* m_buff;
		TU(int) m_len;
	};

	/********************************************************
	*	类名：CCFile
	*	功能：基于stdio.h的File类
	*	时间：2020-08-15
	*/
	class CCFile
	{
	public:
		/********************************************************
		*	成员函数功能：构造函数，初始化对象为nullptr
		*	参数：无
		*	返回：无
		*	时间：2020-08-15
		*/
		CCFile();
		/********************************************************
		*	成员函数功能：析构函数，如果文件未关闭，自动关闭
		*	参数：无
		*	返回：无
		*	时间：2020-08-15
		*/
		~CCFile();
		/********************************************************
		*	Seek：文件指针位置设置指针枚举
		*		seek_start		: 文件起点
		*		seek_current	: 文件当前位置
		*		seek_end		: 文件末尾位置
		*/
		enum Seek{ seek_start, seek_current, seek_end };

	public:
		/********************************************************
		*	成员函数功能：打开文件
		*	参数：
		*		file 文件路径
		*		mode 文件打开模式(r : 读，w : 写，b : 二进制)
		*	返回：无
		*	时间：2020-08-15
		*/
		uint open(TCP(char) file, TCP(char) mode = "rb+");
		/********************************************************
		*	成员函数功能：关闭打开的文件路径
		*	参数：无
		*	返回：无
		*	时间：2020-08-15
		*/
		void close();
		/********************************************************
		*	成员函数功能：格式化输出字符串
		*	参数：fmt 格式化字符串
		*	返回：写入字符串个数，失败返回负数-1
		*	时间：2020-08-15
		*/
		int printf(TCP(char) fmt, ...);
		/********************************************************
		*	成员函数功能：格式化输入字符串
		*	参数：fmt 格式化字符串
		*	返回：写入字符串个数，失败返回负数-1
		*	时间：2020-08-15
		*/
		int scanf(TCP(char) fmt, ...);
		/********************************************************
		*	成员函数功能：读取数组(指针)
		*	参数：	buff  内存首地址
		*			nsize 每个对象内存大小
		*			count 对象数量
		*	返回：读取的对象数量
		*	时间：2020-08-15
		*/
		int read(TP(void) buff, TCQ(int) nsize, TCQ(int) count);
		/********************************************************
		*	成员函数功能：读取数组(指针),读取文件中的所有内容
		*	参数：	buff  内存首地址，内存不够会报错
		*	返回：无
		*	时间：2020-08-15
		*/
		void readAll(TP(char) buff);
		/********************************************************
		*	成员函数功能：读取数组(指针)
		*	参数：	buff  内存首地址
		*			nsize 每个对象内存大小
		*			count 对象数量
		*	返回：写入的对象数量
		*	时间：2020-08-15
		*/
		int write(TCP(void) buff, TCQ(int) nsize, TCQ(int) count);
		/********************************************************
		*	成员函数功能：设置文件指针
		*	参数：	offset 偏移
		*			sek 起点
		*	返回：写入的对象数量
		*	时间：2020-08-15
		*/
		void seek(TCUQ(int) offset, TCQ(Seek) sek = seek_current);
		/********************************************************
		*	成员函数功能：获取文件大小
		*	参数：无
		*	返回：文件大小
		*	时间：2020-08-15
		*/
		TU(int) size();

	private:
		void * m_pFile;
		TU(int) m_size;
	};

	/********************************************************
	*	类名：CMemoryPool
	*	功能：基于stdlib.h的内存池类
	*	时间：2020-08-16
	*	注释：	分配的一个内存块<内存大小(2 byte), 实际返回的内存(nsize byte)>
				释放时，仅是将(内存大小(2 byte)的值取反)(10 - -10)
	*/
	class CMemoryPool
	{
	public:
		/********************************************************
		*	成员函数功能：构造函数，初始化对象
		*	参数：size 内存池大小,默认为 64 MB
		*	返回：无
		*	时间：2020-08-16
		*/
		CMemoryPool(TCUQ(int) size = 0x06400000);
		/********************************************************
		*	成员函数功能：析构函数，释放内存
		*	参数：无
		*	返回：无
		*	时间：2020-08-16
		*/
		~CMemoryPool();
		/********************************************************
		*	成员函数功能：分配一块nsize大小的内存，虚函数
		*	参数：nsize 要分配内存的大小
		*	返回：分配的内存首地址
		*	时间：2020-08-16
		*/
		virtual TP(void) alloc(TCUQ(int) nsize);
		/********************************************************
		*	成员函数功能：释放一块nsize大小的内存，虚函数
		*	参数：ptr 要释放内存的大小
		*	返回：无
		*	时间：2020-08-16
		*/
		virtual void free(TP(void) ptr);

	private:
		TP(char) m_p; /* 内存首地址 */
		TU(int) m_size; /* 内存大小 */
	};
}

/********************************************************
*	CStr类的静态成员变量：用于设置类的Format函数的最大内存
*/
#define CSTR_FORMAT_MAX_SIZE	lmw::CStr::m_fmtmaxsize
/********************************************************
*	简化声明内存池类
*/
typedef lmw::CMemoryPool CMPOOL;

#endif
