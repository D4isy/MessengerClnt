// RoomList.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "afxdialogex.h"

// CRoomList 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRoomList, CDialogEx)

CRoomList::CRoomList(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TABCTL, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Lastest_Index = 0;
	m_mScrollPos.clear();
}

CRoomList::~CRoomList()
{
	m_pTabIdx.clear();
	m_pText.clear();
	m_pInputText.clear();
	m_mScrollPos.clear();

	if (GetParent() != NULL) {
		((Lobby *)GetParent())->m_pRoomList = NULL;
		((Lobby *)GetParent())->m_bRoomList = FALSE;
		((Lobby *)GetParent())->BtnTalkList.SetWindowText(_T("<<"));
	}
}

void CRoomList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, TAB_ROOMLIST, m_Tab);
}


BEGIN_MESSAGE_MAP(CRoomList, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, TAB_ROOMLIST, &CRoomList::OnTcnSelchangeRoomlist)
	ON_WM_SYSCOMMAND()
	ON_WM_KEYDOWN()
	ON_NOTIFY(TCN_SELCHANGING, TAB_ROOMLIST, &CRoomList::OnSelchangingTabRoomlist)
END_MESSAGE_MAP()


// CRoomList 메시지 처리기입니다.


BOOL CRoomList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CRect Rect;
	m_Tab.GetClientRect(&Rect);

	m_pRoom = new CRoom;
	m_pRoom->Create(IDD_ROOM, &m_Tab);
	m_pRoom->SetWindowPos(NULL, 5, 25, Rect.Width() - 12, Rect.Height() - 33,
		SWP_SHOWWINDOW | SWP_NOZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRoomList::OnSelchangingTabRoomlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_Tab.GetCurSel();
	UpdateData();
	int nMapIndex = m_pTabIdx.at(nIndex);
	m_pText[nMapIndex] = m_pRoom->m_RichEditCtrl.GetRTF();
	m_pRoom->EditText.GetWindowText(m_pInputText[nMapIndex]);
	m_mScrollPos[nMapIndex] = m_pRoom->m_RichEditCtrl.GetScrollPos(SB_VERT);
	*pResult = 0;
}

void CRoomList::OnTcnSelchangeRoomlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_Tab.GetCurSel();
	SelectRoom(nIndex);
	*pResult = 0;
}

void CRoomList::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//m_pTabIdx.clear();
	//m_pText.clear();
	//m_pInputText.clear();
	//m_mScrollPos.clear();
	//
	//if (GetParent() != NULL) {
	//	((Lobby *)GetParent())->m_pRoomList = NULL;
	//	((Lobby *)GetParent())->m_bRoomList = FALSE;
	//	((Lobby *)GetParent())->BtnTalkList.SetWindowText(_T("<<"));
	//}
	//delete this;

	CDialogEx::PostNcDestroy();
}


void CRoomList::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	}
	else if (nID == SC_CLOSE) {
		this->PostNcDestroy();
	}
	else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CRoomList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_ESCAPE) {
		// this->PostNcDestroy();
#ifdef DEBUG
		MessageBox(_T("ESCAPE (for RoomList.cpp)"));
#endif // DEBUG

		return;
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CRoomList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) { return TRUE; }
	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CRoomList::RemoveRoom()
{
	int nIndex = m_Tab.GetCurSel();
	int nMapIndex = m_pTabIdx.at(nIndex);

	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	if (pApp) {
		// 1 |/| 퇴장:2 |/| 룸 번호 |/| (원본과 암호화 값 두 개 전송)
		CString sendData;
		sendData.Format(_T("\\x80x1|/|2|/|%u|/|(원본과 암호화 값 두 개 전송)"), nMapIndex);
		pApp->SendData(sendData);
	}

	ExitRoom(nIndex, nMapIndex);
	//if (m_pWndShow != NULL) {
	//	vector<CRoom *>::iterator it;
	//	int i;
	//	for (i = 0, it = m_pTabRoom.begin(); it != m_pTabRoom.end(); it++, i++) {
	//		if (*it == m_pWndShow) {
	//			if (i == 0 && m_Tab.GetItemCount() > 1) {
	//				it++;
	//				m_pWndShow = *it;
	//			}
	//			else if (i > 0 && m_Tab.GetItemCount() > 0) {
	//				it--;
	//				m_pWndShow = *it;
	//			}
	//			else {
	//				m_pWndShow = NULL;
	//			}
	//			// 현재 화면 메모리 할당 지우기
	//			m_pTabRoom.erase(m_pTabRoom.begin() + i);

	//			// 메뉴 제거
	//			m_Tab.DeleteItem(i);

	//			if (m_Tab.GetItemCount() == i) {
	//				m_Tab.SetCurSel(i-1);
	//			}
	//			else {
	//				m_Tab.SetCurSel(i);
	//			}

	//			if (m_pWndShow) {
	//				// m_pWndShow->ShowWindow(SW_SHOW);
	//			}
	//			break;
	//		}
	//	}

	//	if (!m_Tab.GetItemCount())
	//		this->PostNcDestroy();
	//}
	
	return 0;
}

void CRoomList::SendRoomMessage(UINT32 roomIndex, int type, CString userName, CString msg)
{
	if (m_pRoom) {
		int lastest_index = m_Lastest_Index;

		m_pText[lastest_index] = m_pRoom->m_RichEditCtrl.GetRTF();
		m_pRoom->EditText.GetWindowText(m_pInputText[lastest_index]);
		m_mScrollPos[lastest_index] = m_pRoom->m_RichEditCtrl.GetScrollPos(SB_VERT);
		UpdateData(FALSE);
		SelectRoomMapIndex(roomIndex);
		
		m_pRoom->ViewMessage(type, userName, msg);
		m_pText[roomIndex] = m_pRoom->m_RichEditCtrl.GetRTF();
		m_pRoom->EditText.GetWindowText(m_pInputText[roomIndex]);
		m_mScrollPos[roomIndex] = m_pRoom->m_RichEditCtrl.GetScrollPos(SB_VERT);

		SelectRoomMapIndex(lastest_index);
	}
}

void CRoomList::SetSelNewTab()
{
	m_Tab.SetCurSel(m_Tab.GetItemCount()-1);
}

void CRoomList::SelectRoom(INT32 Index)
{
	int nMapIndex;
	if (Index != -1) {
		nMapIndex = m_pTabIdx.at(Index);
	}
	m_Lastest_Index = nMapIndex;
	m_pRoom->m_RichEditCtrl.SetRTF(m_pText[nMapIndex]);
	m_pRoom->EditText.SetWindowText(m_pInputText[nMapIndex]);
	m_pRoom->m_RichEditCtrl.SetScrollPos(SB_VERT, m_mScrollPos[nMapIndex]);
	UpdateData(FALSE);
}

void CRoomList::SelectRoomMapIndex(INT32 nMapIndex)
{
	if (nMapIndex >= 0) {
		m_pRoom->m_RichEditCtrl.SetRTF(m_pText[nMapIndex]);
		m_pRoom->EditText.SetWindowText(m_pInputText[nMapIndex]);
		m_pRoom->m_RichEditCtrl.SetScrollPos(SB_VERT, m_mScrollPos[nMapIndex]);
		UpdateData(FALSE);
	}
}

void CRoomList::InsertRoom(CString &title, INT32 Index)
{
	if (m_pText[Index]) {
		int i;
		std::vector<INT32>::iterator it;
		for (i=0, it = m_pTabIdx.begin(); it != m_pTabIdx.end(); it++, i++) {
			if ((*it) == Index) {
				m_Tab.SetCurSel(i);
				SelectRoom(i);
				return;
			}
		}
	}

	// 최근 방 번호
	m_Lastest_Index = Index;
	m_pTabIdx.push_back(Index);
	m_Tab.InsertItem(m_Tab.GetItemCount()+1, title);
	m_pText.insert(map<INT32, CString>::value_type(Index, CString("")));
	m_pInputText.insert(map<INT32, CString>::value_type(Index, CString("")));

	LRESULT tmp;
	OnSelchangingTabRoomlist(NULL, &tmp);
	SetSelNewTab();
	OnTcnSelchangeRoomlist(NULL, &tmp);
	Invalidate();

	/*
	if (m_pRoom) {
		m_pRoom->m_RichEditCtrl.SetWindowText(_T(""));
		m_pRoom->EditText.SetWindowText(_T(""));
	}
	*/
}

void CRoomList::ExitRoom(INT32 IndexRoom, INT32 Index)
{
	// IndexRoom: 0 ~
	int nIndex;

	m_pTabIdx.erase(m_pTabIdx.begin() + IndexRoom);
	m_Tab.DeleteItem(IndexRoom);
	if (m_Tab.GetItemCount() == IndexRoom) {
		nIndex = IndexRoom - 1;

		m_Tab.SetCurSel(IndexRoom - 1);
	}
	else {
		nIndex = IndexRoom;

		m_Tab.SetCurSel(IndexRoom);
	}
	m_pText.erase(Index);
	m_pInputText.erase(Index);
	m_mScrollPos.erase(Index);

	Lobby *pLobby = (Lobby *)GetParent();
	if (pLobby) {
		CString name = pLobby->m_WhispIndex[Index];
		pLobby->m_WhispIndex.erase(Index);
		if (name != _T("")) {
			for (int i = 0; i < pLobby->m_ctrlListWhisp.GetItemCount(); i++) {
				if (pLobby->m_ctrlListWhisp.GetItemText(i, 0) == name) {
					pLobby->m_ctrlListWhisp.DeleteItem(i);
					break;
				}
			}
		}
	}

	if (!m_Tab.GetItemCount()) {
		delete this;
	}
	else {
		Invalidate();
		if (m_pRoom) {
			SelectRoom(nIndex);
		}
	}
}