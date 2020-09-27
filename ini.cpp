#include "ini.h"
#include <stdio.h>

namespace lmw
{
	CLmwIni::CLmwIni()
	{
		m_len = 0;
		memset(m_filepath, 0, 260);
	}
	CLmwIni::~CLmwIni()
	{
		Close();
	}
	/**************************************
	*	功能：打开配置文件
	*		file	文件路径+名
	*		key		文件密码
	*	返回TRUE -> 成功
	**/
	BOOL CLmwIni::Open(TCPCH file, TCPCH key)
	{
		lmw::CCFile cfp;
		if (0 == cfp.open(file))
		{
			int len = cfp.size() + 1;
			if (len > INI_FILE_MAX_SIZE)
			{
				return FALSE;
			}
			m_buff[len - 1] = 0;

			cfp.readAll(m_buff);
			cfp.close();

			/* 将加密的字符串解密 */
			if (key != nullptr)
			{
				lmw::PassStrToStr(m_buff, len - 1, key);
			}

			m_len = len - 1;
			strcpy(m_filepath, file);
			return TRUE;
		}
		return FALSE;
	}
	/**************************************
	*	功能：设置配置项
	*		topic	主题
	*		name	项名
	*		value	项值
	*	无返回
	**/
	void CLmwIni::SetItemText(TCPCH topic, TCPCH name, TCPCH value)
	{
		char* p1 = strstr(m_buff, topic);
		char* p2 = strstr(p1, "[");
		char val[256];
		lmw::CStr str;

		p1 = strstr(p1, name);
		if (p1 == NULL)
		{
			return;
		}
		else if (p2 == NULL)
		{
			//替换字符串
			str.Format("%s=%%s", name); // name=value
			sscanf(p1, str.c_str(), val);
			int dlen = strlen(value); // 目标字符串长度
			int len = strlen(val) - dlen; // 差值
			if (len > 0)
			{
				int i;
				p1 = p1 + strlen(name) + 1;
				for (i = 0; i < dlen; i++)
				{
					p1[i] = value[i];
				}
				p1 += dlen;
				for (i = 0; p1[i] != 0; i++)
				{
					p1[i] = p1[i + len];
				}
				p1[i] = 0;
			}
			else if (len == 0)
			{
				int i;
				p1 = p1 + strlen(name) + 1;
				for (i = 0; i < dlen; i++)
				{
					p1[i] = value[i];
				}
			}
			else
			{
				int i = m_len - len - 1;
				m_buff[i--] = 0;
				while (m_buff + i > p1 + 1 + strlen(name) + strlen(val))
				{
					m_buff[i] = m_buff[i + len];
					--i;
				}
				p1 = p1 + strlen(name) + 1;
				for (i = 0; i < dlen; i++)
				{
					p1[i] = value[i];
				}
			}

			m_len -= len;
			return;
		}
		else if (p1 > p2)
		{
			return;
		}

		//替换字符串
		str.Format("%s=%%s", name); // name=value
		sscanf(p1, str.c_str(), val);
		int dlen = strlen(value); // 目标字符串长度
		int len = strlen(val) - dlen; // 差值
		if (len > 0)
		{
			int i;
			p1 = p1 + strlen(name) + 1;
			for (i = 0; i < dlen; i++)
			{
				p1[i] = value[i];
			}
			p1 += dlen;
			for (i = 0; p1[i] != 0; i++)
			{
				p1[i] = p1[i + len];
			}
			p1[i] = 0;
		}
		else if (len == 0)
		{
			int i;
			p1 = p1 + strlen(name) + 1;
			for (i = 0; i < dlen; i++)
			{
				p1[i] = value[i];
			}
		}
		else
		{
			int i = m_len - len - 1;
			m_buff[i--] = 0;
			while (m_buff + i > p1 + 1 + strlen(name) + strlen(val))
			{
				m_buff[i] = m_buff[i + len];
				--i;
			}
			p1 = p1 + strlen(name) + 1;
			for (i = 0; i < dlen; i++)
			{
				p1[i] = value[i];
			}
		}
		m_len -= len;
	}
	/**************************************
	*	功能：获取配置项
	*		topic	主题
	*		name	项名
	*		value	项值(输出)
	*	返回TRUE -> 成功
	**/
	BOOL CLmwIni::GetItemText(TCPCH topic, TCPCH name, char* value)
	{
		if (m_len == 0)
		{
			return FALSE;
		}

		char* p1 = strstr(m_buff, topic); // 起点
		char* p2 = strstr(p1, "["); // 终点
		lmw::CStr str; // temp

		p1 = strstr(p1, name);
		if (p1 == NULL)
			return FALSE;
		else if (p2 == NULL)
		{
			str.Format("%s=%%s", name); // name=value
			sscanf(p1, str.c_str(), value);
		}
		else if (p1 > p2)
		{
			return FALSE;
		}
		else
		{
			str.Format("%s=%%s", name); // name=value
			sscanf(p1, str.c_str(), value);
		}
		return TRUE;
	}
	/**************************************
	*	功能：保存到配置文件中
	*		key		文件密码
	*	无返回
	**/
	void CLmwIni::Close(TCPCH key)
	{
		if (0 == m_len)
		{
			return;
		}
		if (key != nullptr)
		{
			/* 加密 */
			lmw::StrToPassStr(m_buff, m_len, key);
		}

		lmw::CCFile cfp;

		if (0 == cfp.open(m_filepath, "wb"))
		{
			cfp.write(m_buff, 1, m_len);
			cfp.close();
		}

		memset(m_filepath, 0, 260);
		m_len = 0;
	}
}

