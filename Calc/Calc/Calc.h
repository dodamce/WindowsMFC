#pragma once
#include<Windows.h>
#include"resource.h"
#include<string>
#include<map>
#include <functional>

HINSTANCE g_hInstance;

std::wstring ShowText;//�����������ʾ���ַ���
std::wstring PreText;
bool init = false;//�ж��ַ����Ƿ�ɾ����0
bool is_op = false;//�ж��Ƿ��²�����ť
char op = 0;//��¼Ҫ�Ĳ���
double num = 0.0;//��¼��������
double ret = 0.0;

INT_PTR CALLBACK CalcProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		//���ش���ͼ��
		HICON Hicon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1));

		//�������ô���ͼ�����Ϣ
		SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)Hicon);//���ô�ͼ��
		SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)Hicon);//����Сͼ��
		//��������
		HFONT hfont=CreateFont(32, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET
			, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH
			, L"����");
		HFONT hfont_pre = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET
			, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH
			, L"����");
		//��ȡ�ؼ�
		HWND text_hwnd=GetDlgItem(hwnd, IDC_STATIC_SHOWTEXT);
		HWND pre_hwnd = GetDlgItem(hwnd, IDC_STATIC_PERTEXT);
		SendMessage(text_hwnd, WM_SETFONT, WPARAM(hfont), 0);
		SendMessage(pre_hwnd, WM_SETFONT, WPARAM(hfont_pre), 0);
		break;
	}
	case WM_COMMAND:
	{
		init = false;
		//��װ������װ����
		std::map<char, std::function<float(float, float)>>opMap =
		{
		  {'+',[](float x,float y) {return x + y; }},
		  {'-',[](float x,float y) {return x - y; }},
		  {'*',[](float x,float y) {return x * y; }},
		  {'/',[](float x,float y) {return x / y; }},
		};

		switch (LOWORD(wParam))
		{
		case IDC_BNT_NUM0:
			//���ַ�����
			ShowText += L"0";
			break;
		case IDC_BNT_NUM1:
			ShowText += L"1";
			break;
		case IDC_BNT_NUM2:
			ShowText += L"2";
			break;
		case IDC_BNT_NUM3:
			ShowText += L"3";
			break;
		case IDC_BNT_NUM4:
			ShowText += L"4";
			break;
		case IDC_BNT_NUM5:
			ShowText += L"5";
			break;
		case IDC_BNT_NUM6:
			ShowText += L"6";
			break;
		case IDC_BNT_NUM7:
			ShowText += L"7";
			break;
		case IDC_BNT_NUM8:
			ShowText += L"8";
			break;
		case IDC_BNT_NUM9:
			ShowText += L"9";
			break;
		case IDC_BNT_CLEAR:
			PreText.clear();
			ShowText.clear();
			ret = 0;
			num = 0;
			op = 0;
			SetDlgItemText(hwnd, IDC_STATIC_SHOWTEXT, L"0");
			init = true;
			break;
		case IDC_BNT_DELEAT:
		{
			if (ShowText.size() == 0) {
				SetDlgItemText(hwnd, IDC_STATIC_SHOWTEXT, L"0");
				init = true;
			}
			else if (ShowText.size() > 0) {
				ShowText.pop_back();
				if (ShowText.size() == 0) {
					SetDlgItemText(hwnd, IDC_STATIC_SHOWTEXT, L"0");
					init = true;
				}
			}
			break;
		}
		case IDC_BNT_ADD:
		{
			if (ShowText.size() != 0) {
				if (op != 0) {
					//��ʱ�Ѿ��в�������˵��û�а�=�ţ���Ҫ����
					//�����Ȳ�����
					break;
				}
				op = '+';
				ret = _wtoi(PreText.c_str());
				PreText = ShowText;
				PreText += L"+";
				ShowText.clear();
			}
			break;
		}
		case IDC_BNT_MIN:
		{
			if (ShowText.size() != 0) {
				if (op != 0) {
					break;
				}
				op = '-';
				PreText = ShowText;
				ret = _wtoi(PreText.c_str());
				PreText += L"-";
				ShowText.clear();
			}
			break;
		}
		case IDC_BNT_SUB:
		{
			if (ShowText.size() != 0) {
				if (op != 0) {
					break;
				}
				op = '*';
				PreText = ShowText;
				ret = _wtoi(PreText.c_str());
				PreText += L"��";
				ShowText.clear();
			}
			break;
		}
		case IDC_BNT_DIV:
		{
			if (ShowText.size() != 0) {
				if (op != 0) {
					break;
				}
				op = '/';
				PreText = ShowText;
				ret = _wtoi(PreText.c_str());
				PreText += L"��";
				ShowText.clear();
			}
			break;
		}
		case IDC_BNT_RET:
		{
			if (op != 0) {
				num = _wtoi(ShowText.c_str());
				PreText += std::to_wstring(num);
				ret = opMap[op](ret, num);
				ShowText = std::to_wstring(ret);
				//��շ���
				op = 0;
			}
			break;
		}
		/*case IDC_BNT_REM:
		{
			double num= _wtoi(ShowText.c_str());
			ShowText = std::to_wstring((int)num*100);
			break;
		}
		case IDC_BNT_POINT:
			ShowText += L".";
			break;*/
		default:
			break;
		}
		//�����ı�
		if (init == false) {
			SetDlgItemText(hwnd, IDC_STATIC_SHOWTEXT, ShowText.c_str());
		}
		SetDlgItemText(hwnd, IDC_STATIC_PERTEXT, PreText.c_str());
		break;
	}
	case WM_CLOSE:
		EndDialog(hwnd, IDOK);
		break;
	default:
		break;
	}
	return FALSE;
}