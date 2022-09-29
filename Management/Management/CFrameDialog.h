#pragma once
#include "afxdialogex.h"


// CFrameDialog 对话框

class CFrameDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFrameDialog)

public:
	CFrameDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFrameDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FRAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
