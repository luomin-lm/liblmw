#include "win.h"

namespace lmw
{
	/********************************************************
	*	成员函数功能：构造函数，初始化对象，默认为NULL
	*	参数：hwnd 初始窗口句柄
	*	返回：无
	*	时间：2020-08-17
	*/
	CHwnd::CHwnd(TCQ(HWND) hwnd)
	{
		m_hwnd = hwnd;
	}
	/********************************************************
	*	成员函数功能：获取安全的窗口句柄(不可修改)
	*	参数：无
	*	返回：常量窗口句柄
	*	时间：2020-08-17
	*/
	TCQ(HWND) CHwnd::GetSafeHwnd()
	{
		return m_hwnd;
	}
	/********************************************************
	*	成员函数功能：设置窗口句柄
	*	参数：hwnd 窗口句柄
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::SetHwnd(TCQ(HWND) hwnd)
	{
		m_hwnd = hwnd;
	}
	/********************************************************
	*	成员函数功能：设置当前窗口句柄为子窗口句柄
	*	参数：
	*		hwnd	父窗口句柄
	*		id		子窗口ID
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::SetHwnd(TCQ(HWND) hParent, TCQ(int) id)
	{
		m_hwnd = GetDlgItem(hParent, id);
	}
	/********************************************************
	*	成员函数功能：查询窗口，并设置
	*	参数：
	*		clsName		窗口类名
	*		windowName	窗口标题
	*	返回：无
	*	时间：2020-08-17
	*/
	BOOL CHwnd::FindHwnd(TCP(char) clsName, TCP(char) windowName)
	{
		m_hwnd = FindWindowA(clsName, windowName);
		if (NULL == m_hwnd)
		{
			return FALSE;
		}
		return TRUE;
	}
	/********************************************************
	*	成员函数功能：查询窗口，并设置
	*	参数：
	*		hParent		父窗口
	*		hwnd		子窗口句柄，用于遍历窗口
	*		clsName		窗口类名
	*		windowName	窗口标题
	*	返回：无
	*	时间：2020-08-17
	*/
	BOOL CHwnd::FindHwndEx(TCQ(HWND) hParent, TCQ(HWND) hwnd, TCP(char) clsName, TCP(char) windowName)
	{
		m_hwnd = FindWindowExA(hParent, hwnd, clsName, windowName);
		if (NULL == m_hwnd)
		{
			return FALSE;
		}
		return TRUE;
	}
	/********************************************************
	*	成员函数功能：向窗口发送消息
	*	参数：
	*		Msg		消息
	*		wParam	消息参数
	*		lParam	消息参数
	*	返回：无
	*	时间：2020-08-17
	*/
	UINT CHwnd::SendMsg(TCQ(UINT) Msg, TCQ(WPARAM) wParam, TCQ(LPARAM) lParam)
	{
		return SendMessage(m_hwnd, Msg, wParam, lParam);
	}
	/********************************************************
	*	成员函数功能：显示并激活窗口
	*	参数：无
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::Show()
	{
		ShowWindow(m_hwnd, SW_RESTORE);
	}
	/********************************************************
	*	成员函数功能：隐藏窗口
	*	参数：无
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::Hide()
	{
		ShowWindow(m_hwnd, SW_HIDE);
	}
	/********************************************************
	*	成员函数功能：更新窗口(重绘)
	*	参数：无
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::Update()
	{
		UpdateWindow(m_hwnd);
	}
	/********************************************************
	*	成员函数功能：更新窗口(重绘)
	*	参数：无
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::Update(TCQ(RECT) rc, TCQ(BOOL) isErase)
	{
		InvalidateRect(m_hwnd, &rc, isErase);
	}
	/********************************************************
	*	成员函数功能：设置窗口使能(是否接收消息)
	*	参数：isEnable		是否使能，TRUE是，FALSE否
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::SetEnable(TCQ(BOOL) isEnable)
	{
		EnableWindow(m_hwnd, isEnable);
	}
	/********************************************************
	*	成员函数功能：设置窗口位置(窗口左上方再父窗口的的坐标<x, y>)
	*	参数：
	*		x	x坐标，横坐标
	*		y	y坐标，纵坐标
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::SetPos(TCQ(int) x, TCQ(int) y)
	{
		SetWindowPos(m_hwnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	/********************************************************
	*	成员函数功能：设置窗口大小(宽、高)
	*	参数：
	*		width	窗口宽
	*		height	窗口高
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::SetSize(TCQ(int) width, TCQ(int) height)
	{
		SetWindowPos(m_hwnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
	}
	/********************************************************
	*	成员函数功能：设置固定的窗口大小(宽、高)
	*	参数：
	*		width	窗口宽
	*		height	窗口高
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::SetFixedSize(TCQ(int) width, TCQ(int) height)
	{
		SetWindowPos(m_hwnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
		/* 删除WS_THICKFRAME风格，去掉拖动大小的功能 */
		SetWindowLong(m_hwnd, GWL_STYLE, GetWindowLong(m_hwnd, GWL_STYLE) & ~WS_THICKFRAME);
	}
	/********************************************************
	*	成员函数功能：设置窗口风格
	*	参数：style 新设置的风格
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::SetStyle(TCUQ(int) style)
	{
		SetWindowLong(m_hwnd, GWL_STYLE, style);
	}
	/********************************************************
	*	成员函数功能：设置窗口扩展风格
	*	参数：exStyle 新设置的扩展风格
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::SetStyleEx(TCUQ(int) exStyle)
	{
		SetWindowLong(m_hwnd, GWL_EXSTYLE, exStyle);
	}
	/********************************************************
	*	成员函数功能：获取窗口风格
	*	参数：无
	*	返回：窗口风格
	*	时间：2020-08-17
	*/
	TU(int) CHwnd::GetStyle()
	{
		return GetWindowLong(m_hwnd, GWL_STYLE);
	}
	/********************************************************
	*	成员函数功能：获取窗口扩展风格
	*	参数：无
	*	返回：获取窗口扩展风格
	*	时间：2020-08-17
	*/
	TU(int) CHwnd::GetStyleEx()
	{
		return GetWindowLong(m_hwnd, GWL_EXSTYLE);
	}
	/********************************************************
	*	成员函数功能：添加窗口风格
	*	参数：style 风格(WS_*)
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::AddStyle(TCUQ(int) style)
	{
		SetWindowLong(m_hwnd, GWL_STYLE, GetWindowLong(m_hwnd, GWL_STYLE) | style);
	}
	/********************************************************
	*	成员函数功能：添加窗口扩展风格
	*	参数：exStyle 风格(WS_*)
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::AddExStyle(TCUQ(int) exStyle)
	{
		SetWindowLong(m_hwnd, GWL_EXSTYLE, GetWindowLong(m_hwnd, GWL_EXSTYLE) | exStyle);
	}
	/********************************************************
	*	成员函数功能：删除部分窗口风格
	*	参数：style 风格(WS_*)
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::DelStyle(TCUQ(int) style)
	{
		SetWindowLong(m_hwnd, GWL_STYLE, GetWindowLong(m_hwnd, GWL_STYLE) & ~style);
	}
	/********************************************************
	*	成员函数功能：删除部分窗口扩展风格
	*	参数：exStyle 风格(WS_*)
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::DelExStyle(TCUQ(int) exStyle)
	{
		SetWindowLong(m_hwnd, GWL_EXSTYLE, GetWindowLong(m_hwnd, GWL_EXSTYLE) & ~exStyle);
	}
	/********************************************************
	*	成员函数功能：设置窗口顶置
	*	参数：isTop 是否置顶(默认为顶置)
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::SetZorder(BOOL isTop)
	{
		if (TRUE == isTop)
		{
			SetWindowPos(m_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		else
		{
			SetWindowPos(m_hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
	}
	/********************************************************
	*	成员函数功能：获取客户端区域
	*	参数：无
	*	返回：RECT(left = 0, top = 0, right = width, bottom = height)
	*	时间：2020-08-17
	*/
	RECT CHwnd::GetClientRect()
	{
		RECT rc;
		::GetClientRect(m_hwnd, &rc);
		return rc;
	}
	/********************************************************
	*	成员函数功能：获取窗口区域
	*	参数：无
	*	返回：RECT(left = x1, top = y1, right = x2, bottom = y2)
	*	时间：2020-08-17
	*/
	RECT CHwnd::GetWindowRect()
	{
		RECT rc;
		::GetWindowRect(m_hwnd, &rc);
		return rc;
	}
	/********************************************************
	*	成员函数功能：设置窗口标题
	*	参数：str 窗口标题字符串
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::SetTitle(TCP(char) str)
	{
		SetWindowText(m_hwnd, str);
	}
	/********************************************************
	*	成员函数功能：设置窗口标题
	*	参数：str 窗口标题字符串
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::GetTitle(TP(char) strbuff, TCUQ(int) bufflen)
	{
		GetWindowText(m_hwnd, strbuff, bufflen);
	}
	/********************************************************
	*	成员函数功能：设置窗口形状
	*	参数：hRgn 剪裁区域
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::SetRgn(const HRGN& hRgn)
	{
		SetWindowRgn(m_hwnd, hRgn, TRUE);
	}
	/********************************************************
	*	成员函数功能：最大化窗口
	*	参数：无
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::MaxWindow()
	{
		SendMsg(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	}
	/********************************************************
	*	成员函数功能：最小化窗口
	*	参数：无
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::MinWindow()
	{
		SendMsg(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	}
	/********************************************************
	*	成员函数功能：启用文件拖拽功能
	*	参数：无
	*	返回：无
	*	时间：2020-08-17
	*	注释：响应WM_DROPFILES消息，实现拖拽功能
	*/
	void CHwnd::SetAcceptDrops()
	{
		AddExStyle(WS_EX_ACCEPTFILES);
	}
	/********************************************************
	*	成员函数功能：设置窗口透明度
	*	参数：value 透明度(0 - 255)
	*	返回：无
	*	时间：2020-08-17
	*/
	BOOL CHwnd::SetAlpha(TCUQ(char) value)
	{
		AddExStyle(WS_EX_LAYERED);
		return SetLayeredWindowAttributes(GetSafeHwnd(), RGB(0, 0, 0), value, LWA_ALPHA);
	}
	/********************************************************
	*	成员函数功能：设置窗口透明颜色
	*	参数：color 透明色(RGB宏)
	*	返回：是否成功
	*	时间：2020-08-17
	*/
	BOOL CHwnd::SetTransparentColor(TCQ(COLORREF) color)
	{
		AddExStyle(WS_EX_LAYERED);
		return SetLayeredWindowAttributes(GetSafeHwnd(), color, 0, LWA_COLORKEY);
	}
	/********************************************************
	*	成员函数功能：获取窗口类的名称
	*	参数：
	*		str		缓冲内存首地址
	*		bufflen	缓冲大小
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::GetClsName(TP(char) str, TCUQ(int) bufflen)
	{
		GetClassName(m_hwnd, str, bufflen);
	}
	/********************************************************
	*	成员函数功能：设置字体
	*	参数：font 字体句柄
	*	返回：无
	*	时间：2020-08-17
	*/
	void CHwnd::SetFont(HFONT font)
	{
		SendMsg(WM_SETFONT, (WPARAM)font, TRUE);
	}
	/********************************************************
	*	成员函数功能：设置窗口居中
	*	参数：无
	*	返回：无
	*	时间：2020-09-03
	*/
	void CHwnd::SetCenterPos()
	{
		RECT rc = GetClientRect();
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;

		SetPos((width - rc.right) / 2, (height - rc.bottom) / 2);
	}
}


