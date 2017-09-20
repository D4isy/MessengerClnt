// ClientSock.cpp : ���� �����Դϴ�.
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


// CClientSock ��� �Լ�

void CClientSock::OnClose(int nErrorCode)
{
	MessageBox(NULL, _T("������ ���� �Ǿ����ϴ�."), _T("�˸�"), MB_ICONSTOP);
	CMessaengerClientApp *pApp = (CMessaengerClientApp*)AfxGetApp();
	pApp->CloseClient();

	CAsyncSocket::OnClose(nErrorCode);
}

void CClientSock::OnConnect(int nErrorCode)
{
	CMessaengerClientApp *pApp = (CMessaengerClientApp*)AfxGetApp();
	if (nErrorCode == 0)
	{
		// �α��� ������ ����
		pApp->bConnect = TRUE;
		CString str, userID, userPASS;

		pApp->m_pMainWnd->GetDlgItemText(EDIT_ID, userID);
		pApp->m_pMainWnd->GetDlgItemText(EDIT_PASS, userPASS);

		if (userID != _T("") || userPASS != _T("")) {
			// 0 |/| �α���:0 / �α׾ƿ� : 1 |/| �� �� �� |/| ��й�ȣ
			str.Format(_T("\\x80x0|/|0|/|%s|/|%s"), userID, userPASS);
			pApp->SendData(str);
		}
	}
	else
	{
		MessageBox(NULL, _T("���� ����!"), _T("����"), MB_ICONSTOP);
	}

	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSock::OnReceive(int nErrorCode)
{
	CMessaengerClientApp *pApp = (CMessaengerClientApp*)AfxGetApp();
	pApp->ReceiveData();

	CAsyncSocket::OnReceive(nErrorCode);
}
