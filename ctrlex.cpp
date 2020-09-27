#include "ctrlex.h"
#include <stdarg.h>

namespace lmw
{
	void ExCtrlInit()
	{
		InitCommonControls();
	}
	CImageList::CImageList(const int& cx, const int& cy, const int& num, const int& max, TCUQ(int) color)
	{
		UINT flg;

		switch (color)
		{
		case 4:
			flg = ILC_COLOR4;
			break;
		case 8:
			flg = ILC_COLOR8;
			break;
		case 16:
			flg = ILC_COLOR16;
			break;
		case 24:
			flg = ILC_COLOR24;
			break;
		case 32:
			flg = ILC_COLOR32;
			break;
		default:
			flg = ILC_COLOR;
			break;
		}

		m_hImageList = ImageList_Create(cx, cy, flg, num, max);
		if (NULL == m_hImageList)
			throw "����ͼ���б�ʧ��";
	}
	CImageList::~CImageList()
	{
		if (NULL != m_hImageList)
			ImageList_Destroy(m_hImageList);
	}
	void CImageList::SetImageList(TCQ(HIMAGELIST) hil)
	{
		if (NULL != m_hImageList)
			ImageList_Destroy(m_hImageList);
		m_hImageList = hil;
	}
	void CImageList::AddIcon(HICON hIcon)
	{
		ImageList_AddIcon(m_hImageList, hIcon);
	}
	void CImageList::AddBitmap(HBITMAP bmp)
	{
		ImageList_Add(m_hImageList, bmp, NULL);
	}
	const HIMAGELIST& CImageList::GetImageList()
	{
		return m_hImageList;
	}

	CImageReport::CImageReport(const HWND& hParent, const int& id) :
		CListView(hParent, id, WS_CHILD | WS_BORDER | WS_VISIBLE | LVS_REPORT)
	{
		SendMessageA(m_hwnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	}
	void CImageReport::SetImageList(CImageList* imageList)
	{
		if (NULL == ListView_SetImageList(m_hwnd, imageList->GetImageList(), LVSIL_SMALL))
		{
			DWORD errcode = GetLastError();
			errcode = 1;
		}
	}

	CIconView::CIconView(const HWND& hParent, const int& id, BOOL isSmallIcon) :
		CListView(hParent, id, WS_CHILD | WS_BORDER | WS_VISIBLE | (isSmallIcon == TRUE ? LVS_SMALLICON : LVS_ICON))
	{
		SetExtendStyle(LVS_EX_AUTOAUTOARRANGE);
		m_isSmallIcon = isSmallIcon;
	}
	void CIconView::SetImageList(CImageList* imageList)
	{
		ListView_SetImageList(m_hwnd, imageList->GetImageList(),
			m_isSmallIcon == TRUE ? LVSIL_SMALL : LVSIL_NORMAL);
	}
	HIMAGELIST CIconView::CreateDropImage()
	{
		POINT p = { 0 };

		return ListView_CreateDragImage(m_hwnd, 0, &p);
	}

	CListBox::CListBox(const HWND& hParent, const UINT& id) :
		CCtrl(hParent, id)
	{
		if (m_hwnd != NULL)
		{
			return;
		}

		m_hwnd = CreateWindow(TEXT("COMBOBOX"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
			0, 0, 100, 200,
			hParent, (HMENU)id, (HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE), NULL);

		if (m_hwnd == NULL)
		{
			throw "����CListBoxʧ��";
		}
	}
	BOOL CListBox::DelItem(TCUQ(int) nu)
	{
		SendMessage(m_hwnd, CB_DELETESTRING, nu, 0);
		return TRUE;
	}
	BOOL CListBox::SelectItem(TCUQ(int) nu)
	{
		SendMessage(m_hwnd, CB_SETCURSEL, nu, 0);
		return TRUE;
	}
	TCU(int) CListBox::FindStr(TCPCH str)
	{
		return SendMessage(m_hwnd, CB_FINDSTRING, -1, (LPARAM)str);
	}
	void CListBox::AddIten(TCPCH str)
	{
		SendMessage(m_hwnd, CB_ADDSTRING, 0, (LPARAM)str);
	}

	CProBox::CProBox(TCQ(HWND) hParent, TCQ(UINT) id) :
		CCtrl(hParent, id)
	{
		if (NULL != m_hwnd)
		{
			/* ��ȡ������λ�� */
			m_pos = SendMessage(m_hwnd, PBM_GETPOS, (WPARAM)0, (LPARAM)0);
			PBRANGE pr;
			SendMessage(m_hwnd, PBM_GETRANGE, (WPARAM)0, (LPARAM)&pr);

			m_max = pr.iHigh;
			m_min = pr.iLow;
			return;
		}

		m_hwnd = CreateWindow(PROGRESS_CLASS,  //windows ������������
			NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | PBS_SMOOTH, // | PBS_MARQUEE  PBS_SMOOTHREVERSE  PBS_SMOOTH  PBS_VERTICAL
			0, 0, 100, 30,
			hParent, (HMENU)id, (HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE), NULL);

		if (NULL == m_hwnd)
		{
			throw "�������ؼ�����ʧ��";
		}
		else
		{
			m_pos = 0;
		}
	}
	void CProBox::SetRange(TCQ(int) maxv, TCUQ(int) minv)
	{
		m_max = maxv;
		m_min = minv;
		SendMessageA(m_hwnd, PBM_SETRANGE, 0, MAKELPARAM(m_min, m_max)); //���ý������ķ�Χ
	}
	void CProBox::SetPosValue(TCQ(int) num)
	{
		m_pos = num;
		SendMessageA(m_hwnd, PBM_SETPOS, m_pos, (LPARAM)0);   //���ý���
	}
	void CProBox::AddPos(TCQ(int) pos)
	{
		m_pos += pos;
		if (m_pos > m_max)
			m_pos = m_max;
		if (m_pos < m_min)
			m_pos = m_min;

		SendMessageA(m_hwnd, PBM_SETPOS, m_pos, (LPARAM)0);
	}
	void CProBox::DelPos(TCQ(int) pos)
	{
		m_pos -= pos;
		if (m_pos > m_max)
			m_pos = m_max;
		if (m_pos < m_min)
			m_pos = m_min;

		SendMessageA(m_hwnd, PBM_SETPOS, m_pos, (LPARAM)0);
	}
	int CProBox::GetPos()
	{
		m_pos = SendMessage(m_hwnd, PBM_GETPOS, (WPARAM)0, (LPARAM)0);
		return m_pos;
	}

	CSlider::CSlider(TCQ(HWND) hParent, TCQ(UINT) id, TCQ(BOOL) isVert) : CCtrl(hParent, id)
	{
		if (NULL != m_hwnd)
		{
			GetPosValue();
			return;
		}

		TCHAR *pName = TEXT("TrackBar");
		DWORD dwStyle = WS_CHILD | WS_VISIBLE;
		if (TRUE == isVert)
		{
			dwStyle |= TBS_VERT;
		}

		m_hwnd = CreateWindow(TRACKBAR_CLASS, // �༶����
			TEXT("Trackbar Control"), //���⣨���⣩
			dwStyle, //���
			0, 0, 50, 100,  // x, y, w, h
			hParent, (HMENU)id, (HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE), NULL);

		if (NULL == m_hwnd)
		{
			throw "����CSliderʧ��";
		}
	}
	void CSlider::SetRange(const int& range)
	{
		SendMessage(m_hwnd, TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(0, range));
	}
	void CSlider::SetPosValue(const int& pos)
	{
		SendMessage(m_hwnd, TBM_SETPOS, (WPARAM)1, (LPARAM)pos);
	}
	int CSlider::GetPosValue()
	{
		m_pos = (unsigned char)SendMessage(m_hwnd, TBM_GETPOS, 0, 0);
		return m_pos;
	}

	CStateBar::CStateBar(TCQ(HWND) hParent, TCQ(UINT) id) :
		CCtrl(hParent, id)
	{
		m_pSbps = new CVector<SBP>(10, 10);
		m_SbpsNum = 0;

		if (NULL == m_hwnd)
		{
			m_hwnd = CreateWindow(STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
				0, 0, 0, 0, hParent, (HMENU)id, (HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE), NULL);

			if (NULL == m_hwnd){
				throw "CStateBar����ʧ��";
			}
		}
	}
	CStateBar::~CStateBar()
	{
		delete m_pSbps;
	}
	void CStateBar::Paint()
	{
		TU(int) i, size = m_pSbps->size();
		int wth = 0;

		if (size < 1)
		{
			return;
		}

		int *pWidths = new int[size];
		for (i = 0; i < size - 1; i++)
		{
			pWidths[i] = (*m_pSbps)[i].width + wth;
			wth = pWidths[i];
		}
		pWidths[i] = -1;

		//����width����������״̬�������ֵĿ��
		SendMessage(m_hwnd, SB_SETPARTS, size, (LPARAM)pWidths);

		/* ���ø����ֵ��ı� */
		for (i = 0; i < size; i++)
		{
			SendMessage(m_hwnd, SB_SETTEXT, (WPARAM)i | SBT_POPOUT, (LPARAM)(*m_pSbps)[i].text.c_str());
		}
	}
	void CStateBar::AddPart(TCQ(CStr) str, TCUQ(int) width)
	{
		SBP sbp;
		sbp.text = str;
		sbp.width = width;

		m_pSbps->push_back(sbp);
	}
	void CStateBar::SetItemText(TCUQ(int) index, TCPCH text)
	{
		m_pSbps[0][index].text = text;
		Paint();
	}
	void CStateBar::OnSize()
	{
		SetPos(0, 0);
		SetSize(0, 0);
	}
	void CStateBar::SetBkColor(TCQ(COLORREF) color)
	{
		SendMsg(SB_SETBKCOLOR, 0, (LPARAM)color);
	}
	void CStateBar::SetTipText(TCUQ(int) index, TCPCH str)
	{
		SendMsg(SB_SETTIPTEXT, index, (LPARAM)str);
	}

	CStatic::CStatic(TCQ(HWND) hParent, TCQ(UINT) id) : CCtrl(hParent, id)
	{
		if (nullptr != m_hwnd)
		{
			return;
		}
		m_hwnd = CreateWindow(TEXT("static"), TEXT(""), WS_CHILD | WS_VISIBLE | SS_LEFT,
			0, 0, 100, 24, hParent,
			(HMENU)id, (HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE), NULL);

		SetWindowLong(m_hwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT);

		if (NULL == m_hwnd){
			throw "CStatic����ʧ��";
		}
	}

	CToolBar::CToolBar(TCQ(HWND) hParent, TCQ(UINT) id) : CCtrl(hParent, id)
	{
		m_pImageList = nullptr;
		m_pImageList2 = nullptr;

		if (m_hwnd != nullptr)
		{
			return;
		}
		m_vTbt = new CVector<TBT>(10, 10);

		m_hwnd = CreateWindow(TOOLBARCLASSNAME, TEXT(""), 
			WS_CHILD | WS_BORDER | WS_VISIBLE | TBS_TOOLTIPS,
			0, 0, 0, 0, hParent, (HMENU)id, (HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE), NULL);

		if (NULL == m_hwnd){
			throw "����CToolBarʧ��";
		}

		SendMessage(m_hwnd, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	}
	BOOL CToolBar::AddButtons(TCQ(int) iBmpIndex, TCUQ(int) id, LPSTR text, BOOL isShowText)
	{
		TBBUTTON btn = { 0 };
		BOOL ret;

		btn.iBitmap = iBmpIndex == -1 ? I_IMAGENONE : iBmpIndex;
		btn.idCommand = id;
		btn.fsState = TBSTATE_ENABLED;
		btn.fsStyle = BTNS_AUTOSIZE;
		if (TRUE == isShowText)
		{
			btn.iString = (int)text;
		}

		ret = SNDMSG(m_hwnd, TB_ADDBUTTONS, 1, (LPARAM)&btn);

		if (TRUE == ret)
		{
			TBT t = { 0 };
			t.id = id;
			t.tip = text;
			m_vTbt->push_back(t);
		}

		return ret;
	}
	void CToolBar::OnSize()
	{
		SNDMSG(m_hwnd, TB_AUTOSIZE, 0, (LPARAM)0);
	}
	void CToolBar::SetItemEnable(TCUQ(int) id, TCQ(BOOL) isEnable)
	{
		if (TRUE == isEnable)
			SNDMSG(m_hwnd, TB_SETSTATE, id, (LPARAM)TBSTATE_ENABLED);
		else
			SNDMSG(m_hwnd, TB_SETSTATE, id, (LPARAM)TBSTATE_INDETERMINATE);
	}
	void CToolBar::AddBitmap(TCUQ(int) width, TCUQ(int) height, TCU(int) num, ...)
	{
		UINT id;
		HBITMAP bmp;
		va_list arg;

		if (nullptr == m_pImageList)
		{
			m_pImageList = new CImageList(width, height, num, num * 2, 32);
			m_pImageList2 = new CImageList(width, height, num, num * 2, 4);
		}
		else
		{
			return ;
		}

		va_start(arg, num);
		for (TU(int) i = 0; i < num; i++)
		{
			id = va_arg(arg, UINT);
			bmp = lmw::GetBitmap(id);
			m_pImageList->AddBitmap(bmp);
			m_pImageList2->AddBitmap(bmp);
			DeleteObject(bmp);
		}

		SendMessage(m_hwnd, TB_SETIMAGELIST, (WPARAM)0,
			(LPARAM)m_pImageList->GetImageList());
		SendMessage(m_hwnd, TB_SETDISABLEDIMAGELIST, (WPARAM)0,
			(LPARAM)m_pImageList2->GetImageList());
	}
	CToolBar::~CToolBar()
	{
		if (nullptr != m_pImageList)
		{
			delete m_pImageList;
		}
		if (nullptr != m_pImageList2)
		{
			delete m_pImageList2;
		}
		delete m_vTbt;
	}
	void CToolBar::OnNotify(TCQ(LPARAM) lParam)
	{
		LPNMHDR phmr = (LPNMHDR)lParam;
		LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;

		if (TTN_GETDISPINFO == phmr->code)
		{
			// Set the instance of the module that contains the resource.
			lpttt->hinst = HINST;

			UINT_PTR idButton = lpttt->hdr.idFrom;

			for (TU(int) i = 0; i < m_vTbt->size(); i++)
			{
				if (idButton == (*m_vTbt)[i].id)
				{
					lpttt->lpszText = (LPSTR)(*m_vTbt)[i].tip.c_str();
					break;
				}
			}
		}
	}

	CTreeItem::CTreeItem()
	{
		m_hwnd = NULL;
		m_item = NULL;
	}
	void CTreeItem::SetTreeItem(HTREEITEM item)
	{
		m_item = item;
	}
	void CTreeItem::SetHwnd(TCQ(HWND) hwnd)
	{
		m_hwnd = hwnd;
	}
	CStr CTreeItem::GetItemText()
	{
		TV_ITEM pitem;
		char s[128];
		pitem.mask = TVIF_TEXT;
		pitem.cchTextMax = 128;
		pitem.pszText = s;
		memset(pitem.pszText, 0, 128);
		pitem.hItem = m_item;	// ��ȡ�Ľڵ�
		SendMessage(m_hwnd, TVM_GETITEM, 0, (LPARAM)&pitem);// ��ȡ�ڵ��ֵ

		return s;
	}
	UINT CTreeItem::GetItemImage()
	{
		TV_ITEM pitem = { 0 };
		pitem.hItem = m_item;	// ��ȡ�Ľڵ�
		pitem.mask = TVIF_IMAGE;

		SendMessage(m_hwnd, TVM_GETITEM, 0, (LPARAM)&pitem);// ��ȡ�ڵ��ֵ

		return pitem.iImage;
	}
	CTreeItem CTreeItem::GetParentItem()
	{
		HTREEITEM item;
		CTreeItem ti;

		item = TreeView_GetParent(m_hwnd, m_item);
		ti.SetTreeItem(item);
		ti.SetHwnd(m_hwnd);
		return ti;
	}
	void CTreeItem::SetItemText(LPSTR str)
	{
		TV_ITEM pitem = { 0 };
		pitem.mask = TVIF_TEXT;
		pitem.cchTextMax = strlen(str);
		pitem.pszText = str;

		pitem.hItem = m_item;	// ��ȡ�Ľڵ�

		TreeView_SetItem(m_hwnd, &pitem);
	}
	void CTreeItem::SetItemImage(TCUQ(int) iImage)
	{
		TV_ITEM pitem;
		pitem.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;

		pitem.hItem = m_item;	// ��ȡ�Ľڵ�
		pitem.iImage = iImage;
		pitem.iSelectedImage = iImage;

		TreeView_SetItem(m_hwnd, &pitem);
	}
	BOOL CTreeItem::IsNullTree()
	{
		if (NULL == m_item)
		{
			return TRUE;
		}

		return FALSE;
	}
	HTREEITEM CTreeItem::GetTreeItem()
	{
		return m_item;
	}
	BOOL CTreeItem::HaveChildTree()
	{
		HTREEITEM item = TreeView_GetChild(m_hwnd, m_item);

		if (NULL == item)
		{
			return FALSE;
		}

		return TRUE;
	}

	CTree::CTree(TCQ(HWND) hParent, TCQ(UINT) id) : CCtrl(hParent, id)
	{
		if (m_hwnd != nullptr)
		{
			return;
		}

		m_hwnd = CreateWindowEx(0, WC_TREEVIEW, TEXT("Tree View"), 
			WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT,
			0, 0, 100, 200,	hParent, (HMENU)id, 
			(HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE), NULL);

		if (NULL == m_hwnd){
			throw "��������ͼʧ��...";
		}
	}
	void CTree::AddRootItem(TCPCH str, TCQ(int) iImage)
	{
		TVINSERTSTRUCT tvins;
		//����ITEM�Ĳ���
		tvins.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_DI_SETITEM | TVIF_PARAM | TVIF_SELECTEDIMAGE;
		tvins.item.pszText = (char*)str;
		//���STRUCT�ṹ
		tvins.hInsertAfter = TVI_ROOT;
		// ���ڵ�
		tvins.hParent = TVI_ROOT;

		if (-1 != iImage)
		{
			tvins.item.iImage = iImage;
			tvins.item.iSelectedImage = iImage;
		}

		//���ùؼ���TreeView_InsertItem����
		TreeView_InsertItem(m_hwnd, &tvins);
	}
	BOOL CTree::IsItemStr(HTREEITEM hitem, TCPCH str)
	{
		TV_ITEM pitem;
		TCHAR* s = new TCHAR[128];
		pitem.mask = TVIF_TEXT;
		pitem.cchTextMax = 128;
		pitem.pszText = s;
		memset(pitem.pszText, 0, 128);
		pitem.hItem = hitem;	// ��ȡ�Ľڵ�
		SendMessage(m_hwnd, TVM_GETITEM, 0, (LPARAM)&pitem);// ��ȡ�ڵ��ֵ

		if (lstrcmp(s, str) == 0)
		{
			delete[] s;
			return TRUE;
		}
		delete[] s;
		return FALSE;
	}
	BOOL CTree::SerachChildItem(HTREEITEM& hitem, TCPCH str)
	{
		HTREEITEM item;

		/* �����һ���ǶԵ� */
		if (TRUE == IsItemStr(hitem, str))
		{
			return TRUE;
		}

		/* ���������ÿһ�� */
		item = TreeView_GetNextSibling(m_hwnd, hitem); /* ��ȡ��һ�� */
		while (NULL != item)
		{
			if (TRUE == IsItemStr(item, str))
			{
				hitem = item;
				return TRUE;
			}

			item = TreeView_GetNextSibling(m_hwnd, hitem); /* ��ȡ��һ�� */
		}

		return FALSE;
	}
	BOOL CTree::AddItem(TCU(int) height, ...)
	{
		va_list arg;
		char* p, str[256] = { 0 };
		HTREEITEM item = NULL;

		va_start(arg, height);
		for (size_t i = 0; i < height - 1; i++)
		{
			p = va_arg(arg, char*);

			item = TreeView_GetChild(m_hwnd, item);

			if(SerachChildItem(item, p) == FALSE)
			{
				return FALSE;
			}
		}
		p = va_arg(arg, char*);

		TVINSERTSTRUCT tvins;
		//����ITEM�Ĳ���
		tvins.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_DI_SETITEM | TVIF_PARAM;
		tvins.item.pszText = (char*)p;
		//���STRUCT�ṹ
		tvins.hInsertAfter = TVI_LAST;
		// ���ڵ�
		tvins.hParent = item;

		//���ùؼ���TreeView_InsertItem����
		TreeView_InsertItem(m_hwnd, &tvins);

		va_end(arg);
		return TRUE;
	}
	BOOL CTree::AddItem(TCQ(int) iImage, TCU(int) height, ...)
	{
		va_list arg;
		char* p, str[256] = { 0 };
		HTREEITEM item = NULL;

		/* ���Ҹ��ڵ� */
		va_start(arg, height);
		for (size_t i = 0; i < height - 1; i++)
		{
			p = va_arg(arg, char*);

			item = TreeView_GetChild(m_hwnd, item);

			if (SerachChildItem(item, p) == FALSE)
			{
				return FALSE;
			}
		}
		p = va_arg(arg, char*);

		TVINSERTSTRUCT tvins;
		//����ITEM�Ĳ���
		tvins.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_DI_SETITEM | TVIF_PARAM | TVIF_SELECTEDIMAGE;
		tvins.item.pszText = (char*)p;
		//���STRUCT�ṹ
		tvins.hInsertAfter = TVI_LAST;
		// ���ڵ�
		tvins.hParent = item;

		if (-1 != iImage)
		{
			tvins.item.iImage = iImage;
			tvins.item.iSelectedImage = iImage;
		}

		//���ùؼ���TreeView_InsertItem����
		TreeView_InsertItem(m_hwnd, &tvins);

		va_end(arg);
		return TRUE;
	}
	BOOL CTree::AddItem(TQ(CTreeItem) ti, LPSTR text, TCQ(int) iImage)
	{
		TVINSERTSTRUCT tvins;
		//����ITEM�Ĳ���
		tvins.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_DI_SETITEM | TVIF_PARAM | TVIF_SELECTEDIMAGE;
		tvins.item.pszText = (char*)text;
		//���STRUCT�ṹ
		tvins.hInsertAfter = TVI_LAST;
		// ���ڵ�
		tvins.hParent = ti.GetTreeItem();

		if (-1 != iImage)
		{
			tvins.item.iImage = iImage;
			tvins.item.iSelectedImage = iImage;
		}

		//���ùؼ���TreeView_InsertItem����
		TreeView_InsertItem(m_hwnd, &tvins);
		return TRUE;
	}
	CTreeItem CTree::GetSelectItem()
	{
		HTREEITEM item;
		CTreeItem ti;

		item = TreeView_GetSelection(m_hwnd);
		ti.SetTreeItem(item);
		ti.SetHwnd(m_hwnd);
		return ti;
	}
	CTreeItem CTree::GetItem(TCU(int) height, ...)
	{
		va_list arg;
		char* p, str[256] = { 0 };
		HTREEITEM item = NULL;
		CTreeItem ti;

		ti.SetHwnd(m_hwnd);
		ti.SetTreeItem(NULL);

		va_start(arg, height);
		for (size_t i = 0; i < height; i++)
		{
			p = va_arg(arg, char*);

			item = TreeView_GetChild(m_hwnd, item);

			if (SerachChildItem(item, p) == FALSE)
			{
				return ti;
			}
		}

		ti.SetTreeItem(item);
		return ti;
	}
	void CTree::SetImageList(CImageList * pImageList)
	{
		TreeView_SetImageList(m_hwnd, pImageList->GetImageList(), TVSIL_NORMAL);
	}
	void CTree::DeleteItem(HTREEITEM item)
	{
		TreeView_DeleteItem(m_hwnd, item);
	}
	void CTree::DeleteAllItems()
	{
		TreeView_DeleteAllItems(m_hwnd);
	}
	void CTree::SetEditItem(HTREEITEM item)
	{
		SetFocus(m_hwnd);
		TreeView_EditLabel(m_hwnd, item);
	}
}



