/**********************************************************************
*	�ļ����ܣ����ݽṹ���������
*	������@ ������
*	��д������Win7 + VS2013
*	��дʱ�䣺2020-08-13
*	�޸�ʱ�䣺2020-08-13
**/
#ifndef _CPP_DATA_STRUCT_H_
#define _CPP_DATA_STRUCT_H_

namespace lmw
{
#include "types.h"
	/********************************************************
	*	������DIter
	*	���ܣ���������Vector�е�һ��
	*	ʱ�䣺2020-08-13
	*/
	template<typename T>
	class VIter
	{
	public:
		/********************************************************
		*	��Ա�������ܣ����캯������ʼ������
		*	������p vector��ĳ������ĵ�ַ
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		VIter(T* p = nullptr)
		{
			m_p = p;
		}
		/********************************************************
		*	��Ա�������ܣ�����*������
		*	��������
		*	���أ��������е�����
		*	ʱ�䣺2020-08-13
		*/
		T& operator*()
		{
			return *m_p;
		}
		/********************************************************
		*	��Ա�������ܣ�����ǰ��++������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void operator ++()
		{
			m_p += 1;
		}
		/********************************************************
		*	��Ա�������ܣ����غ���++������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void operator ++(int)
		{
			m_p += 1;
		}
		/********************************************************
		*	��Ա�������ܣ�����ǰ��!=������
		*	������obj,�ȽϵĶ���
		*	���أ��Ƿ���ͬһ������
		*	ʱ�䣺2020-08-13
		*/
		int operator !=(const VIter<T>& obj)
		{
			return m_p != obj.m_p;
		}
		/********************************************************
		*	��Ա�������ܣ���ȡ�����
		*	��������
		*	���أ�����ڶ���ָ��
		*	ʱ�䣺2020-08-13
		*/
		T* data()
		{
			return m_p;
		}

	private:
		T* m_p;
	};
	/********************************************************
	*	������CVector
	*	���ܣ��������ɱ�����
	*	ʱ�䣺2020-08-13
	*/
	template<typename T>
	class CVector
	{
	public:
		/********************************************************
		*	��Ա�������ܣ����캯������ʼ������
		*	������initnum ��ʼ����С
		*	������addnum  �ڴ治������ӵĴ�С
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		CVector(TCUQ(int) initnum = 10, TCUQ(int) addnum = 10)
		{
			m_pT = nullptr;		// ����ָ��
			m_anums = addnum;	// �ڴ�ľ�����������
			m_index = 0;		// ָʾ��ǰ�洢������

			if (initnum == 0 && addnum == 0){
				throw "������ʼ��ʧ��";
			}
			else
			{
				/* �洢���� */
				m_maxs = initnum == 0 ? addnum : initnum;
			}

			memalloc();
		}
		/********************************************************
		*	��Ա�������ܣ��������캯������ʼ������
		*	������obj �����Ķ���
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		CVector(const CVector<T>& obj)
		{
			m_pT = nullptr;			// ����ָ��
			m_anums = obj.m_anums;	// �ڴ�ľ�����������
			m_index = obj.m_index;	// ָʾ��ǰ�洢������
			m_maxs = obj.m_maxs;	/* �洢���� */

			/* �ڴ���� */
			m_pT = new T[m_maxs];
			/* ���ݴ洢 */
			for (size_t i = 0; i < m_index; i++)
			{
				m_pT[i] = obj.m_pT[i];
			}
		}
		/********************************************************
		*	��Ա�������ܣ������������ͷ��ڴ�
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		~CVector()
		{
			delete[] m_pT;
		}
		/********************************************************
		*	��Ա�������ܣ��ڴ�ռ�ķ���+�޸�
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void memalloc()
		{
			/* �����ڴ� */
			T* pTmp = new T[m_maxs];

			if (nullptr == m_pT)
			{
				m_pT = pTmp;
				return;
			}

			for (size_t i = 0; i < m_index; i++)
			{
				pTmp[i] = m_pT[i];
			}
			/* �ͷ���ǰ���ڴ� */
			delete[] m_pT;
			/* �ڴ��ַ�л� */
			m_pT = pTmp;
		}
		/********************************************************
		*	��Ա�������ܣ���β�����һ������
		*	������t Ҫ��ӵ�����
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void push_back(const T& t)
		{
			if (m_index == m_maxs)
			{
				m_maxs += m_anums;
				memalloc();
			}
			m_pT[m_index++] = t;
		}
		/********************************************************
		*	��Ա�������ܣ���β��ɾ��һ������
		*	��������
		*	���أ�����ɾ����ֵ,û�������򷵻�0
		*	ʱ�䣺2020-08-13
		*/
		T pop_back()
		{
			if (0 != m_index)
				return m_pT[--m_index];
			return 0;
		}
		/********************************************************
		*	��Ա�������ܣ�����һ������
		*	������t  ���������
		*		index λ��
		*	���أ���
		*	ʱ�䣺2020-08-28
		*/
		void Insert(const T& t, const uint& index)
		{
			if (index > m_index)
			{
				return;
			}
			if (m_index == m_maxs)
			{
				m_maxs += m_anums;
				memalloc();
			}
			uint i = m_index;
			while (i > index)
			{
				m_pT[i] = m_pT[i - 1];
				--i;
			}
			m_pT[i] = t;
			m_index += 1;
		}
		/********************************************************
		*	��Ա�������ܣ�ɾ��ָ��λ�õ�ֵ
		*	������index���׵�ַƫ��
		*	���أ�����ɾ��������
		*	ʱ�䣺2020-08-28
		*/
		T Delete(const uint& index)
		{
			if (index >= m_index)
			{
				return 0;
			}
			T t = m_pT[index];
			uint i = index;
			while (i < m_index)
			{
				m_pT[i] = m_pT[i + 1];
				++i;
			}

			m_index -= 1;
			return t;
		}
		/********************************************************
		*	��Ա�������ܣ�����[]��������ֱ�ӷ����ڲ�����
		*	������index���׵�ַƫ��
		*	���أ������ڲ����ݵ�����
		*	ʱ�䣺2020-08-13
		*/
		T& operator[](size_t index)
		{
			return m_pT[index];
		}
		/********************************************************
		*	��Ա�������ܣ��������Ѵ�ŵ��������
		*	��������
		*	���أ�m_index����ŵ��������޷�����
		*	ʱ�䣺2020-08-13
		*/
		size_t size()
		{
			return m_index;
		}
		/********************************************************
		*	��Ա�������ܣ�����=����������ֵ��������
		*	��������ֵ����
		*	���أ����ز����ĳ�������
		*	ʱ�䣺2020-08-13
		*/
		const CVector<T>& operator=(const CVector<T>& obj)
		{
			m_pT = nullptr;			// ����ָ��
			m_anums = obj.m_anums;	// �ڴ�ľ�����������
			m_index = obj.m_index;	// ָʾ��ǰ�洢������
			m_maxs = obj.m_maxs;	/* �洢���� */

			if (m_pT != nullptr)
			{
				delete[] m_pT;
			}

			/* �ڴ���� */
			m_pT = new T[m_maxs];
			/* ���ݴ洢 */
			for (size_t i = 0; i < m_index; i++)
			{
				m_pT[i] = obj.m_pT[i];
			}
		}

	public:
		typedef VIter<T> iterator;
		/********************************************************
		*	��Ա�������ܣ���ȡ���������
		*	��������
		*	���أ����ص��������
		*	ʱ�䣺2020-08-13
		*/
		iterator begin()
		{
			return m_pT;
		}
		/********************************************************
		*	��Ա�������ܣ���ȡ�������յ�
		*	��������
		*	���أ����ص������յ�
		*	ʱ�䣺2020-08-13
		*/
		iterator end()
		{
			return m_pT + m_index;
		}
		/********************************************************
		*	��Ա�������ܣ�ɾ����������ָ������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void erase(iterator& it)
		{
			T* p = m_pT + m_index;
			T* p1 = it.data();

			while (p1 < p)
			{
				p1[0] = p1[1];
				p1++;
			}

			m_index -= 1;
		}
		T* data()
		{
			return m_pT;
		}

	private:
		T* m_pT;		// ����ָ��
		size_t m_maxs;	// ��ǰ�洢����
		size_t m_anums;	// �ڴ�ľ�����������
		size_t m_index;	// ָʾ��ǰ�洢������
	};
	/********************************************************
	*	������data_struct_dlist
	*	���ܣ����������������һ���ڣ�ģ����
	*	ʱ�䣺2020-08-13
	*/
	template<typename T>
	struct data_struct_dlist
	{
		data_struct_dlist<T>* next;
		T data;
	};
	/********************************************************
	*	������DIter
	*	���ܣ������������������һ����
	*	ʱ�䣺2020-08-13
	*/
	template<typename T>
	class DIter
	{
	public:
		/********************************************************
		*	��Ա�������ܣ����캯������ʼ������
		*	������pdsd ���������һ����ָ��ṹ��
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		DIter(data_struct_dlist<T>* pdsd = nullptr)
		{
			m_pdsd = pdsd;
		}
		/********************************************************
		*	��Ա�������ܣ�����*������
		*	��������
		*	���أ��������е�����
		*	ʱ�䣺2020-08-13
		*/
		T& operator*()
		{
			return m_pdsd->data;
		}
		/********************************************************
		*	��Ա�������ܣ�����ǰ��++������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void operator ++()
		{
			if (nullptr != m_pdsd)
			{
				m_pdsd = m_pdsd->next;
			}
		}
		/********************************************************
		*	��Ա�������ܣ����غ���++������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void operator ++(int)
		{
			if (nullptr != m_pdsd)
			{
				m_pdsd = m_pdsd->next;
			}
		}
		/********************************************************
		*	��Ա�������ܣ�����ǰ��!=������
		*	������obj,�ȽϵĶ���
		*	���أ��Ƿ���ͬһ������
		*	ʱ�䣺2020-08-13
		*/
		int operator !=(const DIter<T>& obj)
		{
			return m_pdsd != obj.m_pdsd;
		}
		/********************************************************
		*	��Ա�������ܣ���ȡ�����
		*	��������
		*	���أ�����ڶ���ָ��
		*	ʱ�䣺2020-08-13
		*/
		const data_struct_dlist<T>* data()
		{
			return m_pdsd;
		}

	private:
		data_struct_dlist<T>* m_pdsd;
	};
	/********************************************************
	*	������data_struct_slist
	*	���ܣ�������˫�������һ���ڣ�ģ����
	*	ʱ�䣺2020-08-13
	*/
	template<typename T>
	struct data_struct_slist
	{
		data_struct_slist<T>* last;
		data_struct_slist<T>* next; 
		T data;
	};
	/********************************************************
	*	������SIter
	*	���ܣ���������˫�������һ����
	*	ʱ�䣺2020-08-13
	*/
	template<typename T>
	class SIter
	{
	public:
		/********************************************************
		*	��Ա�������ܣ����캯������ʼ������
		*	������pdsd ˫�������һ����ָ��ṹ��
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		SIter(data_struct_slist<T>* pdsd = nullptr)
		{
			m_pdsd = pdsd;
		}
		/********************************************************
		*	��Ա�������ܣ�����*������
		*	��������
		*	���أ��������е�����
		*	ʱ�䣺2020-08-13
		*/
		T& operator*()
		{
			return m_pdsd->data;
		}
		/********************************************************
		*	��Ա�������ܣ�����ǰ��++������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void operator ++()
		{
			if (nullptr != m_pdsd)
			{
				m_pdsd = m_pdsd->next;
			}
		}
		/********************************************************
		*	��Ա�������ܣ�����ǰ��--������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void operator --()
		{
			if (nullptr != m_pdsd)
			{
				m_pdsd = m_pdsd->last;
			}
		}
		/********************************************************
		*	��Ա�������ܣ����غ���++������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void operator ++(int)
		{
			if (nullptr != m_pdsd)
			{
				m_pdsd = m_pdsd->next;
			}
		}
		/********************************************************
		*	��Ա�������ܣ����غ���--������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void operator --(int)
		{
			if (nullptr != m_pdsd)
			{
				m_pdsd = m_pdsd->last;
			}
		}
		/********************************************************
		*	��Ա�������ܣ�����ǰ��!=������
		*	������obj,�ȽϵĶ���
		*	���أ��Ƿ���ͬһ������
		*	ʱ�䣺2020-08-13
		*/
		int operator !=(const SIter<T>& obj)
		{
			return m_pdsd != obj.m_pdsd;
		}
		/********************************************************
		*	��Ա�������ܣ���ȡ�����
		*	��������
		*	���أ�����ڶ���ָ��
		*	ʱ�䣺2020-08-13
		*/
		const data_struct_slist<T>* data()
		{
			return m_pdsd;
		}

	private:
		data_struct_slist<T>* m_pdsd;
	};
	/********************************************************
	*	������CdList
	*	���ܣ���������������
	*	ʱ�䣺2020-08-13
	*/
	template<typename T>
	class CdList
	{
	public:
		/********************************************************
		*	��Ա�������ܣ����캯������ʼ������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		CdList()
		{
			m_pdsd = new data_struct_dlist<T>;
			m_pdsd->next = nullptr;
		}
		/********************************************************
		*	��Ա�������ܣ��������캯������ʼ������
		*	������list ��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		CdList(const CdList& list)
		{
			m_pdsd = new data_struct_dlist<T>;
			m_pdsd->next = nullptr;

			iterator it = list.begin();
			iterator end = list.end();
			while (it != end)
			{
				push_back(*it);
				++it;
			}
		}
		/********************************************************
		*	��Ա�������ܣ������������ͷŶ���
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		~CdList()
		{
			clear();
			delete m_pdsd;
		}

	public:
		/********************************************************
		*	��Ա�������ܣ��������,������β��
		*	������t ��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void push_back(const T& t)
		{
			/* ��ʼ���µĽڵ� */
			data_struct_dlist<T>* pdsd = new data_struct_dlist<T>;
			pdsd->data = t;
			pdsd->next = nullptr;

			/* �ҵ����һ���ڵ� */
			data_struct_dlist<T>* p = m_pdsd;
			while (nullptr != p->next)
			{
				p = p->next;
			}
			/* ������ */
			p->next = pdsd;
		}
		/********************************************************
		*	��Ա�������ܣ��������,�������ײ�
		*	������t ��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void push_front(const T& t)
		{
			/* ��ʼ���µĽڵ� */
			data_struct_dlist<T>* pdsd = new data_struct_dlist<T>;
			pdsd->data = t;
			pdsd->next = nullptr;

			/* ������ */
			pdsd->next = m_pdsd->next;
			m_pdsd->next = pdsd;
		}
		/********************************************************
		*	��Ա�������ܣ�ɾ������,������β��
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		T pop_back()
		{
			data_struct_dlist<T>* pdsd = m_pdsd;

			/* ������ɾ��ʧ�� */
			if (nullptr == m_pdsd->next)
			{
				return 0;
			}
			/* �ҵ������ڶ��� */
			while (nullptr != pdsd->next->next)
			{
				pdsd = pdsd->next;
			}
			/* ����ָ�룬�Ͽ����� */
			data_struct_dlist<T>* p = pdsd->next;
			pdsd->next = nullptr;
			/* �ͷ��ڴ� */
			T t = p->data;
			delete p;
			return t;
		}
		/********************************************************
		*	��Ա�������ܣ�ɾ������,�������ײ�
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		T pop_front()
		{
			data_struct_dlist<T>* pdsd = m_pdsd;

			/* ������ɾ��ʧ�� */
			if (nullptr == m_pdsd->next)
			{
				return 0;
			}
			/* �Ͽ����� */
			data_struct_dlist<T>* p = m_pdsd->next;
			m_pdsd->next = p->next;
			/* �������� */
			T t = p->data;
			/* �ͷ��ڴ� */
			delete p;

			return t;
		}
		/********************************************************
		*	��Ա�������ܣ�����=������
		*	������list ���ݼ���
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void operator=(const CdList& list)
		{
			/* ������ǰ�� */
			clear();
			/* ����list�е� */
			iterator it = list.begin();
			iterator end = list.end();
			while (it != end)
			{
				push_back(*it);
				++it;
			}
		}
		/********************************************************
		*	��Ա�������ܣ��������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void clear()
		{
			while (m_pdsd->next != nullptr)
			{
				pop_front();
			}
		}

	public:
		typedef DIter<T> iterator;
		/********************************************************
		*	��Ա�������ܣ���ȡָ�������ײ��ĵ�����
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		iterator begin()
		{
			return m_pdsd->next;
		}
		/********************************************************
		*	��Ա�������ܣ���ȡָ������β���ĵ�����
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		iterator end()
		{
			return nullptr;
		}
		/********************************************************
		*	��Ա�������ܣ�ɾ����������ָ��λ��
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		T erase(iterator& it)
		{
			data_struct_dlist<T> *p1 = m_pdsd;
			data_struct_dlist<T> *p2 = m_pdsd->next;

			if (nullptr == it.data())
			{
				return 0;
			}

			while (p2 != nullptr && it.data() != p2)
			{
				p1 = p1->next;
				p2 = p2->next;
			}
			T t = p2->data;

			p1->next = p2->next;
			delete p2;
			return t;
		}

	private:
		data_struct_dlist<T> *m_pdsd;
	};
	/*** Ĭ�ϵ�List�ǵ������� ***/
#define		List	CdList
	/********************************************************
	*	������CxList
	*	���ܣ�����������ѭ������
	*	ʱ�䣺2020-08-13
	*/
	template<typename T>
	class CxList
	{
	public:
		/********************************************************
		*	��Ա�������ܣ����캯������ʼ������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		CxList()
		{
			m_pdsd = new data_struct_dlist<T>;
			m_pdsd->next = m_pdsd;
		}
		/********************************************************
		*	��Ա�������ܣ��������캯������ʼ������
		*	������list ��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		CxList(const CxList& list)
		{
			m_pdsd = new data_struct_dlist<T>;
			m_pdsd->next = m_pdsd;

			iterator it = list.begin();
			iterator end = list.end();
			while (it != end)
			{
				push_back(*it);
				++it;
			}
		}
		/********************************************************
		*	��Ա�������ܣ������������ͷŶ���
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		~CxList()
		{
			clear();
			delete m_pdsd;
		}

	public:
		/********************************************************
		*	��Ա�������ܣ��������,������β��
		*	������t ��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void push_back(const T& t)
		{
			/* ��ʼ���µĽڵ� */
			data_struct_dlist<T>* pdsd = new data_struct_dlist<T>;
			pdsd->data = t;
			pdsd->next = m_pdsd;

			/* �ҵ����һ���ڵ� */
			data_struct_dlist<T>* p = m_pdsd;
			while (m_pdsd != p->next)
			{
				p = p->next;
			}
			/* ������ */
			p->next = pdsd;
		}
		/********************************************************
		*	��Ա�������ܣ��������,�������ײ�
		*	������t ��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void push_front(const T& t)
		{
			/* ��ʼ���µĽڵ� */
			data_struct_dlist<T>* pdsd = new data_struct_dlist<T>;
			pdsd->data = t;
			pdsd->next = nullptr;

			/* ������ */
			pdsd->next = m_pdsd->next;
			m_pdsd->next = pdsd;
		}
		/********************************************************
		*	��Ա�������ܣ�ɾ������,������β��
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		T pop_back()
		{
			data_struct_dlist<T>* pdsd = m_pdsd;

			/* ������ɾ��ʧ�� */
			if (m_pdsd == m_pdsd->next)
			{
				return 0;
			}
			/* �ҵ������ڶ��� */
			while (m_pdsd != pdsd->next->next)
			{
				pdsd = pdsd->next;
			}
			/* ����ָ�룬�Ͽ����� */
			data_struct_dlist<T>* p = pdsd->next;
			pdsd->next = m_pdsd;
			/* �ͷ��ڴ� */
			T t = p->data;
			delete p;
			return t;
		}
		/********************************************************
		*	��Ա�������ܣ�ɾ������,�������ײ�
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		T pop_front()
		{
			data_struct_dlist<T>* pdsd = m_pdsd;

			/* ������ɾ��ʧ�� */
			if (m_pdsd == m_pdsd->next)
			{
				return 0;
			}
			/* �Ͽ����� */
			data_struct_dlist<T>* p = m_pdsd->next;
			m_pdsd->next = p->next;
			/* �������� */
			T t = p->data;
			/* �ͷ��ڴ� */
			delete p;

			return t;
		}
		/********************************************************
		*	��Ա�������ܣ�����=������
		*	������list ���ݼ���
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void operator=(const CxList& list)
		{
			/* ������ǰ�� */
			clear();
			/* ����list�е� */
			iterator it = list.begin();
			iterator end = list.end();
			while (it != end)
			{
				push_back(*it);
				++it;
			}
		}
		/********************************************************
		*	��Ա�������ܣ��������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void clear()
		{
			while (m_pdsd->next != m_pdsd)
			{
				pop_front();
			}
		}

	public:
		typedef DIter<T> iterator;
		/********************************************************
		*	��Ա�������ܣ���ȡָ�������ײ��ĵ�����
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		iterator begin()
		{
			return m_pdsd->next;
		}
		/********************************************************
		*	��Ա�������ܣ���ȡָ������β���ĵ�����
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		iterator end()
		{
			return m_pdsd;
		}
		/********************************************************
		*	��Ա�������ܣ�ɾ����������ָ��λ��
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		T erase(iterator& it)
		{
			data_struct_dlist<T> *p1 = m_pdsd;
			data_struct_dlist<T> *p2 = m_pdsd->next;

			if (m_pdsd == it.data())
			{
				return 0;
			}

			while (p2 != m_pdsd && it.data() != p2)
			{
				p1 = p1->next;
				p2 = p2->next;
			}
			T t = p2->data;

			p1->next = p2->next;
			delete p2;

			return t;
		}

	private:
		data_struct_dlist<T> *m_pdsd;
	};
	/********************************************************
	*	������CsxList
	*	���ܣ�������˫��ѭ������
	*	ʱ�䣺2020-08-13
	*/
	template<typename T>
	class CsxList
	{
	public:
		/********************************************************
		*	��Ա�������ܣ����캯������ʼ������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		CsxList()
		{
			m_pdss = new data_struct_slist<T>;
			m_pdss->last = m_pdss;
			m_pdss->next = m_pdss;
		}
		/********************************************************
		*	��Ա�������ܣ����캯������ʼ������
		*	������obj, ��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		CsxList(TCQ(CsxList<T>) obj)
		{
			m_pdss = new data_struct_slist<T>;
			m_pdss->last = m_pdss;
			m_pdss->next = m_pdss;

			iterator it = obj.begin();
			iterator end = obj.end();
			while (it != end)
			{
				push_back(*it);
				++it;
			}
		}
		/********************************************************
		*	��Ա�������ܣ������������ͷ��ڴ�
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		~CsxList()
		{
			clear();
			delete m_pdss;
		}

	public:
		/********************************************************
		*	��Ա�������ܣ�������ݣ����ײ����
		*	������t ��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void push_front(TCQ(T) t)
		{
			data_struct_slist<T>* pss = new data_struct_slist<T>;
			pss->data = t;
			data_struct_slist<T>* p2 = m_pdss->next;

			m_pdss->next = pss;
			pss->last = m_pdss;
			pss->next = p2;
			p2->last = pss;
		}
		/********************************************************
		*	��Ա�������ܣ�������ݣ���β�����
		*	������t ��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void push_back(TCQ(T) t)
		{
			/* �������� */
			data_struct_slist<T>* pss = new data_struct_slist<T>;
			pss->data = t;

			/* �Ҳ���� */
			data_struct_slist<T>* p = m_pdss->last;

			m_pdss->last = pss;
			pss->next = m_pdss;
			pss->last = p;
			p->next = pss;
		}
		/********************************************************
		*	��Ա�������ܣ�������ݣ����ײ�ɾ��
		*	��������
		*	���أ���������
		*	ʱ�䣺2020-08-13
		*/
		T pop_front()
		{
			/* �������˳� */
			if (m_pdss == m_pdss->next)
			{
				return 0;
			}
			/* Ӧ��ɾ���� */
			data_struct_slist<T>* p1 = m_pdss->next;
			data_struct_slist<T>* p2 = p1->next;
			/* �Ͽ������� */
			m_pdss->next = p2;
			p2->last = m_pdss;
			/* �ͷ��ڴ� */
			T t = p1->data;
			delete p1;
			return t;
		}
		/********************************************************
		*	��Ա�������ܣ�������ݣ���β��ɾ��
		*	��������
		*	���أ���������
		*	ʱ�䣺2020-08-13
		*/
		T pop_back()
		{
			/* �������˳� */
			if (m_pdss == m_pdss->next)
			{
				return 0;
			}
			/* Ӧ��ɾ���� */
			data_struct_slist<T>* p1 = m_pdss->last;
			data_struct_slist<T>* p2 = p1->last;

			/* �Ͽ������� */
			m_pdss->last = p2;
			p2->next = m_pdss;
			/* �ͷ��ڴ� */
			T t = p1->data;
			delete p1;
			return t;
		}
		/********************************************************
		*	��Ա�������ܣ��������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		void clear()
		{
			while (m_pdss != m_pdss->next)
			{
				pop_front();
			}
		}

	public:
		/********************************************************
		*	���������
		*/
		typedef SIter<T> iterator;
		/********************************************************
		*	��Ա�������ܣ���ȡ���������
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		iterator begin()
		{
			return m_pdss->next;
		}
		/********************************************************
		*	��Ա�������ܣ���ȡ�������յ�
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		iterator end()
		{
			return m_pdss;
		}
		/********************************************************
		*	��Ա�������ܣ�ɾ����������ʶ�Ľڵ�
		*	��������
		*	���أ���
		*	ʱ�䣺2020-08-13
		*/
		T erase(iterator& it)
		{
			data_struct_slist<T>* p = m_pdss->next;
			while (p != m_pdss)
			{
				if (p == it.data())
				{
					/* ��p�޳� */
					data_struct_slist<T>* p1 = p->last;
					data_struct_slist<T>* p2 = p->next;
					
					p1->next = p2;
					p2->last = p1;

					/*  �ͷ��ڴ� */
					T t = p->data;
					delete p;
					return t;
				}

				p = p->next;
			}
			return 0;
		}

	private:
		data_struct_slist<T>* m_pdss;
	};
}


#endif