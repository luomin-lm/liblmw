#include "libcpp.h"
#include <stdio.h>
#include <stdarg.h>

namespace lmw
{
	/********************************************************
	*	��Ա�������ܣ����캯������ʼ������Ϊnullptr
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-15
	*/
	CCFile::CCFile()
	{
		m_pFile = nullptr;
		m_size = 0;
	}
	/********************************************************
	*	��Ա�������ܣ���������������ļ�δ�رգ��Զ��ر�
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-15
	*/
	CCFile::~CCFile()
	{
		if (m_pFile != nullptr)
		{
			close();
		}
	}
	/********************************************************
	*	��Ա�������ܣ����ļ�
	*	������
	*		file �ļ�·��
	*		mode �ļ���ģʽ(r : ����w : д��b : ������)
	*	���أ���
	*	ʱ�䣺2020-08-15
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
	*	��Ա�������ܣ��رմ򿪵��ļ�·��
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-15
	*/
	void CCFile::close()
	{
		fclose((FILE*)m_pFile);
		m_pFile = nullptr;
		m_size = 0;
	}
	/********************************************************
	*	��Ա�������ܣ���ʽ������ַ���
	*	������fmt ��ʽ���ַ���
	*	���أ�д���ַ���������ʧ�ܷ��ظ���-1
	*	ʱ�䣺2020-08-15
	*/
	int CCFile::printf(TCP(char) fmt, ...)
	{
		va_list arg;

		va_start(arg, fmt);
		return vfprintf((FILE*)m_pFile, fmt, arg);
	}
	/********************************************************
	*	��Ա�������ܣ���ʽ�������ַ���
	*	������fmt ��ʽ���ַ���
	*	���أ�д���ַ���������ʧ�ܷ��ظ���-1
	*	ʱ�䣺2020-08-15
	*/
	int CCFile::scanf(TCP(char) fmt, ...)
	{
		va_list arg;

		va_start(arg, fmt);
		return vfscanf((FILE*)m_pFile, fmt, arg);
	}
	/********************************************************
	*	��Ա�������ܣ���ȡ����(ָ��)
	*	������	buff  �ڴ��׵�ַ
	*			nsize ÿ�������ڴ��С
	*			count ��������
	*	���أ���ȡ�Ķ�������
	*	ʱ�䣺2020-08-15
	*/
	int CCFile::read(TP(void) buff, TCQ(int) nsize, TCQ(int) count)
	{
		return fread(buff, nsize, count, (FILE*)m_pFile);
	}
	/********************************************************
	*	��Ա�������ܣ���ȡ����(ָ��)
	*	������	buff  �ڴ��׵�ַ���ڴ治���ᱨ��
	*	���أ���
	*	ʱ�䣺2020-08-15
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
	*	��Ա�������ܣ���ȡ����(ָ��)
	*	������	buff  �ڴ��׵�ַ
	*			nsize ÿ�������ڴ��С
	*			count ��������
	*	���أ�д��Ķ�������
	*	ʱ�䣺2020-08-15
	*/
	int CCFile::write(TCP(void) buff, TCQ(int) nsize, TCQ(int) count)
	{
		return fwrite(buff, nsize, count, (FILE*)m_pFile);
	}
	/********************************************************
	*	��Ա�������ܣ������ļ�ָ��
	*	������	offset ƫ��
	*			sek ���
	*	���أ�д��Ķ�������
	*	ʱ�䣺2020-08-15
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
	*	��Ա�������ܣ���ȡ�ļ���С
	*	��������
	*	���أ��ļ���С
	*	ʱ�䣺2020-08-15
	*/
	TU(int) CCFile::size()
	{
		return m_size;
	}
}
