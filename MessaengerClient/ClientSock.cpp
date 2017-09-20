// ClientSock.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MessaengerClient.h"
#include "ClientSock.h"
#include "afxdialogex.h"


// CClientSock

CClientSock::CClientSock()
{
}

CClientSock::~CClientSock()
{
}


// CClientSock 멤버 함수

void CClientSock::OnClose(int nErrorCode)
{
	MessageBox(NULL, _T("서버가 종료 되었습니다."), _T("알림"), MB_ICONSTOP);
	CMessaengerClientApp *pApp = (CMessaengerClientApp*)AfxGetApp();
	pApp->CloseClient();

	CAsyncSocket::OnClose(nErrorCode);
}

void CClientSock::OnConnect(int nErrorCode)
{
	CMessaengerClientApp *pApp = (CMessaengerClientApp*)AfxGetApp();
	if (nErrorCode == 0)
	{
		// 로그인 데이터 전송
		pApp->bConnect = TRUE;
		CString str, userID, userPASS;

		pApp->m_pMainWnd->GetDlgItemText(EDIT_ID, userID);
		pApp->m_pMainWnd->GetDlgItemText(EDIT_PASS, userPASS);

		if (userID != _T("") || userPASS != _T("")) {
			// 0 |/| 로그인:0 / 로그아웃 : 1 |/| 아 이 디 |/| 비밀번호
			str.Format(_T("\\x80x0|/|0|/|%s|/|%s"), userID, userPASS);
			pApp->SendData(str);
		}
	}
	else
	{
		MessageBox(NULL, _T("연결 실패!"), _T("접속"), MB_ICONSTOP);
	}

	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSock::OnReceive(int nErrorCode)
{
	CMessaengerClientApp *pApp = (CMessaengerClientApp*)AfxGetApp();
	pApp->ReceiveData();

	CAsyncSocket::OnReceive(nErrorCode);
}
