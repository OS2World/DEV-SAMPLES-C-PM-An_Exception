#pragma	title("Exception Example  --  Version 1.0  --  (WndProc.C)")
#pragma	subtitle("   Module Purpose - Interface Definitions")

#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#pragma	info(noext)

#include <os2.h>

#include "appdefs.h"
#include "except.h"
#include "heapmem.h"

/* This	module contains	routine	used to	process	the window procedure	*/
/* for the applicaiton.							*/

/* Filename:   WndProc.C						*/

/*  Version:   1.0							*/
/*  Created:   1994-08-23						*/
/*  Revised:   1994-08-23						*/

/* Routines:								*/


/* Copyright ¸ 1994, 1995  Prominare Inc.  All Rights Reserved.		*/

/* --------------------------------------------------------------------	*/

static INTERNALADDRESSLIST aial[ ] = { { (PFNINTADD)ExceptionExampleWndProc, "ExceptionExampleWndProc"	},
				       { NULL, NULL } };

INTERNALADDRESS	intaddWndProc =	 { __FILE__, 0,	aial };

#pragma	subtitle("   Client Window - Client Window Procedure")
#pragma	page( )

/* --- ExceptionExampleWndProc ------------------------- [ Public ] ---	*/
/*									*/
/*     This function is	used to	process	the messages sent to the	*/
/*     applications client window.					*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND   hWnd; = Window Handle					*/
/*     ULONG  msg;  = PM Message					*/
/*     MPARAM mp1;  = Message Parameter	1				*/
/*     MPARAM mp2;  = Message Parameter	2				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     ExceptionExampleWndProc = Message Handling Result		*/
/*									*/
/* --------------------------------------------------------------------	*/

MRESULT	EXPENTRY ExceptionExampleWndProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{
RECTL rcl;			    /* Window Rectangle			*/
HPS   hPS;			    /* Presentation Space Handle	*/

switch ( msg )
   {
			/* Process key press from keyboard		*/
   case	WM_CHAR	:
			/************************************************/
			/* PDSKeyProc is used to allow controls	in	*/
			/* windows.  Do	not remove this	function if you	*/
			/* intend to include controls within the window.*/
			/************************************************/

       return(PDSKeyProc(hWnd, msg, mp1, mp2));

			/* Process menu	and button selections		*/
   case	WM_COMMAND :
       switch (	SHORT1FROMMP(mp1) )
	   {
	   case	IDM_DIALOGUE1EXCEPTION :
	       WinDlgBox(HWND_DESKTOP, hwndExceptFrame,	(PFNWP)DialogueException1DlgProc,
			 (HMODULE)NULL,	DLG_DIALOGUE1EXCEPTION,	NULL);
	       break;

	   case	IDM_DIALOGUE2EXCEPTION :
	       WinDlgBox(HWND_DESKTOP, hwndExceptFrame,	(PFNWP)DialogueException2DlgProc,
			 (HMODULE)NULL,	DLG_DIALOGUE2EXCEPTION,	NULL);
	       break;
	   }
       break;
			/* Process control selections			*/
   case	WM_CONTROL :
	switch ( SHORT2FROMMP(mp1) )
	    {
	    }
	break;
			/* Window being	created, perform window		*/
			/* initialization				*/
   case	WM_CREATE :
       hHeap = HeapAlloc(8192UL, 8192UL);

			/************************************************/
			/* PDSGetTemplate is used to allow controls in	*/
			/* windows.  Do	not remove this	function if you	*/
			/* intend to include controls within the window.*/
			/************************************************/

	PDSGetTemplate(hWnd, WIN_EXCEPTIONEXAMPLE);
	break;
			/* Window being	destroyed, perform clean-up	*/
			/* operations					*/
   case	WM_DESTROY :
       HeapRelease(hHeap);
       break;
			/* Erase window	background			*/

   case	WM_ERASEBACKGROUND :
       WinQueryWindowRect(hWnd,	&rcl);
       WinFillRect((HPS)LONGFROMMP(mp1), &rcl, SYSCLR_WINDOW);
       break;
			/* Perform menu	initialization			*/
   case	WM_INITMENU :
       switch (	SHORT1FROMMP(mp1) )
	   {
	  case IDM_FILE	:
	       break;

	   }
       break;
			/* Paint client	window				*/
   case	WM_PAINT :
       WinFillRect(hPS = WinBeginPaint(hWnd, (HPS)NULL,	&rcl), &rcl, SYSCLR_WINDOW);
       WinEndPaint(hPS);
       break;

			/* Default message processing			*/
   default :
       return(WinDefWindowProc(hWnd, msg, mp1, mp2));
   }
return(0L);
}
