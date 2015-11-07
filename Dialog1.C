#pragma	title("Exception Example  --  Version 1.0  --  (Dialog1.C)")
#pragma	subtitle("   Module Purpose - Interface Definitions")

#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#pragma	info(noext)

#include <os2.h>

#include "appdefs.h"
#include "except.h"

/* This	module contains	routine	used to	handle a dialogue procedure.	*/

/* Filename:   Dialog1.C						*/

/*  Version:   1.0							*/
/*  Created:   1994-08-23						*/
/*  Revised:   1994-08-23						*/

/* Routines:   MRESULT EXPENTRY	DialogueException1DlgProc(HWND hWnd,	*/
/*							  ULONG	msg,	*/
/*							  MPARAM mp1,	*/
/*							  MPARAM mp2);	*/


/* Copyright ¸ 1994, 1995  Prominare Inc.  All Rights Reserved.		*/

/* --------------------------------------------------------------------	*/

PINT pi;			   /* Pointer				*/

static INTERNALADDRESSLIST aial[ ] = { { (PFNINTADD)DialogueException1DlgProc, "DialogueException1DlgProc" },
				       { NULL, NULL } };

INTERNALADDRESS	intaddDialog1 =	 { __FILE__, 0,	aial };

#pragma	subtitle("   Dialogues - Dialogue Procedure")
#pragma	page( )

/* --- DialogueException1DlgProc ----------------------- [ Public ] ---	*/
/*									*/
/*     This function is	used to	process	the messages for the dialog	*/
/*     procedure.							*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND   hWnd; = Dialog Window Handle				*/
/*     ULONG  msg;  = PM Message					*/
/*     MPARAM mp1;  = Message Parameter	1				*/
/*     MPARAM mp2;  = Message Parameter	2				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     DialogueException1DlgProc = Message Handling Result		*/
/*									*/
/* --------------------------------------------------------------------	*/

MRESULT	EXPENTRY DialogueException1DlgProc(HWND	hWnd, ULONG msg, MPARAM	mp1, MPARAM mp2)

{

switch ( msg )
   {
			/* Perform dialog initialization		*/
   case	WM_INITDLG :
       break;
			/* Process control selections			*/
   case	WM_CONTROL :
       switch (	SHORT2FROMMP(mp1) )
	   {
	   }
       break;
			/* Process push	button selections		*/
   case	WM_COMMAND :
       switch (	SHORT1FROMMP(mp1) )
	   {
	   case	DID_OK :
	       *pi = 0;
	       WinDismissDlg(hWnd, TRUE);
	       break;
	   }
       break;
			/* Close requested, exit dialogue		*/
   case	WM_CLOSE :
       WinDismissDlg(hWnd, FALSE);
       break;

			/* Pass	through	unhandled messages		*/
   default :
       return(WinDefDlgProc(hWnd, msg, mp1, mp2));
   }
return(0L);
}
