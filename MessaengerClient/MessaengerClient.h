
// MessaengerClient.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.


// CMessaengerClientApp:
// 이 클래스의 구현에 대해서는 MessaengerClient.cpp을 참조하십시오.
//

class CMessaengerClientApp : public CWinApp
{
public:
	CMessaengerClientApp();
	Lobby  *m_pLobby;
	CClientSock  *m_pClient;
	BOOL bConnect; // 연결 유무
	CString userID;
	std::vector<CString> m_friendName;
	LONG m_publicKey;

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

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
