
// NotePadeDemoDlg.h: 头文件
//

#pragma once


// CNotePadeDemoDlg 对话框
class CNotePadeDemoDlg : public CDialogEx
{
// 构造
public:
	CNotePadeDemoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTEPADEDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuSaveAs();
	afx_msg void OnChangeColour();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	COLORREF m_choice;//用户选择的颜色
	afx_msg void OnChangeTitle();
	afx_msg void OnExit();
	afx_msg void OnFind();
	afx_msg void OnReplace();

	//注册消息
	afx_msg  LRESULT OnFindReplace(WPARAM wparam, LPARAM lparam);
	//标记选择的是替换还是查找
	BOOL m_flag;
	//记录查找位置的光标
	int nStartIndex;
	int nEndIndex;
};
