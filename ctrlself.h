#ifndef _CPP_CTRL_SELF_H_
#define _CPP_CTRL_SELF_H_

#include "ctrlex.h"

namespace lmw
{
#include "types.h"

	/* 图形 */
	class CRgn
	{
	public:
		CRgn();
		~CRgn();
		HRGN GetRgn();
		/* 矩形 */
		void CreateRectRgn(TCQ(int) xStart, TCQ(int) yStart, TCQ(int) xEnd, TCQ(int) yEnd);
		void CreateRectRgn(RECT rc);
		void DeleteObject();
		/* 椭圆 */
		void CreateEllipticRgn(TCQ(int) xStart, TCQ(int) yStart, TCQ(int) xEnd, TCQ(int) yEnd);
		void CreateEllipticRgn(RECT rc);
		/* 圆角矩形
		* nLeftRect			[in] 指定了x坐标的左上角区域逻辑单位。
		* nTopRect			[in] 指定了y坐标的左上角区域逻辑单位。
		* nRightRect		[in] 指定了x坐标的右下角区域逻辑单位。
		* nBottomRect		[in] 指定了y坐标的右下角区域逻辑单位。
		* nWidthEllipse		[in] 指定创建圆角的宽度逻辑单位。
		* nHeightEllipse	[in] 指定创建圆角的高度逻辑单位。
		**/
		void CreateRoundRectRgn(TCQ(int) nLeftRect, TCQ(int) nTopRect, TCQ(int) nRightRect, TCQ(int) nBottomRect,
			TCQ(int) nWidthEllipse = 10, TCQ(int) nHeightEllipse = 10);
		/* 多边形
		* lpPoint			POINTAPI，nCount个POINTAPI结构中的第一个POINTAPI结构
		* nCount			Long，多边形的点数
		* nPolyFillMode		Long，描述多边形填充模式。可为ALTERNATE 或 WINDING常数。nPolyFillMode在默认情 况下为ALTERNATE;
		模式ALTERNATE:其从封闭区域中的一个点向无穷远处水平画一条射线，只有当该射线穿越奇数条边框线时，封闭区域才被填充，
		如为偶数，则不填充该区域；
		模式WINDING：方法一样，如为奇数，填充该区域；
		如为偶数则要根据边框线的方向来判断：如果穿过的边框线在不同方向的边框线数目相等，则不填充，如不等，则填充。
		*/
		void CreatePolygonRgn(LPPOINT lpPoints, TCQ(int) nCount, TCQ(int) nMode = ALTERNATE);
		/* 操作两个区域 
		iCombine含有的值      新区域
			RGN_AND             两个源区域的公共部分
			RGN_OR              两个源区域的全部
			RGN_XOR             两个源区域的全部除去公共部分
			RGN_DIFF            rgn1不在rgn2中的部分
			RGN_COPY            rgn1的全部（忽略rgn2）
		*/
		static void Op(const CRgn& rgn1, const CRgn& rgn2, TCQ(int) nmode, CRgn& result);
		/* 填充区域 */
		void Fill(const HDC& hdc, const COLORREF& color);
		/* 绘制边框 */
		void FrameRgn(const HDC& hdc, const COLORREF& color, TCQ(int) width, TCQ(int) height);
		/* 选择块 */
		void Select(const HDC& hdc);
		BOOL HavePoint(TCQ(int) cx, TCQ(int) cy);

	private:
		HRGN m_rgn;
	};

	/* 自定义控件 */
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
		/* 按下，未按下 */
		void SetImage(TCQ(UINT) ImgId, TCQ(UINT) BkImgId);

	private:
		UINT m_ImgId, m_BkImgId;
		int m_enter;
	};

	/* Http链接控件 */
	class CSLink : public CSelfCtrl
	{
	public:
		CSLink(TCQ(int) x, TCQ(int) y, TCQ(int) width, TCQ(int) height, TCQ(CStr) link);
		CSLink(const RECT& rc, TCQ(CStr) link);

		/* 消息处理 */
		virtual void MsgHandle(TCQ(HWND) hwnd, TCUQ(int) msg,
			TCQ(WPARAM) wParam, TCQ(LPARAM) lParam);

		/* 绘制消息 */
		virtual void OnDraw(TCQ(HDC) hdc);
		/* 绘制显示图标 */
		void DrawShowIcon(TCQ(HDC) hdc);
		/* 绘制显示文本 */
		UINT DrawTipText(TCQ(HDC) hdc);
		/* 绘制文本下划线 */
		void DrawBottomLine(TCQ(HDC) hdc, TCUQ(int) height);

		/* 设置文本提示 */
		void SetTextTip(TCPCH tip);
		/* 设置Link提示,移动到该处显示链接 */
		void SetLinkTip(TCQ(HWND) hParent, TCUQ(int) id);
		/* 设置显示图标 */
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
