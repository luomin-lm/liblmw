#ifndef _CPP_CTRL_SELF_H_
#define _CPP_CTRL_SELF_H_

#include "ctrlex.h"

namespace lmw
{
#include "types.h"

	/* ͼ�� */
	class CRgn
	{
	public:
		CRgn();
		~CRgn();
		HRGN GetRgn();
		/* ���� */
		void CreateRectRgn(TCQ(int) xStart, TCQ(int) yStart, TCQ(int) xEnd, TCQ(int) yEnd);
		void CreateRectRgn(RECT rc);
		void DeleteObject();
		/* ��Բ */
		void CreateEllipticRgn(TCQ(int) xStart, TCQ(int) yStart, TCQ(int) xEnd, TCQ(int) yEnd);
		void CreateEllipticRgn(RECT rc);
		/* Բ�Ǿ���
		* nLeftRect			[in] ָ����x��������Ͻ������߼���λ��
		* nTopRect			[in] ָ����y��������Ͻ������߼���λ��
		* nRightRect		[in] ָ����x��������½������߼���λ��
		* nBottomRect		[in] ָ����y��������½������߼���λ��
		* nWidthEllipse		[in] ָ������Բ�ǵĿ���߼���λ��
		* nHeightEllipse	[in] ָ������Բ�ǵĸ߶��߼���λ��
		**/
		void CreateRoundRectRgn(TCQ(int) nLeftRect, TCQ(int) nTopRect, TCQ(int) nRightRect, TCQ(int) nBottomRect,
			TCQ(int) nWidthEllipse = 10, TCQ(int) nHeightEllipse = 10);
		/* �����
		* lpPoint			POINTAPI��nCount��POINTAPI�ṹ�еĵ�һ��POINTAPI�ṹ
		* nCount			Long������εĵ���
		* nPolyFillMode		Long��������������ģʽ����ΪALTERNATE �� WINDING������nPolyFillMode��Ĭ���� ����ΪALTERNATE;
		ģʽALTERNATE:��ӷ�������е�һ����������Զ��ˮƽ��һ�����ߣ�ֻ�е������ߴ�Խ�������߿���ʱ���������ű���䣬
		��Ϊż��������������
		ģʽWINDING������һ������Ϊ��������������
		��Ϊż����Ҫ���ݱ߿��ߵķ������жϣ���������ı߿����ڲ�ͬ����ı߿�����Ŀ��ȣ�����䣬�粻�ȣ�����䡣
		*/
		void CreatePolygonRgn(LPPOINT lpPoints, TCQ(int) nCount, TCQ(int) nMode = ALTERNATE);
		/* ������������ 
		iCombine���е�ֵ      ������
			RGN_AND             ����Դ����Ĺ�������
			RGN_OR              ����Դ�����ȫ��
			RGN_XOR             ����Դ�����ȫ����ȥ��������
			RGN_DIFF            rgn1����rgn2�еĲ���
			RGN_COPY            rgn1��ȫ��������rgn2��
		*/
		static void Op(const CRgn& rgn1, const CRgn& rgn2, TCQ(int) nmode, CRgn& result);
		/* ������� */
		void Fill(const HDC& hdc, const COLORREF& color);
		/* ���Ʊ߿� */
		void FrameRgn(const HDC& hdc, const COLORREF& color, TCQ(int) width, TCQ(int) height);
		/* ѡ��� */
		void Select(const HDC& hdc);
		BOOL HavePoint(TCQ(int) cx, TCQ(int) cy);

	private:
		HRGN m_rgn;
	};

	/* �Զ���ؼ� */
	class CSelfCtrl
	{
	public:
		enum SC_TYPE { SCS_RECT = 0, SCS_ELLIPTIC };

		CSelfCtrl(TCQ(int) x, TCQ(int) y, TCQ(int) width = 32, TCQ(int) height = 32, SC_TYPE mode = SCS_RECT);
		CSelfCtrl(const RECT& rc, SC_TYPE mode = SCS_RECT);
		virtual void MsgHandle(TCQ(HWND) hwnd, TCUQ(int) msg,
			TCQ(WPARAM) wParam, TCQ(LPARAM) lParam) = 0;

	protected:
		CRgn m_rgn;
		RECT m_rc;
	};

	class CSPushButton : public CSelfCtrl
	{
	public:
		CSPushButton(TCQ(int) x, TCQ(int) y, TCQ(int) width, TCQ(int) height);
		CSPushButton(const RECT& rc);
		virtual void MsgHandle(TCQ(HWND) hwnd, TCUQ(int) msg,
			TCQ(WPARAM) wParam, TCQ(LPARAM) lParam);
		/* ���£�δ���� */
		void SetImage(TCQ(UINT) ImgId, TCQ(UINT) BkImgId);

	private:
		UINT m_ImgId, m_BkImgId;
		int m_enter;
	};

	/* Http���ӿؼ� */
	class CSLink : public CSelfCtrl
	{
	public:
		CSLink(TCQ(int) x, TCQ(int) y, TCQ(int) width, TCQ(int) height, TCQ(CStr) link);
		CSLink(const RECT& rc, TCQ(CStr) link);

		/* ��Ϣ���� */
		virtual void MsgHandle(TCQ(HWND) hwnd, TCUQ(int) msg,
			TCQ(WPARAM) wParam, TCQ(LPARAM) lParam);

		/* ������Ϣ */
		virtual void OnDraw(TCQ(HDC) hdc);
		/* ������ʾͼ�� */
		void DrawShowIcon(TCQ(HDC) hdc);
		/* ������ʾ�ı� */
		UINT DrawTipText(TCQ(HDC) hdc);
		/* �����ı��»��� */
		void DrawBottomLine(TCQ(HDC) hdc, TCUQ(int) height);

		/* �����ı���ʾ */
		void SetTextTip(TCPCH tip);
		/* ����Link��ʾ,�ƶ����ô���ʾ���� */
		void SetLinkTip(TCQ(HWND) hParent, TCUQ(int) id);
		/* ������ʾͼ�� */
		void SetIcon(TCQ(int) id);
		~CSLink();

	protected:
		CStr m_link;
		CStr m_tip;
		HICON m_hIcon;
		CStatic* m_pStatic;
	};
}



#endif
