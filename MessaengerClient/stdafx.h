
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#define UWM_TREEMOVECOMPLETE     (WM_USER + 6)   // A tree item has been moved.
#define UWM_TREEITEMDELETED      (WM_USER + 7)   // A tree item has been deleted
#define UWM_TREEBEGINEDIT        (WM_USER + 8)   // A tree item is being edited
#define UWM_TREEENDEDIT          (WM_USER + 9)   // A tree item label has finished being edited

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원


#include <afxsock.h>            // MFC 소켓 확장

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


