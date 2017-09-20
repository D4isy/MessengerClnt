// FriendList.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MessaengerClient.h"
#include "FriendList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// typedef for callback function for copying item data
// Passes in the tree control, the item being copied, and the item's data.
// The function should make and return a new copy of the data if required.
typedef LPARAM(*PFNMTICOPYDATA)(const CTreeCtrl&, HTREEITEM, LPARAM);

// copy our lParam, which happens to be a CString pointer
static LPARAM CopyData(const CTreeCtrl& tree, HTREEITEM hItem, LPARAM lParam)
{
	if (lParam == 0)
		return 0;
	CString* ps = (CString*)lParam;
	CString* psNew = new CString(*ps);
	return (LPARAM)psNew;
}


HTREEITEM MoveTreeItem(CTreeCtrl& tree, HTREEITEM hItem, HTREEITEM hItemTo,
	BOOL bCopyOnly = FALSE, PFNMTICOPYDATA pfnCopyData = NULL,
	HTREEITEM hItemPos = TVI_LAST)
{
	if (hItem == NULL || hItemTo == NULL)
		return NULL;
	if (hItem == hItemTo || hItemTo == tree.GetParentItem(hItem))
		return hItem;
	// check we're not trying to move to a descendant
	HTREEITEM hItemParent = hItemTo;
	while (hItemParent != TVI_ROOT && (hItemParent = tree.GetParentItem(hItemParent)) != NULL)
		if (hItemParent == hItem)
			return NULL;

	// copy items to new location, recursively, then delete old heirarchy
	// get text, and other info
	CString sText = tree.GetItemText(hItem);
	TVINSERTSTRUCT tvis;
	tvis.item.mask = TVIF_HANDLE | TVIF_IMAGE | TVIF_PARAM |
		TVIF_SELECTEDIMAGE | TVIF_STATE;
	tvis.item.hItem = hItem;
	// we don't want to copy selection/expanded state etc
	tvis.item.stateMask = (UINT)-1 & ~(TVIS_DROPHILITED | TVIS_EXPANDED |
		TVIS_EXPANDEDONCE | TVIS_EXPANDPARTIAL | TVIS_SELECTED);
	tree.GetItem(&tvis.item);
	tvis.hParent = hItemTo;
	tvis.hInsertAfter = hItemPos;
	// if we're only copying, then ask for new data
	if (bCopyOnly && pfnCopyData != NULL)
		tvis.item.lParam = pfnCopyData(tree, hItem, tvis.item.lParam);
	HTREEITEM hItemNew = tree.InsertItem(&tvis);
	tree.SetItemText(hItemNew, sText);

	// now move children to under new item
	HTREEITEM hItemChild = tree.GetChildItem(hItem);
	while (hItemChild != NULL)
	{
		HTREEITEM hItemNextChild = tree.GetNextSiblingItem(hItemChild);
		MoveTreeItem(tree, hItemChild, hItemNew, bCopyOnly, pfnCopyData);
		hItemChild = hItemNextChild;
	}

	if (!bCopyOnly)
	{
		// clear item data, so nothing tries to delete stuff based on lParam
		tree.SetItemData(hItem, 0);
		// no (more) children, so we can safely delete top item
		tree.DeleteItem(hItem);
	}

	return hItemNew;
}

// CFriendList

IMPLEMENT_DYNCREATE(CFriendList, CFormView)

CFriendList::CFriendList(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FRIENDLIST, pParent)
{
	m_hItemDrag = NULL;
	m_imgList.Create(IDB_TREE_ICON, 16, 1, RGB(255, 255, 255));
}

CFriendList::~CFriendList()
{
	m_imgList.DeleteImageList();
	m_Tree.DeleteAllItems();
}

void CFriendList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, TREE_FRIEND, m_Tree);
	DDX_Control(pDX, EDIT_FRIENDNAME, m_EditName);
}

BEGIN_MESSAGE_MAP(CFriendList, CDialogEx)
//	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, TREE_FRIEND, &CFriendList::OnSelchangedTreeFriend)
	ON_BN_CLICKED(ID_FRIEND_DEL, &CFriendList::OnClickedFriendDel)
	ON_BN_CLICKED(ID_FRIEND_ADD, &CFriendList::OnClickedFriendAdd)
//	ON_WM_CREATE()
//ON_WM_SYSCOMMAND()
//ON_WM_PAINT()
ON_NOTIFY(TVN_BEGINDRAG, TREE_FRIEND, &CFriendList::OnBegindragTreeFriend)
ON_WM_MOUSEMOVE()
ON_WM_CANCELMODE()
ON_WM_LBUTTONUP()
ON_NOTIFY(NM_DBLCLK, TREE_FRIEND, &CFriendList::OnDblclkTreeFriend)
END_MESSAGE_MAP()

// CFriendList 메시지 처리기입니다.

//void CFriendList::OnSize(UINT nType, int cx, int cy)
//{
//	CDialogEx::OnSize(nType, cx, cy);
//
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//	// resize tree
//	if (m_Tree.m_hWnd)
//	{                                                         // otherwise not created yet
//		RECT rect;
//		GetClientRect(&rect);
//#define BORDER 55
//		int iSizeX, iSizeY;
//		iSizeX = rect.right - rect.left - BORDER * 2;
//		iSizeY = rect.bottom - rect.top - BORDER * 2;
//		if ((iSizeX > 0) && (iSizeY > 0)) m_Tree.SetWindowPos(NULL, BORDER, BORDER, iSizeX, iSizeY, SWP_NOZORDER);
//#undef BORDER
//	}
//}


void CFriendList::OnSelchangedTreeFriend(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UNREFERENCED_PARAMETER(pNMHDR);
	UNREFERENCED_PARAMETER(pResult);
	*pResult = 0;
}


void CFriendList::OnClickedFriendDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HTREEITEM hOld = m_Tree.GetSelectedItem();
	CString friendName = m_Tree.GetItemText(hOld);
	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	if (pApp) {
		// 접속 메시지 전송 요청
		CString sendData;
		sendData.Format(_T("\\x80x4|/|3|/|%s"), friendName);
		pApp->SendData(sendData);
	}
	// DeleteSelected();
}

void CFriendList::DeleteSelected()
{
	HTREEITEM hOld = m_Tree.GetSelectedItem();
	if (m_Tree.ItemHasChildren(hOld))
	{
		int nRet = AfxMessageBox(_T("You have chosen to delete a folder.  Please confirm you want to delete this folder and all items in it?"), MB_YESNO);
		if (nRet != IDYES)
		{
			return;     // User has changed their mind
		}
	}
	if (hOld != NULL)
	{
		// Use recursive function to callback to parents on all items being deleted.
		ReportDeleteBackToParent(hOld);
		m_Tree.DeleteItem(hOld);
	}
}

void CFriendList::ReportDeleteBackToParent(HTREEITEM hOld)
{
	// Call this function recursively for all children of this item
	ASSERT(hOld != NULL);
	HTREEITEM hNextChildItem = m_Tree.GetChildItem(hOld);
	while (hNextChildItem != NULL)
	{
		ReportDeleteBackToParent(hNextChildItem);
		hNextChildItem = m_Tree.GetNextSiblingItem(hNextChildItem);
	}
	GetParent()->SendMessage(UWM_TREEITEMDELETED, (WPARAM)hOld, 0);
}

void CFriendList::OnClickedFriendAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString friendName;
	m_EditName.GetWindowText(friendName);
	// m_Tree.InsertItem(text, 3, 3, m_hItemDrag);

	// 4 |/| 0: 추가요청 |/| 추가할 닉네임
	// 4 |/| 1: 허    용 |/| 추가할 닉네임
	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	if (pApp) {
		// 접속 메시지 전송 요청
		CString sendData;
		sendData.Format(_T("\\x80x4|/|0|/|%s"), friendName);
		pApp->SendData(sendData);
	}
}


BOOL CFriendList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_Tree.SetImageList(&m_imgList, TVSIL_NORMAL);
	// m_Tree.SetNoDuplicates(TRUE);
	m_imgList.Detach();

	// now that the tree exists, force resize
	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	if (pApp) {
		int nSize = pApp->m_friendName.size();
		for (int i = 0; i < nSize; i++) {
			m_Tree.InsertItem(pApp->m_friendName.at(i), 2, 2, m_hItemDrag);
		}
	}

	//RECT rect;
	//GetWindowRect(&rect);
	//OnSize(SIZE_RESTORED, rect.right - rect.left, rect.bottom - rect.top);

	// populate tree example
	//HTREEITEM hScene = m_Tree.InsertItem(_T("scene"), FOLDER_IMAGE, FOLDER_IMAGE + 1);
	//HTREEITEM hCams = m_Tree.InsertItem(_T("cameras"), FOLDER_IMAGE, FOLDER_IMAGE, hScene);
	//HTREEITEM hLights = m_Tree.InsertItem(_T("lights"), FOLDER_IMAGE, FOLDER_IMAGE, hScene);
	//HTREEITEM hMeshes = m_Tree.InsertItem(_T("meshes"), 9, 9, hScene);
	//HTREEITEM hChrs = m_Tree.InsertItem(_T("characters"), FOLDER_IMAGE, FOLDER_IMAGE, hMeshes);
	//HTREEITEM hBlocks = m_Tree.InsertItem(_T("blocks"), FOLDER_IMAGE, FOLDER_IMAGE, hMeshes);
	//HTREEITEM hHouses = m_Tree.InsertItem(_T("buildings"), FOLDER_IMAGE, FOLDER_IMAGE, hMeshes);
	//CString strTmp;

	//for (int i = 0; i < 10; i++)
	//{
	//	strTmp.Format(_T("camera %u"), i + 1);
	//	m_Tree.InsertItem(LPCTSTR(strTmp), 2, 2, hCams);
	//	strTmp.Format(_T("light %u"), i + 1);
	//	m_Tree.InsertItem(LPCTSTR(strTmp), 5, 5, hLights);
	//	strTmp.Format(_T("character %u"), i + 1);
	//	m_Tree.InsertItem(LPCTSTR(strTmp), 12, 12, hChrs);
	//	strTmp.Format(_T("block %u"), i + 1);
	//	m_Tree.InsertItem(LPCTSTR(strTmp), 9, 9, hBlocks);
	//	strTmp.Format(_T("house %u"), i + 1);
	//	m_Tree.InsertItem(LPCTSTR(strTmp), 10, 10, hHouses);
	//}

	////  m_Tree.Expand(hHouses,TVE_EXPAND);
	////  m_Tree.Expand(hBlocks,TVE_EXPAND);
	//m_Tree.Expand(hChrs, TVE_EXPAND);
	//m_Tree.Expand(hMeshes, TVE_EXPAND);
	//m_Tree.Expand(hLights, TVE_EXPAND);
	//m_Tree.Expand(hCams, TVE_EXPAND);
	//m_Tree.Expand(hScene, TVE_EXPAND);

	//MessageBox(_T("친구목록 초기화!"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CFriendList::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//m_imgList.DeleteImageList();
	//m_Tree.DeleteAllItems();
	//if (this->m_hWnd) {
	//delete this;
	CDialogEx::PostNcDestroy();
}

void CFriendList::OnBegindragTreeFriend(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;	// allow drag

	CImageList* piml = NULL;    /* handle of image list */
	POINT ptOffset;
	RECT rcItem;

	if ((piml = m_Tree.CreateDragImage(pNMTreeView->itemNew.hItem)) == NULL)
		return;

	/* get the bounding rectangle of the item being dragged (rel to top-left of control) */
	if (m_Tree.GetItemRect(pNMTreeView->itemNew.hItem, &rcItem, TRUE))
	{
		CPoint ptDragBegin;
		int nX, nY;
		/* get offset into image that the mouse is at */
		/* item rect doesn't include the image */
		ptDragBegin = pNMTreeView->ptDrag;
		ImageList_GetIconSize(piml->GetSafeHandle(), &nX, &nY);
		ptOffset.x = (ptDragBegin.x - rcItem.left) + (nX - (rcItem.right - rcItem.left));
		ptOffset.y = (ptDragBegin.y - rcItem.top) + (nY - (rcItem.bottom - rcItem.top));
		/* convert the item rect to screen co-ords, for use later */
		MapWindowPoints(NULL, &rcItem);
	}
	else
	{
		GetWindowRect(&rcItem);
		ptOffset.x = ptOffset.y = 8;
	}

	BOOL bDragBegun = piml->BeginDrag(0, ptOffset);
	if (!bDragBegun)
	{
		delete piml;
		return;
	}

	CPoint ptDragEnter = pNMTreeView->ptDrag;
	ClientToScreen(&ptDragEnter);
	if (!piml->DragEnter(NULL, ptDragEnter))
	{
		delete piml;
		return;
	}

	delete piml;

	/* set the focus here, so we get a WM_CANCELMODE if needed */
	SetFocus();

	/* redraw item being dragged, otherwise it remains (looking) selected */
	InvalidateRect(&rcItem, TRUE);
	UpdateWindow();

	/* Hide the mouse cursor, and direct mouse input to this window */
	SetCapture();
	m_hItemDrag = pNMTreeView->itemNew.hItem;
}


void CFriendList::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_hItemDrag != NULL)
	{
		CPoint pt;

		/* drag the item to the current position */
		pt = point;
		ClientToScreen(&pt);

		CImageList::DragMove(pt);
		CImageList::DragShowNolock(FALSE);

		if (CWnd::WindowFromPoint(pt) != &m_Tree)
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_NO));
		else
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			TVHITTESTINFO tvhti;
			tvhti.pt = pt;
			m_Tree.ScreenToClient(&tvhti.pt);
			HTREEITEM hItemSel = m_Tree.HitTest(&tvhti);
			m_Tree.SelectDropTarget(tvhti.hItem);
		}

		CImageList::DragShowNolock(TRUE);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CFriendList::OnCancelMode()
{
	/* stop dragging */
	FinishDragging(TRUE);
	// redraw
	RedrawWindow();

	CDialogEx::OnCancelMode();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CFriendList::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_hItemDrag != NULL)
		OnEndDrag(nFlags, point);
	else
		CDialogEx::OnLButtonUp(nFlags, point);
}

void CFriendList::OnEndDrag(UINT nFlags, CPoint point)
{
	if (m_hItemDrag == NULL)
		return;

	CPoint pt;

	pt = point;
	ClientToScreen(&pt);

	BOOL bCopy = (GetKeyState(VK_CONTROL) & 0x10000000);

	// do drop
	HTREEITEM hItemDrop = m_Tree.GetDropHilightItem();
	if (hItemDrop != NULL)
		TRACE("Dropped item %s (%s) onto item %s (%s)\n", m_Tree.GetItemText(m_hItemDrag), m_Tree.GetItemData(m_hItemDrag),
			m_Tree.GetItemText(hItemDrop), m_Tree.GetItemData(hItemDrop));
	else
		TRACE("Dropped item %s (%s) onto empty space\n", m_Tree.GetItemText(m_hItemDrag), m_Tree.GetItemData(m_hItemDrag));
	m_Tree.SelectDropTarget(NULL);

	int nImage = 0, nSelectedImage = 0;
	m_Tree.GetItemImage(hItemDrop, nImage, nSelectedImage);
	if (nImage == FOLDER_IMAGE) {
		MoveTreeItem(m_Tree, m_hItemDrag, hItemDrop == NULL ? TVI_ROOT : hItemDrop, bCopy, CopyData);
	}

	FinishDragging(TRUE);
	RedrawWindow();
}

void CFriendList::FinishDragging(BOOL bDraggingImageList)
{
	if (m_hItemDrag != NULL)
	{
		if (bDraggingImageList)
		{
			CImageList::DragLeave(NULL);
			CImageList::EndDrag();
		}
		ReleaseCapture();
		ShowCursor(TRUE);
		m_hItemDrag = NULL;
		m_Tree.SelectDropTarget(NULL);
	}
}

void CFriendList::OnDblclkTreeFriend(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CPoint pos;
	GetCursorPos(&pos);

	UINT flag;
	m_Tree.ScreenToClient(&pos);

	HTREEITEM hItemDC = m_Tree.HitTest(pos, &flag);

	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	if (pApp) {
		// 접속 메시지 전송 요청
		CString sendData;
		sendData.Format(_T("\\x80x4|/|2|/|%s"), m_Tree.GetItemText(hItemDC));
		pApp->SendData(sendData);
	}
	// *pResult = 0;
}
