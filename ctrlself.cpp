#include "ctrlself.h"
#include "Reg.h"
#include "win.h"

namespace lmw
{
	CSelfCtrl::CSelfCtrl(TCQ(int) x, TCQ(int) y, TCQ(int) width, TCQ(int) height, SC_TYPE mode)
	{
		m_rc.top = y;
		m_rc.left = x;
		m_rc.bottom = height + y;
		m_rc.right = width + x;

		if (SCS_RECT == mode)
		{
			m_rgn.CreateRectRgn(m_rc);
		}
		else if (SCS_ELLIPTIC == mode)
		{
			m_rgn.CreateEllipticRgn(m_rc);
		}
	}
	CSelfCtrl::CSelfCtrl(const RECT& rc, SC_TYPE mode)
	{
		m_rc = rc;
		if (SCS_RECT == mode)
		{
			m_rgn.CreateRectRgn(m_rc);
		}
		else if (SCS_ELLIPTIC == mode)
		{
			m_rgn.CreateEllipticRgn(m_rc);
		}
	}
	
	CSPushButton::CSPushButton(TCQ(int) x, TCQ(int) y, TCQ(int) width, TCQ(int) height) :
		CSelfCtrl(x, y, width, height)
	{
		m_enter = FALSE;
	}
	CSPushButton::CSPushButton(const RECT& rc) :
		CSelfCtrl(rc)
	{
		m_enter = FALSE;
	}
	void CSPushButton::SetImage(TCQ(UINT) ImgId, TCQ(UINT) BkImgId)
	{
		m_ImgId = ImgId;
		m_BkImgId = BkImgId;
	}
	void CSPushButton::MsgHandle(const HWND& hwnd, const UINT& msg,
		const WPARAM& wParam, const LPARAM& lParam)
	{
		HDC hdc, mdc;
		HBITMAP bmp;

		switch (msg)
		{
		case WM_PAINT:
			hdc = GetDC(hwnd);
			m_rgn.Fill(hdc, RGB(0xFF, 0xFF, 0));

			bmp = GetBitmap(m_enter ? m_ImgId : m_BkImgId);
			mdc = CreateCompatibleDC(hdc);
			SelectObject(mdc, bmp);
			//选入设备环境
			BitBlt(hdc, 0, 0, 26, 10, mdc, 26, 0, SRCCOPY);
			
			DeleteObject(bmp);
			DeleteDC(mdc);
			ReleaseDC(hwnd, hdc);
			break;
		case WM_LBUTTONDOWN:
			if (TRUE == m_rgn.HavePoint(LOWORD(lParam), HIWORD(lParam)))
			{
				m_enter = TRUE;
			}
			break;
		case WM_LBUTTONUP:
			if (TRUE == m_rgn.HavePoint(LOWORD(lParam), HIWORD(lParam)))
			{
				MessageBox(hwnd, TEXT("自定义控件"), 0, MB_OK);
				m_enter = FALSE;
			}
			break;
		}
	}

	CSLink::CSLink(TCQ(int) x, TCQ(int) y, TCQ(int) width, TCQ(int) height, TCQ(CStr) link) :
		CSelfCtrl(x, y, width, height)
	{
		m_link = link;
		m_hIcon = NULL;
		m_pStatic = nullptr;
	}
	CSLink::CSLink(const RECT& rc, TCQ(CStr) link) :
		CSelfCtrl(rc)
	{
		m_link = link;
		m_hIcon = NULL;
		m_pStatic = nullptr;
	}
	CSLink::~CSLink()
	{
		if (NULL != m_hIcon)
		{
			DeleteObject(m_hIcon);
		}
		if (m_pStatic != nullptr)
		{
			delete m_pStatic;
		}
	}
	void CSLink::SetTextTip(TCPCH tip)
	{
		m_tip = tip;
	}
	void CSLink::MsgHandle(TCQ(HWND) hwnd, TCUQ(int) msg,
		TCQ(WPARAM) wParam, TCQ(LPARAM) lParam)
	{
		HDC hdc;

		switch (msg)
		{
		case WM_PAINT:
			hdc = GetDC(hwnd);
			OnDraw(hdc);
			ReleaseDC(hwnd, hdc);
			break;

		case WM_LBUTTONDOWN:
			if (TRUE == m_rgn.HavePoint(LOWORD(lParam), HIWORD(lParam)))
			{
				ShellExecute(NULL, "open", m_link.c_str(), NULL, NULL, SW_SHOWMAXIMIZED);
			}
		case WM_MOUSEMOVE:
			if (m_pStatic != nullptr)
			{
				if (TRUE == m_rgn.HavePoint(LOWORD(lParam), HIWORD(lParam)))
				{
					m_pStatic->Show();
				}
				else
				{
					m_pStatic->Hide();
				}
			}
			break;
		}
	}
	void CSLink::SetIcon(TCQ(int) id)
	{
		m_hIcon = LoadIcon(HINST, MAKEINTRESOURCE(id));
	}
	void CSLink::OnDraw(TCQ(HDC) hdc)
	{
		if (NULL == m_hIcon)
		{
			UINT h = DrawTipText(hdc);
			DrawBottomLine(hdc, h);
		}
		else
		{
			DrawShowIcon(hdc);
		}
	}
	void CSLink::DrawShowIcon(TCQ(HDC) hdc)
	{
		DrawIcon(hdc, m_rc.left, m_rc.top, m_hIcon);
	}
	UINT CSLink::DrawTipText(TCQ(HDC) hdc)
	{
		SetTextColor(hdc, RGB(0, 0, 0XFF));
		SetBkMode(hdc, TRANSPARENT);
		if (0 == m_tip.size())
		{
			m_tip = m_link;
		}

		m_rc.bottom = 0;
		m_rc.right = 0;
		DrawText(hdc, (char*)m_tip.c_str(), -1, &m_rc, DT_CALCRECT);
		return DrawTextExA(hdc, (char*)m_tip.c_str(), -1, &m_rc,
			DT_LEFT | DT_VCENTER | DT_SINGLELINE, NULL);
	}
	void CSLink::DrawBottomLine(TCQ(HDC) hdc, TCUQ(int) height)
	{
		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0xff)); // 创建画笔
		SelectObject(hdc, hPen);

		MoveToEx(hdc, m_rc.left, m_rc.top + height + 3, NULL);
		LineTo(hdc, m_rc.right, m_rc.top + height + 3);

		DeleteObject(hPen);
	}
	void CSLink::SetLinkTip(TCQ(HWND) hParent, TCUQ(int) id)
	{
		m_pStatic = new CStatic(hParent, id);
		m_pStatic->Hide();
		m_pStatic->SetPos(m_rc.left, m_rc.top + 30);
		m_pStatic->SetSize(500, 30);
		m_pStatic->SetTitle(m_link.c_str());
	}
}









