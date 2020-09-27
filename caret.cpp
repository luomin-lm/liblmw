#include "win.h"

namespace lmw
{
	CCaret::CCaret(int x, int y)
	{
		m_x = x;
		m_y = y;
	}
	BOOL CCaret::Create(TCQ(HWND) hwnd, TCUQ(int) width, TCUQ(int) height, HBITMAP bmp)
	{
		if (FALSE == CreateCaret(hwnd, bmp, width, height))
		{
			return FALSE;
		}
		return TRUE;
	}
	void CCaret::Show(TCQ(HWND) hwnd)
	{
		ShowCaret(hwnd);
	}
	void CCaret::Hide(TCQ(HWND) hwnd)
	{
		HideCaret(hwnd);
	}
	void CCaret::SetPos(TCQ(int) cx, TCQ(int) cy)
	{
		m_x = cx;
		m_y = cy;
		SetCaretPos(cx, cy);
	}
	void CCaret::SetBlinkTime(TCUQ(int) BlinkTime)
	{
		SetCaretBlinkTime(BlinkTime);
	}
	void CCaret::Destory()
	{
		DestroyCaret();
	}
	void CCaret::GetPos(TQ(int) cx, TQ(int) cy)
	{
		cx = m_x;
		cy = m_y;
	}
}



