#include "win.h"

namespace lmw
{
	/********************************************************
	*	ȫ�ֺ������ܣ���Ϣѭ��
	*	��������Ϣ����
	*	���أ�
	*	ʱ�䣺2020-08-18
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
	*	��Ա�������ܣ���ʾ�Ի���
	*	������
	*		dlgId		�Ի���ID
	*		parentHWND	�����ھ��
	*	���أ��Ƿ񴴽��ɹ�
	*	ʱ�䣺2020-08-18
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
	*	��Ա�������ܣ���ʾģ̬�Ի���(ֱ�ӽ�����Ϣѭ��)
	*	������
	*		dlgId		�Ի���ID
	*		lastApp		��һ������
	*	���أ��Ƿ񴴽��ɹ�
	*	ʱ�䣺2020-08-18
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
	*	��Ա�������ܣ��˳���Ϣѭ��
	*	������exitCode �˳���,DoModal��������ֵ
	*	���أ��Ƿ񴴽��ɹ�
	*	ʱ�䣺2020-08-18
	*/
	void CDlgApp::EndDialog(const int& exitCode)
	{
		m_nResult = exitCode;
		Exit();
	}
}






