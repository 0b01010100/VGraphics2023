#pragma once
#include <iostream>
#include <d3d11.h>
#include <windows.h>
#include<string>
#include <sstream>
//Used for Error Handling related to windows only.
#define DX11_ERROR(hr, error)\
{\
	if(FAILED(hr)){\
		std::wostringstream ws; \
		ws << L"DX11 ERROR \n" << error<< L"\n"<< L"Error Code: " << hr << "\n"; \
		OutputDebugString(ws.str().c_str()); \
		MessageBox(0, ws.str().c_str(), L"DX11 ERROR" , 0);\
		return;\
	}\
\
}
//Used for warrning Handling related to windows only.
#define DX11_WARNING(expr,err_code, details)\
{\
	if(expr != 0){\
		std::wostringstream ws; \
		ws << L"DX11 WARNING \n" << details << "\n" << L"Error Code: " << err_code << "\n"; \
		OutputDebugString(ws.str().c_str()); \
		MessageBox(0, ws.str().c_str(), L"DX11 WARNING" , 0);\
	}\
\
}
//Assert if value is null
#include <assert.h>
#define Win32_ERROR(arg, error)\
{\
	if(arg == 0){\
		std::wostringstream ws; \
		ws << error<< L"\n"; \
		OutputDebugString(ws.str().c_str()); \
		MessageBox(0, ws.str().c_str(), L"WIN32 Error" , 0);\
	}\
}