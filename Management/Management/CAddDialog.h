#pragma once
#include "afxdialogex.h"
#include<vector>


// CAddDialog 对话框

class CAddDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDialog)

public:
	CAddDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


	std::vector<CString>work_Type = { L"研发部",L"人事部",L"财务部",L"销售部" };

	void InitDeparment() {
		for (int i = 0; i < work_Type.size(); i++) {
			m_deparment.AddString(work_Type[i]);
		}
		m_deparment.SetCurSel(0);

	}
public:
	CString deparment_name = L" ";
	CString job_name = L" ";
	int m_number;
	CString m_worknum;
	int m_sex;
	int m_age;
	CComboBox m_deparment;
	CComboBox m_job;
	float m_money;
	COleDateTime m_joinTile;
	COleDateTime m_leaveTime;
	CString m_phone;
	CString m_address;
	afx_msg void OnBnClickedBtnAdd();

	//返回添加的信息
	void GetMsg(std::vector<CString>& msg) {
		msg.clear();
		CString turn;
		turn.Format(L"%05d", m_number);
		msg.push_back(turn);
		msg.push_back(m_worknum);
		msg.push_back(m_sex ? L"女" : L"男");

		turn.Format(L"%d", m_age);
		msg.push_back(turn);

		//获取部门信息
		msg.push_back(deparment_name);

		//获取工作岗位信息
		msg.push_back(job_name);

		//住址
		msg.push_back(m_address);
		//入职时间
		msg.push_back(m_joinTile.Format(L"%Y-%m-%d"));
		//离职时间
		if (m_leaveTime != m_joinTile) {
			msg.push_back(m_leaveTime.Format(L"%Y-%m-%d"));
		}
		else {
			msg.push_back(L"没有离职");
		}
		//薪资
		turn.Empty();
		turn.Format(L"%0.2f", m_money);
		msg.push_back(turn);
		//电话
		msg.push_back(m_phone);
	}
	virtual BOOL OnInitDialog();
};
