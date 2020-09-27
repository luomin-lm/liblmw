#include "win.h"

namespace lmw
{
	/********************************************************
	*	��Ա�������ܣ����캯������ʼ������Ĭ��ΪNULL
	*	������hwnd ��ʼ���ھ��
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	CHwnd::CHwnd(TCQ(HWND) hwnd)
	{
		m_hwnd = hwnd;
	}
	/********************************************************
	*	��Ա�������ܣ���ȡ��ȫ�Ĵ��ھ��(�����޸�)
	*	��������
	*	���أ��������ھ��
	*	ʱ�䣺2020-08-17
	*/
	TCQ(HWND) CHwnd::GetSafeHwnd()
	{
		return m_hwnd;
	}
	/********************************************************
	*	��Ա�������ܣ����ô��ھ��
	*	������hwnd ���ھ��
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::SetHwnd(TCQ(HWND) hwnd)
	{
		m_hwnd = hwnd;
	}
	/********************************************************
	*	��Ա�������ܣ����õ�ǰ���ھ��Ϊ�Ӵ��ھ��
	*	������
	*		hwnd	�����ھ��
	*		id		�Ӵ���ID
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::SetHwnd(TCQ(HWND) hParent, TCQ(int) id)
	{
		m_hwnd = GetDlgItem(hParent, id);
	}
	/********************************************************
	*	��Ա�������ܣ���ѯ���ڣ�������
	*	������
	*		clsName		��������
	*		windowName	���ڱ���
	*	���أ���
	*	ʱ�䣺2020-08-17
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
	*	��Ա�������ܣ���ѯ���ڣ�������
	*	������
	*		hParent		������
	*		hwnd		�Ӵ��ھ�������ڱ�������
	*		clsName		��������
	*		windowName	���ڱ���
	*	���أ���
	*	ʱ�䣺2020-08-17
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
	*	��Ա�������ܣ��򴰿ڷ�����Ϣ
	*	������
	*		Msg		��Ϣ
	*		wParam	��Ϣ����
	*		lParam	��Ϣ����
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	UINT CHwnd::SendMsg(TCQ(UINT) Msg, TCQ(WPARAM) wParam, TCQ(LPARAM) lParam)
	{
		return SendMessage(m_hwnd, Msg, wParam, lParam);
	}
	/********************************************************
	*	��Ա�������ܣ���ʾ�������
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::Show()
	{
		ShowWindow(m_hwnd, SW_RESTORE);
	}
	/********************************************************
	*	��Ա�������ܣ����ش���
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::Hide()
	{
		ShowWindow(m_hwnd, SW_HIDE);
	}
	/********************************************************
	*	��Ա�������ܣ����´���(�ػ�)
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::Update()
	{
		UpdateWindow(m_hwnd);
	}
	/********************************************************
	*	��Ա�������ܣ����´���(�ػ�)
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::Update(TCQ(RECT) rc, TCQ(BOOL) isErase)
	{
		InvalidateRect(m_hwnd, &rc, isErase);
	}
	/********************************************************
	*	��Ա�������ܣ����ô���ʹ��(�Ƿ������Ϣ)
	*	������isEnable		�Ƿ�ʹ�ܣ�TRUE�ǣ�FALSE��
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::SetEnable(TCQ(BOOL) isEnable)
	{
		EnableWindow(m_hwnd, isEnable);
	}
	/********************************************************
	*	��Ա�������ܣ����ô���λ��(�������Ϸ��ٸ����ڵĵ�����<x, y>)
	*	������
	*		x	x���꣬������
	*		y	y���꣬������
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::SetPos(TCQ(int) x, TCQ(int) y)
	{
		SetWindowPos(m_hwnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	/********************************************************
	*	��Ա�������ܣ����ô��ڴ�С(����)
	*	������
	*		width	���ڿ�
	*		height	���ڸ�
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::SetSize(TCQ(int) width, TCQ(int) height)
	{
		SetWindowPos(m_hwnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
	}
	/********************************************************
	*	��Ա�������ܣ����ù̶��Ĵ��ڴ�С(����)
	*	������
	*		width	���ڿ�
	*		height	���ڸ�
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::SetFixedSize(TCQ(int) width, TCQ(int) height)
	{
		SetWindowPos(m_hwnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
		/* ɾ��WS_THICKFRAME���ȥ���϶���С�Ĺ��� */
		SetWindowLong(m_hwnd, GWL_STYLE, GetWindowLong(m_hwnd, GWL_STYLE) & ~WS_THICKFRAME);
	}
	/********************************************************
	*	��Ա�������ܣ����ô��ڷ��
	*	������style �����õķ��
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::SetStyle(TCUQ(int) style)
	{
		SetWindowLong(m_hwnd, GWL_STYLE, style);
	}
	/********************************************************
	*	��Ա�������ܣ����ô�����չ���
	*	������exStyle �����õ���չ���
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::SetStyleEx(TCUQ(int) exStyle)
	{
		SetWindowLong(m_hwnd, GWL_EXSTYLE, exStyle);
	}
	/********************************************************
	*	��Ա�������ܣ���ȡ���ڷ��
	*	��������
	*	���أ����ڷ��
	*	ʱ�䣺2020-08-17
	*/
	TU(int) CHwnd::GetStyle()
	{
		return GetWindowLong(m_hwnd, GWL_STYLE);
	}
	/********************************************************
	*	��Ա�������ܣ���ȡ������չ���
	*	��������
	*	���أ���ȡ������չ���
	*	ʱ�䣺2020-08-17
	*/
	TU(int) CHwnd::GetStyleEx()
	{
		return GetWindowLong(m_hwnd, GWL_EXSTYLE);
	}
	/********************************************************
	*	��Ա�������ܣ���Ӵ��ڷ��
	*	������style ���(WS_*)
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::AddStyle(TCUQ(int) style)
	{
		SetWindowLong(m_hwnd, GWL_STYLE, GetWindowLong(m_hwnd, GWL_STYLE) | style);
	}
	/********************************************************
	*	��Ա�������ܣ���Ӵ�����չ���
	*	������exStyle ���(WS_*)
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::AddExStyle(TCUQ(int) exStyle)
	{
		SetWindowLong(m_hwnd, GWL_EXSTYLE, GetWindowLong(m_hwnd, GWL_EXSTYLE) | exStyle);
	}
	/********************************************************
	*	��Ա�������ܣ�ɾ�����ִ��ڷ��
	*	������style ���(WS_*)
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::DelStyle(TCUQ(int) style)
	{
		SetWindowLong(m_hwnd, GWL_STYLE, GetWindowLong(m_hwnd, GWL_STYLE) & ~style);
	}
	/********************************************************
	*	��Ա�������ܣ�ɾ�����ִ�����չ���
	*	������exStyle ���(WS_*)
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::DelExStyle(TCUQ(int) exStyle)
	{
		SetWindowLong(m_hwnd, GWL_EXSTYLE, GetWindowLong(m_hwnd, GWL_EXSTYLE) & ~exStyle);
	}
	/********************************************************
	*	��Ա�������ܣ����ô��ڶ���
	*	������isTop �Ƿ��ö�(Ĭ��Ϊ����)
	*	���أ���
	*	ʱ�䣺2020-08-17
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
	*	��Ա�������ܣ���ȡ�ͻ�������
	*	��������
	*	���أ�RECT(left = 0, top = 0, right = width, bottom = height)
	*	ʱ�䣺2020-08-17
	*/
	RECT CHwnd::GetClientRect()
	{
		RECT rc;
		::GetClientRect(m_hwnd, &rc);
		return rc;
	}
	/********************************************************
	*	��Ա�������ܣ���ȡ��������
	*	��������
	*	���أ�RECT(left = x1, top = y1, right = x2, bottom = y2)
	*	ʱ�䣺2020-08-17
	*/
	RECT CHwnd::GetWindowRect()
	{
		RECT rc;
		::GetWindowRect(m_hwnd, &rc);
		return rc;
	}
	/********************************************************
	*	��Ա�������ܣ����ô��ڱ���
	*	������str ���ڱ����ַ���
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::SetTitle(TCP(char) str)
	{
		SetWindowText(m_hwnd, str);
	}
	/********************************************************
	*	��Ա�������ܣ����ô��ڱ���
	*	������str ���ڱ����ַ���
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::GetTitle(TP(char) strbuff, TCUQ(int) bufflen)
	{
		GetWindowText(m_hwnd, strbuff, bufflen);
	}
	/********************************************************
	*	��Ա�������ܣ����ô�����״
	*	������hRgn ��������
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::SetRgn(const HRGN& hRgn)
	{
		SetWindowRgn(m_hwnd, hRgn, TRUE);
	}
	/********************************************************
	*	��Ա�������ܣ���󻯴���
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::MaxWindow()
	{
		SendMsg(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	}
	/********************************************************
	*	��Ա�������ܣ���С������
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::MinWindow()
	{
		SendMsg(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	}
	/********************************************************
	*	��Ա�������ܣ������ļ���ק����
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-17
	*	ע�ͣ���ӦWM_DROPFILES��Ϣ��ʵ����ק����
	*/
	void CHwnd::SetAcceptDrops()
	{
		AddExStyle(WS_EX_ACCEPTFILES);
	}
	/********************************************************
	*	��Ա�������ܣ����ô���͸����
	*	������value ͸����(0 - 255)
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	BOOL CHwnd::SetAlpha(TCUQ(char) value)
	{
		AddExStyle(WS_EX_LAYERED);
		return SetLayeredWindowAttributes(GetSafeHwnd(), RGB(0, 0, 0), value, LWA_ALPHA);
	}
	/********************************************************
	*	��Ա�������ܣ����ô���͸����ɫ
	*	������color ͸��ɫ(RGB��)
	*	���أ��Ƿ�ɹ�
	*	ʱ�䣺2020-08-17
	*/
	BOOL CHwnd::SetTransparentColor(TCQ(COLORREF) color)
	{
		AddExStyle(WS_EX_LAYERED);
		return SetLayeredWindowAttributes(GetSafeHwnd(), color, 0, LWA_COLORKEY);
	}
	/********************************************************
	*	��Ա�������ܣ���ȡ�����������
	*	������
	*		str		�����ڴ��׵�ַ
	*		bufflen	�����С
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::GetClsName(TP(char) str, TCUQ(int) bufflen)
	{
		GetClassName(m_hwnd, str, bufflen);
	}
	/********************************************************
	*	��Ա�������ܣ���������
	*	������font ������
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CHwnd::SetFont(HFONT font)
	{
		SendMsg(WM_SETFONT, (WPARAM)font, TRUE);
	}
	/********************************************************
	*	��Ա�������ܣ����ô��ھ���
	*	��������
	*	���أ���
	*	ʱ�䣺2020-09-03
	*/
	void CHwnd::SetCenterPos()
	{
		RECT rc = GetClientRect();
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;

		SetPos((width - rc.right) / 2, (height - rc.bottom) / 2);
	}
}


