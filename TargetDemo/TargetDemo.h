
// TargetDemo.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTargetDemoApp:
// �� Ŭ������ ������ ���ؼ��� TargetDemo.cpp�� �����Ͻʽÿ�.
//

class CTargetDemoApp : public CWinApp
{
public:
	CTargetDemoApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTargetDemoApp theApp;