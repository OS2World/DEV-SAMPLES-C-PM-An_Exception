#pragma	title("Prominare Development System Support DLL  --  Version 3.0 -- (3DText.C)")
#pragma	subtitle("  3D Text Control DLL - Interface Definitions")

#pragma	strings(readonly)
#pragma	info(noext)

#define	INCL_GPI		   /* Include OS/2 PM GPI Interface	*/
#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#include <os2.h>
#include <string.h>
#include <stdio.h>

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
/* Build Type	       Subsystem					*/
/* CPU		       80486						*/
/* Warning Level       3						*/
/*									*/
/* Equivalent command line invocation:					*/
/*									*/
/*     Icc -C -G4e -O+ -Rn -W3 3DText.C					*/

/* Filename:   3DText.C							*/

/*  Version:   3.0							*/
/*  Created:   1994-08-23						*/
/*  Revised:   1994-08-23						*/

/* Routines:   static VOID CalcSize(PRECTL prcl, PTEXTFIELD ptf);	*/
/*	       static VOID SetDefaultColours(HWND hWnd,			*/
/*						 PTEXTFIELD ptf);	*/
/*	       static HPS  hpsDrawText(HPS hPS,	PTEXTFIELD ptf);	*/
/*	       MRESULT EXPENTRY	Text3DWndProc(HWND hWnd, ULONG msg,	*/
/*					      MPARAM mp1, MPARAM mp2);	*/


/* Copyright ¸ 1989-1994  Prominare Inc.  All Rights Reserved.		*/

/* --------------------------------------------------------------------	*/

typedef	struct _TEXTFIELD	   /* tf */
   {
   POINTL aptl[4];		   /* Entry Field Outline Points	*/
   RECTL  rcl;			   /* Frame Rectangle			*/
   LONG	  lClrLeftTop;		   /* Left and Top Edge	Colour		*/
   LONG	  lClrBottomRight;	   /* Right and	Bottom Edge Colour	*/
   BOOL	  fRaised;		   /* Raised Field Flag			*/
   LONG	  lClrText;		   /* Text Colour			*/
   LONG	  lClrBackground;	   /* Background Colour			*/
   LONG	  lClrBorder;		   /* Border Colour			*/
   LONG	  cText;		   /* Text Length Holder		*/
   PSZ	  pszText;		   /* Text Holder			*/
   ULONG  flFormat;		   /* Formatting Flags			*/
   ULONG  flStyle;		   /* Style Flags			*/
   BOOL	  fDraw;		   /* Draw Flag				*/
   } TEXTFIELD ;

typedef	TEXTFIELD *PTEXTFIELD;

extern HHEAPMEM	hHeap;		 /* Heap Handle			      */

#define	DT_MASK	(DT_LEFT | DT_CENTER | DT_RIGHT	| DT_TOP | DT_VCENTER |	DT_BOTTOM | DT_HALFTONE	| DT_MNEMONIC |	DT_WORDBREAK)

/* --- Module Prototype	Definitions -----------------------------------	*/

static VOID CalcSize(PRECTL prcl, PTEXTFIELD ptf);
static VOID SetDefaultColours(HWND hWnd, PTEXTFIELD ptf);
static HPS  hpsDrawText(HPS hPS, PTEXTFIELD ptf);

static INTERNALADDRESSLIST aial[ ] = { { (PFNINTADD)CalcSize,	       "CalcSize"	   },
				       { (PFNINTADD)SetDefaultColours, "SetDefaultColours" },
				       { (PFNINTADD)hpsDrawText,       "hpsDrawText"	   },
				       { (PFNINTADD)Text3DWndProc,     "Text3DWndProc"	   },
				       { NULL, NULL } };

INTERNALADDRESS	intadd3DText =	{ __FILE__, 0, aial };

#pragma	subtitle("   Shadowed Text DLL - Control Window Sizing Procedure")
#pragma	page ( )

/* --- CalcSize	---------------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	calculate the sizes and	positions	*/
/*     of the various elements that are	used to	make up	a shadowed	*/
/*     text field.							*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     PRECTL	  prcl;	= Control Rectangle Pointer			*/
/*     PTEXTFIELD ptf;	= Group	Box Information	Pointer			*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     Nothing								*/
/*									*/
/* --------------------------------------------------------------------	*/

static VOID CalcSize(PRECTL prcl, PTEXTFIELD ptf)

{

if ( (prcl->yTop <= prcl->yBottom) || (prcl->xRight <= prcl->xLeft) )
   ptf->fDraw =	FALSE;
else
   {
   ptf->fDraw =	TRUE;
		       /* Save the rectangle for the control		*/
   ptf->rcl = *prcl;
		       /* Adjust the rectangle size for	the text which	*/
		       /* resides inside the 3D	frame			*/
   ++ptf->rcl.xLeft;
   ++ptf->rcl.yBottom;
   ptf->rcl.yTop -= 2L;
   ptf->rcl.xRight -= 2L;

	       /*  Text	display	points					*/
	       /*							*/
	       /*	  1			      2			*/
	       /*	   +-------------------------+			*/
	       /*	   |			     |			*/
	       /*	   |			     |			*/
	       /*	   |			     |			*/
	       /*	   |			     |			*/
	       /*	   +-------------------------+			*/
	       /*	  0 4			      3			*/

   ptf->aptl[0].x = prcl->xLeft;
   ptf->aptl[0].y = prcl->yTop	 - 1L;
   ptf->aptl[1].x = prcl->xRight - 1L;
   ptf->aptl[1].y = prcl->yTop	 - 1L;
   ptf->aptl[2].x = prcl->xRight - 1L;
   ptf->aptl[2].y = prcl->yBottom;
   ptf->aptl[3].x = prcl->xLeft;
   ptf->aptl[3].y = prcl->yBottom;

		       /* Get the text formatting flags	and save	*/

   ptf->flFormat = (ptf->flStyle &  DT_MASK) | DT_ERASERECT;
   }
}
#pragma	subtitle("   Shadowed Text DLL - Default Colours Procedure")
#pragma	page( )

/* --- SetDefaultColours ------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	set the	default	colours	that the	*/
/*     image button should use within the internal paint routines.	*/
/*     The colour can either be	a presentation parameter that has	*/
/*     been set	or it can be the default colour	as defined within	*/
/*     control.								*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND	  hWnd;	= Window Handle					*/
/*     PTEXTFIELD ptf;	= Text Field Structure Pointer			*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     Nothing								*/
/*									*/
/* --------------------------------------------------------------------	*/

static VOID SetDefaultColours(HWND hWnd, PTEXTFIELD ptf)

{
		       /* Set up the colours that will be used within	*/
		       /* the painting of the control.			*/

ptf->lClrText	    = lGetPresParam(hWnd, PP_FOREGROUNDCOLOR,
				    PP_FOREGROUNDCOLORINDEX,
				    SYSCLR_OUTPUTTEXT);
ptf->lClrBackground = lGetPresParam(hWnd, PP_BACKGROUNDCOLOR,
				    PP_BACKGROUNDCOLORINDEX,
				    SYSCLR_DIALOGBACKGROUND);
ptf->lClrBorder	    = lGetPresParam(hWnd, PP_BORDERCOLOR,
				    PP_BORDERCOLORINDEX,
				    SYSCLR_BUTTONDARK);
}
#pragma	subtitle("   Shadowed Text DLL - 3D Text Window Procedure")
#pragma	page ( )

/* --- DrawText	---------------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	draw the text and 3D outline.		*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HPS	  hPS; = Window	Presentation Space Handle		*/
/*     PTEXTFIELD ptf; = Text Field Pointer				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     hpsDrawText = Window Presentation Space Handle			*/
/*									*/
/* --------------------------------------------------------------------	*/

static HPS hpsDrawText(HPS hPS,	PTEXTFIELD ptf)

{
FONTMETRICS fm3D;		   /* Font Metrics Holder		*/
RECTL	    rcl;		   /* Rectangle	Holder			*/
register LONG i, k, n;		   /* String Length Counter		*/

		       /* Get the presentation space for the control	*/
		       /* and set the colour table to RGB mode		*/

GpiCreateLogColorTable(hPS, 0L,	LCOLF_RGB, 0L, 0L, (PLONG)NULL);

		       /* Check	to see if any text present and if the	*/
		       /* case,	draw it	within the rectangle		*/

if ( ptf->cText	)
		       /* Check	to see if the text is to be broken over	*/
		       /* more than one	line if	the length of the text	*/
		       /* is greater than the width of the control	*/

   if (	ptf->flStyle & DT_WORDBREAK )
       {
		       /* Word break style specified, set the drawing	*/
		       /* of the text within a loop such that it can	*/
		       /* be drawn on successive lines			*/
       n = ptf->cText;
       GpiQueryFontMetrics(hPS,	sizeof(FONTMETRICS), &fm3D);
       rcl = ptf->rcl;
       i = 0;
       do
	   {
	   n -=	(k = WinDrawText(hPS, n, &ptf->pszText[i], &rcl, ptf->lClrText,
				 ptf->lClrBackground, ptf->flFormat));
	   i +=	k;
	   if (	(rcl.yTop -= fm3D.lMaxBaselineExt) < rcl.yBottom )
	       break;
	   } while ( n > 0 );
       }
   else
       WinDrawText(hPS,	ptf->cText, ptf->pszText, &ptf->rcl, ptf->lClrText,
		   ptf->lClrBackground,	ptf->flFormat);
else
   WinFillRect(hPS, &ptf->rcl, ptf->lClrBackground);

GpiSetColor(hPS, ptf->lClrLeftTop);

GpiMove(hPS, &ptf->aptl[3]);
GpiPolyLine(hPS, 2L, ptf->aptl);

GpiSetColor(hPS, ptf->lClrBottomRight);
GpiPolyLine(hPS, 2L, &ptf->aptl[2]);

return(hPS);
}
#pragma	subtitle("   Shadowed Text DLL - 3D Text Window Procedure")
#pragma	page ( )

/* --- Text3DWndProc ----------------------------------	[ Private ] ---	*/
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
/*     Text3DWndProc = Message Handling	Result				*/
/*									*/
/* --------------------------------------------------------------------	*/

MRESULT	EXPENTRY Text3DWndProc(HWND hWnd, ULONG	msg, MPARAM mp1, MPARAM	mp2)

{
LONG	       lClr;		   /* Presentation Parameter Colour	*/
PCREATESTRUCT  pcrst;		   /* Create Structure Pointer		*/
PTEXTFIELD     ptf;		   /* Text Field Structure Pointer	*/
PWNDPARAMS     pwprm;		   /* Window Parameters	Pointer		*/
RECTL	       rcl;		   /* Rectangle	Holder			*/
ULONG	       flStyle;		   /* Control Style			*/
ULONG	       ulID;		   /* Presentation Parameter ID		*/

switch ( msg )
   {
		       /* Perform control initialization when the	*/
		       /* control is created				*/
   case	WM_CREATE :
		       /* Save the address of the text string pointer	*/
		       /* in the control's reserved memory to allow it  */
		       /* to be	referenced as required by the control	*/

       WinSetWindowPtr(hWnd, QWW_CDATA,
		       (PVOID)(ptf = (PTEXTFIELD)HeapMalloc(hHeap, sizeof(TEXTFIELD))));

		       /* Get the control's creation structure address  */
		       /* to copy the default text of the control to	*/
		       /* the memory in	the heap			*/

       pcrst = (PCREATESTRUCT)PVOIDFROMMP(mp2);

       if ( pcrst->pszText )
	   {
	   ptf->pszText	= (PSZ)HeapMalloc(hHeap, (ULONG)(ptf->cText = (LONG)strlen(pcrst->pszText)) + 1UL);
	   memcpy(ptf->pszText,	pcrst->pszText,	(UINT)ptf->cText);
	   }
		       /* Set up the colours that will be used within	*/
		       /* the painting of the control.			*/

       SetDefaultColours(hWnd, ptf);

		       /* Check	to see if the user provided font that	*/
		       /* should override the default font that	would	*/
		       /* be set					*/

       if ( !WinQueryPresParam(hWnd, PP_FONTNAMESIZE, 0L, &ulID, 4L,
			       (PVOID)&lClr, QPF_NOINHERIT) )

		       /* System indicates not set since not data was	*/
		       /* returned, therefore set default font for the	*/
		       /* control					*/

	   WinSetPresParam(hWnd, PP_FONTNAMESIZE, 8L, (PVOID)"10.Helv");

       if ( (ptf->flStyle = pcrst->flStyle) & DS_RAISED	)
	   {
	   ptf->fRaised	= TRUE;
	   ptf->lClrLeftTop	= RGB_WHITE;
	   ptf->lClrBottomRight	= ptf->lClrBorder;
	   }
       else
	   {
	   ptf->fRaised	= FALSE;
	   ptf->lClrLeftTop	= ptf->lClrBorder;
	   ptf->lClrBottomRight	= RGB_WHITE;
	   }

       if ( ((rcl.xRight = pcrst->cx) >	0L) && ((rcl.yTop = pcrst->cy) > 0L) )
	   {
	   rcl.xLeft = rcl.yBottom = 0L;
	   CalcSize(&rcl, ptf);
	   }
       break;
		       /* Control size changing, update	the rectangle	*/
		       /* points for the 3D text control		*/
   case	WM_SIZE	:
       if ( ((LONG)(SHORT)SHORT1FROMMP(mp2) > 0L) && ((LONG)(SHORT)SHORT2FROMMP(mp2) > 0L) )
	   {
	   WinQueryWindowRect(hWnd, &rcl);
	   CalcSize(&rcl, (PTEXTFIELD)WinQueryWindowPtr(hWnd, QWW_CDATA));
	   }
       else
	   {
	   ptf = (PTEXTFIELD)WinQueryWindowPtr(hWnd, QWW_CDATA);
	   ptf->fDraw =	FALSE;
	   }
       break;
		       /* Process window parameters setting		*/

   case	WM_SETWINDOWPARAMS :

		       /* Get the address for the windows parameters	*/
		       /* structure					*/

       pwprm = (PWNDPARAMS)PVOIDFROMMP(mp1);

		       /* Check	to see if the text for the control is	*/
		       /* being	set					*/

       if ( pwprm->fsStatus & WPM_TEXT )
	   {
		       /* Text being set, get the address of the text	*/
		       /* string stored	in the heap			*/

	   ptf = (PTEXTFIELD)WinQueryWindowPtr(hWnd, QWW_CDATA);

		       /* Check	to see if any text is being set		*/

	   if (	pwprm->cchText )
	       {
	       if ( ptf->cText )
		   ptf->pszText	= (PSZ)HeapRealloc(hHeap, ptf->pszText,
						   (ULONG)(ptf->cText =	(LONG)pwprm->cchText) +	1UL);
	       else
		   ptf->pszText	= (PSZ)HeapMalloc(hHeap, (ULONG)(ptf->cText = (LONG)pwprm->cchText) + 1UL);

		       /* Check	to make	sure that the text that	is to	*/
		       /* be set is not	greater	than the memory		*/
		       /* allocated					*/

	       memcpy(ptf->pszText, pwprm->pszText, (UINT)pwprm->cchText);
	       ptf->pszText[ptf->cText]	= 0;
	       }
	   else
	       {
	       if ( ptf->cText )
		   HeapFree(hHeap, ptf->pszText);

		       /* No text is being set,	clear any existing text	*/

	       ptf->cText = 0L;
	       }

	   if (	ptf->fDraw )
	       WinReleasePS(hpsDrawText(WinGetPS(hWnd),	ptf));
	   }
       break;
		       /* Process window parameters query		*/

   case	WM_QUERYWINDOWPARAMS :

		       /* Get the address for the windows parameters	*/
		       /* structure					*/

       pwprm = (PWNDPARAMS)PVOIDFROMMP(mp1);

		       /* Determine the	type of	query			*/

       switch (	pwprm->fsStatus	)
	   {
		       /* Query	type:  get text				*/

	   case	WPM_TEXT :

		       /* Text being asked for,	get the	address	of the	*/
		       /* text string stored in	the heap		*/

	       ptf = (PTEXTFIELD)WinQueryWindowPtr(hWnd, QWW_CDATA);

		       /* Copy the text	from the string	to the		*/
		       /* structure					*/

	       memcpy(pwprm->pszText, ptf->pszText, (UINT)(ptf->cText +	1));
	       break;
		       /* Query	type:  get text	length			*/

	   case	WPM_CCHTEXT :

		       /* Text length being asked for, get the address	*/
		       /* of the text string stored in the heap		*/

	       ptf = (PTEXTFIELD)WinQueryWindowPtr(hWnd, QWW_CDATA);

		       /* Place	the length the string within the	*/
		       /* structure					*/

	       pwprm->cchText =	(ULONG)ptf->cText;
	       break;
		       /* Query	type:  get control data	length		*/

	   case	WPM_CBCTLDATA :

		       /* Set the control data length to zero		*/

	       pwprm->cbCtlData	= 0;
	       break;

	   default :
	       return(WinDefWindowProc(hWnd, msg, mp1, mp2));
	   }
       break;
		       /* Presentation parameters changed, record the	*/
		       /* change internally				*/

   case	WM_PRESPARAMCHANGED :

		       /* Check	to see if an individual	presentation	*/
		       /* parameter has	changed	if so, get the new	*/
		       /* colour value for use by the painting routines	*/

       if ( LONGFROMMP(mp1) && (LONGFROMMP(mp1)	< PP_FONTNAMESIZE) )
	   {
		       /* Get the address of the control info from the	*/
		       /* control's reserved memory                     */

	   ptf = (PTEXTFIELD)WinQueryWindowPtr(hWnd, QWW_CDATA);

		       /* Get the new presentation parameter colour for	*/
		       /* the presentation parameter that has changed.	*/
		       /* Get the colour as a RGB value	so as to be	*/
		       /* able to get an exact value and not an		*/
		       /* approximation	which could happen if the	*/
		       /* presentation parameter was set as a RGB but	*/
		       /* queried as an	index.	When WinQueryPresParam	*/
		       /* returns a 0, it indicates that no		*/
		       /* presentation parameter set and the default	*/
		       /* colours should be used.			*/

	   switch ( LONGFROMMP(mp1) )
	       {
	       case PP_FOREGROUNDCOLOR :
	       case PP_FOREGROUNDCOLORINDEX :
		   ptf->lClrText = lGetPresParam(hWnd, PP_FOREGROUNDCOLOR,
						PP_FOREGROUNDCOLORINDEX,
						SYSCLR_OUTPUTTEXT);
		   break;

	       case PP_BACKGROUNDCOLOR :
	       case PP_BACKGROUNDCOLORINDEX :
		   ptf->lClrBackground = lGetPresParam(hWnd, PP_BACKGROUNDCOLOR,
						PP_BACKGROUNDCOLORINDEX,
						SYSCLR_DIALOGBACKGROUND);
		   break;

	       case PP_BORDERCOLOR :
	       case PP_BORDERCOLORINDEX	:
		   ptf->lClrBorder = lGetPresParam(hWnd, PP_BORDERCOLOR,
						PP_BORDERCOLORINDEX,
						SYSCLR_BUTTONDARK);
		   break;
	       }
	   if (	ptf->fRaised )
	       ptf->lClrBottomRight = ptf->lClrBorder;
	   else
	       ptf->lClrLeftTop	    = ptf->lClrBorder;

		       /* Invalidate the button	to force to use	the	*/
		       /* new colours just set or removed		*/

	   if (	ptf->fDraw )
	       WinReleasePS(hpsDrawText(WinGetPS(hWnd),	ptf));
	   }
       else
		       /* Determine if the Scheme Palette has forced a	*/
		       /* global scheme	update in which	case, check all	*/
		       /* of the presentation parameters to see	if they	*/
		       /* have been added or removed			*/

	   if (	LONGFROMMP(mp1)	== 0L )

		       /* Set up the colours that will be used within	*/
		       /* the painting of the control.			*/

	       SetDefaultColours(hWnd,
				 ptf = (PTEXTFIELD)WinQueryWindowPtr(hWnd, QWW_CDATA));
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

       ptf = (PTEXTFIELD)WinQueryWindowPtr(hWnd, QWW_CDATA);

		       /* Before painting, check to see	if the style of	*/
		       /* the control has changed.  When it has	changed	*/
		       /* make sure that the control internal values	*/
		       /* are updated to reflect any changes made.	*/

       if ( ((flStyle =	WinQueryWindowULong(hWnd, QWL_STYLE)) &	(DT_MASK && SS_TEXT)) !=
	    (ptf->flStyle & (DT_MASK &&	SS_TEXT)) )
	   {
	   if (	(ptf->flStyle =	flStyle) & DS_RAISED )
	       {
	       ptf->fRaised = TRUE;
	       ptf->lClrLeftTop	    = RGB_WHITE;
	       ptf->lClrBottomRight = ptf->lClrBorder;
	       }
	   else
	       {
	       ptf->fRaised = FALSE;
	       ptf->lClrLeftTop	    = ptf->lClrBorder;
	       ptf->lClrBottomRight = RGB_WHITE;
	       }

	   WinQueryWindowRect(hWnd, &rcl);
	   CalcSize(&rcl, ptf);
	   }
		       /* Get the presentation space for the control	*/
		       /* and set the colour table to RGB mode		*/
       if ( ptf->fDraw )
	   WinEndPaint(hpsDrawText(WinBeginPaint(hWnd, (HPS)NULL, (PRECTL)NULL), ptf));
       break;
		       /* Control being	destroyed			*/
   case	WM_DESTROY :
		       /* Release the heap allocated for use by	the	*/
		       /* control					*/

       ptf = (PTEXTFIELD)WinQueryWindowPtr(hWnd, QWW_CDATA);
       if ( ptf->cText )
	   HeapFree(hHeap, ptf->pszText);
       HeapFree(hHeap, ptf);
       break;
		       /* Default message processing			*/
   default :
       return(WinDefWindowProc(hWnd, msg, mp1, mp2));
   }

return(0L);
}
