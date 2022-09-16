#pragma once

#include"framework.h"

class ChangeCharSet{
private:
	wchar_t* w_charbuff;
	char* charbuff;
public:
	ChangeCharSet()
		:w_charbuff(nullptr), charbuff(nullptr)
	{}
	~ChangeCharSet() {
		if (w_charbuff != nullptr) {
			delete[] w_charbuff;
			w_charbuff = nullptr;
		}
		if (charbuff != nullptr) {
			delete[] charbuff;
			charbuff = nullptr;
		}
	}

	//ANSI=>Unicode
	wchar_t* AnsiToUnicode(const char* str) {
		//-1会自动推导字符串长度
		if (w_charbuff != nullptr) {
			delete[] w_charbuff;
			w_charbuff = nullptr;
		}
		DWORD dsize = ::MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
		w_charbuff = new wchar_t[dsize];
		::MultiByteToWideChar(CP_ACP, 0, str, -1, w_charbuff, dsize);
		return w_charbuff;
	}

	//Uncode=>ANSI
	char* UnicodeToAnsi(const wchar_t* w_str) {
		if (charbuff != nullptr) {
			delete[] charbuff;
			charbuff = nullptr;
		}
		DWORD dsize = ::WideCharToMultiByte(CP_ACP, 0, w_str, -1, NULL, 0, NULL, NULL);
		charbuff = new char[dsize];
		::WideCharToMultiByte(CP_ACP, 0, w_str, -1, charbuff, dsize, NULL, NULL);
		return charbuff;
	}

	//Unicode=>UTF-8
	char* UnicodeToUTF_8(const wchar_t* w_str) {
		if (charbuff != nullptr) {
			delete[] charbuff;
			charbuff = nullptr;
		}
		DWORD dsize = ::WideCharToMultiByte(CP_UTF8, 0, w_charbuff, -1, NULL, 0, NULL, NULL);
		charbuff = new char[dsize];
		::WideCharToMultiByte(CP_UTF8, 0, w_charbuff, -1, charbuff, dsize, NULL, NULL);
		return charbuff;
	}

	//UTF-8=>Unicode
	wchar_t* UTF_8ToUnicode(const char* str) {
		if (w_charbuff != nullptr) {
			delete[] w_charbuff;
			w_charbuff = nullptr;
		}
		DWORD dsize = ::MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
		w_charbuff = new wchar_t[dsize];
		::MultiByteToWideChar(CP_UTF8, 0, str, -1, w_charbuff, dsize);
		return w_charbuff;
	}

	//ANSI=>UTF-8
	char* AnsiToUTF_8(const char* str) {
		//ANSI=>Uncode
		w_charbuff = AnsiToUnicode(str);
		//Unicode=>UTF-8
		charbuff = UnicodeToUTF_8(w_charbuff);
		return charbuff;
	}

	//UTF-8=>ANSI
	char* UTF_8ToAnsi(const char* str) {
		//UTF-8->Unicode
		w_charbuff = UTF_8ToUnicode(str);
		//Unicode->ANSI
		charbuff = UnicodeToAnsi(w_charbuff);
		return charbuff;
	}
};

