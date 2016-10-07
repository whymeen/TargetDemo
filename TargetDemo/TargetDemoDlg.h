
// TargetDemoDlg.h : 헤더 파일
//
#include "GridCtrl.h"
//#include "afxtempl.h"
#include <vector>
#pragma once


// CTargetDemoDlg 대화 상자
class CTargetDemoDlg : public CDialogEx
{
// 생성입니다.
public:
	CTargetDemoDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	CGridCtrl m_Grid;
	int		m_nRows;
	int		m_nFixRows;
    typedef	struct targetInform {
		int id;
		int type;
		double x;
		double y;
		CString path;
	}targetInform;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TARGETDEMO_DIALOG };
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
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSave();
	int ti_id;
	int ti_type;
	double ti_x;
	double ti_y;
	CString ti_path;
	std::vector<targetInform> tVector;
	std::vector<targetInform>::iterator tVec_it;
	afx_msg void OnBnClickedButtonInput();
	afx_msg void OnBnClickedButtonClear();
	void VectorAdd(int id, int type, double x, double y, CString path);
	void ShowGrid();
};
