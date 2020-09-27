/**********************************************************************
*	�ļ����ܣ������ļ�������
*	������@ ������
*	��д������Win7 + VS2013
*	��дʱ�䣺2020-09-24
*	�޸�ʱ�䣺2020-09-24
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
		*	���ܣ��������ļ�
		*		file	�ļ�·��+��
		*		key		�ļ�����
		*	����TRUE -> �ɹ�
		**/
		BOOL Open(TCPCH file, TCPCH key = nullptr);
		/**************************************
		*	���ܣ�����������
		*		topic	����
		*		name	����
		*		value	��ֵ
		*	�޷���
		**/
		void SetItemText(TCPCH topic, TCPCH name, TCPCH value);
		/**************************************
		*	���ܣ���ȡ������
		*		topic	����
		*		name	����
		*		value	��ֵ(���)
		*	����TRUE -> �ɹ�
		**/
		BOOL GetItemText(TCPCH topic, TCPCH name, char* value);
		/**************************************
		*	���ܣ����浽�����ļ���
		*		key		�ļ�����
		*	�޷���
		**/
		void Close(TCPCH key = nullptr);

	private:
		char m_buff[INI_FILE_MAX_SIZE]; // ����
		int m_len; // �ļ�����
		char m_filepath[260]; // �ļ�·��
	};
}

#endif