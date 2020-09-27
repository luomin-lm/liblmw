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
		ofn.lpstrFilter = filter;//要选择的文件后缀
		ofn.lpstrInitialDir = initDir;//默认的文件路径
		ofn.lpstrFile = szBuffer;//存放文件的缓冲区
		ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
		ofn.nFilterIndex = 0;
		ofn.lpstrTitle = title;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;//标志如果是多选要加上OFN_ALLOWMULTISELECT

		result = GetOpenFileNameA(&ofn);

		filepath = szBuffer;

		if (result == TRUE){
			result = ofn.nFileExtension; // 返回扩展名起始位置
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
		ofn.lpstrFilter = filter;//要选择的文件后缀
		ofn.lpstrInitialDir = initDir;//默认的文件路径
		ofn.lpstrFile = szBuffer;//存放文件的缓冲区
		ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
		ofn.nFilterIndex = 0;
		ofn.lpstrTitle = title;
		ofn.Flags = OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT;
		//如果用户输入了一个不存在的文件名，对话框向用户提问“是否建立文件” | 在“保存”文件对话框中使用过的时候，当选择一个已存在的文件时，对话框会提问“是否覆盖文件”。

		result = GetSaveFileNameA(&ofn);

		filepath = szBuffer;

		if (result == TRUE){
			result = ofn.nFileExtension; // 返回扩展名起始位置
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
		strcpy_s(lf.lfFaceName, "楷体");

		cf.hwndOwner = hwnd;
		cf.lStructSize = sizeof(CHOOSEFONT);	//	初始化结构体大小
		cf.lpLogFont = &lf;						//	逻辑字体选择
		cf.nFontType = SCREEN_FONTTYPE;			//	选择屏幕字体
		cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_EFFECTS | CF_SCREENFONTS;

		result = ChooseFont(&cf);				//	打开字体选择对话框
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
		cor.rgbResult = color; // 默认值
		cor.Flags = CC_ANYCOLOR;
		cor.lpCustColors = crCustColors;

		result = ChooseColor(&cor);
		color = cor.rgbResult;

		return result;
	}
}





