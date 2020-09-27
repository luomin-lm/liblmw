/**********************************************************************
*	文件功能：配置文件操作类
*	所有者@ ：罗敏
*	编写环境：Win7 + VS2013
*	编写时间：2020-09-24
*	修改时间：2020-09-24
**/
#ifndef _CCPP_INI_H_
#define _CCPP_INI_H_

#include "fd.h"
#define INI_FILE_MAX_SIZE	4096

namespace lmw
{
	class CLmwIni
	{
	public:
		CLmwIni();
		~CLmwIni();
		/**************************************
		*	功能：打开配置文件
		*		file	文件路径+名
		*		key		文件密码
		*	返回TRUE -> 成功
		**/
		BOOL Open(TCPCH file, TCPCH key = nullptr);
		/**************************************
		*	功能：设置配置项
		*		topic	主题
		*		name	项名
		*		value	项值
		*	无返回
		**/
		void SetItemText(TCPCH topic, TCPCH name, TCPCH value);
		/**************************************
		*	功能：获取配置项
		*		topic	主题
		*		name	项名
		*		value	项值(输出)
		*	返回TRUE -> 成功
		**/
		BOOL GetItemText(TCPCH topic, TCPCH name, char* value);
		/**************************************
		*	功能：保存到配置文件中
		*		key		文件密码
		*	无返回
		**/
		void Close(TCPCH key = nullptr);

	private:
		char m_buff[INI_FILE_MAX_SIZE]; // 内容
		int m_len; // 文件长度
		char m_filepath[260]; // 文件路径
	};
}

#endif