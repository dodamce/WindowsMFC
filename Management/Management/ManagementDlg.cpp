
// ManagementDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Management.h"
#include "ManagementDlg.h"
#include "afxdialogex.h"
#include"CAddDialog.h"
#include<vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CManagementDlg 对话框



CManagementDlg::CManagementDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MANAGEMENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CManagementDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BNT_ADD, &CManagementDlg::OnBnClickedBntAdd)
	ON_BN_CLICKED(IDC_BNT_DEL, &CManagementDlg::OnBnClickedBntDel)
END_MESSAGE_MAP()


// CManagementDlg 消息处理程序

BOOL CManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//获取主窗口客户区的宽高
	CRect rect;
	GetClientRect(rect);

	m_dialog.Create(IDD_FRAME_DIALOG, this);
	m_dialog.ShowWindow(SW_SHOW);
	m_dialog.MoveWindow(120, 25, rect.Width() - 175, rect.Height() - 50);
	ShowWindow(SW_MAXIMIZE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CManagementDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//最大化窗口重绘
void CManagementDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_dialog.GetSafeHwnd()) {
		//句柄存在,移动窗口，重绘
		//获取主窗口客户区的宽高
		CRect rect;
		GetClientRect(rect);

		m_dialog.MoveWindow(120, 25, rect.Width() - 175, rect.Height() - 50);
	}
}


void CManagementDlg::OnBnClickedBntAdd()
{
	CAddDialog addlg;
	if (IDCANCEL == addlg.DoModal()) {
		return;
	}

	//获取添加的信息
	std::vector<CString>msg;
	addlg.GetMsg(msg);

	//插入到list控件中
	InsertList(msg);
}


void CManagementDlg::OnBnClickedBntDel()
{
	//获取光标选择的位置
	CListCtrl& hand = m_dialog.m_list;
	POSITION pos = hand.GetFirstSelectedItemPosition();
	//获取选择索引
	int nSel = hand.GetNextSelectedItem(pos);
	if (nSel < 0) {
		MessageBox(L"没有找到选择上的内容,请选择后删除内容");
	}
	else {
		hand.DeleteItem(nSel);
	}
}
