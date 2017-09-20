
// MessaengerClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMessaengerClientApp:
// �� Ŭ������ ������ ���ؼ��� MessaengerClient.cpp�� �����Ͻʽÿ�.
//

class CMessaengerClientApp : public CWinApp
{
public:
	CMessaengerClientApp();
	Lobby  *m_pLobby;
	CClientSock  *m_pClient;
	BOOL bConnect; // ���� ����
	CString userID;
	std::vector<CString> m_friendName;
	LONG m_publicKey;

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	void LoginBtnResponse();

public:
	void LoginData(CString Data);
	void LobbyData(CString Data);
	void RoomData(CString Data);
	void WhisperData(CString Data);
	void FriendData(CString Data);
	void ReceiveData(void);
	void ServerConnect(void);
	void ServerDisconnect(void);
	void CloseClient(void);
	void SendData(CString& strData);
//	virtual int ExitInstance();
	BOOL m_Destroy;
};

extern CMessaengerClientApp theApp;
