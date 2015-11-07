#pragma	title("Prominare Development System Support DLL  --  Version 3.0 -- (3DLine.C)")
#pragma	subtitle("  3D Line Control DLL - Interface Definitions")

#define	INCL_GPI		   /* Include OS/2 PM GPI Interface	*/
#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#include <os2.h>
#include <string.h>

#include <ccls32.h>
#include <heapmem.h>

#include "appdefs.h"
#include "except.h"

/* This	module contains	an example installable control that can	be used	*/
/* by Prominare	Designer to include within applications	where		*/
/* additional facilities are provided that are not found within	the	*/
/* default controls of OS/2 Presentation Manager.			*/
/*									*/
/* For complete	details	regarding the Custom Control Library		*/
/* Specification (CCLS), Version 2.1c, consult Section 2 in the		*/
/* Prominare Development System	Programming Guide.			*/
/*									*/
/* The DLL is created using the	following options in Prominare Builder:	*/
/*									*/
/* Option	       Value						*/
/* ------	       -----						*/
/* Op Sys	       OS/2 PM Static DLL				*/
/* Optimization	       Maximize						*/
/* Compile Type	       Subsystem					*/
/* CPU		       80486						*/
/* Warning Level       3						*/
/*									*/
/* Equivalent command line invocation:					*/
/*									*/
/*     Icc -C -G4e -O+ -Rn -W3 3DLine.C					*/

/* Filename:   3DLine.C							*/

/*  Version:   3.0							*/
/*  Created:   1994-08-23						*/
/*  Revised:   1994-08-23						*/

/* Routines:   LONG lGetPresParam(HWND hWnd, ULONG ulID1, ULONG	ulID2,	*/
/*				  LONG lDefault);			*/
/*	       static VOID CalcSize(PRECTL prcl, PLINEFIELD plf);	*/
/*	       MRESULT EXPENTRY	Line3DWndProc(HWND hWnd, ULONG msg,	*/
/*					      MPARAM mp1, MPARAM mp2);	*/


/* Copyright ¸ 1987-1994  Prominare Inc.  All Rights Reserved.		*/

/* --------------------------------------------------------------------	*/

typedef	struct _LINEFIELD	   /* lf */
   {
   POINTL aptl[4];		   /* Entry Field Outline Points	*/
   ULONG  flStyle;		   /* Line Style			*/
   LONG	  lClrShadow;		   /* Shadow Colour			*/
   BOOL	  fDraw;		   /* Draw Flag				*/
   } LINEFIELD ;

typedef	LINEFIELD *PLINEFIELD;

extern HHEAPMEM	hHeap;		   /* Heap Handle			*/

static VOID CalcSize(PRECTL prcl, PLINEFIELD plf);

static INTERNALADDRESSLIST aial[ ] = { { (PFNINTADD)lGetPresParam, "lGetPresParam" },
				       { (PFNINTADD)CalcSize,	   "CalcSize"	   },
				       { (PFNINTADD)Line3DWndProc, "Line3DWndProc" },
				       { NULL, NULL } };

INTERNALADDRESS	intadd3DLine =	{ __FILE__, 0, aial };

#pragma	subtitle("   Traffic Manager - Presentation Parameter Retrieve Procedure")
#pragma	page( )

/* --- lGetPresParam ----------------------------------	[ Private } ---	*/
/*									*/
/*     This function is	used to	retrieve a presentation	parameter	*/
/*     that may	be present.  If	the presentation parameter is not,	*/
/*     the default colour passed to the	function will be used.	All	*/
/*     colours queried for are RGB or their RGB	equivalents.		*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND  hWnd;     = Window	Handle					*/
/*     ULONG ulID1;    = Presentation Parameter	1 ID (RGB)		*/
/*     ULONG ulID2;    = Presentation Parameter	2 ID (Index)		*/
/*     LONG  lDefault; = Default Colour					*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     lGetPresParam = Colour to Use (RGB)				*/
/*									*/
/* --------------------------------------------------------------------	*/

LONG lGetPresParam(HWND	hWnd, ULONG ulID1, ULONG ulID2,	LONG lDefault)

{
HPS   hPS;			   /* Presentation Space Handle		*/
LONG  lClr;			   /* Presentation Parameter Colour	*/
ULONG ulID;			   /* Presentation Parameter ID		*/

		       /* First	try to determine if any	presentation	*/
		       /* parameters are set for the area requested.	*/
		       /* The first ID is RGB index and	the second ID	*/
		       /* is colour index.				*/

if ( WinQueryPresParam(hWnd, ulID1, ulID2, &ulID, sizeof(LONG),	(PVOID)&lClr,
		       QPF_NOINHERIT | QPF_ID2COLORINDEX) )

		       /* Presentation parameter set for the area,	*/
		       /* return the RGB colour				*/
   return(lClr);
else
		       /* No presentation parameters set, check	to see	*/
		       /* if the default is a system colour in which	*/
		       /* only need to query the index for the RGB	*/
		       /* value						*/

   if (	(lDefault >= SYSCLR_SHADOWHILITEBGND) &&
	(lDefault <= SYSCLR_HELPHILITE)	)
       return(WinQuerySysColor(HWND_DESKTOP, lDefault, 0L));
   else
		       /* Standard colour index, get the RGB equivalent	*/
		       /* for the index					*/

       if ( (hPS = WinGetPS(hWnd)) != (HPS)NULL	)
	   if (	(lClr =	GpiQueryRGBColor(hPS, LCOLOPT_REALIZED,	lDefault)) == GPI_ALTERROR )
	       {
		       /* Colour was not found,	return white as	colour	*/

	       WinReleasePS(hPS);
	       return(RGB_WHITE);
	       }
	   else
	       {
		       /* Colour found,	return the RGB value		*/

	       WinReleasePS(hPS);
	       return(lClr);
	       }
       else
	   return(RGB_WHITE);
}
#pragma	subtitle("   Shadowed Group Box DLL - Control Window Procedure")
#pragma	page ( )

/* --- CalcSize	---------------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	calculate the sizes and	positions	*/
/*     of the various elements that are	used to	make up	a 3D text	*/
/*     field.								*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     PRECTL	  prcl;	= Control Rectangle Pointer			*/
/*     PLINEFIELD ptf;	= Text Field Information Pointer		*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     Nothing								*/
/*									*/
/* --------------------------------------------------------------------	*/

static VOID CalcSize(PRECTL prcl, PLINEFIELD plf)

{

if ( (prcl->xRight <= prcl->xLeft) ||
     (prcl->yTop <= prcl->yBottom) )
   plf->fDraw =	FALSE;
else
   {
   plf->fDraw =	TRUE;

	       /*  Line	display	points					*/
	       /*							*/
	       /*	  0			      1			*/
	       /*	   ===========================			*/
	       /*	  2			      3			*/

   if (	plf->flStyle & LNS_VERTICAL )
       {
       plf->aptl[0].x =	plf->aptl[1].x = (prcl->xRight - prcl->xLeft) /	2L +
					  prcl->xLeft;
       plf->aptl[2].x =	plf->aptl[3].x = plf->aptl[0].x	+ 1L;
       plf->aptl[0].y =	plf->aptl[2].y = prcl->yBottom;
       plf->aptl[1].y =	plf->aptl[3].y = prcl->yTop   -	1L;
       }
   else
       {
       plf->aptl[0].x =	plf->aptl[2].x = prcl->xLeft;
       plf->aptl[1].x =	plf->aptl[3].x = prcl->xRight;
       plf->aptl[0].y =	plf->aptl[1].y = (prcl->yTop - prcl->yBottom) /	2L +
					  prcl->yBottom;
       plf->aptl[2].y =	plf->aptl[3].y = plf->aptl[0].y	- 1L;
       }
   }
}
#pragma	subtitle("   3D Line Control DLL - Control Window Procedure")
#pragma	page ( )

/* --- Line3DWndProc ----------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	handle the messages sent to the		*/
/*     installed control.  The window procedure	is designed to		*/
/*     allow for multiple instances and	to be totally re-entrant.	*/
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
/*     Line3DWndProc = Message Handling	Result				*/
/*									*/
/* --------------------------------------------------------------------	*/

MRESULT	EXPENTRY Line3DWndProc(HWND hWnd, ULONG	msg, MPARAM mp1, MPARAM	mp2)

{
HPS	      hPS;		   /* Presentation Space Handle		*/
PCREATESTRUCT pcrst;		   /* Create Structure Pointer		*/
PLINEFIELD    plf;		   /* Text Field Structure Pointer	*/
RECTL	      rcl;		   /* Rectangle	Holder			*/
ULONG	      flStyle;		   /* Style Flag			*/

switch ( msg )
   {
		       /* Perform control initialization when the	*/
		       /* control is created				*/
   case	WM_CREATE :
		       /* Save the address of the text string pointer	*/
		       /* in the control's reserved memory to allow it  */
		       /* to be	referenced as required by the control	*/

       WinSetWindowPtr(hWnd, QWW_CDATA,
		       (PVOID)(plf = (PLINEFIELD)HeapMalloc(hHeap, sizeof(LINEFIELD))));

		       /* Get the control's creation structure address  */
		       /* to copy the default text of the control to	*/
		       /* the memory in	the heap			*/

       pcrst = (PCREATESTRUCT)PVOIDFROMMP(mp2);

       plf->flStyle   =	pcrst->flStyle;

       plf->lClrShadow = WinQuerySysColor(HWND_DESKTOP,	SYSCLR_SHADOW, 0L);
       if ( ((rcl.xRight = pcrst->cx) >	0L) && ((rcl.yTop = pcrst->cy) > 0L) )
	   {
	   rcl.xLeft = rcl.yBottom = 0L;
	   CalcSize(&rcl, plf);
	   }
       break;
		       /* Size of control changing, reset the display	*/
		       /* points of the	line				*/
   case	WM_SIZE	:
       if ( ((LONG)(SHORT)SHORT1FROMMP(mp2) > 0L) && ((LONG)(SHORT)SHORT2FROMMP(mp2) > 0L) )
	   {
	   WinQueryWindowRect(hWnd, &rcl);
	   CalcSize(&rcl, (PLINEFIELD)WinQueryWindowPtr(hWnd, QWW_CDATA));
	   }
       else
	   {
	   plf = (PLINEFIELD)WinQueryWindowPtr(hWnd, QWW_CDATA);
	   plf->fDraw =	FALSE;
	   }
       break;
		       /* Mouse	being passed over the control, imply	*/
		       /* that the control is transparent to the	*/
		       /* system					*/
   case	WM_HITTEST :
       return(MRFROMLONG(HT_TRANSPARENT));

		       /* Erase	control	background			*/

   case	WM_ERASEBACKGROUND :
       return(MRFROMLONG(TRUE));

		       /* Paint	the Control				*/
   case	WM_PAINT :
		       /* Get the address of the text from the		*/
		       /* control's reserved memory                     */

       plf = (PLINEFIELD)WinQueryWindowPtr(hWnd, QWW_CDATA);
       if ( ((flStyle =	WinQueryWindowULong(hWnd, QWL_STYLE)) &	LNS_VERTICAL) &&
	    (plf->flStyle & LNS_HORIZONTAL) )
	   {
	   plf->flStyle	&= (ULONG)~LNS_HORIZONTAL;
	   plf->flStyle	|= LNS_VERTICAL;
	   WinQueryWindowRect(hWnd, &rcl);
	   CalcSize(&rcl, plf);
	   }
       else
	   if (	(flStyle & LNS_HORIZONTAL) && (plf->flStyle & LNS_VERTICAL) )
	       {
	       plf->flStyle &= (ULONG)~LNS_VERTICAL;
	       plf->flStyle |= LNS_HORIZONTAL;
	       WinQueryWindowRect(hWnd,	&rcl);
	       CalcSize(&rcl, plf);
	       }

       if ( plf->fDraw )
	   {
		       /* Get the presentation space for the control	*/
		       /* and set the colour table to RGB mode		*/

	   GpiCreateLogColorTable(hPS =	WinBeginPaint(hWnd, (HPS)NULL, (PRECTL)NULL),
				  0L, LCOLF_RGB, 0L, 0L, (PLONG)NULL);
	   GpiSetColor(hPS, plf->lClrShadow);

	   GpiMove(hPS,	plf->aptl);
	   GpiLine(hPS,	&plf->aptl[1]);

	   GpiSetColor(hPS, RGB_WHITE);

	   GpiMove(hPS,	&plf->aptl[2]);
	   GpiLine(hPS,	&plf->aptl[3]);

	   WinEndPaint(hPS);
	   }
       break;
		       /* Control being	destroyed			*/
   case	WM_DESTROY :
		       /* Get the address of the text from the		*/
		       /* control's reserved memory and release the     */
		       /* heap allocated for use by the	control		*/

       HeapFree(hHeap, (PVOID)WinQueryWindowPtr(hWnd, QWW_CDATA));
       break;
		       /* Default message processing			*/
   default :
       return(WinDefWindowProc(hWnd, msg, mp1, mp2));
   }

return(0L);
}
