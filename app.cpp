#include "win.h"
#include "ctrlself.h"

namespace lmw
{
	// ����Դ�м���λͼ
	HBITMAP GetBitmap(TCUQ(int) id)
	{
		return LoadBitmap(HINST, MAKEINTRESOURCE(id));
	}
	// ���ļ��м���λͼ
	HBITMAP GetBitmap(TCPCH path, TCUQ(int) width, TCUQ(int) height)
	{
		HBITMAP bmp = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
		return bmp;
	}
	// ����Դ�м���ͼ��
	HICON GetIcon(TCUQ(int) id)
	{
		return LoadIcon(HINST, MAKEINTRESOURCE(id));
	}
	// ���ļ��м���ͼ��
	HICON GetIcon(TCPCH path, TCUQ(int) width, TCUQ(int) height)
	{
		return (HICON)LoadImage(NULL, path, IMAGE_ICON, width, height, LR_LOADFROMFILE);
	}
	/********************************************************
	*	��Ա�������ܣ������������ͷſؼ��ڴ�
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-18
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
	*	��Ա�������ܣ���Ϣѭ����ֱ����ǰ�����������Ĵ����˳�
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	int CApp1::MsgLoop()
	{
		MSG msg = { 0 };
		this->m_closeFlg = FALSE;

		do{
			/* ��Ϣѭ�� */
			while (0 != GetMessage(&msg, NULL, 0, 0))
			//while (msg.message != WM_QUIT)
			{
				//if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				//{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				//}
			}
			/* �����ڹر� */
			if (TRUE == this->m_closeFlg)
			{
				return msg.wParam;
			}
		} while (1);

		return 0;
	}
	/********************************************************
	*	��Ա�������ܣ�������Ϣѭ�������ظ��麯��ʵ����Ϣ����
	*	��������
	*	���أ��������Ϣ�򷵻�TRUE��δ������FALSE
	*	ʱ�䣺2020-08-18
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
		case WM_LBUTTONDOWN: // ���
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_MBUTTONDOWN: // �м�
		case WM_MBUTTONUP:
		case WM_MBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK: // �Ҽ�
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MOUSEMOVE: // ����ƶ�
		case WM_MOUSEHOVER: // ����
		case WM_MOUSELEAVE: // �Ƴ�
		case WM_MOUSEHWHEEL: // ����
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
	*	��Ա�������ܣ���ʼ������
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::OnInit()
	{

	}
	/********************************************************
	*	��Ա�������ܣ��򵥿ؼ���Ϣ����(��ť����/�˵����)
	*	������id �ؼ�/�˵�ID
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp::OnCommand(TCUQ(int) id, TCUQ(int) msg)
	{
	}
	/********************************************************
	*	��Ա�������ܣ����ӿؼ���Ϣ����
	*	������
	*		id �ؼ�ID
	*		code �¼�
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::OnNotify(TCUQ(int) id, TCUQ(int) code)
	{

	}
	/********************************************************
	*	��Ա�������ܣ��������»�����Ϣ
	*	������hdc ��ͼ���
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::OnPaint(TCQ(HDC) hdc)
	{

	}
	/********************************************************
	*	��Ա�������ܣ����ڴ�С�ı���Ϣ
	*	������
	*		width  �µĿ��
	*		height �µĸ߶�
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::OnSize(TCUQ(int) width, TCUQ(int) height)
	{

	}
	/********************************************************
	*	��Ա�������ܣ����ڹر���Ϣ
	*	��������
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::OnClose()
	{
		Hide();
		Exit();
	}
	/********************************************************
	*	��Ա�������ܣ���ʱ����Ϣ
	*	������id ��ʱ��ID
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::OnTimer(TCUQ(int) id)
	{

	}
	/********************************************************
	*	��Ա�������ܣ������Ϣ(���С���)��(����/̧��/˫��)���ƶ������롢�Ƴ�������
	*	������
	*		msg ��Ϣ����
	*		wParam ��Ϣ����
	*		lParam ��Ϣ����
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::OnMouse(TCQ(int) msg, TCQ(WPARAM) wParam, TCQ(LPARAM) lParam)
	{

	}
	/********************************************************
	*	��Ա�������ܣ��ؼ��Ի�����Ϣ
	*	������
	*		hdc �滭���
	*		id �ؼ�ID
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	UINT CApp1::OnCtlColor(TCQ(HDC) hdc, TCUQ(int) id)
	{
		return FALSE;
	}
	/********************************************************
	*	��Ա�������ܣ�������Ϣ
	*	������
	*		wParam ��Ϣ����
	*		lParam ��Ϣ����
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::OnSocket(TCQ(WPARAM) wParam, TCQ(LPARAM) lParam)
	{

	}
	/********************************************************
	*	��Ա�������ܣ�����δ�������Ϣ
	*	��������Ϣ����
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	BOOL CApp1::OnOtherMsgHandle(TCQ(HWND) hwnd, TCQ(int) msg, TCQ(WPARAM) wParam, TCQ(LPARAM) lParam)
	{
		return FALSE;
	}

	/********************************************************
	*	��Ա�������ܣ����ô���ͼ��
	*	������IconID ����ͼ��ID
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::SetIcon(TCUQ(int) IconID)
	{
		HICON icon = LoadIcon(HINST, MAKEINTRESOURCE(IconID));
		SendMessage(m_hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
		SendMessage(m_hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
		DeleteObject(icon);
	}
	/********************************************************
	*	��Ա�������ܣ����ô��ڲ˵�
	*	������MenuID ���ڲ˵�ID
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::SetMenu(TCUQ(int) MenuID)
	{
		HMENU menu = LoadMenu(HINST, MAKEINTRESOURCE(MenuID));
		::SetMenu(m_hwnd, menu);

		DeleteObject(menu);
	}
	/********************************************************
	*	��Ա�������ܣ����ô����ڿؼ�(�Ӵ���)�Ĵ�С
	*	������
	*		id		�ؼ�ID
	*		width   ���
	*		height  �߶�
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::SetCtrlSize(TCUQ(int) id, TCUQ(int) width, TCUQ(int) height)
	{
		CHwnd h;
		h.SetHwnd(m_hwnd, id);
		h.SetSize(width, height);
	}
	/********************************************************
	*	��Ա�������ܣ����ô����ڿؼ�(�Ӵ���)�Ĵ�С
	*	������
	*		id		�ؼ�ID
	*		x		x����
	*		y		y����
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::SetCtrlPos(TCUQ(int) id, TCUQ(int) x, TCUQ(int) y)
	{
		CHwnd h;
		h.SetHwnd(m_hwnd, id);
		h.SetPos(x, y);
	}
	/********************************************************
	*	��Ա�������ܣ����ÿؼ�����
	*	������
	*		id		�ؼ�ID
	*		str		�ؼ�����
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::SetCtrlText(TCUQ(int) id, TCP(char) str)
	{
		SetDlgItemText(m_hwnd, id, str);
	}
	/********************************************************
	*	��Ա�������ܣ����ÿؼ�����(int)
	*	������
	*		id		�ؼ�ID
	*		value	�ؼ�����
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::SetCtrlInt(TCUQ(int) id, TCQ(int) value)
	{
		SetDlgItemInt(m_hwnd, id, value, TRUE);
	}
	/********************************************************
	*	��Ա�������ܣ����ÿؼ�ʹ��
	*	������
	*		id			�ؼ�ID
	*		isEnable	�Ƿ�ʹ��
	*	���أ���
	*	ʱ�䣺2020-08-18
	*/
	void CApp1::SetCtrlEnable(TCUQ(int) id, TCUQ(int) isEnable)
	{
		EnableWindow(GetDlgItem(m_hwnd, id), isEnable);
	}
	/********************************************************
	*	��Ա�������ܣ���ȡ���ڱ���
	*	������
	*		id			�ؼ�ID
	*	���أ�CStr �ؼ�����
	*	ʱ�䣺2020-08-18
	*/
	CStr CApp1::GetCtrlText(TCUQ(int) id)
	{
		CStr str;
		uint size = SNDMSG(GetDlgItem(m_hwnd, id), WM_GETTEXTLENGTH, 0, 0) + 1;
		GetDlgItemText(m_hwnd, id, str.get_buffer_set_length(size), size);
		return str;
	}
	/********************************************************
	*	��Ա�������ܣ���ȡ���ڱ���(int)
	*	������
	*		id			�ؼ�ID
	*	���أ�int �ؼ�����
	*	ʱ�䣺2020-08-18
	*/
	int CApp1::GetCtrlInt(TCUQ(int) id)
	{
		return GetDlgItemInt(m_hwnd, id, NULL, TRUE);
	}
	/********************************************************
	*	��Ա�������ܣ��˳�����
	*	������exitCode �˳�����
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CApp1::Exit()
	{
		m_closeFlg = TRUE;
		PostQuitMessage(0);
	}
	/********************************************************
	*	��Ա�������ܣ����ö�ʱ��
	*	������
	*		id	��ʱ��ID
	*		ms	ÿ�ζ�ʱ��ʱ�䣬��λms
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CApp1::SetTimer(TCUQ(int) id, TCUQ(int) ms)
	{
		::SetTimer(m_hwnd, id, ms, NULL);
	}
	/********************************************************
	*	��Ա�������ܣ�ɾ����ʱ��
	*	������
	*		id	��ʱ��ID
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CApp1::KillTimer(TCUQ(int) id)
	{
		::KillTimer(m_hwnd, id);
	}
	/********************************************************
	*	��Ա�������ܣ�����Զ���ؼ�ָ��
	*	������p �ؼ�ָ��
	*	���أ���
	*	ʱ�䣺2020-08-17
	*/
	void CApp1::AddSelfCtrl(CSelfCtrl* p)
	{
		m_dlsc.push_back(p);
	}
	/********************************************************
	*	��Ա�������ܣ�MessageBox
	*	������ͬMessageBox
	*	���أ���
	*	ʱ�䣺2020-08-17
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
		//����һ����ָ���豸���ݵ��ڴ��豸�����Ļ���
		HBITMAP bg = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, w, h, LR_LOADFROMFILE);
		//����һ��ָ����·����bmpͼƬ����ͼƬ��СΪw*h�����������֮ǰ��Ҫ֪������ͼ�Ĵ�С���ֱ���д�ڵ�4��5�������� ���ڶ�����������ͼƬ·��
		SelectObject(mdc, bg);
		//ѡ���豸����
		BitBlt(hdc, x, y, w, h, mdc, 0, 0, Mode);
		//ɾ����Դ
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
		//����һ����ָ���豸���ݵ��ڴ��豸�����Ļ���
		HINSTANCE hinst = (HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE);
		HBITMAP bmp = LoadBitmap(hinst, MAKEINTRESOURCE(id));
		SelectObject(mdc, bmp);
		//ѡ���豸����
		BitBlt(hdc, x, y, w, h, mdc, 0, 0, Mode);
		//ɾ����Դ
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
		//����һ����ָ���豸���ݵ��ڴ��豸�����Ļ���
		HINSTANCE hinst = (HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE);
		SelectObject(mdc, bmp);
		//ѡ���豸����
		BitBlt(hdc, x, y, w, h, mdc, 0, 0, Mode);
		//ɾ����Դ
		DeleteDC(mdc);
	}
	/********************************************************
	*	��Ա�������ܣ���ȡ�ؼ�λ��
	*	������
	*		id	�ؼ�id
	*		x	x����(���)
	*		y	y����(���)
	*	���أ���
	*	ʱ�䣺2020-09-24
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
	*	��Ա�������ܣ���ȡ�ؼ���ʾ������
	*	������
	*		id		�ؼ�id
	*		isShow	�Ƿ���ʾ
	*	���أ���
	*	ʱ�䣺2020-09-24
	*/
	void CApp1::SetCtrlShow(TCUQ(int) id, TCQ(BOOL) isShow)
	{
		::ShowWindow(GetDlgItem(m_hwnd, id), isShow);
	}
	/********************************************************
	*	��Ա�������ܣ����ò˵���ѡ��
	*	������
	*		id		�˵�id
	*		isShow	�Ƿ�ѡ��
	*	���أ���
	*	ʱ�䣺2020-09-24
	*/
	void CApp1::SetMenuCheck(TCUQ(int) id, TCQ(BOOL) isCheck)
	{
		HMENU menu;

		menu = GetMenu(m_hwnd);

		CheckMenuItem(menu, id, isCheck == FALSE ? MF_UNCHECKED : MF_CHECKED);
	}
	/********************************************************
	*	��Ա�������ܣ����ò˵���ʹ��
	*	������
	*		id		�˵�id
	*		isShow	�Ƿ�ʹ��
	*	���أ���
	*	ʱ�䣺2020-09-24
	*/
	void CApp1::SetMenuEnable(TCUQ(int) id, TCQ(BOOL) isEnable)
	{
		HMENU menu;

		menu = GetMenu(m_hwnd);

		EnableMenuItem(menu, id, isEnable == FALSE ? MF_DISABLED : MF_ENABLED);
	}
}

