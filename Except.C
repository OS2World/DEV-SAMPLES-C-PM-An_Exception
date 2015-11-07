#pragma	title("Exception Example  --  Version 1.0  --  ( Except.C)")
#pragma	subtitle("   main() Module - Interface Definitions")

#define	INCL_DOS		   /* Include OS/2 DOS Kernal		*/
#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#pragma	info(nopar)

#include <os2.h>

#include "appdefs.h"
#include "ccls32.h"
#include "except.h"

/* This	module contains	the main entry point to	the application	and	*/
/* also	performs that application interface setup with PM.		*/

/* Filename:	Except.C						*/

/*  Version:   1.0							*/
/*  Created:   1994-08-23						*/
/*  Revised:   1994-08-23						*/

/* Routines:   INT main(INT argc, CHAR *argv[ ]);			*/


/* Copyright ¸ 1994, 1995  Prominare Inc.  All Rights Reserved.		*/

/* --------------------------------------------------------------------	*/

INT main(INT argc, CHAR	*argv[ ]);
APIRET APIENTRY	ExceptionHandler(PEXCEPTIONREPORTRECORD	pxcptrepr,
				 PEXCEPTIONREGISTRATIONRECORD pxcptregr,
				 PCONTEXTRECORD	pcr, PVOID sysinfo);

static INTERNALADDRESSLIST aial[ ] = { { (PFNINTADD)main, "main" },
				       { NULL, NULL } };

INTERNALADDRESS	intaddExcept =	{ __FILE__, 0, aial };

PSZ pszExceptClassName = (PSZ)"Except";

INT main(INT argc, CHAR	*argv[ ])

{
EXCEPTIONREGISTRATIONRECORD xcptregr;  /* Exception Record		*/
QMSG			    qmsg;      /* PM Message Queue Holder	*/

		       /* Register the exception handler		*/


xcptregr.prev_structure	  = NULL;
xcptregr.ExceptionHandler = &ExceptionHandler;
DosSetExceptionHandler(&xcptregr);

		       /* Initialize the program for PM	and create the	*/
		       /* message queue					*/

hmqExcept = WinCreateMsgQueue(hAB = WinInitialize(0UL),	0L);

		       /* Register the window class			*/

if ( !WinRegisterClass(hAB, pszExceptClassName,	(PFNWP)ExceptionExampleWndProc,
		       CS_SYNCPAINT | CS_SIZEREDRAW, 0UL) )
   {
   DosUnsetExceptionHandler(&xcptregr);
   return(0);
   }
		       /* Register the control class with OS/2		*/
		       /* Presentation Manager and return registration	*/
		       /* result					*/

if ( !WinRegisterClass(hAB, "PDS.3DLine", (PFNWP)Line3DWndProc,
		       CS_SYNCPAINT | CS_HITTEST | CS_PARENTCLIP | CS_SIZEREDRAW,
		       USER_CWINDOWWORDS) )
   {
   DosUnsetExceptionHandler(&xcptregr);
   return(0);
   }
		       /* Register the control class with OS/2		*/
		       /* Presentation Manager and return registration	*/
		       /* result					*/

if ( !WinRegisterClass(hAB, "PDS.3DText", (PFNWP)Text3DWndProc,
			CS_SYNCPAINT | CS_HITTEST | CS_PARENTCLIP | CS_SIZEREDRAW,
			USER_CWINDOWWORDS) )
   {
   DosUnsetExceptionHandler(&xcptregr);
   return(0);
   }
		       /* Create the main program window		*/

if ( !(hwndExceptFrame = CreateStdWindow(HWND_DESKTOP, WS_VISIBLE,
					 FCF_NOBYTEALIGN | FCF_TASKLIST	|
					 FCF_TITLEBAR |	FCF_ICON | FCF_SYSMENU |
					 FCF_MENU | FCF_MINMAX | FCF_SIZEBORDER,
					 pszExceptClassName, (PSZ)"Exception Example", 0L,
					 (HMODULE)NULL,	WIN_EXCEPTIONEXAMPLE, &hwndExcept, 8, 65, 322, 132)) )
   {
   DosUnsetExceptionHandler(&xcptregr);
   return(0);
   }
		       /* Perform application initialization		*/

InitApp(hwndExceptFrame, hwndExcept, NULL);

		       /* Get and dispatch the message to program	*/
		       /* windows					*/

while (	WinGetMsg(hAB, &qmsg, (HWND)NULL, 0UL, 0UL) )
   WinDispatchMsg(hAB, &qmsg);

		       /* Have received	a WM_QUIT, start the program	*/
		       /* shutdown by destroying the program windows	*/
		       /* and destroying the message queue		*/

WinDestroyWindow(hwndExceptFrame);

WinDestroyMsgQueue(hmqExcept);

		       /* Notify PM that main program thread not needed	*/
		       /* any longer					*/
WinTerminate(hAB);

DosUnsetExceptionHandler(&xcptregr);

		       /* Exit back to OS/2 cleanly			*/
return(0);
}
