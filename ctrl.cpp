#include "win.h"
#define EM_SETCUEBANNER		0x1501

namespace lmw
{
	CCtrl::CCtrl(const HWND& hParent, const UINT& id)
	{
		m_hwnd = GetDlgItem(hParent, id);
	}

	CButton::CButton(const HWND& hParent, const UINT& id, const UINT& style) : CCtrl(hParent, id)
	{
		if (NULL == m_hwnd)
		{
			m_hwnd = CreateWindow(TEXT("BUTTON"), TX(""), style,
				0, 0, 100, 30, hParent, (HMENU)id, (HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE), NULL);
		}
	}
	void CButton::SetCheck(BOOL isCheck)
	{
		PostMessage(m_hwnd, BM_SETCHECK, isCheck == TRUE ? BST_CHECKED : BST_UNCHECKED, 0);
	}
	BOOL CButton::GetCheck()
	{
		if (BST_CHECKED == SendMessage(m_hwnd, BM_GETCHECK, 0, 0))
		{
			return TRUE;
		}
		return FALSE;
	}

	CPushButton::CPushButton(const HWND& hParent, const UINT& id) :
		CButton(hParent, id, WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON)
	{
	}
	CRadioButton::CRadioButton(const HWND& hParent, const UINT& id) :
		CButton(hParent, id, WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON)
	{
	}
	CCheckButton::CCheckButton(const HWND& hParent, const UINT& id) :
		CButton(hParent, id, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX)
	{
	}
	CBitmapButton::CBitmapButton(const HWND& hParent, const UINT& id, const UINT& bmpId) :
		CButton(hParent, id, WS_CHILD | WS_VISIBLE | BS_BITMAP)
	{
		SendMessage(m_hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(HINST, MAKEINTRESOURCE(bmpId)));
	}

	CRadioButtonGroup::CRadioButtonGroup(const HWND& hParent, int nums)
	{
		m_ids = new int[nums];
		m_nums = nums;
		m_hwnd = hParent;
		m_index = 0;
	}
	CRadioButtonGroup::~CRadioButtonGroup()
	{
		delete[] m_ids;
	}
	void CRadioButtonGroup::AddRadioId(const int& id)
	{
		if (m_index < m_nums)
		{
			m_ids[m_index++] = id;
		}
	}
	void CRadioButtonGroup::AddRadioIds(int num, ...)
	{
		va_list arg;
		va_start(arg, num);
		for (int i = 0; i < num; i++)
		{
			m_ids[m_index] = va_arg(arg, int);
			m_index++;
		}
		va_end(arg);
	}
	void CRadioButtonGroup::SetCheckRadioId(const int& id)
	{
		CButton * ctrl = new CButton(m_hwnd, m_ids[0], 0);

		for (int i = 0; i < m_index; i++)
		{
			if (id != m_ids[i])
			{
				ctrl->SetHwnd(m_hwnd, m_ids[i]);
				ctrl->SetCheck(FALSE);
			}
			else
			{
				ctrl->SetHwnd(m_hwnd, m_ids[i]);
				ctrl->SetCheck(TRUE);
			}
		}

		delete ctrl;
	}
	int CRadioButtonGroup::GetCheckRadioId()
	{
		int id = -1;
		CButton * ctrl = new CButton(m_hwnd, m_ids[0], 0);
		if (TRUE == ctrl->GetCheck())
		{
			delete ctrl;
			return 0;
		}

		for (int i = 1; i < m_index; i++)
		{
			ctrl->SetHwnd(m_hwnd, m_ids[i]);
			if (TRUE == ctrl->GetCheck())
			{
				id = i;
				break;
			}
		}

		delete ctrl;
		return id;
	}

	CEdit::CEdit(const HWND& hParent, const UINT& id, const UINT& style)
		: CCtrl(hParent, id)
	{
		if (NULL == m_hwnd)
		{
			m_hwnd = CreateWindow(TEXT("EDIT"), TX(""), style,
				0, 0, 100, 30, hParent, (HMENU)id, (HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE), NULL);
		}
	}
	BOOL CEdit::IsModify()
	{
		return FALSE == SendMsg(EM_GETMODIFY, 0, 0) ? FALSE : TRUE;
	}
	void CEdit::SetTipText(const wchar_t* tipText)
	{
		SendMsg(EM_SETCUEBANNER, FALSE, (LPARAM)tipText);
	}
	void CEdit::SetReadOnly(BOOL isReadOnly)
	{
		SendMsg(EM_SETREADONLY, isReadOnly, 0);
	}
	CLineEdit::CLineEdit(const HWND& hParent, const UINT& id) :
		CEdit(hParent, id, WS_CHILD | WS_BORDER | WS_VISIBLE | ES_MULTILINE | ES_AUTOHSCROLL)
	{

	}
	CPassEdit::CPassEdit(const HWND& hParent, const UINT& id) :
		CEdit(hParent, id, WS_CHILD | WS_BORDER | WS_VISIBLE | ES_PASSWORD)
	{

	}
	void CPassEdit::SetShowChar(TCQ(char) ch)
	{
		SendMsg(EM_SETPASSWORDCHAR, ch, 0);
	}
	CTextEdit::CTextEdit(const HWND& hParent, const UINT& id) :
		CEdit(hParent, id, WS_CHILD | WS_BORDER | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN)
	{

	}
	int CTextEdit::GetLineCount()
	{
		return SendMsg(EM_GETLINECOUNT, 0, 0);
	}
	int CTextEdit::GetLine(TCUQ(int) line, CStr &str)
	{
		int num = 0;
		char tmp[257];
		WORD* pw = (WORD*)tmp;
		*pw = 256;

		num = SendMsg(EM_GETLINE, line, (LPARAM)tmp);

		tmp[num] = 0;
		str = tmp;
		return num;
	}
	int CTextEdit::GetThumb()
	{
		return SendMsg(EM_GETTHUMB, 0, 0);
	}
	int CTextEdit::GetLineIndex(TCUQ(int) line)
	{
		return SendMsg(EM_LINEINDEX, line , 0);
	}
	int CTextEdit::GetLineLength(TCUQ(int) line)
	{
		return SendMsg(EM_LINELENGTH, line, 0);
	}
	CNumEdit::CNumEdit(const HWND& hParent, const UINT& id) :
		CEdit(hParent, id, WS_CHILD | WS_BORDER | WS_VISIBLE | ES_NUMBER)
	{

	}

#define LVS_REPORT              0x0001
#define LVS_EX_GRIDLINES        0x00000001
#define LVS_EX_FULLROWSELECT    0x00000020
#define	LVM_FIRST						0x1000
#define LVM_SETBKCOLOR					(LVM_FIRST + 1)
#define LVM_DELETEALLITEMS				(LVM_FIRST + 9)
#define LVM_INSERTITEM					(LVM_FIRST + 7)
#define LVM_SETITEM						(LVM_FIRST + 6)
#define LVM_INSERTCOLUMN				(LVM_FIRST + 27)
#define LVM_SETCOLUMNWIDTH				(LVM_FIRST + 30)
#define LVM_CREATEDRAGIMAGE				(LVM_FIRST + 33)
#define LVM_SETTEXTCOLOR				(LVM_FIRST + 36)
#define LVM_SETTEXTBKCOLOR				(LVM_FIRST + 38)
#define LVM_GETCOUNTPERPAGE				(LVM_FIRST + 40)
#define LVM_GETITEMTEXT					(LVM_FIRST + 45)
#define LVM_SETICONSPACING				(LVM_FIRST + 53)
#define LVM_SETLISTSTYLE				(LVM_FIRST + 54)
#define LVM_SETEXTENDEDLISTVIEWSTYLE	(LVM_FIRST + 54)
#define LVM_GETSELECTIONMARK			(LVM_FIRST + 66)
#define LVM_SETSELECTIONMARK			(LVM_FIRST + 67)

#define LVIF_TEXT				0x0001
#define LVIF_IMAGE              0x0002
#define LVCF_WIDTH              0x0002
#define LVCF_TEXT               0x0004
#define LVCF_SUBITEM            0x0008
#define LVSCW_AUTOSIZE_USEHEADER    -2

	typedef struct tagLVITEMA
	{
		UINT mask;				//说明LVITEM结构中哪些成员有效
		int iItem;				//项目的索引值(可以视为行号)从0开始
		int iSubItem;			//子项的索引值(可以视为列号)从0开始
		UINT state;				//子项的状态
		UINT stateMask;			//状态有效的屏蔽位
		LPSTR pszText;			//主项或子项的名称
		int cchTextMax;			//pszText所指向的缓冲区大小
		int iImage;				//关联图像列表中指定图像的索引值
		LPARAM lParam;			//程序定义的32位参数
		int iIndent;			//表示图像位置缩进的单位
#if (NTDDI_VERSION >= NTDDI_WINXP)
		int iGroupId;
		UINT cColumns; // tile view columns
		PUINT puColumns;
#endif
#if (NTDDI_VERSION >= NTDDI_VISTA) // Will be unused downlevel, but sizeof(LVITEMA) must be equal to sizeof(LVITEMW)
		int* piColFmt;
		int iGroup; // readonly. only valid for owner data.
#endif
	} LVITEM, *LPLVITEMA;
	typedef struct tagLVCOLUMNA
	{
		UINT mask;					//说明此结构中哪些成员是有效的
		int fmt;					//列的对齐方式
		int cx;						//列的初始宽度
		LPSTR pszText;				//列的标题
		int cchTextMax;				//pszText所指向的缓冲区的大小
		int iSubItem;				//与列关联的子项的索引值，从0开始
		int iImage;					//与列关联的图像列表中指定图像的索引值
		int iOrder;					//第几列，0代表最左一列
#if (NTDDI_VERSION >= NTDDI_VISTA)
		int cxMin;       // min snap point
		int cxDefault;   // default snap point
		int cxIdeal;     // read only. ideal may not eqaul current width if auto sized (LVS_EX_AUTOSIZECOLUMNS) to a lesser width.
#endif
	} LVCOLUMN, *LPLVCOLUMNA;

	CListView::CListView(const HWND& hParent, const UINT& id, const UINT& style) :
		CCtrl(hParent, id)
	{
		if (NULL == m_hwnd)
		{
			m_hwnd = CreateWindow(TEXT("syslistview32"), TX(""), style,
				0, 0, 100, 30, hParent, (HMENU)id, (HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE), NULL);
		}
	}
	void CListView::InsertColumn(const int& index, const char* str, const int& width)
	{
		LVCOLUMN _lvcol;
		memset(&_lvcol, 0, sizeof(LVCOLUMN));
		_lvcol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		_lvcol.pszText = (char*)str;
		_lvcol.cx = width;
		SendMessageA(m_hwnd, LVM_INSERTCOLUMN, index, (LPARAM)&_lvcol);
	}
	void CListView::SetItemText(const int& line, const int& col, const char* str, const int& nImage)
	{
		LVITEM _lvitem;
		memset(&_lvitem, 0, sizeof(LVITEM));
		_lvitem.mask = LVIF_TEXT;
		if (-1 != nImage)
		{
			_lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
			_lvitem.iImage = nImage;
		}

		_lvitem.cchTextMax = MAX_PATH;
		_lvitem.iItem = line;
		_lvitem.iSubItem = col;
		_lvitem.pszText = (char*)str;

		if (col == 0)
			SendMessageA(m_hwnd, LVM_INSERTITEM, 0, LPARAM(&_lvitem));
		else
			SendMessageA(m_hwnd, LVM_SETITEM, 0, LPARAM(&_lvitem));
	}
	void CListView::Clear()
	{
		SendMessage(m_hwnd, LVM_DELETEALLITEMS, 0, 0);
	}
	int CListView::GetSelectItem()
	{
		return (int)SendMessage(m_hwnd, LVM_GETSELECTIONMARK, 0, 0);
	}
	void CListView::SetSelectItem(const int& index)
	{
		SNDMSG(m_hwnd, LVM_SETSELECTIONMARK, 0, (LPARAM)index);
	}
	void CListView::GetItemText(const int& line, const int& col, char* buff, const int& bufflen)
	{
		LVITEM item;

		item.cchTextMax = bufflen;
		item.iSubItem = col;
		item.pszText = buff;

		SendMessage(m_hwnd, LVM_GETITEMTEXT, line, (LPARAM)&item);
	}
	int CListView::GetCount()
	{
		return (int)SendMessage(m_hwnd, LVM_GETCOUNTPERPAGE, 0, 0);
	}
	void CListView::SetBkColor(COLORREF color)
	{
		SNDMSG(m_hwnd, LVM_SETBKCOLOR, 0, color);
		SNDMSG(m_hwnd, LVM_SETTEXTBKCOLOR, 0, color);
	}
	void CListView::SetTextColor(COLORREF color)
	{
		SNDMSG(m_hwnd, LVM_SETTEXTCOLOR, 0, color);
	}
	void CListView::SetExtendStyle(const UINT& style)
	{
		SNDMSG(m_hwnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, style);
	}
	void CListView::SetColumnWidth(const int& index, const int& width)
	{
		SNDMSG(m_hwnd, LVM_SETCOLUMNWIDTH, index, width);
	}

	CReportView::CReportView(const HWND& hParent, const UINT& id) :
		CListView(hParent, id, WS_CHILD | WS_BORDER | WS_VISIBLE | LVS_REPORT)
	{
		SendMessageA(m_hwnd, LVM_SETLISTSTYLE, 0, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	}
	void CReportView::SetColumnEndFill(const int& index)
	{
		SNDMSG(m_hwnd, LVM_SETCOLUMNWIDTH, index, LVSCW_AUTOSIZE_USEHEADER);
	}

	CComboBox::CComboBox(const HWND& hParent, const UINT& id, const UINT& style) : CCtrl(hParent, id)
	{
		if (NULL == m_hwnd)
		{
			m_hwnd = CreateWindow(TEXT("ComboBox"), TEXT(""),
				style,// 仅能下拉   
				0, 0, 100, 100,
				hParent, (HMENU)id, HINST, NULL);
		}
	}
	void CComboBox::AddStr(const char* str)
	{
		SendMessage(m_hwnd, CB_ADDSTRING, 0, (LPARAM)str);
	}
	void CComboBox::InsertStr(const char* str, const int& index)
	{
		SendMessage(m_hwnd, CB_INSERTSTRING, index, (LPARAM)str);
	}
	void CComboBox::DeleteItem(const char* str, const int& index)
	{
		SendMessage(m_hwnd, CB_DELETESTRING, index, 0);
	}
	void CComboBox::DeleteAllItems()
	{
		SendMessage(m_hwnd, CB_RESETCONTENT, 0, 0);
	}
	void CComboBox::Select(const int& index)
	{
		SendMessage(m_hwnd, CB_SETCURSEL, index, 0);
	}
	int CComboBox::GetSelect()
	{
		return SNDMSG(m_hwnd, CB_GETCURSEL, 0, 0);
	}
	int CComboBox::GetCount()
	{
		return SNDMSG(m_hwnd, CB_GETCOUNT, 0, 0);
	}
	CStr CComboBox::GetItemText(TCUQ(int) index)
	{
		int size;
		char *pStr;
		CStr temp;

		size = SNDMSG(m_hwnd, CB_GETLBTEXTLEN, index, 0);
		pStr = new char[size + 1];
		if (pStr == NULL)
		{
			return NULL;
		}
		//pStr[size] = 0;
		memset(pStr, size + 1, 0);

		SNDMSG(m_hwnd, CB_GETLBTEXT, index, (LPARAM)pStr);

		temp = pStr;
		delete[] pStr;

		return temp;
	}
}








