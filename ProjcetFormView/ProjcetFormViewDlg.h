
// ProjcetFormViewDlg.h: 헤더 파일
//

#pragma once
#include "CPerson.h"

// CProjcetFormViewDlg 대화 상자
class CProjcetFormViewDlg : public CDialogEx
{
// 생성입니다.
public:
	CProjcetFormViewDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJCETFORMVIEW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	INT m_nAge;
	BOOL m_Gender;
	
	CListCtrl m_ctrlFriend;
	CSpinButtonCtrl m_ctrlSpin;

	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnLvnEndlabeleditCtrlFriend(NMHDR* pNMHDR, LRESULT* pResult);

	int m_nCount;
	CPerson m_pPerson[5];
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
};
