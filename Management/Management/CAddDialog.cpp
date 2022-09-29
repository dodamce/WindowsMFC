// CAddDialog.cpp: 实现文件
//

#include "pch.h"
#include "Management.h"
#include "afxdialogex.h"
#include "CAddDialog.h"


// CAddDialog 对话框

IMPLEMENT_DYNAMIC(CAddDialog, CDialogEx)

CAddDialog::CAddDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_DLG, pParent)
	, m_number(0)
	, m_worknum(_T(" "))
	, m_sex(0)
	, m_age(0)
	, m_money(0.0)
	, m_joinTile(COleDateTime::GetCurrentTime())
	, m_leaveTime(COleDateTime::GetCurrentTime())
	, m_phone(_T(" "))
	, m_address(_T(" "))
{

}

CAddDialog::~CAddDialog()
{
}

void CAddDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUM, m_number);
	DDX_Text(pDX, IDC_NAME, m_worknum);
	DDX_Radio(pDX, IDC_MAN, m_sex);
	DDX_Text(pDX, IDC_AHE, m_age);
	DDX_Control(pDX, IDC_WORK_TYPE, m_deparment);
	DDX_Control(pDX, IDC_WORK, m_job);
	DDX_Text(pDX, IDC_MONEY, m_money);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_BEGIN, m_joinTile);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEZ_END, m_leaveTime);
	DDX_Text(pDX, IDC_TELEPHONE, m_phone);
	DDX_Text(pDX, IDC_HOME, m_address);
}


BEGIN_MESSAGE_MAP(CAddDialog, CDialogEx)
	ON_BN_CLICKED(ID_BTN_ADD, &CAddDialog::OnBnClickedBtnAdd)
END_MESSAGE_MAP()


// CAddDialog 消息处理程序


void CAddDialog::OnBnClickedBtnAdd()
{
	UpdateData(TRUE);
	//判断工号和姓名存在
	if (m_worknum.IsEmpty() || m_number == 0) {
		MessageBox(L"请填写完全工号和姓名");
	}
	else {
		//添加完毕
		m_deparment.GetWindowText(deparment_name);
		m_job.GetWindowText(job_name);
		EndDialog(IDOK);
	}
}


BOOL CAddDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//初始化下拉列表
	InitDeparment();
	m_job.AddString(L"C++工程师");
	m_job.AddString(L"Java工程师");
	m_job.AddString(L"Python工程师");
	m_job.AddString(L"WEB工程师");
	m_job.AddString(L"会计");
	m_job.AddString(L"销售");
	m_job.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
