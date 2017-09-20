
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#define UWM_TREEMOVECOMPLETE     (WM_USER + 6)   // A tree item has been moved.
#define UWM_TREEITEMDELETED      (WM_USER + 7)   // A tree item has been deleted
#define UWM_TREEBEGINEDIT        (WM_USER + 8)   // A tree item is being edited
#define UWM_TREEENDEDIT          (WM_USER + 9)   // A tree item label has finished being edited

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����


#include <afxsock.h>            // MFC ���� Ȯ��

#include <iostream>
#include <vector>
#include <map>
// #import <msxml3.dll> named_guids raw_interfaces_only	//	XML parser

using namespace std;
enum { MSG_ME, MSG_YOU };

int strsplit(CString &src, CString &c, CString *dst, int max);

#include "./encrypt/des.h"
#include "./encrypt/sha1.h"
#include "./encrypt/hmac_sha1.h"
#include "./encrypt/rsa.h"

#include "ClientSock.h"
#include "COleRichEditCtrl.h"
#include "TreeCtrlDrag.h"
#include "Room.h"
#include "RoomList.h"
#include "FriendList.h"
#include "RoomCreate.h"
#include "Lobby.h"
#include "Register.h"
#include "PassHelp.h"
#include "MessaengerClient.h"
#include "MessaengerClientDlg.h"
#include <afxdisp.h>
#include <afxdhtml.h>


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


