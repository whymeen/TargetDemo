
// TargetDemoDlg.h : ��� ����
//
#include "GridCtrl.h"
//#include "afxtempl.h"
#include <vector>
#pragma once


// CTargetDemoDlg ��ȭ ����
class CTargetDemoDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CTargetDemoDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
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
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TARGETDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
