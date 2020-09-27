/**********************************************************************
*	文件功能：LMW库的C++代码头文件,控件扩展
*	所有者@ ：罗敏
*	编写环境：Windows7 + VS2013
*	编写时间：2020-08-21
*	修改时间：2020-08-21
*
*	内容0001：CImageList图像列表
*	内容0002：CListBox列表框
*	内容0003：CImageReport CIconView列表视图
*	内容0004：CProBox进度条
*	内容0005：CSlider滑块
*	内容0006：CStateBar状态栏
*	内容0007：CStatic静态文本
*	内容0008：CToolBar工具栏
*	内容0009：CTree树控件
*	内容0010：CTreeItem树控件的一个节点
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

	/* 通用控件扩展(移植后可能需要一些DLL的支持) */
	void ExCtrlInit();

	/* 图像列表 */
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

	/* 包含图像列表的列表控件 */
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

	/* 列表框 */
	class CListBox : public CCtrl
	{
	public:
		CListBox(const HWND& hParent, const UINT& id);
		BOOL DelItem(TCUQ(int) nu);
		BOOL SelectItem(TCUQ(int) nu);
		TCU(int) FindStr(TCPCH str);
		void AddIten(TCPCH str);
	};

	/* 进度条 */
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

	/* 滑块 */
	class CSlider : public CCtrl
	{
	public:
		/* isVert 是否垂直 */
		CSlider(TCQ(HWND) hParent, TCQ(UINT) id, TCQ(BOOL) isVert = TRUE);
		void SetRange(const int& range);
		void SetPosValue(const int& pos);
		int  GetPosValue();

	private:
		int m_pos;
	};

	/* 状态栏部分 */
	struct _STATEBAR_PART_
	{
		CStr text;
		int width;
	};
	typedef _STATEBAR_PART_ SBP;
	/* 状态栏 */
	class CStateBar : public CCtrl
	{
	public:
		CStateBar(TCQ(HWND) hParent, TCQ(UINT) id);
		~CStateBar();
		void Paint();
		void AddPart(TCQ(CStr) str, TCUQ(int) width);
		void OnSize();
		void SetBkColor(TCQ(COLORREF) color);
		/* 设置工具提示 */
		void SetTipText(TCUQ(int) index, TCPCH str);
		void SetItemText(TCUQ(int) index, TCPCH text);

	private:
		CVector<SBP>* m_pSbps;
		int m_SbpsNum;
	};

	/* 静态文本 */
	class CStatic : public CCtrl
	{
	public :
		CStatic(TCQ(HWND) hParent, TCQ(UINT) id);
	};

	/* 工具栏 */
	struct _TOOLBAR_TIP_
	{
		CStr tip; /* 提示 */
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

	/* 树节点项 */
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

/* 初始化控件窗口类 */
#define WINDOW_CTRL_INIT()		lmw::ExCtrlInit()

#endif
