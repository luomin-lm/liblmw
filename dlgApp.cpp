#include "win.h"

namespace lmw
{
	/********************************************************
	*	全局函数功能：消息循环
	*	参数：消息参数
	*	返回：
	*	时间：2020-08-18
	*/
	LRESULT CALLBACK Func_dlg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		CDlgApp *dlg = (CDlgApp*)GetWindowLong(hwnd, GWL_USERDATA);

		if (dlg != NULL){
			return dlg->MsgHandle(hwnd, message, wParam, lParam);
		}

		if (message == WM_INITDIALOG){
			dlg = (CDlgApp*)lParam;
			dlg->SetHwnd(hwnd);
			SetWindowLong(hwnd, GWL_USERDATA, (UINT)dlg);

			dlg->OnInit();
			return TRUE;
		}

		return FALSE;
	}
	/********************************************************
	*	成员函数功能：显示对话框
	*	参数：
	*		dlgId		对话框ID
	*		parentHWND	父窗口句柄
	*	返回：是否创建成功
	*	时间：2020-08-18
	*/
	BOOL CDlgApp::Show(TCQ(int) dlgId, TCQ(HWND) parentHWND)
	{
		m_hwnd = CreateDialogParamA(HINST, MAKEINTRESOURCE(dlgId), NULL, (DLGPROC)Func_dlg, (LPARAM)this);

		if (NULL == m_hwnd)
		{
			return FALSE;
		}

		::ShowWindow(m_hwnd, SW_NORMAL);
		::UpdateWindow(m_hwnd);

		return TRUE;
	}
	/********************************************************
	*	成员函数功能：显示模态对话框(直接进入消息循环)
	*	参数：
	*		dlgId		对话框ID
	*		lastApp		上一个窗口
	*	返回：是否创建成功
	*	时间：2020-08-18
	*/
	UINT CDlgApp::DoModal(const UINT& dlgId, CApp* lastApp)
	{
		m_nResult = 0;
		if (nullptr != lastApp)
		{
			lastApp->SetEnable(FALSE);
		}
		Show(dlgId);
		this->MsgLoop();
		if (nullptr != lastApp)
		{
			lastApp->SetEnable(TRUE);
		}
		return m_nResult;
	}
	/********************************************************
	*	成员函数功能：退出消息循环
	*	参数：exitCode 退出码,DoModal函数返回值
	*	返回：是否创建成功
	*	时间：2020-08-18
	*/
	void CDlgApp::EndDialog(const int& exitCode)
	{
		m_nResult = exitCode;
		Exit();
	}
}






