
// MessaengerClient.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
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


// CMessaengerClientApp ����

CMessaengerClientApp::CMessaengerClientApp()
	: m_Destroy(FALSE)
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
	m_pClient = NULL;
	bConnect = FALSE;
	m_publicKey = 0;
}


// ������ CMessaengerClientApp ��ü�Դϴ�.

CMessaengerClientApp theApp;


// CMessaengerClientApp �ʱ�ȭ

BOOL CMessaengerClientApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
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

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// MFC ��Ʈ���� �׸��� ����ϱ� ���� "Windows ����" ���־� ������ Ȱ��ȭ
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	LoginBtnResponse();

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}



void CMessaengerClientApp::LoginBtnResponse()
{
	CMessaengerClientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == ID_LOGIN)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
		MessageBox(NULL, _T("LOGIN"), _T("â"), IDOK);
	}
	else if (nResponse == ID_REGISTER)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
		MessageBox(NULL, _T("REGISTER"), _T("â"), IDOK);
	}
	else if (nResponse == ID_ACC_SEARCH)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
		MessageBox(NULL, _T("SEARCH"), _T("â"), IDOK);
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "���: ��ȭ ���ڸ� ������ �������Ƿ� ���� ���α׷��� ����ġ �ʰ� ����˴ϴ�.\n");
		TRACE(traceAppMsg, 0, "���: ��ȭ ���ڿ��� MFC ��Ʈ���� ����ϴ� ��� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS�� ������ �� �����ϴ�.\n");
	}
}

void CMessaengerClientApp::LoginData(CString Data)
{
	// 0 |/| �α���:0 / �α׾ƿ�:1 |/| �� �� �� |/| ��й�ȣ
	// 0 |/| ����:0   / ����:1     |/| ����Ű ����(serv), ���Ű ���� ���� |/| �Ҽ�
	// 0 |/| ȸ������:2 |/| ���:0, �����:1
	// 0 |/| ���ã��:3 |/| ���:0, �����:1
	CString token[5];
	int nPos = 0;

	nPos = strsplit(Data, CString("|/|"), token, 5);
	//for (int i = 0; i < nPos; i++) {
	//	str.Format(_T("[%d] %s"), i + 1, token[i]);
	//	MessageBox(NULL, str, _T(""), 0);
	//}

	CString sendData;
	if (token[1] == _T("0")) {
		// ����
		m_pMainWnd->GetDlgItemText(EDIT_ID, this->userID);
		m_publicKey = _ttoi(token[2]);
		SetPrime(_ttoi(token[3]));

		// �α��� �����
		// PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);
		if (!m_pMainWnd->SetLayeredWindowAttributes(0, 0, LWA_ALPHA)) {
			AfxMessageBox(_T("Fail to SetWindowLong..."));
		}

		// �κ�â ����
		m_pLobby = new Lobby(m_pMainWnd);
		// lobby->DoModal();
		m_pLobby->Create(IDD_LOBBY, m_pMainWnd);
		m_pLobby->ShowWindow(SW_SHOW);

		// ģ����� ��û
		sendData = _T("\\x80x4|/|9|/|(��ȣȭ)");
		SendData(sendData);

		// �� ����Ʈ ��û
		sendData = _T("\\x80x1|/|3|/|(��ȣȭ)");
		SendData(sendData);
		// MessageBox(editID + " " + editPASS, _T("LOGIN"));
		MessageBox(NULL, _T("�α��� ����"), _T("�˸�"), MB_ICONINFORMATION);
	}
	else if (token[1] == _T("2")) {
		// token[2] : ����:0/����:1
		if (token[2] == _T("0")) {
			MessageBox(NULL, _T("���� ���� ����!"), _T("�˸�"), MB_ICONINFORMATION);
		}
		else {
			MessageBox(NULL, _T("���� ���� ����!"), _T("�˸�"), MB_ICONINFORMATION);
		}
	}
	else if (token[1] == _T("3")) {
		// token[2] : ����:0/����:1
		// token[3] : ��й�ȣ
		if (token[2] == _T("0")) {
			CString str;
			str.Format(_T("���� ã�� ����!\n�ӽ� ��й�ȣ: %s"), token[3]);
			MessageBox(NULL, str, _T("�˸�"), MB_ICONINFORMATION);
		}
		else {
			MessageBox(NULL, _T("���� ã�� ����!"), _T("�˸�"), MB_ICONINFORMATION);
		}
	}
	else {
		// ����
		sendData = _T("���̵� �Ǵ� ��й�ȣ�� ���� �ʽ��ϴ�.");
		MessageBox(NULL, sendData, _T("�˸�"), MB_ICONSTOP);
	}
}

void CMessaengerClientApp::LobbyData(CString Data)
{
	// 1 |/| ����Ʈ:2 |/| ����Ʈ ���� |/| �� ��ȣ,Ÿ��Ʋ,����, ... |/| (������ ��ȣȭ �� �� �� ����)
	// 1 |/| ����:1,����:0 |/| �� ��ȣ |/| ����:1,���:0 |/| �г��� |/| (������ ��ȣȭ �� �� �� ����)
	CString token[6];
	int nPos = 0;

	nPos = strsplit(Data, CString("|/|"), token, 6);
	//for (int i = 0; i < nPos; i++) {
	//	str.Format(_T("[%d] %s"), i + 1, token[i]);
	//	MessageBox(NULL, str, _T(""), 0);
	//}

	if (token[1] == _T("0")) {	// ����
		// token[2] : �� ��ȣ
		// token[3] : ����:1,���:0
		// token[4] : �г���
		if (m_pLobby) {
			// [To����] ä�ù� ���� �䱸
			if (!m_pLobby->m_pRoomList) {		// �� ����Ʈ ����
				m_pLobby->m_pRoomList = new CRoomList(m_pLobby);
				m_pLobby->m_pRoomList->Create(IDD_TABCTL, m_pLobby);
				m_pLobby->OnClickedTalklist();
			}

			// �� ����
			m_pLobby->m_pRoomList->InsertRoom(m_pLobby->TitleString, _ttoi(token[2]));
			CString msg;
			msg.Format(_T("%s���� �����ϼ̽��ϴ�."), token[4]);
			m_pLobby->m_pRoomList->SendRoomMessage(_ttoi(token[2]), MSG_ME, token[4], msg);
		}
	}
	else if (token[1] == _T("1")) {	// ����
		// token[2] : ��ȭ��û:1, ����:0
		// token[3] : �� ��ȣ
		// token[4] : �г���
		// token[5] : ��ȣȭ
		if (token[2] == _T("0")) {	// ����
			if (m_pLobby) {
				// [To����] ä�ù� ���� �䱸
				if (!m_pLobby->m_pRoomList) {		// �� ����Ʈ ����
					m_pLobby->m_pRoomList = new CRoomList(m_pLobby);
					m_pLobby->m_pRoomList->Create(IDD_TABCTL, m_pLobby);
					m_pLobby->OnClickedTalklist();
				}

				// �� ����
				m_pLobby->m_pRoomList->InsertRoom(m_pLobby->TitleString, _ttoi(token[3]));
				CString msg;
				msg.Format(_T("%s���� �����ϼ̽��ϴ�."), token[4]);
				m_pLobby->m_pRoomList->SendRoomMessage(_ttoi(token[3]), MSG_ME, token[4], msg);

				CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
				if (pApp) {
					// ���� �޽��� ���� ��û
					CString sendData;
					sendData.Format(_T("\\x80x1|/|1|/|1|/|%u|/|��ȣȭ"), _ttoi(token[3]));
					pApp->SendData(sendData);
				}
			}
		}
		else if (token[2] == _T("1")) {	// ��ȭ
			CString msg;
			msg.Format(_T("%s���� �����ϼ̽��ϴ�."), token[4]);
			if (m_pLobby) {
				if (m_pLobby->m_pRoomList) {
					m_pLobby->m_pRoomList->SendRoomMessage(_ttoi(token[3]), MSG_YOU, token[4], msg);
				}
			}
		}
		else if (token[2] == _T("2")) {	// �ƿ�
			CString msg;
			msg.Format(_T("%s���� �����ϼ̽��ϴ�."), token[4]);
			if (m_pLobby) {
				if (m_pLobby->m_pRoomList) {
					m_pLobby->m_pRoomList->SendRoomMessage(_ttoi(token[3]), MSG_YOU, token[4], msg);
				}
			}
		}
		else if (token[2] == _T("3")) {	// ���� �޽���
			CString msg;
			msg.Format(_T("���� �Ǿ����ϴ�."));
			MessageBox(NULL, msg, _T("�˸�"), MB_ICONSTOP);
		}
	}
	else if (token[1] == _T("2")) { // �� ����Ʈ
		// token[2] : ����Ʈ ����
		// token[3] : �� ��ȣ,Ÿ��Ʋ,����, ... 
		// token[4] : (������ ��ȣȭ �� �� �� ����)
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
				case 0:	RoomIdx = subString; break;	// ���ȣ

				case 1:	Title = subString; break;	// Ÿ��Ʋ

				case 2:		// ����
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
	// 2 |/| �� ��ȣ    |/| �� �� ��  |/| �Է� ���� + �ð�(serv)
	// 2 |/| -1:�� ���� |/| �� ��ȣ 
	CString token[6];
	int nPos = 0;

	nPos = strsplit(Data, CString("|/|"), token, 4);
	//for (int i = 0; i < nPos; i++) {
	//	str.Format(_T("[%d] %s"), i + 1, token[i]);
	//	MessageBox(NULL, str, _T(""), 0);
	//}

	if (token[1] == _T("-1")) {
		// token[2] : �� ��ȣ
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
	// recv: 3 |/| 0: ���� |/| �� ��ȣ  |/| �� �� �� |/| ��ȣȭ
	// send: 3 |/| �� ��ȣ |/| �� �� �� |/| ��ȣȭ
	CString token[6];
	int nPos = 0;

	nPos = strsplit(Data, CString("|/|"), token, 6);
	//for (int i = 0; i < nPos; i++) {
	//	str.Format(_T("[%d] %s"), i + 1, token[i]);
	//	MessageBox(NULL, str, _T(""), 0);
	//}

	if (token[1] == _T("0")) {
		//token[2] : �� ��ȣ
		//token[3] : �г���
		//token[4] : ��ȣȭ
		// �г����� ���̸����� �ϴ� �� ���� (�Ϸ�)
		if (m_pLobby) {
			// Lobby ����Ʈ�� �ӼӸ� �� ���̵� �ֱ� (�Ϸ�)
			// �Ӹ��� ������ Lobby ����Ʈ�� �ش� ���̵� �����ϱ� (�Ϸ�)

			if (m_pLobby->m_WhispIndex[_ttoi(token[2])] != _T("")) { // �����Ѵٸ� �׳� �۾� ���
				return;
			}

			m_pLobby->m_WhispIndex[_ttoi(token[2])] = token[3];
			m_pLobby->m_ctrlListWhisp.InsertItem(m_pLobby->m_ctrlListWhisp.GetItemCount(), token[3]);

			// ä�ù� �� ����
			if (!m_pLobby->m_pRoomList) {		// �� ����Ʈ ����
				m_pLobby->m_pRoomList = new CRoomList(m_pLobby);
				m_pLobby->m_pRoomList->Create(IDD_TABCTL, m_pLobby);
				m_pLobby->OnClickedTalklist();
			}

			// �� ����
			m_pLobby->m_pRoomList->InsertRoom(token[3], _ttoi(token[2]));
			CString msg;
			msg.Format(_T("%s���� �����ϼ̽��ϴ�."), token[3]);
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
	// 4 |/| 0: �߰���û   |/| �߰��� �г���
	// 4 |/| 1: ��    ��   |/| �߰��� �г���
	// 4 |/| 2: ��ȭ��û   |/| �г���
	// 4 |/| 9: ģ�����   |/| �г���1, �г���2, ...
	CString token[6];
	int nPos = 0;

	nPos = strsplit(Data, CString("|/|"), token, 6);
	
	if (token[1] == _T("1")) {
		// �� ��
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
		// ģ�����
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

	//int n = 0; // �޸� index
	//int k = 0; // �޸� ���� ���� index
	//CString s;
	//if (str.Right(3) == _T("������"))
	//{
	//	while (1)
	//	{
	//		n = str.Find(_T(","), n);
	//		if (n == -1) break;   // ��,���� �� ã�� ���
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
	//if (str.Left(1) == "<")  // ���� 
	//{
	//	k = str.Find('>'); // �ε����� �̴´�. ��<hong>���̸� k�� 5�� ����.
	//	CTime time = CTime::GetCurrentTime();
	//	CString strt;
	//	strt = str.Mid(1, k - 1) + time.Format(_T("(%d %H:%M)"));
	//	CListBox *pUser = (CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST_USER);
	//	pUser->AddString(strt);
	//	return;

	//}
	//if (str.Left(1) == "(") // ����
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