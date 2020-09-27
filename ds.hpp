/**********************************************************************
*	文件功能：数据结构相关类的设计
*	所有者@ ：罗敏
*	编写环境：Win7 + VS2013
*	编写时间：2020-08-13
*	修改时间：2020-08-13
**/
#ifndef _CPP_DATA_STRUCT_H_
#define _CPP_DATA_STRUCT_H_

namespace lmw
{
#include "types.h"
	/********************************************************
	*	类名：DIter
	*	功能：迭代器，Vector中的一项
	*	时间：2020-08-13
	*/
	template<typename T>
	class VIter
	{
	public:
		/********************************************************
		*	成员函数功能：构造函数，初始化对象
		*	参数：p vector中某个对象的地址
		*	返回：无
		*	时间：2020-08-13
		*/
		VIter(T* p = nullptr)
		{
			m_p = p;
		}
		/********************************************************
		*	成员函数功能：重载*操作符
		*	参数：无
		*	返回：迭代器中的数据
		*	时间：2020-08-13
		*/
		T& operator*()
		{
			return *m_p;
		}
		/********************************************************
		*	成员函数功能：重载前置++操作符
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		void operator ++()
		{
			m_p += 1;
		}
		/********************************************************
		*	成员函数功能：重载后置++操作符
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		void operator ++(int)
		{
			m_p += 1;
		}
		/********************************************************
		*	成员函数功能：重载前置!=操作符
		*	参数：obj,比较的对象
		*	返回：是否不是同一个对象
		*	时间：2020-08-13
		*/
		int operator !=(const VIter<T>& obj)
		{
			return m_p != obj.m_p;
		}
		/********************************************************
		*	成员函数功能：获取链表节
		*	参数：无
		*	返回：链表节对象指针
		*	时间：2020-08-13
		*/
		T* data()
		{
			return m_p;
		}

	private:
		T* m_p;
	};
	/********************************************************
	*	类名：CVector
	*	功能：容器，可变数组
	*	时间：2020-08-13
	*/
	template<typename T>
	class CVector
	{
	public:
		/********************************************************
		*	成员函数功能：构造函数，初始化对象
		*	参数：initnum 初始化大小
		*	参数：addnum  内存不够用添加的大小
		*	返回：无
		*	时间：2020-08-13
		*/
		CVector(TCUQ(int) initnum = 10, TCUQ(int) addnum = 10)
		{
			m_pT = nullptr;		// 数据指针
			m_anums = addnum;	// 内存耗尽后，增长数量
			m_index = 0;		// 指示当前存储的数量

			if (initnum == 0 && addnum == 0){
				throw "容器初始化失败";
			}
			else
			{
				/* 存储数量 */
				m_maxs = initnum == 0 ? addnum : initnum;
			}

			memalloc();
		}
		/********************************************************
		*	成员函数功能：拷贝构造函数，初始化对象
		*	参数：obj 拷贝的对象
		*	返回：无
		*	时间：2020-08-13
		*/
		CVector(const CVector<T>& obj)
		{
			m_pT = nullptr;			// 数据指针
			m_anums = obj.m_anums;	// 内存耗尽后，增长数量
			m_index = obj.m_index;	// 指示当前存储的数量
			m_maxs = obj.m_maxs;	/* 存储数量 */

			/* 内存分配 */
			m_pT = new T[m_maxs];
			/* 数据存储 */
			for (size_t i = 0; i < m_index; i++)
			{
				m_pT[i] = obj.m_pT[i];
			}
		}
		/********************************************************
		*	成员函数功能：析构函数，释放内存
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		~CVector()
		{
			delete[] m_pT;
		}
		/********************************************************
		*	成员函数功能：内存空间的分配+修改
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		void memalloc()
		{
			/* 创建内存 */
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
			/* 释放以前的内存 */
			delete[] m_pT;
			/* 内存地址切换 */
			m_pT = pTmp;
		}
		/********************************************************
		*	成员函数功能：从尾部添加一个数据
		*	参数：t 要添加的数据
		*	返回：无
		*	时间：2020-08-13
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
		*	成员函数功能：从尾部删除一个数据
		*	参数：无
		*	返回：返回删除的值,没有内容则返回0
		*	时间：2020-08-13
		*/
		T pop_back()
		{
			if (0 != m_index)
				return m_pT[--m_index];
			return 0;
		}
		/********************************************************
		*	成员函数功能：插入一个数据
		*	参数：t  插入的数据
		*		index 位置
		*	返回：无
		*	时间：2020-08-28
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
		*	成员函数功能：删除指定位置的值
		*	参数：index，首地址偏移
		*	返回：返回删除的数据
		*	时间：2020-08-28
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
		*	成员函数功能：重载[]操作符，直接访问内部数据
		*	参数：index，首地址偏移
		*	返回：返回内部数据的引用
		*	时间：2020-08-13
		*/
		T& operator[](size_t index)
		{
			return m_pT[index];
		}
		/********************************************************
		*	成员函数功能：容器中已存放的物件数量
		*	参数：无
		*	返回：m_index，存放的数量，无符号数
		*	时间：2020-08-13
		*/
		size_t size()
		{
			return m_index;
		}
		/********************************************************
		*	成员函数功能：重载=操作符，赋值操作。。
		*	参数：赋值对象
		*	返回：返回参数的常量引用
		*	时间：2020-08-13
		*/
		const CVector<T>& operator=(const CVector<T>& obj)
		{
			m_pT = nullptr;			// 数据指针
			m_anums = obj.m_anums;	// 内存耗尽后，增长数量
			m_index = obj.m_index;	// 指示当前存储的数量
			m_maxs = obj.m_maxs;	/* 存储数量 */

			if (m_pT != nullptr)
			{
				delete[] m_pT;
			}

			/* 内存分配 */
			m_pT = new T[m_maxs];
			/* 数据存储 */
			for (size_t i = 0; i < m_index; i++)
			{
				m_pT[i] = obj.m_pT[i];
			}
		}

	public:
		typedef VIter<T> iterator;
		/********************************************************
		*	成员函数功能：获取迭代器起点
		*	参数：无
		*	返回：返回迭代器起点
		*	时间：2020-08-13
		*/
		iterator begin()
		{
			return m_pT;
		}
		/********************************************************
		*	成员函数功能：获取迭代器终点
		*	参数：无
		*	返回：返回迭代器终点
		*	时间：2020-08-13
		*/
		iterator end()
		{
			return m_pT + m_index;
		}
		/********************************************************
		*	成员函数功能：删除迭代器所指的数据
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
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
		T* m_pT;		// 数据指针
		size_t m_maxs;	// 当前存储数量
		size_t m_anums;	// 内存耗尽后，增长数量
		size_t m_index;	// 指示当前存储的数量
	};
	/********************************************************
	*	类名：data_struct_dlist
	*	功能：容器，单向链表的一个节，模板类
	*	时间：2020-08-13
	*/
	template<typename T>
	struct data_struct_dlist
	{
		data_struct_dlist<T>* next;
		T data;
	};
	/********************************************************
	*	类名：DIter
	*	功能：迭代器，单向链表的一个节
	*	时间：2020-08-13
	*/
	template<typename T>
	class DIter
	{
	public:
		/********************************************************
		*	成员函数功能：构造函数，初始化对象
		*	参数：pdsd 单向链表的一个节指针结构体
		*	返回：无
		*	时间：2020-08-13
		*/
		DIter(data_struct_dlist<T>* pdsd = nullptr)
		{
			m_pdsd = pdsd;
		}
		/********************************************************
		*	成员函数功能：重载*操作符
		*	参数：无
		*	返回：迭代器中的数据
		*	时间：2020-08-13
		*/
		T& operator*()
		{
			return m_pdsd->data;
		}
		/********************************************************
		*	成员函数功能：重载前置++操作符
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		void operator ++()
		{
			if (nullptr != m_pdsd)
			{
				m_pdsd = m_pdsd->next;
			}
		}
		/********************************************************
		*	成员函数功能：重载后置++操作符
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		void operator ++(int)
		{
			if (nullptr != m_pdsd)
			{
				m_pdsd = m_pdsd->next;
			}
		}
		/********************************************************
		*	成员函数功能：重载前置!=操作符
		*	参数：obj,比较的对象
		*	返回：是否不是同一个对象
		*	时间：2020-08-13
		*/
		int operator !=(const DIter<T>& obj)
		{
			return m_pdsd != obj.m_pdsd;
		}
		/********************************************************
		*	成员函数功能：获取链表节
		*	参数：无
		*	返回：链表节对象指针
		*	时间：2020-08-13
		*/
		const data_struct_dlist<T>* data()
		{
			return m_pdsd;
		}

	private:
		data_struct_dlist<T>* m_pdsd;
	};
	/********************************************************
	*	类名：data_struct_slist
	*	功能：容器，双向链表的一个节，模板类
	*	时间：2020-08-13
	*/
	template<typename T>
	struct data_struct_slist
	{
		data_struct_slist<T>* last;
		data_struct_slist<T>* next; 
		T data;
	};
	/********************************************************
	*	类名：SIter
	*	功能：迭代器，双向链表的一个节
	*	时间：2020-08-13
	*/
	template<typename T>
	class SIter
	{
	public:
		/********************************************************
		*	成员函数功能：构造函数，初始化对象
		*	参数：pdsd 双向链表的一个节指针结构体
		*	返回：无
		*	时间：2020-08-13
		*/
		SIter(data_struct_slist<T>* pdsd = nullptr)
		{
			m_pdsd = pdsd;
		}
		/********************************************************
		*	成员函数功能：重载*操作符
		*	参数：无
		*	返回：迭代器中的数据
		*	时间：2020-08-13
		*/
		T& operator*()
		{
			return m_pdsd->data;
		}
		/********************************************************
		*	成员函数功能：重载前置++操作符
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		void operator ++()
		{
			if (nullptr != m_pdsd)
			{
				m_pdsd = m_pdsd->next;
			}
		}
		/********************************************************
		*	成员函数功能：重载前置--操作符
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		void operator --()
		{
			if (nullptr != m_pdsd)
			{
				m_pdsd = m_pdsd->last;
			}
		}
		/********************************************************
		*	成员函数功能：重载后置++操作符
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		void operator ++(int)
		{
			if (nullptr != m_pdsd)
			{
				m_pdsd = m_pdsd->next;
			}
		}
		/********************************************************
		*	成员函数功能：重载后置--操作符
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		void operator --(int)
		{
			if (nullptr != m_pdsd)
			{
				m_pdsd = m_pdsd->last;
			}
		}
		/********************************************************
		*	成员函数功能：重载前置!=操作符
		*	参数：obj,比较的对象
		*	返回：是否不是同一个对象
		*	时间：2020-08-13
		*/
		int operator !=(const SIter<T>& obj)
		{
			return m_pdsd != obj.m_pdsd;
		}
		/********************************************************
		*	成员函数功能：获取链表节
		*	参数：无
		*	返回：链表节对象指针
		*	时间：2020-08-13
		*/
		const data_struct_slist<T>* data()
		{
			return m_pdsd;
		}

	private:
		data_struct_slist<T>* m_pdsd;
	};
	/********************************************************
	*	类名：CdList
	*	功能：容器，单向链表
	*	时间：2020-08-13
	*/
	template<typename T>
	class CdList
	{
	public:
		/********************************************************
		*	成员函数功能：构造函数，初始化对象
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		CdList()
		{
			m_pdsd = new data_struct_dlist<T>;
			m_pdsd->next = nullptr;
		}
		/********************************************************
		*	成员函数功能：拷贝构造函数，初始化对象
		*	参数：list 拷贝对象
		*	返回：无
		*	时间：2020-08-13
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
		*	成员函数功能：析构函数，释放对象
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		~CdList()
		{
			clear();
			delete m_pdsd;
		}

	public:
		/********************************************************
		*	成员函数功能：添加数据,在链表尾部
		*	参数：t 数据内容
		*	返回：无
		*	时间：2020-08-13
		*/
		void push_back(const T& t)
		{
			/* 初始化新的节点 */
			data_struct_dlist<T>* pdsd = new data_struct_dlist<T>;
			pdsd->data = t;
			pdsd->next = nullptr;

			/* 找到最后一个节点 */
			data_struct_dlist<T>* p = m_pdsd;
			while (nullptr != p->next)
			{
				p = p->next;
			}
			/* 连接上 */
			p->next = pdsd;
		}
		/********************************************************
		*	成员函数功能：添加数据,在链表首部
		*	参数：t 数据内容
		*	返回：无
		*	时间：2020-08-13
		*/
		void push_front(const T& t)
		{
			/* 初始化新的节点 */
			data_struct_dlist<T>* pdsd = new data_struct_dlist<T>;
			pdsd->data = t;
			pdsd->next = nullptr;

			/* 连接上 */
			pdsd->next = m_pdsd->next;
			m_pdsd->next = pdsd;
		}
		/********************************************************
		*	成员函数功能：删除数据,在链表尾部
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		T pop_back()
		{
			data_struct_dlist<T>* pdsd = m_pdsd;

			/* 空链表，删除失败 */
			if (nullptr == m_pdsd->next)
			{
				return 0;
			}
			/* 找到倒数第二个 */
			while (nullptr != pdsd->next->next)
			{
				pdsd = pdsd->next;
			}
			/* 保存指针，断开连接 */
			data_struct_dlist<T>* p = pdsd->next;
			pdsd->next = nullptr;
			/* 释放内存 */
			T t = p->data;
			delete p;
			return t;
		}
		/********************************************************
		*	成员函数功能：删除数据,在链表首部
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		T pop_front()
		{
			data_struct_dlist<T>* pdsd = m_pdsd;

			/* 空链表，删除失败 */
			if (nullptr == m_pdsd->next)
			{
				return 0;
			}
			/* 断开连接 */
			data_struct_dlist<T>* p = m_pdsd->next;
			m_pdsd->next = p->next;
			/* 保存数据 */
			T t = p->data;
			/* 释放内存 */
			delete p;

			return t;
		}
		/********************************************************
		*	成员函数功能：重载=操作符
		*	参数：list 数据集合
		*	返回：无
		*	时间：2020-08-13
		*/
		void operator=(const CdList& list)
		{
			/* 清理以前的 */
			clear();
			/* 保存list中的 */
			iterator it = list.begin();
			iterator end = list.end();
			while (it != end)
			{
				push_back(*it);
				++it;
			}
		}
		/********************************************************
		*	成员函数功能：清空链表
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
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
		*	成员函数功能：获取指向链表首部的迭代器
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		iterator begin()
		{
			return m_pdsd->next;
		}
		/********************************************************
		*	成员函数功能：获取指向链表尾部的迭代器
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		iterator end()
		{
			return nullptr;
		}
		/********************************************************
		*	成员函数功能：删除迭代器所指的位置
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
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
	/*** 默认的List是单向链表 ***/
#define		List	CdList
	/********************************************************
	*	类名：CxList
	*	功能：容器，单向循环链表
	*	时间：2020-08-13
	*/
	template<typename T>
	class CxList
	{
	public:
		/********************************************************
		*	成员函数功能：构造函数，初始化对象
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		CxList()
		{
			m_pdsd = new data_struct_dlist<T>;
			m_pdsd->next = m_pdsd;
		}
		/********************************************************
		*	成员函数功能：拷贝构造函数，初始化对象
		*	参数：list 拷贝对象
		*	返回：无
		*	时间：2020-08-13
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
		*	成员函数功能：析构函数，释放对象
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		~CxList()
		{
			clear();
			delete m_pdsd;
		}

	public:
		/********************************************************
		*	成员函数功能：添加数据,在链表尾部
		*	参数：t 数据内容
		*	返回：无
		*	时间：2020-08-13
		*/
		void push_back(const T& t)
		{
			/* 初始化新的节点 */
			data_struct_dlist<T>* pdsd = new data_struct_dlist<T>;
			pdsd->data = t;
			pdsd->next = m_pdsd;

			/* 找到最后一个节点 */
			data_struct_dlist<T>* p = m_pdsd;
			while (m_pdsd != p->next)
			{
				p = p->next;
			}
			/* 连接上 */
			p->next = pdsd;
		}
		/********************************************************
		*	成员函数功能：添加数据,在链表首部
		*	参数：t 数据内容
		*	返回：无
		*	时间：2020-08-13
		*/
		void push_front(const T& t)
		{
			/* 初始化新的节点 */
			data_struct_dlist<T>* pdsd = new data_struct_dlist<T>;
			pdsd->data = t;
			pdsd->next = nullptr;

			/* 连接上 */
			pdsd->next = m_pdsd->next;
			m_pdsd->next = pdsd;
		}
		/********************************************************
		*	成员函数功能：删除数据,在链表尾部
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		T pop_back()
		{
			data_struct_dlist<T>* pdsd = m_pdsd;

			/* 空链表，删除失败 */
			if (m_pdsd == m_pdsd->next)
			{
				return 0;
			}
			/* 找到倒数第二个 */
			while (m_pdsd != pdsd->next->next)
			{
				pdsd = pdsd->next;
			}
			/* 保存指针，断开连接 */
			data_struct_dlist<T>* p = pdsd->next;
			pdsd->next = m_pdsd;
			/* 释放内存 */
			T t = p->data;
			delete p;
			return t;
		}
		/********************************************************
		*	成员函数功能：删除数据,在链表首部
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		T pop_front()
		{
			data_struct_dlist<T>* pdsd = m_pdsd;

			/* 空链表，删除失败 */
			if (m_pdsd == m_pdsd->next)
			{
				return 0;
			}
			/* 断开连接 */
			data_struct_dlist<T>* p = m_pdsd->next;
			m_pdsd->next = p->next;
			/* 保存数据 */
			T t = p->data;
			/* 释放内存 */
			delete p;

			return t;
		}
		/********************************************************
		*	成员函数功能：重载=操作符
		*	参数：list 数据集合
		*	返回：无
		*	时间：2020-08-13
		*/
		void operator=(const CxList& list)
		{
			/* 清理以前的 */
			clear();
			/* 保存list中的 */
			iterator it = list.begin();
			iterator end = list.end();
			while (it != end)
			{
				push_back(*it);
				++it;
			}
		}
		/********************************************************
		*	成员函数功能：清空链表
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
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
		*	成员函数功能：获取指向链表首部的迭代器
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		iterator begin()
		{
			return m_pdsd->next;
		}
		/********************************************************
		*	成员函数功能：获取指向链表尾部的迭代器
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		iterator end()
		{
			return m_pdsd;
		}
		/********************************************************
		*	成员函数功能：删除迭代器所指的位置
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
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
	*	类名：CsxList
	*	功能：容器，双向循环链表
	*	时间：2020-08-13
	*/
	template<typename T>
	class CsxList
	{
	public:
		/********************************************************
		*	成员函数功能：构造函数，初始化对象
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		CsxList()
		{
			m_pdss = new data_struct_slist<T>;
			m_pdss->last = m_pdss;
			m_pdss->next = m_pdss;
		}
		/********************************************************
		*	成员函数功能：构造函数，初始化对象
		*	参数：obj, 拷贝对象
		*	返回：无
		*	时间：2020-08-13
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
		*	成员函数功能：析构函数，释放内存
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		~CsxList()
		{
			clear();
			delete m_pdss;
		}

	public:
		/********************************************************
		*	成员函数功能：添加数据，从首部添加
		*	参数：t 数据内容
		*	返回：无
		*	时间：2020-08-13
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
		*	成员函数功能：添加数据，从尾部添加
		*	参数：t 数据内容
		*	返回：无
		*	时间：2020-08-13
		*/
		void push_back(TCQ(T) t)
		{
			/* 创建对象 */
			data_struct_slist<T>* pss = new data_struct_slist<T>;
			pss->data = t;

			/* 找插入点 */
			data_struct_slist<T>* p = m_pdss->last;

			m_pdss->last = pss;
			pss->next = m_pdss;
			pss->last = p;
			p->next = pss;
		}
		/********************************************************
		*	成员函数功能：添加数据，从首部删除
		*	参数：无
		*	返回：数据内容
		*	时间：2020-08-13
		*/
		T pop_front()
		{
			/* 空链表，退出 */
			if (m_pdss == m_pdss->next)
			{
				return 0;
			}
			/* 应被删除的 */
			data_struct_slist<T>* p1 = m_pdss->next;
			data_struct_slist<T>* p2 = p1->next;
			/* 断开的连上 */
			m_pdss->next = p2;
			p2->last = m_pdss;
			/* 释放内存 */
			T t = p1->data;
			delete p1;
			return t;
		}
		/********************************************************
		*	成员函数功能：添加数据，从尾部删除
		*	参数：无
		*	返回：数据内容
		*	时间：2020-08-13
		*/
		T pop_back()
		{
			/* 空链表，退出 */
			if (m_pdss == m_pdss->next)
			{
				return 0;
			}
			/* 应被删除的 */
			data_struct_slist<T>* p1 = m_pdss->last;
			data_struct_slist<T>* p2 = p1->last;

			/* 断开的连上 */
			m_pdss->last = p2;
			p2->next = m_pdss;
			/* 释放内存 */
			T t = p1->data;
			delete p1;
			return t;
		}
		/********************************************************
		*	成员函数功能：清空链表
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
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
		*	定义迭代器
		*/
		typedef SIter<T> iterator;
		/********************************************************
		*	成员函数功能：获取迭代器起点
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		iterator begin()
		{
			return m_pdss->next;
		}
		/********************************************************
		*	成员函数功能：获取迭代器终点
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		iterator end()
		{
			return m_pdss;
		}
		/********************************************************
		*	成员函数功能：删除迭代器标识的节点
		*	参数：无
		*	返回：无
		*	时间：2020-08-13
		*/
		T erase(iterator& it)
		{
			data_struct_slist<T>* p = m_pdss->next;
			while (p != m_pdss)
			{
				if (p == it.data())
				{
					/* 将p剔除 */
					data_struct_slist<T>* p1 = p->last;
					data_struct_slist<T>* p2 = p->next;
					
					p1->next = p2;
					p2->last = p1;

					/*  释放内存 */
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