
// MessaengerClient.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "MessaengerClient.h"
#include "MessaengerClientDlg.h"
#include "CWebBrowser2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMessaengerClientApp

BEGIN_MESSAGE_MAP(CMessaengerClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMessaengerClientApp 생성

CMessaengerClientApp::CMessaengerClientApp()
	: m_Destroy(FALSE)
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
	m_pClient = NULL;
	bConnect = FALSE;
	m_publicKey = 0;
}


// 유일한 CMessaengerClientApp 개체입니다.

CMessaengerClientApp theApp;


// CMessaengerClientApp 초기화

BOOL CMessaengerClientApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxInitRichEdit2();

	AfxEnableControlContainer();

	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// MFC 컨트롤의 테마를 사용하기 위해 "Windows 원형" 비주얼 관리자 활성화
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	LoginBtnResponse();

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}



void CMessaengerClientApp::LoginBtnResponse()
{
	CMessaengerClientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == ID_LOGIN)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
		MessageBox(NULL, _T("LOGIN"), _T("창"), IDOK);
	}
	else if (nResponse == ID_REGISTER)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
		MessageBox(NULL, _T("REGISTER"), _T("창"), IDOK);
	}
	else if (nResponse == ID_ACC_SEARCH)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
		MessageBox(NULL, _T("SEARCH"), _T("창"), IDOK);
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "경고: 대화 상자를 만들지 못했으므로 응용 프로그램이 예기치 않게 종료됩니다.\n");
		TRACE(traceAppMsg, 0, "경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n");
	}
}

void CMessaengerClientApp::LoginData(CString Data)
{
	// 0 |/| 로그인:0 / 로그아웃:1 |/| 아 이 디 |/| 비밀번호
	// 0 |/| 성공:0   / 실패:1     |/| 공개키 생성(serv), 비밀키 서버 저장 |/| 소수
	// 0 |/| 회원가입:2 |/| 허용:0, 비허용:1
	// 0 |/| 비번찾기:3 |/| 허용:0, 비허용:1
	CString token[5];
	int nPos = 0;

	nPos = strsplit(Data, CString("|/|"), token, 5);
	//for (int i = 0; i < nPos; i++) {
	//	str.Format(_T("[%d] %s"), i + 1, token[i]);
	//	MessageBox(NULL, str, _T(""), 0);
	//}

	CString sendData;
	if (token[1] == _T("0")) {
		// 성공
		m_pMainWnd->GetDlgItemText(EDIT_ID, this->userID);
		m_publicKey = _ttoi(token[2]);
		SetPrime(_ttoi(token[3]));

		// 로그인 숨기기
		// PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);
		if (!m_pMainWnd->SetLayeredWindowAttributes(0, 0, LWA_ALPHA)) {
			AfxMessageBox(_T("Fail to SetWindowLong..."));
		}

		// 로비창 띄우기
		m_pLobby = new Lobby(m_pMainWnd);
		// lobby->DoModal();
		m_pLobby->Create(IDD_LOBBY, m_pMainWnd);
		m_pLobby->ShowWindow(SW_SHOW);

		// 친구목록 요청
		sendData = _T("\\x80x4|/|9|/|(암호화)");
		SendData(sendData);

		// 룸 리스트 요청
		sendData = _T("\\x80x1|/|3|/|(암호화)");
		SendData(sendData);
		// MessageBox(editID + " " + editPASS, _T("LOGIN"));
		MessageBox(NULL, _T("로그인 성공"), _T("알림"), MB_ICONINFORMATION);
	}
	else if (token[1] == _T("2")) {
		// token[2] : 성공:0/실패:1
		if (token[2] == _T("0")) {
			MessageBox(NULL, _T("계정 생성 성공!"), _T("알림"), MB_ICONINFORMATION);
		}
		else {
			MessageBox(NULL, _T("계정 생성 실패!"), _T("알림"), MB_ICONINFORMATION);
		}
	}
	else if (token[1] == _T("3")) {
		// token[2] : 성공:0/실패:1
		// token[3] : 비밀번호
		if (token[2] == _T("0")) {
			CString str;
			str.Format(_T("계정 찾기 성공!\n임시 비밀번호: %s"), token[3]);
			MessageBox(NULL, str, _T("알림"), MB_ICONINFORMATION);
		}
		else {
			MessageBox(NULL, _T("계정 찾기 실패!"), _T("알림"), MB_ICONINFORMATION);
		}
	}
	else {
		// 실패
		sendData = _T("아이디 또는 비밀번호가 맞지 않습니다.");
		MessageBox(NULL, sendData, _T("알림"), MB_ICONSTOP);
	}
}

void CMessaengerClientApp::LobbyData(CString Data)
{
	// 1 |/| 리스트:2 |/| 리스트 개수 |/| 룸 번호,타이틀,방장, ... |/| (원본과 암호화 값 두 개 전송)
	// 1 |/| 입장:1,생성:0 |/| 룸 번호 |/| 입장:1,허용:0 |/| 닉네임 |/| (원본과 암호화 값 두 개 전송)
	CString token[6];
	int nPos = 0;

	nPos = strsplit(Data, CString("|/|"), token, 6);
	//for (int i = 0; i < nPos; i++) {
	//	str.Format(_T("[%d] %s"), i + 1, token[i]);
	//	MessageBox(NULL, str, _T(""), 0);
	//}

	if (token[1] == _T("0")) {	// 생성
		// token[2] : 룸 번호
		// token[3] : 입장:1,허용:0
		// token[4] : 닉네임
		if (m_pLobby) {
			// [To서버] 채팅방 입장 요구
			if (!m_pLobby->m_pRoomList) {		// 방 리스트 생성
				m_pLobby->m_pRoomList = new CRoomList(m_pLobby);
				m_pLobby->m_pRoomList->Create(IDD_TABCTL, m_pLobby);
				m_pLobby->OnClickedTalklist();
			}

			// 방 입장
			m_pLobby->m_pRoomList->InsertRoom(m_pLobby->TitleString, _ttoi(token[2]));
			CString msg;
			msg.Format(_T("%s님이 접속하셨습니다."), token[4]);
			m_pLobby->m_pRoomList->SendRoomMessage(_ttoi(token[2]), MSG_ME, token[4], msg);
		}
	}
	else if (token[1] == _T("1")) {	// 입장
		// token[2] : 대화요청:1, 입장:0
		// token[3] : 룸 번호
		// token[4] : 닉네임
		// token[5] : 암호화
		if (token[2] == _T("0")) {	// 입장
			if (m_pLobby) {
				// [To서버] 채팅방 입장 요구
				if (!m_pLobby->m_pRoomList) {		// 방 리스트 생성
					m_pLobby->m_pRoomList = new CRoomList(m_pLobby);
					m_pLobby->m_pRoomList->Create(IDD_TABCTL, m_pLobby);
					m_pLobby->OnClickedTalklist();
				}

				// 방 입장
				m_pLobby->m_pRoomList->InsertRoom(m_pLobby->TitleString, _ttoi(token[3]));
				CString msg;
				msg.Format(_T("%s님이 접속하셨습니다."), token[4]);
				m_pLobby->m_pRoomList->SendRoomMessage(_ttoi(token[3]), MSG_ME, token[4], msg);

				CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
				if (pApp) {
					// 접속 메시지 전송 요청
					CString sendData;
					sendData.Format(_T("\\x80x1|/|1|/|1|/|%u|/|암호화"), _ttoi(token[3]));
					pApp->SendData(sendData);
				}
			}
		}
		else if (token[2] == _T("1")) {	// 대화
			CString msg;
			msg.Format(_T("%s님이 접속하셨습니다."), token[4]);
			if (m_pLobby) {
				if (m_pLobby->m_pRoomList) {
					m_pLobby->m_pRoomList->SendRoomMessage(_ttoi(token[3]), MSG_YOU, token[4], msg);
				}
			}
		}
		else if (token[2] == _T("2")) {	// 아웃
			CString msg;
			msg.Format(_T("%s님이 종료하셨습니다."), token[4]);
			if (m_pLobby) {
				if (m_pLobby->m_pRoomList) {
					m_pLobby->m_pRoomList->SendRoomMessage(_ttoi(token[3]), MSG_YOU, token[4], msg);
				}
			}
		}
		else if (token[2] == _T("3")) {	// 차단 메시지
			CString msg;
			msg.Format(_T("차단 되었습니다."));
			MessageBox(NULL, msg, _T("알림"), MB_ICONSTOP);
		}
	}
	else if (token[1] == _T("2")) { // 방 리스트
		// token[2] : 리스트 개수
		// token[3] : 룸 번호,타이틀,방장, ... 
		// token[4] : (원본과 암호화 값 두 개 전송)
		UINT32 listCount = _ttoi(token[2]);
		UINT32 Count = 0;
		nPos = 0;
		if (listCount > 0) {
			int idx = 0;
			CString RoomIdx, Title, MasterAccount;

			m_pLobby->m_ctrlList.DeleteAllItems();

			CString subString;
			while ((subString = token[3].Tokenize(_T(","), nPos)) != _T("")) {
				switch (idx) {
				case 0:	RoomIdx = subString; break;	// 룸번호

				case 1:	Title = subString; break;	// 타이틀

				case 2:		// 방장
					MasterAccount = subString;

					if (m_pLobby) {
						Count = m_pLobby->m_ctrlList.GetItemCount();
						m_pLobby->m_ctrlList.InsertItem(Count, RoomIdx);
						m_pLobby->m_ctrlList.SetItem(Count, 1, LVIF_TEXT, Title, 0, 0, 0, NULL);
						m_pLobby->m_ctrlList.SetItem(Count, 2, LVIF_TEXT, MasterAccount, 0, 0, 0, NULL);
					}
					break;
				}

				idx = (idx + 1) % 3;
			}
		}
	}
}

void CMessaengerClientApp::RoomData(CString Data)
{
	// 2 |/| 룸 번호    |/| 닉 네 임  |/| 입력 내용 + 시간(serv)
	// 2 |/| -1:방 종료 |/| 룸 번호 
	CString token[6];
	int nPos = 0;

	nPos = strsplit(Data, CString("|/|"), token, 4);
	//for (int i = 0; i < nPos; i++) {
	//	str.Format(_T("[%d] %s"), i + 1, token[i]);
	//	MessageBox(NULL, str, _T(""), 0);
	//}

	if (token[1] == _T("-1")) {
		// token[2] : 방 번호
		if (m_pLobby) {
			if (m_pLobby->m_pRoomList) {
				INT32 idx, count=0;
				INT32 data = _ttoi(token[2]);
				std::vector<INT32>::iterator iter;
				for (iter = m_pLobby->m_pRoomList->m_pTabIdx.begin(); iter != m_pLobby->m_pRoomList->m_pTabIdx.end(); iter++, count++) {
					idx = (*iter);
					if (idx == data) {
						m_pLobby->m_pRoomList->SelectRoomMapIndex(idx);
						m_pLobby->m_pRoomList->m_Tab.SetCurSel(count);
						m_pLobby->m_pRoomList->RemoveRoom();
						break;
					}
				}
			}
		}
	}
	else {
		if (m_pLobby) {
			if (m_pLobby->m_pRoomList) {
				m_pLobby->m_pRoomList->SendRoomMessage(_ttoi(token[1]), MSG_YOU, token[2], token[3]);
			}
		}
	}
}

void CMessaengerClientApp::WhisperData(CString Data)
{
	// recv: 3 |/| 0: 승인 |/| 룸 번호  |/| 닉 네 임 |/| 암호화
	// send: 3 |/| 룸 번호 |/| 닉 네 임 |/| 암호화
	CString token[6];
	int nPos = 0;

	nPos = strsplit(Data, CString("|/|"), token, 6);
	//for (int i = 0; i < nPos; i++) {
	//	str.Format(_T("[%d] %s"), i + 1, token[i]);
	//	MessageBox(NULL, str, _T(""), 0);
	//}

	if (token[1] == _T("0")) {
		//token[2] : 룸 번호
		//token[3] : 닉네임
		//token[4] : 암호화
		// 닉네임을 탭이름으로 하는 탭 생성 (완료)
		if (m_pLobby) {
			// Lobby 리스트에 귓속말 온 아이디 넣기 (완료)
			// 귓말은 나가면 Lobby 리스트에 해당 아이디 삭제하기 (완료)

			if (m_pLobby->m_WhispIndex[_ttoi(token[2])] != _T("")) { // 존재한다면 그냥 작업 취소
				return;
			}

			m_pLobby->m_WhispIndex[_ttoi(token[2])] = token[3];
			m_pLobby->m_ctrlListWhisp.InsertItem(m_pLobby->m_ctrlListWhisp.GetItemCount(), token[3]);

			// 채팅방 탭 생성
			if (!m_pLobby->m_pRoomList) {		// 방 리스트 생성
				m_pLobby->m_pRoomList = new CRoomList(m_pLobby);
				m_pLobby->m_pRoomList->Create(IDD_TABCTL, m_pLobby);
				m_pLobby->OnClickedTalklist();
			}

			// 방 입장
			m_pLobby->m_pRoomList->InsertRoom(token[3], _ttoi(token[2]));
			CString msg;
			msg.Format(_T("%s님이 접속하셨습니다."), token[3]);
			m_pLobby->m_pRoomList->SendRoomMessage(_ttoi(token[3]), MSG_ME, token[3], msg);
		}
	}
	else if (token[1] == _T("3")) {
		if (m_pLobby) {
			if (m_pLobby->m_pFriendList) {
				m_pLobby->m_pFriendList->DeleteSelected();
			}
		}
	}
}

void CMessaengerClientApp::FriendData(CString Data)
{
	// 4 |/| 0: 추가요청   |/| 추가할 닉네임
	// 4 |/| 1: 허    용   |/| 추가할 닉네임
	// 4 |/| 2: 대화요청   |/| 닉네임
	// 4 |/| 9: 친구목록   |/| 닉네임1, 닉네임2, ...
	CString token[6];
	int nPos = 0;

	nPos = strsplit(Data, CString("|/|"), token, 6);
	
	if (token[1] == _T("1")) {
		// 허 용
		if (m_pLobby) {
			if (m_pLobby->m_pFriendList) {
				CFriendList *pFriendList = m_pLobby->m_pFriendList;
				pFriendList->m_Tree.InsertItem(token[2], 2, 2, pFriendList->m_hItemDrag);
			}

			CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
			if (pApp) {
				pApp->m_friendName.push_back(token[2]);
			}
		}
	}
	else if (token[1] == _T("9")) {
		// 친구목록
		CString token2[1024];
		nPos = strsplit(token[2], CString(","), token2, 1024);
		CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
		if (pApp) {
			pApp->m_friendName.clear();
			for (int i = 0; i < nPos; i++) {
				pApp->m_friendName.push_back(token2[i]);
			}
		}
	}
}

void CMessaengerClientApp::ReceiveData(void)
{
	TCHAR temp[10240];
	memset(temp, 0, 10240);
	m_pClient->Receive(temp, sizeof temp);
	CString str;
	str = temp;

	if (m_publicKey > 0) {
		CString token[4096];
		int nPos = 0;

		nPos = strsplit(str, CString(" "), token, 4096);

		char sendDataConv[4096];
		long sendDataConv2[4096];

		for (int i = 0; i < nPos; i++) {
			sendDataConv2[i] = _ttoi(token[i]);
		}

		Make_Plain_text(sendDataConv2, nPos, sendDataConv, m_publicKey);
		str = CA2T(sendDataConv);
	}
	str.Trim();

	CString token[20];
	int nPos = 0;

	nPos = strsplit(str, CString(_T("\\x80x")), token, 20);

	for (int i = 0; i < nPos; i++) {
		str = token[i];

		CString type = str.Left(1);
		if (type == _T("0")) {
			LoginData(str);
		}
		else if (type == _T("1")) {
			LobbyData(str);
		}
		else if (type == _T("2")) {
			RoomData(str);
		}
		else if (type == _T("3")) {
			WhisperData(str);
		}
		else if (type == _T("4")) {
			FriendData(str);
		}
	}

	//int n = 0; // 콤마 index
	//int k = 0; // 콤마 다음 문자 index
	//CString s;
	//if (str.Right(3) == _T("마지막"))
	//{
	//	while (1)
	//	{
	//		n = str.Find(_T(","), n);
	//		if (n == -1) break;   // “,”를 못 찾은 경우
	//		s = str.Mid(k, n - k);
	//		pUser->AddString(s);
	//		n++;
	//		k = n;
	//	}
	//	return;
	//}
	//pList->AddString(str);
	//int index = pList->GetCount();
	//pList->SetAnchorIndex(index - 1);
	//if (str.Left(1) == "<")  // 입장 
	//{
	//	k = str.Find('>'); // 인덱스를 뽑는다. “<hong>”이면 k는 5가 들어간다.
	//	CTime time = CTime::GetCurrentTime();
	//	CString strt;
	//	strt = str.Mid(1, k - 1) + time.Format(_T("(%d %H:%M)"));
	//	CListBox *pUser = (CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST_USER);
	//	pUser->AddString(strt);
	//	return;

	//}
	//if (str.Left(1) == "(") // 퇴장
	//{
	//	k = str.Find(')');
	//	CString strOut;
	//	strOut = str.Mid(1, k - 1);
	//	CListBox *pUser = (CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST_USER);
	//	int nFind = pUser->FindString(-1, strOut);
	//	pUser->DeleteString(nFind);
	//}

}

void CMessaengerClientApp::ServerConnect(void)
{
	if (!bConnect) {
		if (!m_pClient) {
			m_pClient = new CClientSock;
			m_pClient->Create();
		}

		CString str;
		str.Format(_T("%d.%d.%d.%d"), 127, 0, 0, 1);
		m_pClient->Connect(str, 2010);
	}
	else {
		m_pClient->OnConnect(0);
	}
}

void CMessaengerClientApp::ServerDisconnect(void)
{
	if (bConnect)
	{
		if (this->userID != _T("")) {
			CString str;
			str.Format(_T("\\x80x0|/|1|/|%s"), this->userID);
			SendData(str);
		}
		m_pClient->Close();
		delete m_pClient;
		m_pClient = NULL;
		bConnect = FALSE;
		// CListBox *pUser = (CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST_USER);
		// pUser->ResetContent();
	}
}

void CMessaengerClientApp::CloseClient(void)
{
	if (m_pClient)
		m_pClient->Close();

	if (!m_Destroy && this->m_pLobby) {
		if (this->m_pLobby->m_pRoomList) {
			delete this->m_pLobby->m_pRoomList;
		}
	}
	PostQuitMessage(0);
}

void CMessaengerClientApp::SendData(CString& strData)
{
	if (m_publicKey > 0) {

		char sendDataConv[4096];
		long sendDataConv2[4096];

		strcpy_s(sendDataConv, sizeof(sendDataConv), CT2A(strData));
		Make_Cyper_text(sendDataConv, sendDataConv2, m_publicKey);

		CString str;
		for (int i = 0; i < strlen(sendDataConv); i++) {
			if ((i + 1) == strlen(sendDataConv))
				str.Format(_T("%s%d"), str, sendDataConv2[i]);
			else
				str.Format(_T("%s%d "), str, sendDataConv2[i]);
		}

		m_pClient->Send(str, str.GetLength() * 2);
	}
	else {
		m_pClient->Send(strData, strData.GetLength() * 2);
	}

	//CListBox *pList = (CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST_MSG);
	//pList->AddString(strData);
	//int index = pList->GetCount();
	//pList->SetAnchorIndex(index - 1);
}