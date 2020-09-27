/**********************************************************************
*	�ļ����ܣ�LMW���C++����ͷ�ļ�,�ؼ���չ
*	������@ ������
*	��д������Windows7 + VS2013
*	��дʱ�䣺2020-08-21
*	�޸�ʱ�䣺2020-08-21
*
*	����0001��CImageListͼ���б�
*	����0002��CListBox�б��
*	����0003��CImageReport CIconView�б���ͼ
*	����0004��CProBox������
*	����0005��CSlider����
*	����0006��CStateBar״̬��
*	����0007��CStatic��̬�ı�
*	����0008��CToolBar������
*	����0009��CTree���ؼ�
*	����0010��CTreeItem���ؼ���һ���ڵ�
**/
#ifndef _CPP_CTRL_EX_H_
#define _CPP_CTRL_EX_H_

#include "win.h"
#include <CommCtrl.h>

#pragma comment(lib,"ComCtl32.lib") 
#include "libcpp.h"
#include "ds.hpp"

namespace lmw
{
#include "types.h"

	/* ͨ�ÿؼ���չ(��ֲ�������ҪһЩDLL��֧��) */
	void ExCtrlInit();

	/* ͼ���б� */
	class CImageList
	{
	public:
		CImageList(TCQ(int) cx, TCQ(int) cy, TCQ(int) num, TCQ(int) max = 10, TCUQ(int) color = 8);
		~CImageList();
		void SetImageList(TCQ(HIMAGELIST) hil);
		void AddIcon(HICON hIcon);
		void AddBitmap(HBITMAP bmp);
		const HIMAGELIST& GetImageList();

	private:
		HIMAGELIST m_hImageList;
	};

	/* ����ͼ���б���б�ؼ� */
	class CImageReport : public CListView
	{
	public:
		CImageReport(const HWND& hParent, const int& id);
		void SetImageList(CImageList* imageList);
	};

	class CIconView : public CListView
	{
	public:
		CIconView(const HWND& hParent, const int& id, BOOL isSmallIcon = FALSE);
		void SetImageList(CImageList* imageList);
		HIMAGELIST CreateDropImage();

	private:
		BOOL m_isSmallIcon;
	};

	/* �б�� */
	class CListBox : public CCtrl
	{
	public:
		CListBox(const HWND& hParent, const UINT& id);
		BOOL DelItem(TCUQ(int) nu);
		BOOL SelectItem(TCUQ(int) nu);
		TCU(int) FindStr(TCPCH str);
		void AddIten(TCPCH str);
	};

	/* ������ */
	class CProBox : public CCtrl
	{
	public:
		CProBox(TCQ(HWND) hParent, TCQ(UINT) id);
		void SetRange(TCQ(int) maxv = 100, TCUQ(int) minv = 0);
		void SetPosValue(TCQ(int) num);
		void AddPos(TCQ(int) pos);
		void DelPos(TCQ(int) pos);
		int GetPos();

	private:
		int m_max, m_min;
		int m_pos;
	};

	/* ���� */
	class CSlider : public CCtrl
	{
	public:
		/* isVert �Ƿ�ֱ */
		CSlider(TCQ(HWND) hParent, TCQ(UINT) id, TCQ(BOOL) isVert = TRUE);
		void SetRange(const int& range);
		void SetPosValue(const int& pos);
		int  GetPosValue();

	private:
		int m_pos;
	};

	/* ״̬������ */
	struct _STATEBAR_PART_
	{
		CStr text;
		int width;
	};
	typedef _STATEBAR_PART_ SBP;
	/* ״̬�� */
	class CStateBar : public CCtrl
	{
	public:
		CStateBar(TCQ(HWND) hParent, TCQ(UINT) id);
		~CStateBar();
		void Paint();
		void AddPart(TCQ(CStr) str, TCUQ(int) width);
		void OnSize();
		void SetBkColor(TCQ(COLORREF) color);
		/* ���ù�����ʾ */
		void SetTipText(TCUQ(int) index, TCPCH str);
		void SetItemText(TCUQ(int) index, TCPCH text);

	private:
		CVector<SBP>* m_pSbps;
		int m_SbpsNum;
	};

	/* ��̬�ı� */
	class CStatic : public CCtrl
	{
	public :
		CStatic(TCQ(HWND) hParent, TCQ(UINT) id);
	};

	/* ������ */
	struct _TOOLBAR_TIP_
	{
		CStr tip; /* ��ʾ */
		UINT id; /* id */
	};
	typedef struct _TOOLBAR_TIP_ TBT;
	class CToolBar : public CCtrl
	{
	public:
		CToolBar(TCQ(HWND) hParent, TCQ(UINT) id);
		~CToolBar();
		BOOL AddButtons(TCQ(int) iBmpIndex, TCUQ(int) id, LPSTR textTip, BOOL isShowText = FALSE);
		void OnSize();
		void AddBitmap(TCUQ(int) width, TCUQ(int) height, TCU(int) num, ...);
		void OnNotify(TCQ(LPARAM));
		void SetItemEnable(TCUQ(int) id, TCQ(BOOL) isEnable);

	private:
		CImageList* m_pImageList;
		CImageList* m_pImageList2;
		CVector<TBT>* m_vTbt;
	};

	/* ���ڵ��� */
	class CTreeItem
	{
	public:
		CTreeItem();
		void SetTreeItem(HTREEITEM item);
		void SetHwnd(TCQ(HWND) hwnd);
		CStr GetItemText();
		UINT GetItemImage();
		CTreeItem GetParentItem();
		void SetItemText(LPSTR str);
		void SetItemImage(TCUQ(int) iImage);
		BOOL IsNullTree();
		HTREEITEM GetTreeItem();
		BOOL HaveChildTree();

	private:
		HTREEITEM m_item;
		HWND m_hwnd;
	};

	class CTree : public CCtrl
	{
	public:
		CTree(TCQ(HWND) hParent, TCQ(UINT) id);
		void AddRootItem(TCPCH str, TCQ(int) iImage = -1);
		BOOL AddItem(TCU(int) height, ...); 
		BOOL AddItem(TCQ(int) iImage, TCU(int) height, ...);
		BOOL AddItem(TQ(CTreeItem) ti, LPSTR text, TCQ(int) iImage = -1);
		CTreeItem GetSelectItem();
		CTreeItem GetItem(TCU(int) height, ...);
		void SetImageList(CImageList * pImageList);
		void DeleteItem(HTREEITEM item);
		void DeleteAllItems();
		void SetEditItem(HTREEITEM item);

	protected:
		BOOL IsItemStr(HTREEITEM hitem, TCPCH str);
		BOOL SerachChildItem(HTREEITEM& hitem, TCPCH str);
	};

}

/* ��ʼ���ؼ������� */
#define WINDOW_CTRL_INIT()		lmw::ExCtrlInit()

#endif
