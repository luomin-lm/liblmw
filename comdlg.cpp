#include "win.h"

namespace lmw
{
	BOOL CComDlg::OpenFileDlg(TCQ(HWND) hwnd, CStr& filepath, TCPCH filter, TCPCH title, TCPCH initDir)
	{
		OPENFILENAME ofn = { 0 };
		BOOL result = FALSE;

		char szBuffer[1024] = { 0 };
		if (0 != filepath.size())
		{
			strcpy(szBuffer, filepath.c_str());
		}

		ofn.hwndOwner = hwnd;
		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFilter = filter;//Ҫѡ����ļ���׺
		ofn.lpstrInitialDir = initDir;//Ĭ�ϵ��ļ�·��
		ofn.lpstrFile = szBuffer;//����ļ��Ļ�����
		ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
		ofn.nFilterIndex = 0;
		ofn.lpstrTitle = title;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;//��־����Ƕ�ѡҪ����OFN_ALLOWMULTISELECT

		result = GetOpenFileNameA(&ofn);

		filepath = szBuffer;

		if (result == TRUE){
			result = ofn.nFileExtension; // ������չ����ʼλ��
		}
		return result;
	}
	BOOL CComDlg::SaveFileDlg(TCQ(HWND) hwnd, CStr& filepath, TCPCH filter,	TCPCH title, TCPCH initDir)
	{
		OPENFILENAME ofn = { 0 };
		BOOL result = FALSE;

		char szBuffer[1024] = { 0 };
		if (0 != filepath.size())
		{
			strcpy(szBuffer, filepath.c_str());
		}

		ofn.hwndOwner = hwnd;
		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFilter = filter;//Ҫѡ����ļ���׺
		ofn.lpstrInitialDir = initDir;//Ĭ�ϵ��ļ�·��
		ofn.lpstrFile = szBuffer;//����ļ��Ļ�����
		ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
		ofn.nFilterIndex = 0;
		ofn.lpstrTitle = title;
		ofn.Flags = OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT;
		//����û�������һ�������ڵ��ļ������Ի������û����ʡ��Ƿ����ļ��� | �ڡ����桱�ļ��Ի�����ʹ�ù���ʱ�򣬵�ѡ��һ���Ѵ��ڵ��ļ�ʱ���Ի�������ʡ��Ƿ񸲸��ļ�����

		result = GetSaveFileNameA(&ofn);

		filepath = szBuffer;

		if (result == TRUE){
			result = ofn.nFileExtension; // ������չ����ʼλ��
		}
		return result;
	}
	BOOL CComDlg::FontSetDlg(TCQ(HWND) hwnd, HFONT* pFont)
	{
		CHOOSEFONT cf = { 0 };
		LOGFONT lf = { 0 };
		BOOL result = FALSE;

		lf.lfHeight = 15;
		lf.lfWidth = FW_NORMAL;
		lf.lfCharSet = DEFAULT_CHARSET;
		strcpy_s(lf.lfFaceName, "����");

		cf.hwndOwner = hwnd;
		cf.lStructSize = sizeof(CHOOSEFONT);	//	��ʼ���ṹ���С
		cf.lpLogFont = &lf;						//	�߼�����ѡ��
		cf.nFontType = SCREEN_FONTTYPE;			//	ѡ����Ļ����
		cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_EFFECTS | CF_SCREENFONTS;

		result = ChooseFont(&cf);				//	������ѡ��Ի���
		if (TRUE == result)
		{
			*pFont = CreateFontIndirect(cf.lpLogFont);
		}

		return result;
	}
	BOOL CComDlg::ColorSelect(TCQ(HWND) hwnd, COLORREF& color)
	{
		CHOOSECOLOR cor = { 0 };
		BOOL result = FALSE;
		COLORREF crCustColors[16];

		cor.hwndOwner = hwnd;
		cor.lStructSize = sizeof(cor);
		cor.rgbResult = color; // Ĭ��ֵ
		cor.Flags = CC_ANYCOLOR;
		cor.lpCustColors = crCustColors;

		result = ChooseColor(&cor);
		color = cor.rgbResult;

		return result;
	}
}





