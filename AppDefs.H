
/* AppDefs.H	    Created:	1994-08-23  Revised: 1994-08-23		*/

/* Module Definition Header						*/

/* Copyright ¸ 1994, 1995  Prominare Inc.  All Rights Reserved.		*/



/************************************************************************/
/************************************************************************/
/*	Global Variable	Definitions					*/
/************************************************************************/
/************************************************************************/

extern FONTMETRICS fm;		   /* Font Metrics Info			*/
extern HSWITCH	   hSwitch;	   /* Task List	Entry Handle		*/
extern HAB	   hAB;		   /* Program Anchor Block Handle	*/

extern HMQ  hmqExcept;		   /* Program Message Queue Handle	*/
extern HWND hwndExcept;		   /* Client Window Handle		*/
extern HWND hwndExceptFrame;	   /* Frame Window Handle		*/
extern HWND hmenuExcept;	   /* Menu Handle			*/

extern ULONG hHeap;		   /* Controls Heap Handle		*/


/************************************************************************/
/************************************************************************/
/*	Function Prototype Definitions					*/
/************************************************************************/
/************************************************************************/

VOID	InitApp(HWND hwndFrame,	HWND hwndClient, PSZ pszWindowListTitle);
HWND	CreateStdWindow(HWND hwndParent, ULONG flStyle,	ULONG flCreateFlags,
			PSZ pszClientClass, PSZ	pszTitle, ULONG	styleClient,
			HMODULE	hmod, ULONG idResources, PHWND phwndClient,
			LONG x,	LONG y,	LONG cx, LONG cy);

MRESULT	PDSKeyProc(HWND	hWnd, ULONG msg, MPARAM	mp1, MPARAM mp2);
VOID	PDSGetTemplate(HWND hWnd, ULONG	id);

MRESULT	EXPENTRY ExceptionExampleWndProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT	EXPENTRY DialogueException1DlgProc(HWND	hWnd, ULONG msg, MPARAM	mp1, MPARAM mp2);
MRESULT	EXPENTRY DialogueException2DlgProc(HWND	hWnd, ULONG msg, MPARAM	mp1, MPARAM mp2);
MRESULT	EXPENTRY XceptionDlgProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2);

LONG lGetPresParam(HWND	hWnd, ULONG ulID1, ULONG ulID2,	LONG lDefault);
MRESULT	EXPENTRY Line3DWndProc(HWND hWnd, ULONG	msg, MPARAM mp1, MPARAM	mp2);
MRESULT	EXPENTRY Text3DWndProc(HWND hWnd, ULONG	msg, MPARAM mp1, MPARAM	mp2);
