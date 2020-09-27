#include "win.h"
#include "ctrlself.h"

namespace lmw
{
	// 从资源中加载位图
	HBITMAP GetBitmap(TCUQ(int) id)
	{
		return LoadBitmap(HINST, MAKEINTRESOURCE(id));
	}
	// 从文件中加载位图
	HBITMAP GetBitmap(TCPCH path, TCUQ(int) width, TCUQ(int) height)
	{
		HBITMAP bmp = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
		return bmp;
	}
	// 从资源中加载图标
	HICON GetIcon(TCUQ(int) id)
	{
		return LoadIcon(HINST, MAKEINTRESOURCE(id));
	}
	// 从文件中加载图标
	HICON GetIcon(TCPCH path, TCUQ(int) width, TCUQ(int) height)
	{
		return (HICON)LoadImage(NULL, path, IMAGE_ICON, width, height, LR_LOADFROMFILE);
	}
	/********************************************************
	*	成员函数功能：析构函数，释放控件内存
	*	参数：无
	*	返回：无
	*	时间：2020-08-18
	*/
	CApp1::~CApp1()
	{
		CSelfCtrl* p = nullptr;
		do
		{
			p = m_dlsc.pop_front();
			if (nullptr == p)
			{
				break;
			}
			delete p;
		} while (1);
	}
	/********************************************************
	*	成员函数功能：消息循环，直至当前对象所创建的窗口退出
	*	参数：无
	*	返回：无
	*	时间：2020-08-18
	*/
	int CApp1::MsgLoop()
	{
		MSG msg = { 0 };
		this->m_closeFlg = FALSE;

		do{
			/* 消息循环 */
			while (0 != GetMessage(&msg, NULL, 0, 0))
			//while (msg.message != WM_QUIT)
			{
				//if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				//{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				//}
			}
			/* 主窗口关闭 */
			if (TRUE == this->m_closeFlg)
			{
				return msg.wParam;
			}
		} while (1);

		return 0;
	}
	/********************************************************
	*	成员函数功能：处理消息循环，重载该虚函数实现消息处理
	*	参数：无
	*	返回：处理该消息则返回TRUE，未处理返回FALSE
	*	时间：2020-08-18
	*/
	BOOL CApp1::MsgHandle(TCQ(HWND) hwnd, TCQ(int) msg, WPARAM wParam, LPARAM lParam)
	{
		BOOL ret = TRUE;
		PAINTSTRUCT ps;
		LPNMHDR pnmh;

		switch (msg)
		{
		case WM_CREATE:
		case WM_INITDIALOG:
			OnInit();
			break;
		case WM_COMMAND:
			OnCommand(LOWORD(wParam), HIWORD(wParam));
			break;
		case WM_PAINT:
			OnPaint(BeginPaint(hwnd, &ps));
			EndPaint(hwnd, &ps);
			break;
		case WM_SIZE:
			OnSize(LOWORD(lParam), HIWORD(lParam));
			break;
		case WM_NOTIFY:
			pnmh = (LPNMHDR)lParam;
			OnNotify(pnmh->idFrom, pnmh->code);
			break;
		case WM_DESTROY:
		case WM_CLOSE:
			OnClose();
			break;
		case WM_TIMER:
			OnTimer(LOWORD(wParam));
			break;
		case WM_LBUTTONDOWN: // 左键
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_MBUTTONDOWN: // 中键
		case WM_MBUTTONUP:
		case WM_MBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK: // 右键
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MOUSEMOVE: // 鼠标移动
		case WM_MOUSEHOVER: // 移入
		case WM_MOUSELEAVE: // 移出
		case WM_MOUSEHWHEEL: // 滚轮
			OnMouse(msg, wParam, lParam);
			break;
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORSCROLLBAR:
		case WM_CTLCOLORSTATIC:
		case WM_CTLCOLORMSGBOX:
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORDLG:
			ret = OnCtlColor((HDC)wParam, GetDlgCtrlID((HWND)lParam));
			break;
		case WM_SOCKET_MSG:
			OnSocket(wParam, lParam);
			break;
		default:
			ret = OnOtherMsgHandle(hwnd, msg, wParam, lParam);
			break;
		}

		CdList<CSelfCtrl*>::iterator it = m_dlsc.begin();
		CdList<CSelfCtrl*>::iterator end = m_dlsc.end();
		while (it != end)
		{
			(*it)->MsgHandle(hwnd, msg, wParam, lParam);
			++it;
		}

		return ret;
	}
	/********************************************************
	*	成员函数功能：初始化处理
	*	参数：无
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::OnInit()
	{

	}
	/********************************************************
	*	成员函数功能：简单控件消息处理(按钮按下/菜单点击)
	*	参数：id 控件/菜单ID
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp::OnCommand(TCUQ(int) id, TCUQ(int) msg)
	{
	}
	/********************************************************
	*	成员函数功能：复杂控件消息处理
	*	参数：
	*		id 控件ID
	*		code 事件
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::OnNotify(TCUQ(int) id, TCUQ(int) code)
	{

	}
	/********************************************************
	*	成员函数功能：窗口重新绘制消息
	*	参数：hdc 绘图句柄
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::OnPaint(TCQ(HDC) hdc)
	{

	}
	/********************************************************
	*	成员函数功能：窗口大小改变消息
	*	参数：
	*		width  新的宽度
	*		height 新的高度
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::OnSize(TCUQ(int) width, TCUQ(int) height)
	{

	}
	/********************************************************
	*	成员函数功能：窗口关闭消息
	*	参数：无
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::OnClose()
	{
		Hide();
		Exit();
	}
	/********************************************************
	*	成员函数功能：定时器消息
	*	参数：id 定时器ID
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::OnTimer(TCUQ(int) id)
	{

	}
	/********************************************************
	*	成员函数功能：鼠标消息(左、中、右)键(按下/抬起/双击)、移动、移入、移出、滚轮
	*	参数：
	*		msg 消息类型
	*		wParam 消息参数
	*		lParam 消息参数
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::OnMouse(TCQ(int) msg, TCQ(WPARAM) wParam, TCQ(LPARAM) lParam)
	{

	}
	/********************************************************
	*	成员函数功能：控件自绘制消息
	*	参数：
	*		hdc 绘画句柄
	*		id 控件ID
	*	返回：无
	*	时间：2020-08-18
	*/
	UINT CApp1::OnCtlColor(TCQ(HDC) hdc, TCUQ(int) id)
	{
		return FALSE;
	}
	/********************************************************
	*	成员函数功能：网络消息
	*	参数：
	*		wParam 消息参数
	*		lParam 消息参数
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::OnSocket(TCQ(WPARAM) wParam, TCQ(LPARAM) lParam)
	{

	}
	/********************************************************
	*	成员函数功能：其他未处理的消息
	*	参数：消息参数
	*	返回：无
	*	时间：2020-08-18
	*/
	BOOL CApp1::OnOtherMsgHandle(TCQ(HWND) hwnd, TCQ(int) msg, TCQ(WPARAM) wParam, TCQ(LPARAM) lParam)
	{
		return FALSE;
	}

	/********************************************************
	*	成员函数功能：设置窗口图标
	*	参数：IconID 窗口图标ID
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::SetIcon(TCUQ(int) IconID)
	{
		HICON icon = LoadIcon(HINST, MAKEINTRESOURCE(IconID));
		SendMessage(m_hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
		SendMessage(m_hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
		DeleteObject(icon);
	}
	/********************************************************
	*	成员函数功能：设置窗口菜单
	*	参数：MenuID 窗口菜单ID
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::SetMenu(TCUQ(int) MenuID)
	{
		HMENU menu = LoadMenu(HINST, MAKEINTRESOURCE(MenuID));
		::SetMenu(m_hwnd, menu);

		DeleteObject(menu);
	}
	/********************************************************
	*	成员函数功能：设置窗口内控件(子窗口)的大小
	*	参数：
	*		id		控件ID
	*		width   宽度
	*		height  高度
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::SetCtrlSize(TCUQ(int) id, TCUQ(int) width, TCUQ(int) height)
	{
		CHwnd h;
		h.SetHwnd(m_hwnd, id);
		h.SetSize(width, height);
	}
	/********************************************************
	*	成员函数功能：设置窗口内控件(子窗口)的大小
	*	参数：
	*		id		控件ID
	*		x		x坐标
	*		y		y坐标
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::SetCtrlPos(TCUQ(int) id, TCUQ(int) x, TCUQ(int) y)
	{
		CHwnd h;
		h.SetHwnd(m_hwnd, id);
		h.SetPos(x, y);
	}
	/********************************************************
	*	成员函数功能：设置控件标题
	*	参数：
	*		id		控件ID
	*		str		控件标题
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::SetCtrlText(TCUQ(int) id, TCP(char) str)
	{
		SetDlgItemText(m_hwnd, id, str);
	}
	/********************************************************
	*	成员函数功能：设置控件标题(int)
	*	参数：
	*		id		控件ID
	*		value	控件标题
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::SetCtrlInt(TCUQ(int) id, TCQ(int) value)
	{
		SetDlgItemInt(m_hwnd, id, value, TRUE);
	}
	/********************************************************
	*	成员函数功能：设置控件使能
	*	参数：
	*		id			控件ID
	*		isEnable	是否使能
	*	返回：无
	*	时间：2020-08-18
	*/
	void CApp1::SetCtrlEnable(TCUQ(int) id, TCUQ(int) isEnable)
	{
		EnableWindow(GetDlgItem(m_hwnd, id), isEnable);
	}
	/********************************************************
	*	成员函数功能：获取窗口标题
	*	参数：
	*		id			控件ID
	*	返回：CStr 控件标题
	*	时间：2020-08-18
	*/
	CStr CApp1::GetCtrlText(TCUQ(int) id)
	{
		CStr str;
		uint size = SNDMSG(GetDlgItem(m_hwnd, id), WM_GETTEXTLENGTH, 0, 0) + 1;
		GetDlgItemText(m_hwnd, id, str.get_buffer_set_length(size), size);
		return str;
	}
	/********************************************************
	*	成员函数功能：获取窗口标题(int)
	*	参数：
	*		id			控件ID
	*	返回：int 控件标题
	*	时间：2020-08-18
	*/
	int CApp1::GetCtrlInt(TCUQ(int) id)
	{
		return GetDlgItemInt(m_hwnd, id, NULL, TRUE);
	}
	/********************************************************
	*	成员函数功能：退出窗口
	*	参数：exitCode 退出代码
	*	返回：无
	*	时间：2020-08-17
	*/
	void CApp1::Exit()
	{
		m_closeFlg = TRUE;
		PostQuitMessage(0);
	}
	/********************************************************
	*	成员函数功能：设置定时器
	*	参数：
	*		id	定时器ID
	*		ms	每次定时的时间，单位ms
	*	返回：无
	*	时间：2020-08-17
	*/
	void CApp1::SetTimer(TCUQ(int) id, TCUQ(int) ms)
	{
		::SetTimer(m_hwnd, id, ms, NULL);
	}
	/********************************************************
	*	成员函数功能：删除定时器
	*	参数：
	*		id	定时器ID
	*	返回：无
	*	时间：2020-08-17
	*/
	void CApp1::KillTimer(TCUQ(int) id)
	{
		::KillTimer(m_hwnd, id);
	}
	/********************************************************
	*	成员函数功能：添加自定义控件指针
	*	参数：p 控件指针
	*	返回：无
	*	时间：2020-08-17
	*/
	void CApp1::AddSelfCtrl(CSelfCtrl* p)
	{
		m_dlsc.push_back(p);
	}
	/********************************************************
	*	成员函数功能：MessageBox
	*	参数：同MessageBox
	*	返回：无
	*	时间：2020-08-17
	*/
	void CApp1::MsgBox(TCPCH text, TCPCH title, TCQ(UINT) uType)
	{
		MessageBox(m_hwnd, text, title, uType);
	}
	void CApp1::DrawBitmap(TCQ(HDC) hdc, TCPCH path, TCQ(RECT) r, TCQ(UINT) Mode)
	{
		int y = r.left;
		int x = r.top;
		int h = r.right;
		int w = r.bottom;
		HDC mdc = CreateCompatibleDC(hdc);
		//创建一个与指定设备兼容的内存设备上下文环境
		HBITMAP bg = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, w, h, LR_LOADFROMFILE);
		//加载一张指定了路径的bmp图片，此图片大小为w*h，用这个函数之前需要知道这张图的大小，分别填写在第4、5个参数里 ，第二个参数中填图片路径
		SelectObject(mdc, bg);
		//选入设备环境
		BitBlt(hdc, x, y, w, h, mdc, 0, 0, Mode);
		//删除资源
		DeleteObject(bg);
		DeleteDC(mdc);
	}
	void CApp1::DrawBitmap(TCQ(HDC) hdc, TCQ(UINT) id, TCQ(RECT) r, TCQ(UINT) Mode)
	{
		int y = r.left;
		int x = r.top;
		int h = r.right;
		int w = r.bottom;
		HDC mdc = CreateCompatibleDC(hdc);
		//创建一个与指定设备兼容的内存设备上下文环境
		HINSTANCE hinst = (HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE);
		HBITMAP bmp = LoadBitmap(hinst, MAKEINTRESOURCE(id));
		SelectObject(mdc, bmp);
		//选入设备环境
		BitBlt(hdc, x, y, w, h, mdc, 0, 0, Mode);
		//删除资源
		DeleteObject(bmp);
		DeleteDC(mdc);
	}
	void CApp1::DrawBitmap(TCQ(HDC) hdc, TCQ(HBITMAP) bmp, TCQ(RECT) r, TCQ(UINT) Mode)
	{
		int y = r.left;
		int x = r.top;
		int h = r.right;
		int w = r.bottom;
		HDC mdc = CreateCompatibleDC(hdc);
		//创建一个与指定设备兼容的内存设备上下文环境
		HINSTANCE hinst = (HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE);
		SelectObject(mdc, bmp);
		//选入设备环境
		BitBlt(hdc, x, y, w, h, mdc, 0, 0, Mode);
		//删除资源
		DeleteDC(mdc);
	}
	/********************************************************
	*	成员函数功能：获取控件位置
	*	参数：
	*		id	控件id
	*		x	x坐标(输出)
	*		y	y坐标(输出)
	*	返回：无
	*	时间：2020-09-24
	*/
	void CApp1::GetCtrlPos(TCUQ(int) id, int& x, int& y)
	{
		RECT rc;
		POINT pt;

		::GetWindowRect(GetDlgItem(m_hwnd, id), &rc);

		pt.y = rc.top;
		pt.x = rc.left;

		ScreenToClient(GetSafeHwnd(), &pt);

		x = pt.x;
		y = pt.y;
	}
	/********************************************************
	*	成员函数功能：获取控件显示与隐藏
	*	参数：
	*		id		控件id
	*		isShow	是否显示
	*	返回：无
	*	时间：2020-09-24
	*/
	void CApp1::SetCtrlShow(TCUQ(int) id, TCQ(BOOL) isShow)
	{
		::ShowWindow(GetDlgItem(m_hwnd, id), isShow);
	}
	/********************************************************
	*	成员函数功能：设置菜单项选中
	*	参数：
	*		id		菜单id
	*		isShow	是否选中
	*	返回：无
	*	时间：2020-09-24
	*/
	void CApp1::SetMenuCheck(TCUQ(int) id, TCQ(BOOL) isCheck)
	{
		HMENU menu;

		menu = GetMenu(m_hwnd);

		CheckMenuItem(menu, id, isCheck == FALSE ? MF_UNCHECKED : MF_CHECKED);
	}
	/********************************************************
	*	成员函数功能：设置菜单项使能
	*	参数：
	*		id		菜单id
	*		isShow	是否使能
	*	返回：无
	*	时间：2020-09-24
	*/
	void CApp1::SetMenuEnable(TCUQ(int) id, TCQ(BOOL) isEnable)
	{
		HMENU menu;

		menu = GetMenu(m_hwnd);

		EnableMenuItem(menu, id, isEnable == FALSE ? MF_DISABLED : MF_ENABLED);
	}
}

