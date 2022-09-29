
// ManagementDlg.h: 头文件
//

#pragma once
#include"CFrameDialog.h"
#include<vector>

// CManagementDlg 对话框
class CManagementDlg : public CDialogEx
{
// 构造
public:
	CManagementDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGEMENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	CFrameDialog m_dialog;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//将获得的信息添加到m_dialog中的list控件上
	void InsertList(std::vector<CString>& msg) {
		CListCtrl& hand = m_dialog.m_list;
		int nCount = hand.GetItemCount();
		hand.InsertItem(nCount, msg[0]);
		for (int i = 1; i < msg.size(); i++) {
			hand.SetItemText(nCount, i, msg[i]);
		}
	}
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBntAdd();
	afx_msg void OnBnClickedBntDel();
};
