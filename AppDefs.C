#pragma	title("Exception Example  --  Version 1.0  --  (AppDefs.C)")
#pragma	subtitle("   Global Definitions - Interface Definitions")

#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#pragma	info(noext)

#include <os2.h>

#include "appdefs.h"
#include "except.h"
#include "heapmem.h"

/* This	module contains	the global definitions for the exception	*/
/* example.								*/

/* Filename:   AppDefs.C						*/

/*  Version:   1.0							*/
/*  Created:   1994-08-23						*/
/*  Revised:   1994-08-23						*/

/* Routines:								*/


/* Copyright ¸ 1994, 1995  Prominare Inc.  All Rights Reserved.		*/

/* --------------------------------------------------------------------	*/

FONTMETRICS fm;			   /* Font Metrics Info			*/
HAB	    hAB;		   /* Program Anchor Block Handle	*/
HSWITCH	    hSwitch;		   /* Task List	Entry Handle		*/

HMQ  hmqExcept;			   /* Program Message Queue Handle	*/
HWND hwndExcept;		   /* Client Window Handle		*/
HWND hwndExceptFrame;		   /* Frame Window Handle		*/
HWND hmenuExcept;		   /* Menu Handle			*/

HHEAPMEM hHeap;			   /* Controls Heap Handle		*/
