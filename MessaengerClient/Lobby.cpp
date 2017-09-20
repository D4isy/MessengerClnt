// Lobby.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "afxdialogex.h"

// Lobby ��ȭ �����Դϴ�.

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


// Lobby �޽��� ó�����Դϴ�.


BOOL Lobby::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	// ����Ʈ �ʱ�ȭ 
	m_ctrlList.DeleteAllItems();
	m_ctrlListWhisp.DeleteAllItems();

	CRect rect;
	m_ctrlList.GetClientRect(&rect);

	INT32 size = rect.Width() / 6 * 5;
	m_ctrlList.InsertColumn(1, _T("�� ��ȣ"), LVCFMT_CENTER, 80);
	m_ctrlList.InsertColumn(2, _T("�� �� ��"), LVCFMT_CENTER, size - 80);
	m_ctrlList.InsertColumn(3, _T("��  ��"), LVCFMT_CENTER, rect.Width() - size);

	m_ctrlListWhisp.GetClientRect(&rect);
	m_ctrlListWhisp.InsertColumn(0, _T("��  ��"), LVCFMT_CENTER, rect.Width());

	CString str;
	/*
	for (int i = 0; i<7; i++)
	{
		// �̸�
		//m_ctrlList.InsertItem(i, _T("test11111111111111111111111333333333333333333333333333333333"));
		str.Format(_T("%d"), i + 1);
		m_ctrlList.InsertItem(i, str);
		str.Format(_T("%d"), (rand()%9000)+1000);
		m_ctrlList.SetItem(i, 1, LVIF_TEXT, str, 0, 0, 0, NULL);

		// ����
		str.Format(_T("%d"), rand() % 100);
		m_ctrlList.SetItem(i, 2, LVIF_TEXT, str, 0, 0, 0, NULL);
	}
	*/

	/*
	for (int i = 0; i<100; i++)
	{
		// �̸�
		str.Format(_T("test%d"), rand() % 100);
		m_ctrlListWhisp.InsertItem(i, str);
	}
	*/

	m_ctrlList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlListWhisp.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// m_ctrlList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


HCURSOR Lobby::OnQueryDragIcon()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// return CDialogEx::OnQueryDragIcon();
	return static_cast<HCURSOR>(m_hIcon);
}


void Lobby::OnDblclkListRoom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

//#ifdef DEBUG
//	CString str;
//	str.Format(_T("%s %s[%d]"), _T("����"), m_ctrlList.GetItemText((int)m_ctrlList.GetFirstSelectedItemPosition()-1, 0), m_ctrlList.GetFirstSelectedItemPosition());
//	MessageBox(str, _T("�κ�"));
//#endif // DEBUG

	if (m_ctrlList.GetFirstSelectedItemPosition() > 0) {
		// [To����] ä�ù� ���� �䱸
		//if (!m_pRoomList) {		// �� ����Ʈ ����
		//	m_pRoomList = new CRoomList(this);
		//	m_pRoomList->Create(IDD_TABCTL, this);
		//	OnClickedTalklist();
		//}

		//// �� ����
		//m_pRoomList->InsertRoom(m_ctrlList.GetItemText((int)m_ctrlList.GetFirstSelectedItemPosition() - 1, 1), _ttoi(m_ctrlList.GetItemText((int)m_ctrlList.GetFirstSelectedItemPosition() - 1, 0)));

		TitleString = m_ctrlList.GetItemText((int)m_ctrlList.GetFirstSelectedItemPosition() - 1, 1);

		CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
		if (pApp) {
			// 1 |/| ����:1 |/| ��ȭ:1, ����:0 |/| �� ��ȣ |/| (������ ��ȣȭ �� �� �� ����)
			CString sendData;
			sendData.Format(_T("\\x80x1|/|1|/|0|/|%d|/|(������ ��ȣȭ �� �� �� ����)"), _ttoi(m_ctrlList.GetItemText((int)m_ctrlList.GetFirstSelectedItemPosition() - 1, 0)));
			pApp->SendData(sendData);
		}
	}
}

void Lobby::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void Lobby::OnClickedTalklist()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// Room â ����
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nChar != VK_ESCAPE) {
		CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}


void Lobby::OnClickedFriendlist()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	pApp->ServerDisconnect();
	//DestroyWindow();
	delete this;
	pApp->CloseClient();

	CDialogEx::PostNcDestroy();
}


void Lobby::OnBnClickedRoommake()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CRoomCreate RoomDialog(this);
	if (RoomDialog.DoModal() == CR_IDOK) {
		CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
		if (pApp) {
			// 1 |/| ����:0 |/| ����:0,�����:1 |/| Ÿ��Ʋ |/| ��й�ȣ |/| (������ ��ȣȭ �� �� �� ����)
			CString sendData;
			sendData.Format(_T("\\x80x1|/|0|/|%d|/|%s|/|%s|/|(������ ��ȣȭ �� �� �� ����)"), RoomStatus, TitleString, RoomPassString);
			pApp->SendData(sendData);
		}
	}
	else {
		this->RoomStatus = 0;
		this->TitleString = _T("");
		this->RoomPassString = _T("");
	}
}
