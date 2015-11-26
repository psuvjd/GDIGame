// GameTestDlg.h : 头文件
//

#pragma once
#include "MyCreature.h"
#include "MyScenery.h"


// CGameTestDlg 对话框
class CGameTestDlg : public CDialog
{
// 构造
public:
	CGameTestDlg(CWnd* pParent = NULL);	// 标准构造函数
	CMyCreature m_MyCreature;

// 对话框数据
	enum { IDD = IDD_GAMETEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedOk2();
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedOk3();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void TransparentBlt( HDC,int, int,int, int,HDC,int,int,UINT );
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
public:
	int GetBitmapIndex(CMyCreature MyCreature, int idx);
	afx_msg void OnBnClickedAddscenery();
private:
	long m_iWidth;
	long m_iHeight;
	HDC m_hDCBitmap;
	HDC m_hDCMemBitmap;
	HBITMAP m_hBitmap;
	HBITMAP m_hEmptyBitmap; // 空白背景
};
