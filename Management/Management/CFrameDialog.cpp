// CFrameDialog.cpp: 实现文件
//

#include "pch.h"
#include "Management.h"
#include "afxdialogex.h"
#include "CFrameDialog.h"


// CFrameDialog 对话框

IMPLEMENT_DYNAMIC(CFrameDialog, CDialogEx)

CFrameDialog::CFrameDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FRAME_DIALOG, pParent)
{

}

CFrameDialog::~CFrameDialog()
{
}

void CFrameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}


BEGIN_MESSAGE_MAP(CFrameDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFrameDialog::OnBnClickedOk)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CFrameDialog 消息处理程序


void CFrameDialog::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}


BOOL CFrameDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//设置整行选取风格，网格风格
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, L"工号", LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, L"姓名", LVCFMT_LEFT, 120);
	m_list.InsertColumn(2, L"性别", LVCFMT_LEFT, 80);
	m_list.InsertColumn(3, L"年龄", LVCFMT_LEFT, 80);
	m_list.InsertColumn(4, L"部门", LVCFMT_LEFT, 110);
	m_list.InsertColumn(5, L"职位", LVCFMT_LEFT, 110);
	m_list.InsertColumn(6, L"住址", LVCFMT_LEFT, 400);
	m_list.InsertColumn(7, L"入职时间", LVCFMT_LEFT, 200);
	m_list.InsertColumn(8, L"离职时间", LVCFMT_LEFT, 200);
	m_list.InsertColumn(9, L"税前薪资", LVCFMT_LEFT, 80);
	m_list.InsertColumn(10, L"电话", LVCFMT_LEFT, 200);
	m_list.ShowWindow(SW_SHOW);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CFrameDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_list.GetSafeHwnd()) {
		m_list.MoveWindow(0, 0, cx, cy);
	}
}
