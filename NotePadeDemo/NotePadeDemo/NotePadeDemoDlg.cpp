
// NotePadeDemoDlg.cpp: 实现文件
//
#include "framework.h"
#include "NotePadeDemo.h"
#include "NotePadeDemoDlg.h"
#include "afxdialogex.h"
#include"ChangeCharSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//向系统注册消息
static UINT NEAR WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);


// CNotePadeDemoDlg 对话框

CNotePadeDemoDlg::CNotePadeDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOTEPADEDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_choice = RGB(0, 0, 0);//默认选择颜色是黑色
	m_flag = FALSE;
	nStartIndex = 0;
	nEndIndex = 0;
}

void CNotePadeDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNotePadeDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNotePadeDemoDlg::OnBnClickedOk)
	ON_WM_SIZE()
	ON_COMMAND(ID_OPEN, &CNotePadeDemoDlg::OnMenuOpen)
	ON_COMMAND(ID_SAVE_AS, &CNotePadeDemoDlg::OnMenuSaveAs)
	ON_COMMAND(ID_CHANGE_COLOUR, &CNotePadeDemoDlg::OnChangeColour)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_CHANGE_TITLE, &CNotePadeDemoDlg::OnChangeTitle)
	ON_COMMAND(ID_EXIT, &CNotePadeDemoDlg::OnExit)
	ON_COMMAND(ID_FIND, &CNotePadeDemoDlg::OnFind)
	ON_COMMAND(ID_REPLACE, &CNotePadeDemoDlg::OnReplace)
	ON_REGISTERED_MESSAGE(WM_FINDREPLACE, &CNotePadeDemoDlg::OnFindReplace)
END_MESSAGE_MAP()


// CNotePadeDemoDlg 消息处理程序

BOOL CNotePadeDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 
	//设置字体
	HFONT hfont = CreateFont(32, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET
		, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH
		, L"黑体");
	//获取控件
	HWND hwnd = ::GetDlgItem(this->m_hWnd, IDC_EDIT);

	//设置字体大小
	::SendMessage(hwnd, WM_SETFONT, WPARAM(hfont), 0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNotePadeDemoDlg::OnPaint()
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
HCURSOR CNotePadeDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNotePadeDemoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CNotePadeDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//获取控件
	CWnd* wnd = GetDlgItem(IDC_EDIT);
	if (wnd != NULL) {
		wnd->MoveWindow(0, 0, cx, cy);
	}
}


//打开
void CNotePadeDemoDlg::OnMenuOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(TRUE);
	if (IDCANCEL == dlg.DoModal()) {
		return;
	}

	CString strpath = dlg.GetPathName();

	//打开文件,以读取的方式打开文件,读取文件编码为ANSI
	CFile file;
	if (FALSE == file.Open(strpath, CFile::modeRead)) {
		MessageBox(TEXT("打开文件失败"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		return;
	}
	char buff[255] = { 0 };
	CStringA msg;
	//一次读取一个字符
	while (file.Read(buff, 1)) {
		msg += buff;
	}

	ChangeCharSet charset;
	wchar_t* title_msg = charset.AnsiToUnicode(msg);
	//设置窗口
	SetDlgItemText(IDC_EDIT, title_msg);

	//设置窗口标题
	CString title;
	title.Format(TEXT("NodePadeDemo ——%s[%d字节]"), dlg.GetFileName(), file.GetLength());
	SetWindowText(title);

	file.Close();
}

//另存为
void CNotePadeDemoDlg::OnMenuSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL);
	if (IDCANCEL == dlg.DoModal()) {
		return;
	}
	CString path = dlg.GetPathName();
	CFile file;
	if (IDCANCEL == file.Open(path, CFile::modeCreate | CFile::modeWrite)) {
		MessageBox(TEXT("保存文件失败"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		return;
	}

	//读取控件上的所有文本
	CString msg;
	GetDlgItemText(IDC_EDIT, msg);

	ChangeCharSet charset;
	char* title_msg = charset.UnicodeToAnsi(msg);
	//宽字符写入
	file.Write(title_msg, strlen(title_msg));
	file.Close();

	//退出程序
	CDialogEx::OnOK();
}


void CNotePadeDemoDlg::OnChangeColour()
{
	// TODO: 在此添加命令处理程序代码
	//弹出颜色系统框
	CColorDialog color;
	if (IDCANCEL == color.DoModal()) {
		return;
	}
	//获取选择的颜色
	this->m_choice = color.GetColor();
	//更改控件的颜色,通过发送WM_CTLCOLOR消息来改变颜色
}


HBRUSH CNotePadeDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID()){
		case IDC_EDIT:
		{
			pDC->SetTextColor(m_choice);
			break;
		}
		default:
			break;
	}
	return hbr;
}


void CNotePadeDemoDlg::OnChangeTitle()
{
	// TODO: 在此添加命令处理程序代码
	CFontDialog dlg;
	if (IDCANCEL == dlg.DoModal()) {
		return;
	}

	//创建选择的字体
	CFont font;
	font.CreatePointFont(dlg.GetSize(), dlg.GetFaceName());

	//设置字体
	GetDlgItem(IDC_EDIT)->SetFont(&font);
}


void CNotePadeDemoDlg::OnExit()
{
	//退出程序
	CDialogEx::OnOK();
}

//查找对话框

void CNotePadeDemoDlg::OnFind()
{
	//非模态对话框
	CFindReplaceDialog* dlg = new CFindReplaceDialog;

	//TRUE代表是查找框，FALSE代表是替换框
	dlg->Create(TRUE, NULL, NULL);

	dlg->ShowWindow(SW_SHOW);

	//不需要delete，CFindReplaceDialog类内部处理了。不会导致内存泄漏

	//此外，还需要向系统注册一个消息
	this->m_flag = TRUE;
}


void CNotePadeDemoDlg::OnReplace()
{
	//非模态对话框
	CFindReplaceDialog* dlg = new CFindReplaceDialog;

	//TRUE代表是查找框，FALSE代表是替换框
	dlg->Create(FALSE, NULL, NULL);

	dlg->ShowWindow(SW_SHOW);

	this->m_flag = FALSE;
}

//处理查找和替换操作
LRESULT CNotePadeDemoDlg::OnFindReplace(WPARAM wparam, LPARAM lparam) {
	CFindReplaceDialog* lpfindReplace = CFindReplaceDialog::GetNotifier(lparam);  
	if (lpfindReplace == nullptr) {
		return 0;
	}
	//如果要退出窗口
	if (lpfindReplace->IsTerminating()) {
		return 0;
	}
	//获取需要查找字符串
	CString str_find = lpfindReplace->GetFindString();
	//获取要替换的字符串
	CString str_replaces = lpfindReplace->GetReplaceString();

	BOOL SearchDownFlag = lpfindReplace->SearchDown();//判断是否向下查找,TRUE代表向下查找

	BOOL MatchCass = lpfindReplace->MatchCase();//判断是否区分大小

	//获取记事本内的文本
	CString strContent;
	GetDlgItemText(IDC_EDIT, strContent);

	//获取记事本文本控件
	CEdit* lpEdit = (CEdit*)GetDlgItem(IDC_EDIT);

	//查找
	if (this->m_flag == TRUE) {
		//获取光标起始，结束位置
		lpEdit->GetSel(this->nStartIndex, this->nEndIndex);

		if (SearchDownFlag) {
			//向下查找
			//从结束位置开始向下找
			this->nStartIndex = strContent.Find(str_find, this->nEndIndex);
			if (this->nStartIndex != -1) {
				//找到了，标记这个字符串
				lpEdit->SetSel(this->nStartIndex, this->nStartIndex + str_find.GetLength());
				lpEdit->SetFocus();
			}
			else {
				////从头开始找
				//this->nStartIndex = strContent.Find(str_find, 0);
					//文中没有这个字符串
				CString msg;
				msg.Format(L"在下文中没有找到%s这个字符串", str_find.GetString());
				MessageBox(msg, L"警告", MB_OK|MB_ICONWARNING);
				return 0;

				//else {
				//	//找到了，标记这个字符串
				//	MessageBox(L"在上文中找到这个字符串", L"提示");
				//	lpEdit->SetSel(this->nStartIndex, this->nStartIndex + str_find.GetLength());
				//	lpEdit->SetFocus();
				//}
			}
		}
		else {
			//向上查找,反转字符串
			strContent = strContent.MakeReverse();
			CString str_refind = str_find.MakeReverse();
			this->nStartIndex = strContent.Find(str_refind, strContent.GetLength() - this->nStartIndex);

			if (this->nStartIndex != -1) {
				//设置光标
				this->nEndIndex = strContent.GetLength() - this->nStartIndex;
				lpEdit->SetSel(nEndIndex - str_find.GetLength(), nEndIndex);
				lpEdit->SetFocus();
			}
			else {
				CString msg;
				msg.Format(L"在上文中没有找到%s这个字符串", str_find.GetString());
				MessageBox(msg, L"警告", MB_OK | MB_ICONWARNING);
				return 0;
			}
		}
	}
	//替换
	else {
		if (lpfindReplace->ReplaceCurrent()) {
			this->nStartIndex = strContent.Find(str_find);
			if (this->nStartIndex == -1) {
				MessageBox(L"查不到这个字符串", L"警告", MB_OK);
				return 0;
			}
			else {
				this->nEndIndex = this->nStartIndex + str_find.GetLength();

				//字符串剪切
				CString left = strContent.Left(nStartIndex);
				CString right = strContent.Right(strContent.GetLength() - nEndIndex);
				strContent = left + str_replaces + right;
				lpEdit->SetWindowText(strContent);
			}
		}

		//替换全部
		if (lpfindReplace->ReplaceAll()) {
			int ntimes = strContent.Replace(str_find, str_replaces);
			lpEdit->SetWindowText(strContent);
			CString msg;
			msg.Format(L"替换成功,替换了%d处", ntimes);
			MessageBox(msg, L"提示", MB_OK);
		}
	}
	return 0;
}
