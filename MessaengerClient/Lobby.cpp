// Lobby.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "afxdialogex.h"

// Lobby 대화 상자입니다.

IMPLEMENT_DYNAMIC(Lobby, CDialogEx)

Lobby::Lobby(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOBBY, pParent),
	m_bRoomList(FALSE),
	m_bFriendList(FALSE)
	, TitleString(_T(""))
	, RoomPassString(_T(""))
	, RoomStatus(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pRoomList = NULL;
	m_pFriendList = NULL;
	m_WhispIndex.clear();
}

Lobby::~Lobby()
{
	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	if (pApp) {
		pApp->m_Destroy = TRUE;
	}
	if (m_pRoomList) {
		delete m_pRoomList;
		m_pRoomList = NULL;
	}
}

void Lobby::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListDlg)
	DDX_Control(pDX, LIST_ROOM, m_ctrlList);
	DDX_Control(pDX, LIST_WHISPER, m_ctrlListWhisp);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, ID_TALKLIST, BtnTalkList);
}


BEGIN_MESSAGE_MAP(Lobby, CDialogEx)
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, LIST_ROOM, &Lobby::OnDblclkListRoom)
	ON_WM_DESTROY()
	ON_BN_CLICKED(ID_TALKLIST, &Lobby::OnClickedTalklist)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(ID_FRIENDLIST, &Lobby::OnClickedFriendlist)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(ID_ROOMMAKE, &Lobby::OnBnClickedRoommake)
END_MESSAGE_MAP()


// Lobby 메시지 처리기입니다.


BOOL Lobby::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 리스트 초기화 
	m_ctrlList.DeleteAllItems();
	m_ctrlListWhisp.DeleteAllItems();

	CRect rect;
	m_ctrlList.GetClientRect(&rect);

	INT32 size = rect.Width() / 6 * 5;
	m_ctrlList.InsertColumn(1, _T("방 번호"), LVCFMT_CENTER, 80);
	m_ctrlList.InsertColumn(2, _T("방 이 름"), LVCFMT_CENTER, size - 80);
	m_ctrlList.InsertColumn(3, _T("방  장"), LVCFMT_CENTER, rect.Width() - size);

	m_ctrlListWhisp.GetClientRect(&rect);
	m_ctrlListWhisp.InsertColumn(0, _T("이  름"), LVCFMT_CENTER, rect.Width());

	CString str;
	/*
	for (int i = 0; i<7; i++)
	{
		// 이름
		//m_ctrlList.InsertItem(i, _T("test11111111111111111111111333333333333333333333333333333333"));
		str.Format(_T("%d"), i + 1);
		m_ctrlList.InsertItem(i, str);
		str.Format(_T("%d"), (rand()%9000)+1000);
		m_ctrlList.SetItem(i, 1, LVIF_TEXT, str, 0, 0, 0, NULL);

		// 나이
		str.Format(_T("%d"), rand() % 100);
		m_ctrlList.SetItem(i, 2, LVIF_TEXT, str, 0, 0, 0, NULL);
	}
	*/

	/*
	for (int i = 0; i<100; i++)
	{
		// 이름
		str.Format(_T("test%d"), rand() % 100);
		m_ctrlListWhisp.InsertItem(i, str);
	}
	*/

	m_ctrlList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlListWhisp.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// m_ctrlList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


HCURSOR Lobby::OnQueryDragIcon()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// return CDialogEx::OnQueryDragIcon();
	return static_cast<HCURSOR>(m_hIcon);
}


void Lobby::OnDblclkListRoom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

//#ifdef DEBUG
//	CString str;
//	str.Format(_T("%s %s[%d]"), _T("선택"), m_ctrlList.GetItemText((int)m_ctrlList.GetFirstSelectedItemPosition()-1, 0), m_ctrlList.GetFirstSelectedItemPosition());
//	MessageBox(str, _T("로비"));
//#endif // DEBUG

	if (m_ctrlList.GetFirstSelectedItemPosition() > 0) {
		// [To서버] 채팅방 입장 요구
		//if (!m_pRoomList) {		// 방 리스트 생성
		//	m_pRoomList = new CRoomList(this);
		//	m_pRoomList->Create(IDD_TABCTL, this);
		//	OnClickedTalklist();
		//}

		//// 방 입장
		//m_pRoomList->InsertRoom(m_ctrlList.GetItemText((int)m_ctrlList.GetFirstSelectedItemPosition() - 1, 1), _ttoi(m_ctrlList.GetItemText((int)m_ctrlList.GetFirstSelectedItemPosition() - 1, 0)));

		TitleString = m_ctrlList.GetItemText((int)m_ctrlList.GetFirstSelectedItemPosition() - 1, 1);

		CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
		if (pApp) {
			// 1 |/| 입장:1 |/| 대화:1, 입장:0 |/| 룸 번호 |/| (원본과 암호화 값 두 개 전송)
			CString sendData;
			sendData.Format(_T("\\x80x1|/|1|/|0|/|%d|/|(원본과 암호화 값 두 개 전송)"), _ttoi(m_ctrlList.GetItemText((int)m_ctrlList.GetFirstSelectedItemPosition() - 1, 0)));
			pApp->SendData(sendData);
		}
	}
}

void Lobby::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void Lobby::OnClickedTalklist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Room 창 띄우기
	if (m_pRoomList) {
		if (m_bRoomList == TRUE) {
			GetDlgItem(ID_TALKLIST)->SetWindowText(_T("<<"));
			m_pRoomList->ShowWindow(SW_HIDE);
			m_bRoomList = FALSE;
		}
		else {
			GetDlgItem(ID_TALKLIST)->SetWindowText(_T(">>"));
			m_pRoomList->ShowWindow(SW_SHOW);
			m_bRoomList = TRUE;
		}
	}
}


void Lobby::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar != VK_ESCAPE) {
		CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}


void Lobby::OnClickedFriendlist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pFriendList) {
		m_pFriendList = new CFriendList(this);
		m_pFriendList->Create(IDD_FRIENDLIST, this);
		m_pFriendList->OnInitDialog();
	}

	if (m_pFriendList) {
		if (m_bFriendList == TRUE) {
			GetDlgItem(ID_FRIENDLIST)->SetWindowText(_T(">>"));
			m_pFriendList->ShowWindow(SW_HIDE);
			m_bFriendList = FALSE;
		}
		else {
			GetDlgItem(ID_FRIENDLIST)->SetWindowText(_T("<<"));
			m_pFriendList->ShowWindow(SW_SHOW);
			m_bFriendList = TRUE;
		}
	}
}


void Lobby::OnSysCommand(UINT nID, LPARAM lParam)
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


void Lobby::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	pApp->ServerDisconnect();
	//DestroyWindow();
	delete this;
	pApp->CloseClient();

	CDialogEx::PostNcDestroy();
}


void Lobby::OnBnClickedRoommake()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRoomCreate RoomDialog(this);
	if (RoomDialog.DoModal() == CR_IDOK) {
		CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
		if (pApp) {
			// 1 |/| 생성:0 |/| 공개:0,비공개:1 |/| 타이틀 |/| 비밀번호 |/| (원본과 암호화 값 두 개 전송)
			CString sendData;
			sendData.Format(_T("\\x80x1|/|0|/|%d|/|%s|/|%s|/|(원본과 암호화 값 두 개 전송)"), RoomStatus, TitleString, RoomPassString);
			pApp->SendData(sendData);
		}
	}
	else {
		this->RoomStatus = 0;
		this->TitleString = _T("");
		this->RoomPassString = _T("");
	}
}
