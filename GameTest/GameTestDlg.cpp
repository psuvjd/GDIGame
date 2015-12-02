// GameTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GameTest.h"
#include "GameTestDlg.h"
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
int g_index;
HBITMAP g_hbmPerson[125];
HBITMAP g_hbmScenery[97];
HBITMAP g_hbmAnimal[TYPE_MAX][125];
vector<CMyScenery> g_vScenery;
vector<CMyAnimal> g_vAnimal;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CGameTestDlg 对话框

CGameTestDlg::CGameTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CGameTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CGameTestDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDCANCEL, &CGameTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK3, &CGameTestDlg::OnBnClickedOk3)
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_AddScenery, &CGameTestDlg::OnBnClickedAddscenery)
	ON_BN_CLICKED(IDC_AddAnimal, &CGameTestDlg::OnBnClickedAddanimal)
END_MESSAGE_MAP()


// CGameTestDlg 消息处理程序

BOOL CGameTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	g_index = 0;
	srand(unsigned(time(NULL)));

	// 加载人物图片资源
	CString path = "pic/per/";
	for(int i = 0; i < 400; i++) {
		CString name;
		name.Format("c%05d.bmp", i);
		g_hbmPerson[i] = (HBITMAP)LoadImage(AfxGetInstanceHandle(), path + name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	}

	// 加载动物图片资源
	path = "pic/兽/";
	for (int i = 0; i < TYPE_MAX; i++) {
		if (i != HORSE) {
			for (int j = 0; j < 120; j++) {
				CString name;
				name.Format("c%05d.bmp", i * 400 + j);
				g_hbmAnimal[i][j] = (HBITMAP)LoadImage(AfxGetInstanceHandle(), path + name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			}
		}
		else {
			for (int j = 0; j < 40; j++) {
				CString name;
				name.Format("c%05d.bmp", i * 400 + j);
				g_hbmAnimal[i][j] = (HBITMAP)LoadImage(AfxGetInstanceHandle(), path + name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			}
			for (int j = 120; j < 120 + 80; j++) {
				CString name;
				name.Format("c%05d.bmp", i * 400 + j);
				g_hbmAnimal[i][j-80] = (HBITMAP)LoadImage(AfxGetInstanceHandle(), path + name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			}
		}
	}

	// 加载景物图片资源
	path = "pic/景/";
	for (int i = 0; i < 97; i++) {
		CString name;
		name.Format("c%05d.bmp", i);
		g_hbmScenery[i] = (HBITMAP)LoadImage(AfxGetInstanceHandle(), path + name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

	// 加载地图图片资源
	CClientDC dc(this);
	m_hDCBitmap = CreateCompatibleDC(dc);
	m_hDCMemBitmap = CreateCompatibleDC(dc);
	m_hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), "pic/diA.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hEmptyBitmap = CreateCompatibleBitmap(dc, m_iWidth = 640, m_iHeight = 480);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGameTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGameTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CGameTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGameTestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
	CClientDC dc(this);
	HDC hdc = dc.m_hDC;
	HPEN penRed = ::CreatePen(PS_SOLID, 5, RGB(200, 200, 254));
	HPEN penOld = (HPEN)SelectObject(hdc, penRed);
	MoveToEx(hdc, 150, 100, NULL);
	LineTo(hdc, 200, 150);
	LineTo(hdc, 100, 150);
	LineTo(hdc, 150, 100);
	SelectObject(hdc, penOld);
	DeleteObject(penRed);
	return ;
}

void CGameTestDlg::OnBnClickedOk2()
{	
	CClientDC dc(this);
	SelectObject(m_hDCBitmap, m_hBitmap);
	DIBSECTION ds;
	BITMAPINFOHEADER &bm = ds.dsBmih;
	GetObject(m_hBitmap, sizeof(ds), &ds);
	int iWidth = bm.biWidth;
	int iHeight = bm.biHeight;
	BitBlt(dc.m_hDC, 0, 0, iWidth, iHeight, m_hDCBitmap, 0, 0, SRCCOPY);
	KillTimer(0);
}

void CGameTestDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CGameTestDlg::OnBnClickedOk3()
{
	g_index = 0;
	SetTimer(0, FREQUENCY_TIMER, NULL);
}

int CGameTestDlg::GetBitmapIndex(const CMyCreature& nCreature, int idx) {
	int res;
	if (nCreature.GetState() == STAND) {
		res = nCreature.GetFace() + idx % 5;
	}
	else {
		res = nCreature.GetFace() * 2 + 40 + idx % 10;
	}
	return res;
}

void CGameTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 移动
	m_MyCreature.Move(g_index);
	for (int i = 0; i < g_vAnimal.size(); i++) {
		g_vAnimal[i].AI(FREQUENCY_TIMER);
	}
	CClientDC dc(this);
	DIBSECTION ds;
	BITMAPINFOHEADER &bm = ds.dsBmih;

	// 加载地图
	SelectObject(m_hDCBitmap, m_hBitmap);
	SelectObject(m_hDCMemBitmap, m_hEmptyBitmap);
	GetObject(m_hBitmap, sizeof(ds), &ds);
	int iWidth = bm.biWidth;
	int iHeight = bm.biHeight;
	BitBlt(m_hDCMemBitmap, 0, 0, iWidth, iHeight, m_hDCBitmap, 0, 0, SRCCOPY);

	// 加载景物
	int iScenerySize = g_vScenery.size();
	vector<pair<int, int> > *drawSeq = new vector<pair<int, int> >();
	for (int i = 0; i < iScenerySize; i++) {
		GetObject(g_hbmScenery[g_vScenery[i].GetID()], sizeof ds, &ds);
		drawSeq->push_back({ g_vScenery[i].GetY() + bm.biHeight, i });
	}
	GetObject(g_hbmPerson[GetBitmapIndex(m_MyCreature, g_index)], sizeof(ds), &ds);
	drawSeq->push_back({ m_MyCreature.GetY() + bm.biHeight, iScenerySize });

	int id = iScenerySize + 1;
	for (auto i : g_vAnimal) {
		GetObject(g_hbmAnimal[GetBitmapIndex(i, g_index)], sizeof ds, &ds);
		drawSeq->push_back({ i.GetY() + bm.biHeight, id++ });
	}
	sort(drawSeq->begin(), drawSeq->end());
	for (int i = 0; i < id; i++) {
		int iID = (*drawSeq)[i].second;
		if (iID == iScenerySize) {
			// 加载人物
			GetObject(g_hbmPerson[GetBitmapIndex(m_MyCreature, g_index)], sizeof(ds), &ds);
			iWidth = bm.biWidth;
			iHeight = bm.biHeight;
			SelectObject(m_hDCBitmap, g_hbmPerson[GetBitmapIndex(m_MyCreature, g_index)]);
			SelectObject(m_hDCMemBitmap, g_hbmPerson[GetBitmapIndex(m_MyCreature, g_index)]);
			TransparentBlt(m_hDCMemBitmap, m_MyCreature.GetX(), m_MyCreature.GetY(), iWidth, iHeight, m_hDCBitmap, 0, 0, RGB(255, 255, 255));
		}
		else if (iID > iScenerySize) {
			iID -= iScenerySize + 1;
			// 加载动物
			GetObject(g_hbmAnimal[g_vAnimal[iID].GetType()][GetBitmapIndex(g_vAnimal[iID], g_index)], sizeof ds, &ds);
			iWidth = bm.biWidth;
			iHeight = bm.biHeight;
			SelectObject(m_hDCBitmap, g_hbmAnimal[g_vAnimal[iID].GetType()][GetBitmapIndex(g_vAnimal[iID], g_index)]);
			SelectObject(m_hDCMemBitmap, g_hbmAnimal[g_vAnimal[iID].GetType()][GetBitmapIndex(g_vAnimal[iID], g_index)]);
			TransparentBlt(m_hDCMemBitmap, g_vAnimal[iID].GetX(), g_vAnimal[iID].GetY(), iWidth, iHeight, m_hDCBitmap, 0, 0, RGB(255, 255, 255));
		}
		else {
			SelectObject(m_hDCBitmap, g_hbmScenery[g_vScenery[iID].GetID()]);
			SelectObject(m_hDCMemBitmap, g_hbmScenery[g_vScenery[iID].GetID()]);
			GetObject(g_hbmScenery[g_vScenery[iID].GetID()], sizeof ds, &ds);
			iWidth = bm.biWidth;
			iHeight = bm.biHeight;
			TransparentBlt(m_hDCMemBitmap, g_vScenery[iID].GetX(), g_vScenery[iID].GetY(), iWidth, iHeight, m_hDCBitmap, 0, 0, RGB(255, 255, 255));
		}
	}
	drawSeq->clear();
	delete drawSeq;

	BitBlt(dc.m_hDC, 0, 0, m_iWidth, m_iHeight, m_hDCMemBitmap, 0, 0, SRCCOPY);
	g_index = (g_index + 1) % 10;
	CDialog::OnTimer(nIDEvent);
}

void CGameTestDlg::TransparentBlt( HDC hDesDC,	
					 int iDesX, int iDesY,
					 int iWide, int iHigh,
					 HDC hSurDC,
					 int iSurX,int iSurY,
					 UINT iMaskCol
					 )
{	
	HBITMAP hTmpBmp   = CreateCompatibleBitmap( hDesDC, iWide, iHigh );
	HBITMAP hMaskBmp   = CreateBitmap( iWide, iHigh, 1, 1, NULL );	
	HDC		hTmpDC    = CreateCompatibleDC( hDesDC );
	HDC		hMaskDC    = CreateCompatibleDC( hDesDC );
	HBITMAP hOldTmpBmp = (HBITMAP)SelectObject( hTmpDC, hTmpBmp );
	HBITMAP hOldMaskBmp = (HBITMAP)SelectObject( hMaskDC, hMaskBmp );

	BitBlt( hTmpDC, 0, 0, iWide, iHigh, hSurDC, iSurX, iSurY, SRCCOPY );

	COLORREF colOld = SetBkColor( hTmpDC, iMaskCol );
	BitBlt( hMaskDC, 0, 0, iWide, iHigh, hTmpDC, 0, 0, SRCCOPY );
	SetBkColor( hTmpDC, colOld );

	BitBlt( hMaskDC, 0, 0, iWide, iHigh, hMaskDC, 0, 0, NOTSRCCOPY );

	BitBlt( hTmpDC, 0, 0, iWide, iHigh, hMaskDC, 0, 0, SRCAND );


	BitBlt( hMaskDC, 0, 0, iWide, iHigh, hMaskDC, 0, 0, NOTSRCCOPY );
	BitBlt( hDesDC, iDesX, iDesY, iWide, iHigh, hMaskDC, 0, 0, SRCAND );
	BitBlt( hDesDC, iDesX, iDesY, iWide, iHigh, hTmpDC, 0, 0, SRCPAINT);

	SelectObject(hTmpDC, hOldTmpBmp);				
	DeleteDC(hTmpDC);
	SelectObject(hMaskDC, hOldMaskBmp);
	DeleteDC(hMaskDC);

	DeleteObject(hTmpBmp);
	DeleteObject(hMaskBmp);
}
void CGameTestDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int toX = min(640 - 22 - 3, point.x - 11);
	int toY = min(480 - 42 - 3, point.y - 42);
	m_MyCreature.SetDes(toX, toY);
	CDialog::OnLButtonDblClk(nFlags, point);
}


void CGameTestDlg::OnBnClickedAddscenery()
{
	// TODO: 在此添加控件通知处理程序代码
	CMyScenery tmpScenery(rand() % 510, rand() % 300, rand() % 97);
	g_vScenery.push_back(tmpScenery);
}


void CGameTestDlg::OnBnClickedAddanimal()
{
	// TODO: 在此添加控件通知处理程序代码
	CMyAnimal tmpAnimal;
	g_vAnimal.push_back(tmpAnimal);
}
