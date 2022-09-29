// CLoginDialog.cpp: 实现文件
//

#include "pch.h"
#include "Management.h"
#include "afxdialogex.h"
#include "CLoginDialog.h"


// CLoginDialog 对话框

IMPLEMENT_DYNAMIC(CLoginDialog, CDialogEx)

CLoginDialog::CLoginDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOG_DLG, pParent)
	, m_user(_T(""))
	, m_key(_T(""))
{

}

CLoginDialog::~CLoginDialog()
{
}

void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	DDX_Text(pDX, IDC_EDIT_KEY, m_key);
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialogEx)
	ON_BN_CLICKED(ID_BTN_LOG, &CLoginDialog::OnBnClickedBtnLog)
END_MESSAGE_MAP()


// CLoginDialog 消息处理程序


void CLoginDialog::OnBnClickedBtnLog()
{
	UpdateData();
	if (m_key.IsEmpty() || m_user.IsEmpty()) {
		MessageBox(L"用户名或密码为空",L"提示",MB_ICONWARNING);
		return;
	}

	//核对账号密码
	if (m_user == L"admin"&&m_key==L"root") {
		//登录成功
		MessageBox(L"欢迎回来，admin用户");
		EndDialog(IDOK);
	}
	else {
		MessageBox(L"用户名或密码错误", L"提示", MB_ICONERROR);
		return;
	}
}
