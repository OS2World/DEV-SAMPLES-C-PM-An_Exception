#pragma	title("Example Exception Handler  --  Version 1.0  --  (Xcept.C)")
#pragma	subtitle("   Exception Handler - Interface Definitions")

#define	INCL_DOS		   /* Include OS/2 DOS Kernal		*/
#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#pragma	info(nopar, noext)

#include <os2.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "appdefs.h"
#include "except.h"


/* This	module contains	the example exception handler and dialogue	*/
/* display.								*/

/* Filename:   XCept.C							*/

/*  Version:   3.0							*/
/*  Created:   1994-08-22						*/
/*  Revised:   1994-08-22						*/

/* Routines:   VOID XEndAddress(VOID);					*/
/*	       static VOID SortAddresses(INTERNALADDRESSLIST *aial,	*/
/*					 INT sLeft, INT	sRight);	*/
/*	       static BOOL fLookupAddress(PVOID	pvExceptAddress,	*/
/*					  PEXCEPT pex,			*/
/*					  BOOL fStackTrace,		*/
/*					  INT cFunctions);		*/
/*	       APIRET APIENTRY ExceptionHandler(			*/
/*			       PEXCEPTIONREPORTRECORD pxcptrepr,	*/
/*			       PEXCEPTIONREGISTRATIONRECORD pxcptregr,	*/
/*			       PCONTEXTRECORD pcr, PVOID sysinfo);	*/
/*	       static PSZ pszHexShort(ULONG ul,	PSZ pszBuffer);	    */
/*	       static PSZ pszHex(ULONG ul, PSZ pszBuffer);	    */
/*	       static PSZ pszFormAddress(PSZ pszBuffer,	ULONG ulSeg,*/
/*					     ULONG ulBase);		*/
/*	       MRESULT EXPENTRY	ExceptionDlgProc(HWND hWnd, ULONG msg,	*/
/*						 MPARAM	mp1,		*/
/*						 MPARAM	mp2);		*/


/* Copyright ¸ 1994, 1995  Prominare Inc.  All Rights Reserved.		*/

/* --------------------------------------------------------------------	*/

INT  main(INT, CHAR *[ ]);
VOID XEndAddress(VOID);

/* --- External	Definitions -------------------------------------------	*/

/************************************************************************/
/*									*/
/*     DEBUGGING SUPPORT     DEBUGGING SUPPORT	   DEBUGGING SUPPORT	*/
/*									*/
/************************************************************************/

static INTERNALADDRESSLIST aial[ ] = { { (PFNINTADD)XEndAddress, "XEndAddress" },
				       { NULL, NULL } };

static INTERNALADDRESSLIST *pial;  /* Constructed Address List		*/
static PINT piModules;		   /* Constructed Modules Array		*/

INTERNALADDRESS	intaddXceptionHandler =	 { __FILE__, 0,	aial };

extern INTERNALADDRESS intadd3DLine;
extern INTERNALADDRESS intadd3DText;
extern INTERNALADDRESS intaddDialog1;
extern INTERNALADDRESS intaddDialog2;
extern INTERNALADDRESS intaddExcept;
extern INTERNALADDRESS intaddSupport;
extern INTERNALADDRESS intaddWndProc;

#define	CMODULES 7

INTERNALADDRESS	*aintadd[ ] = {	&intaddExcept,	   /* Always place first module	here */
				&intadd3DLine,
				&intadd3DText,
				&intaddDialog1,
				&intaddDialog2,
				&intaddSupport,
				&intaddWndProc,
				&intaddXceptionHandler };

/************************************************************************/
/*									*/
/*     DEBUGGING SUPPORT     DEBUGGING SUPPORT	   DEBUGGING SUPPORT	*/
/*									*/
/************************************************************************/

BOOL   (* EXPENTRY pfnDllExceptionLookup)(PVOID	ExceptionAddress, PSZ pszName,
					  PSZ pszModule, PSZ pszFunction,
					  PVOID	*pfnStart, PVOID *pfnEnd);

typedef	struct _EXCEPT
   {
   PEXCEPTIONREPORTRECORD pxcptrepr;
   PCONTEXTRECORD	  pcr;
   INT			  iIntAdd;
   CHAR			  szComponent[CCHMAXPATH];
   CHAR			  szModule[CCHMAXPATH];
   CHAR			  szFunction[64];
   BOOL			  fStackTraced;
   PVOID		  pfnStart;
   PVOID		  pfnEnd;
   PID			  pid;
   TID			  tid;
   } EXCEPT, *PEXCEPT;

static VOID SortAddresses(INTERNALADDRESSLIST *aial, INT sLeft,	INT sRight);
static BOOL fLookupAddress(PVOID pvExceptAddress, PEXCEPT pex, BOOL fStackTrace, INT cFunctions);

static PSZ pszRegisters	=
"\r\n\r\nRegister dump:\r\nEAX = 0x%08X    EBX = 0x%08X    ECX = 0x%08X    EDX = 0x%08X\r\n"
"EBP = 0x%08X    EDI = 0x%08X    ESI = 0x%08X    ESP = 0x%08X\r\n"
" CS = 0x%04X         DS = 0x%04X         ES = 0x%04X         FS = 0x%04X\r\n"
" GS = 0x%04X         SS = 0x%04X\r\n\r\n"
"%s-%02d-%02d %02d:%02d:%02d.%02d\r\nPID: %u  TID: %u\r\n\r\n";

static PSZ pszAddresses	=
"main( )             : 0x%08X\r\n"
"ExceptionHandler( ) : 0x%08X\r\n"
"-----\r\n\r\n";

static PSZ apszMonth[12] = { "Jan", "Feb", "Mar", "Apr", "May",	"Jun",
			     "Jul", "Aug", "Sep", "Oct", "Nov",	"Dec" };

static PSZ pszFormAddress(PSZ pszBuffer, ULONG ulSeg, ULONG ulBase);
static PSZ pszHexShort(ULONG ul, PSZ pszBuffer);
static PSZ pszHex(ULONG	ul, PSZ	pszBuffer);

typedef	struct _EXCEPTINFO
   {
   PEXCEPT  pex;		   /* Exception	Data			*/
   PSZ	    pszTitle;		   /* Dialogue Title			*/
   PSZ	    pszXCP;		   /* XCP Filename			*/
   BOOL	    fFatal;		   /* Fatal Error Flag			*/
   } EXCEPTINFO, *PEXCEPTINFO;

#pragma	subtitle("   Exception Handler - End Address Function")
#pragma	page( )

/* --- XEndAddress ------------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used as	the end	address	marker for the		*/
/*     main-line code of Prominare Designer.				*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     Nothing								*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     Nothing								*/
/*									*/
/* --------------------------------------------------------------------	*/

VOID XEndAddress(VOID)

{
}
#pragma	subtitle("   Storage Support - Dialogue ID Sort Routine")
#pragma	page( )

/* --- SortAddresses ----------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	sort a source modules function		*/
/*     addresses in ascending order.  The routine implemented is the	*/
/*     "Quick Sort" algorithm.	The function uses recursion to		*/
/*     perform the sort.						*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     INTERNALADDRESSLIST *aial;  = Internal Address List Pointer	*/
/*     INT		   sLeft;  = Low Index Value			*/
/*     INT		   sRight; = High Index	Value			*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     Nothing								*/
/*									*/
/* --------------------------------------------------------------------	*/

static VOID SortAddresses(INTERNALADDRESSLIST *aial, INT sLeft,	INT sRight)

{
PFNINTADD	    pfn;	   /* Function Address			*/
INTERNALADDRESSLIST ial;	   /* Internal Address List Entry	*/
register INT i;			   /* Low Index	Counter			*/
register INT n;			   /* High Index Counter		*/

		       /* Determine target pointer and retrieve	string	*/
		       /* address					*/

pfn = aial[((i = sLeft)	+ (n = sRight))	/ 2].pfn;

do
   {
   while ( ((PVOID)aial[i].pfn < (PVOID)pfn) &&	(i < sRight) )
       ++i;
   while ( ((PVOID)aial[n].pfn > (PVOID)pfn) &&	(n > sLeft) )
       --n;

   if (	i <= n )
       {
       ial = aial[i];
       aial[i++] = aial[n];
       aial[n--] = ial;
       }
   } while ( i <= n );

if ( sLeft < n )
   SortAddresses(aial, sLeft, n);

if ( i < sRight	)
   SortAddresses(aial, i, sRight);
}
#pragma	subtitle("   Exception Handler - Exception Handler Routine")
#pragma	page( )

/* --- fLookupAddress ---------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used lookup the	locate the area	where the	*/
/*     acception occurred when the stack is backtraced.			*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     PVOID   pvExceptAddress;	= Address to Check			*/
/*     PEXCEPT pex;		= Exception Information			*/
/*     BOOL    fStackTrace;	= Stack	Traced Flag			*/
/*     INT     cFunctions;	= Function Count			*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     fLookupAddress =	 TRUE :	Address	Located				*/
/*		      =	FALSE :	Address	Not Located			*/
/*									*/
/* --------------------------------------------------------------------	*/

static BOOL fLookupAddress(PVOID pvExceptAddress, PEXCEPT pex,
			   BOOL	fStackTrace, INT cFunctions)

{
register INT n;			   /* Loop Counters			*/

		       /* Check	to see if dynamic link library loaded	*/
		       /* in which case	check with the DLL to see if	*/
		       /* the exception	occurred within	it		*/

if ( pfnDllExceptionLookup )
   {
   pex->iIntAdd	= 0;
   pex->fStackTraced = fStackTrace;
   if (	pfnDllExceptionLookup(pvExceptAddress, pex->szComponent, pex->szModule,	pex->szFunction,
			      &pex->pfnStart, &pex->pfnEnd) )
      return(TRUE);
   }
		       /* Exception didn't occur within a DLL, check    */
		       /* the function address array for the exception	*/
		       /* address					*/

for ( n	= 0; n < cFunctions; n++ )
   if (	(pvExceptAddress > (PVOID)pial[n].pfn) &&
	(pvExceptAddress < (PVOID)pial[n + 1].pfn) )
       {
		       /* Exception address within the application	*/
		       /* address space, save the necessary information	*/
		       /* before returning				*/

       pex->fStackTraced = fStackTrace;
       memcpy(pex->szComponent,	"Except.Exe", 11);
       strcpy(pex->szModule,	aintadd[pex->iIntAdd = piModules[n]]->pszModule);
       strcpy(pex->szFunction,	pial[n].pszFunction);
       pex->pfnStart = (PVOID)pial[n].pfn;
       pex->pfnEnd   = (PVOID)pial[n + 1].pfn;
       return(TRUE);
       }
return(FALSE);
}
#pragma	subtitle("   Exception Handler - Exception Handler Routine")
#pragma	page( )

/* --- ExceptionHandler	-------------------------------- [ Public ] ---	*/
/*									*/
/*     This function is	used process exceptions	under 2.x and to,	*/
/*     depending on the	exception, terminate the application after	*/
/*     saving relevant information to a	trap file.			*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     PEXCEPTIONREPORTRECORD	    pxcptrepr; = Report	Record		*/
/*     PEXCEPTIONREGISTRATIONRECORD pxcptregr; = Registration Record	*/
/*     PCONTEXTRECORD		    pcr;       = Context Record		*/
/*     PVOID			    sysinfo;   = System	Reserved	*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     ExceptionHandler	= Exception Return Status			*/
/*									*/
/* --------------------------------------------------------------------	*/

APIRET APIENTRY	ExceptionHandler(PEXCEPTIONREPORTRECORD	pxcptrepr,
				 PEXCEPTIONREGISTRATIONRECORD pxcptregr,
				 PCONTEXTRECORD	pcr, PVOID sysinfo)

{
DATETIME   dt;			   /* Date Time	Holder			*/
EXCEPT	   ex;			   /* Exception	Info			*/
EXCEPT	   exTrace;		   /* Exception	Info			*/
EXCEPTINFO exi;			   /* Exception	Information		*/
HFILE	   hf;			   /* Trap File	Handle			*/
PPIB	   ppib;		   /* Process Information Block	Pointer	*/
PSZ	   pszBuffer;		   /* Scratch Buffer			*/
PSZ	   pszXCP;		   /* XCP Filename Pointer		*/
PTIB	   ptib;		   /* Thread Information Block Pointer	*/
PULONG	   pulEBP;		   /* BP Stack Frame			*/
ULONG	   cb;			   /* Bytes Written			*/
ULONG	   ulAction;		   /* Action				*/
register INT i,	n, k;		   /* Loop Counter			*/

if ( EH_EXIT_UNWIND & pxcptrepr->fHandlerFlags )
   return(XCPT_CONTINUE_SEARCH);

if ( EH_UNWINDING & pxcptrepr->fHandlerFlags )
   return(XCPT_CONTINUE_SEARCH);

if ( EH_NESTED_CALL & pxcptrepr->fHandlerFlags )
   return(XCPT_CONTINUE_SEARCH);

		       /* Only handle access violation and divide by	*/
		       /* zero exceptions				*/

if ( (pxcptrepr->ExceptionNum == XCPT_ACCESS_VIOLATION)	||
     (pxcptrepr->ExceptionNum == XCPT_INTEGER_DIVIDE_BY_ZERO) )
   {
		       /* Allocate space for the formatting buffer	*/

   DosAllocMem((PPVOID)(PVOID)&pszBuffer, 4096UL,
	       PAG_READ	| PAG_WRITE | PAG_COMMIT);
   memset(&ex, 0, sizeof(EXCEPT));

		       /* Open the logging file				*/

   DosOpen(memcpy(pszBuffer, pszXCP = "Except.Log", 11), &hf, &ulAction, 0UL, FILE_NORMAL,
	   OPEN_ACTION_OPEN_IF_EXISTS |	OPEN_ACTION_CREATE_IF_NEW,
	   OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYWRITE, NULL);

		       /* Set the file pointer to the end of the	*/
		       /* logging file					*/

   DosSetFilePtr(hf, 0L, FILE_END, &cb);

		       /* Write	out the	start of the exception dump	*/

   DosWrite(hf,	(PVOID)pszBuffer,
	    (ULONG)sprintf(pszBuffer, "Except.Log :\r\nAccess violation occurred at CS:EIP = 0x%04X:%08X\r\n",
			   pcr->ctx_SegCs, pxcptrepr->ExceptionAddress), &cb);

		       /* Write	out the	type of	exception		*/

   if (	pxcptrepr->ExceptionNum	== XCPT_INTEGER_DIVIDE_BY_ZERO )
       DosWrite(hf, (PVOID)"Integer divide by zero\r\n", 24UL, &cb);
   else
       if ( pxcptrepr->ExceptionInfo[0]	& XCPT_READ_ACCESS )
	   DosWrite(hf,	(PVOID)pszBuffer,
		    (ULONG)sprintf(pszBuffer, "Invalid Read Access occurred at 0x%04X:%08X",
				   pcr->ctx_SegDs, pxcptrepr->ExceptionInfo[1]), &cb);
       else
	   if (	pxcptrepr->ExceptionInfo[0] & XCPT_WRITE_ACCESS	)
	       DosWrite(hf, (PVOID)pszBuffer,
			(ULONG)sprintf(pszBuffer, "Invalid Write Access occurred at 0x%04X:%08X",
				       pcr->ctx_SegDs, pxcptrepr->ExceptionInfo[1]), &cb);
	   else
	       if ( pxcptrepr->ExceptionInfo[0]	& XCPT_SPACE_ACCESS )
		   DosWrite(hf,	(PVOID)pszBuffer,
			    (ULONG)sprintf(pszBuffer, "Invalid Space Access occurred with 0x%04X",
					   pxcptrepr->ExceptionInfo[1]), &cb);
	       else
		   if (	pxcptrepr->ExceptionInfo[0] & XCPT_LIMIT_ACCESS	)
		       DosWrite(hf, (PVOID)pszBuffer,
				(ULONG)sprintf(pszBuffer, "Invalid Limit Access occurred"), &cb);
		   else
		       if ( pxcptrepr->ExceptionInfo[0]	== XCPT_UNKNOWN_ACCESS )
			   DosWrite(hf,	(PVOID)pszBuffer,
				    (ULONG)sprintf(pszBuffer, "Invalid Unknown occurred at 0x%04X:%08X\r\n",
						   pcr->ctx_SegDs, pxcptrepr->ExceptionInfo[1]), &cb);

		       /* Get the current date and time	along with the	*/
		       /* thread information				*/
   DosGetDateTime(&dt);
   DosGetInfoBlocks(&ptib, &ppib);

		       /* Write	out the	register information along with	*/
		       /* the current date, time and thread/process	*/
		       /* information					*/

   DosWrite(hf,	(PVOID)pszBuffer,
	    (ULONG)sprintf(pszBuffer, pszRegisters,
			   pcr->ctx_RegEax, pcr->ctx_RegEbx, pcr->ctx_RegEcx, pcr->ctx_RegEdx,
			   pcr->ctx_RegEbp, pcr->ctx_RegEdi, pcr->ctx_RegEsi, pcr->ctx_RegEsp,
			   pcr->ctx_SegCs, pcr->ctx_SegDs, pcr->ctx_SegEs, pcr->ctx_SegFs,
			   pcr->ctx_SegGs, pcr->ctx_SegSs,
			   apszMonth[dt.month -	1], dt.day, dt.year,
			   dt.hours, dt.minutes, dt.seconds, dt.hundredths,
			   ex.pid = ppib->pib_ulpid, ex.tid = ptib->tib_ptib2->tib2_ultid), &cb);

		       /* Walk the list	of module addresses to find	*/
		       /* out total number of functions	for the		*/
		       /* final	function address array			*/

   for ( i = k = 0; i <	CMODULES; i++ )
       {
       n = 0;
       while ( aintadd[i]->aial[n].pfn )
	   {
	   ++n;
	   ++k;
	   }
       }
		       /* Allocate memory for the master address list	*/
		       /* array	along with memory for the module index	*/
		       /* array						*/

   DosAllocMem((PPVOID)(PVOID)&pial, (ULONG)(sizeof(INTERNALADDRESSLIST) * k),
	       PAG_READ	| PAG_WRITE | PAG_COMMIT);

   DosAllocMem((PPVOID)(PVOID)&piModules, (ULONG)(sizeof(INT) *	k),
	       PAG_READ	| PAG_WRITE | PAG_COMMIT);

		       /* Re-walk the module address lists transferring	*/
		       /* the functions	to the master array.  Also save	*/
		       /* the index to the module.			*/

   for ( i = k = 0; i <	CMODULES; i++ )
       {
       n = 0;
       while ( aintadd[i]->aial[n].pfn )
	   {
	   piModules[k]	= i;
	   pial[k++] = aintadd[i]->aial[n++];
	   }
       }
		       /* Sort the list	in ascending order		*/
   if (	k )
       SortAddresses(pial, 0, k	- 1);

		       /* Try looking up the exception address		*/

   if (	fLookupAddress((PVOID)pxcptrepr->ExceptionAddress, &ex,	FALSE, k) )
       {
		       /* Have found the exception location, write out	*/
		       /* the names of the module and function where	*/
		       /* the exception	occurred			*/

       DosWrite(hf, (PVOID)pszBuffer,
		(ULONG)sprintf(pszBuffer, "Component: %s Module: %s Function: %s\r\nFunction start: 0x%08X\r\nFunction end:   0x%08X\r\n\r\n",
			       ex.szComponent, ex.szModule, ex.szFunction, ex.pfnStart,	ex.pfnEnd), &cb);

		       /* Try walking the stack	to give	a full chain	*/
		       /* of function calls since this may actually be	*/
		       /* of use					*/
       cb = 1UL;
       if ( !DosQueryMem((PVOID)(pulEBP	= (PULONG)pcr->ctx_RegEbp), &cb, &cb) )
	   while ( pulEBP && ((PVOID)*(pulEBP +	1) > (PVOID)(PFNINTADD)main) )
	       if ( (PVOID)*pulEBP > ptib->tib_pstacklimit )
		   break;
	       else
		   {
		   if (	fLookupAddress((PVOID)(*(pulEBP	+ 1)), &exTrace, TRUE, k) )
		       DosWrite(hf, (PVOID)pszBuffer,
				(ULONG)sprintf(pszBuffer, "Tracing back through stack\r\nModule: %s Function: %s\r\nFunction start: 0x%08X\r\nFunction end:   0x%08X\r\n\r\n",
					       exTrace.szModule, exTrace.szFunction, exTrace.pfnStart, exTrace.pfnEnd),	&cb);
		   pulEBP = (PULONG)*pulEBP;
		   }
       }
   else
		       /* Could	not find the address within any	program	*/
		       /* or DLL address space,	now try	walking	the	*/
		       /* stack	back to	the address space to at	least	*/
		       /* try to give some information about where the	*/
		       /* mess started					*/

       if ( (PVOID)pxcptrepr->ExceptionAddress > (PVOID)(PFNINTADD)XEndAddress )
	   {
	   cb =	1UL;
	   if (	!DosQueryMem((PVOID)(pulEBP = (PULONG)pcr->ctx_RegEbp),	&cb, &cb) )
	       {
	       while ( (PVOID)*(pulEBP + 1) > (PVOID)(PFNINTADD)XEndAddress )
		   if (	(PVOID)*pulEBP > ptib->tib_pstacklimit )
		       break;
		   else
		       pulEBP =	(PULONG)*pulEBP;
	       if ( fLookupAddress((PVOID)(*(pulEBP + 1)), &ex,	TRUE, k) )
		   DosWrite(hf,	(PVOID)pszBuffer,
			    (ULONG)sprintf(pszBuffer, "Back traced through stack\r\nModule: %s Function: %s\r\nFunction start: 0x%08X\r\nFunction end:   0x%08X\r\n\r\n",
					   ex.szModule,	ex.szFunction, ex.pfnStart, ex.pfnEnd),	&cb);
	       ex.fStackTraced = TRUE;
	       }
	   }
		       /* Write	out the	addresses for the bottom and	*/
		       /* top of the program address space		*/

   DosWrite(hf,	(PVOID)pszBuffer,
	    (ULONG)sprintf(pszBuffer, pszAddresses, &main, &ExceptionHandler), &cb);
   DosFreeMem((PVOID)pszBuffer);
   DosClose(hf);
		       /* Release the array memory			*/
   DosFreeMem((PVOID)pial);
   DosFreeMem((PVOID)piModules);

		       /* Initialize the dialogue information and	*/
		       /* display the dialogue				*/

   ex.pxcptrepr	= pxcptrepr;
   ex.pcr	= pcr;

   exi.pex	= &ex;
   exi.pszTitle	= "Exception Example FATAL ERROR";
   exi.pszXCP	= pszXCP;
   exi.fFatal	= TRUE;

   WinDlgBox(HWND_DESKTOP, HWND_DESKTOP, (PFNWP)XceptionDlgProc,
	      (HMODULE)NULL, DLG_EXCEPTION, (PVOID)&exi);

   DosExit(EXIT_PROCESS, 128UL);
   }

return(XCPT_CONTINUE_SEARCH);
}
#pragma	subtitle("   Exception Support - Exception Dialogue Box Function")
#pragma	page( )

/* --- pszHexShort ------------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	process	the Directory Rename dialogue	*/
/*     box.								*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     PSZ   pszBuffer;	= Buffer					*/
/*     ULONG ul;	= Numeric Value					*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     pszHex =	pszBuffer Address					*/
/*									*/
/* --------------------------------------------------------------------	*/

static PSZ pszHexShort(ULONG ul, PSZ pszBuffer)

{
CHAR szNumber[16];		   /* Segment Address Holder		*/
register INT i,	n;		   /* Loop Counter			*/

memcpy(pszBuffer, "0x0000", 7);

if ( ul	)
   for ( i = 5,	n = (INT)strlen(_ultoa(ul, szNumber, 16)) - 1; n >= 0; i--, n--	)
       pszBuffer[i] = szNumber[n];

return(pszBuffer);
}
#pragma	subtitle("   Exception Support - Exception Dialogue Box Function")
#pragma	page( )

/* --- pszHex -----------------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	process	the Directory Rename dialogue	*/
/*     box.								*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     PSZ   pszBuffer;	= Buffer					*/
/*     ULONG ul;	= Numeric Value					*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     pszHex =	pszBuffer Address					*/
/*									*/
/* --------------------------------------------------------------------	*/

static PSZ pszHex(ULONG	ul, PSZ	pszBuffer)

{
CHAR szNumber[16];		   /* Segment Address Holder		*/
register INT i,	n;		   /* Loop Counter			*/

memcpy(pszBuffer, "0x00000000",	11);

if ( ul	)
   for ( i = 9,	n = (INT)strlen(_ultoa(ul, szNumber, 16)) - 1; n >= 0; i--, n--	)
       pszBuffer[i] = szNumber[n];

return(pszBuffer);
}
#pragma	subtitle("   Exception Support - Exception Dialogue Box Function")
#pragma	page( )

/* --- pszFormAddress ---------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	process	the Directory Rename dialogue	*/
/*     box.								*/
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
/*     ExceptionDlgProc	= Message Handling Result			*/
/*									*/
/* --------------------------------------------------------------------	*/

static PSZ pszFormAddress(PSZ pszBuffer, ULONG ulSeg, ULONG ulBase)

{
CHAR szSegment[16];		   /* Segment Address Holder		*/
CHAR szBase[32];		   /* Base Address Holder		*/

return(strcat(strcat(strcpy(pszBuffer, pszHexShort(ulSeg, szSegment)),
	      ":"),
       pszHex(ulBase, szBase)));
}
#pragma	subtitle("   Exception Support - Exception Dialogue Box Function")
#pragma	page( )

/* --- XceptionDlgProc --------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	process	the Directory Rename dialogue	*/
/*     box.								*/
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
/*     XceptionDlgProc = Message Handling Result			*/
/*									*/
/* --------------------------------------------------------------------	*/

MRESULT	EXPENTRY XceptionDlgProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{
CHAR	    szBuffer[CCHMAXPATH];  /* File Name	Holder			*/
CHAR	    szAddress[32];	   /* File Name	Holder			*/
HMODULE	    hmodSnd;		   /* Sound DLL	Module Handle		*/
PEXCEPTINFO pexi;		   /* Directory	Entry Pointer		*/
SWP	    swp;		   /* Screen Window Position Holder	*/

switch ( msg )
   {
   case WM_CONTROL :
	switch ( SHORT2FROMMP(mp1) )
	    {
			/* Process control selections			*/
	    }
	break;
		       /* Perform dialog initialization			*/
   case	WM_INITDLG :
       WinSetWindowULong(hWnd, QWL_USER, (ULONG)(pexi =	(PEXCEPTINFO)PVOIDFROMMP(mp2)));
       WinSetWindowText(hWnd, pexi->pszTitle);

       strcat(memcpy(szBuffer, "Further detail contained in ", 29), pexi->pszXCP);
       WinSetDlgItemText(hWnd, IT_DETAIL,
			 strcat(szBuffer, " within sub-directory."));
       if ( pexi->fFatal )
	   WinSetDlgItemText(hWnd, IT_STATUS, "Fatal error: NON-RECOVERABLE (application terminating)");
       else
	   {
	   WinSetDlgItemText(hWnd, IT_STATUS, "Recoverable error: last operation non-completed, proceeding to next");
	   WinSetDlgItemText(hWnd, DID_OK, "Resume");
	   }
		       /* Place	file entry selected in first edit field	*/

       WinSetDlgItemText(hWnd, IT_CSEIP,
			 strcat(memcpy(szBuffer,
				       "Access violation occurred at CS:EIP = ", 39),
				pszFormAddress(szAddress, pexi->pex->pcr->ctx_SegCs,
					       (ULONG)pexi->pex->pxcptrepr->ExceptionAddress)));

       if ( pexi->pex->pxcptrepr->ExceptionNum == XCPT_INTEGER_DIVIDE_BY_ZERO )
	   memcpy(szBuffer, "Integer divide by zero.", 24);
       else
	   if (	pexi->pex->pxcptrepr->ExceptionInfo[0] & XCPT_READ_ACCESS )
	       strcat(memcpy(szBuffer,
			     "Invalid Read Access occurred at ", 33),
		      pszFormAddress(szAddress,	pexi->pex->pcr->ctx_SegDs,
				     pexi->pex->pxcptrepr->ExceptionInfo[1]));
	   else
	       if ( pexi->pex->pxcptrepr->ExceptionInfo[0] & XCPT_WRITE_ACCESS )
		   strcat(memcpy(szBuffer,
				 "Invalid Write Access occurred at ", 34),
			  pszFormAddress(szAddress, pexi->pex->pcr->ctx_SegDs,
					 pexi->pex->pxcptrepr->ExceptionInfo[1]));
	       else
		   if (	pexi->pex->pxcptrepr->ExceptionInfo[0] & XCPT_SPACE_ACCESS )
		       strcat(memcpy(szBuffer,
				     "Invalid Space Access occurred with ", 36),
			      _ultoa(pexi->pex->pxcptrepr->ExceptionInfo[1], szAddress,	16));
		   else
		       if ( pexi->pex->pxcptrepr->ExceptionInfo[0] & XCPT_LIMIT_ACCESS )
			   memcpy(szBuffer, "Invalid Limit Access occurred", 30);
		       else
			   strcat(memcpy(szBuffer,
					 "Invalid Unknown occurred at ", 29),
				  pszFormAddress(szAddress, pexi->pex->pcr->ctx_SegDs,
						 pexi->pex->pxcptrepr->ExceptionInfo[1]));
       WinSetDlgItemText(hWnd, IT_EXCEPTTYPE, szBuffer);

       if ( pexi->pex->iIntAdd != -1 )
	   {
	   if (	pexi->pex->fStackTraced	)
	       memcpy(szBuffer,	"Stack backtraced\nComponent: ", 29);
	   else
	       memcpy(szBuffer,	"Component: ", 12);

	   WinSetDlgItemText(hWnd, IT_DEBUGINFO,
			     strcat(strcat(strcat(strcat(strcat(szBuffer, pexi->pex->szComponent),
							 "\nModule:   "),
						  pexi->pex->szModule),
					   "\nFunction: "),
				    pexi->pex->szFunction));
	   }

       WinSetDlgItemText(hWnd, IT_PID, _ultoa(pexi->pex->pid, szBuffer,	10));
       WinSetDlgItemText(hWnd, IT_TID, _ultoa(pexi->pex->tid, szBuffer,	10));

       WinSetDlgItemText(hWnd, IT_PFNSTART, pszHex((ULONG)pexi->pex->pfnStart, szBuffer));
       WinSetDlgItemText(hWnd, IT_PFNEND,   pszHex((ULONG)pexi->pex->pfnEnd,   szBuffer));

       WinSetDlgItemText(hWnd, IT_EAX, pszHex(pexi->pex->pcr->ctx_RegEax, szBuffer));
       WinSetDlgItemText(hWnd, IT_EBX, pszHex(pexi->pex->pcr->ctx_RegEbx, szBuffer));
       WinSetDlgItemText(hWnd, IT_ECX, pszHex(pexi->pex->pcr->ctx_RegEcx, szBuffer));
       WinSetDlgItemText(hWnd, IT_EDX, pszHex(pexi->pex->pcr->ctx_RegEdx, szBuffer));

       WinSetDlgItemText(hWnd, IT_EBP, pszHex(pexi->pex->pcr->ctx_RegEbp, szBuffer));
       WinSetDlgItemText(hWnd, IT_ESP, pszHex(pexi->pex->pcr->ctx_RegEsp, szBuffer));

       WinSetDlgItemText(hWnd, IT_EDI, pszHex(pexi->pex->pcr->ctx_RegEdi, szBuffer));
       WinSetDlgItemText(hWnd, IT_ESI, pszHex(pexi->pex->pcr->ctx_RegEsi, szBuffer));

       WinSetDlgItemText(hWnd, IT_CS, pszHexShort(pexi->pex->pcr->ctx_SegCs, szBuffer));
       WinSetDlgItemText(hWnd, IT_SS, pszHexShort(pexi->pex->pcr->ctx_SegSs, szBuffer));
       WinSetDlgItemText(hWnd, IT_DS, pszHexShort(pexi->pex->pcr->ctx_SegDs, szBuffer));
       WinSetDlgItemText(hWnd, IT_ES, pszHexShort(pexi->pex->pcr->ctx_SegEs, szBuffer));
       WinSetDlgItemText(hWnd, IT_FS, pszHexShort(pexi->pex->pcr->ctx_SegFs, szBuffer));
       WinSetDlgItemText(hWnd, IT_GS, pszHexShort(pexi->pex->pcr->ctx_SegGs, szBuffer));

       WinSetDlgItemText(hWnd, IT_FLAGS, pszHex(pexi->pex->pcr->ctx_EFlags, szBuffer));

       WinPostMsg(hWnd,	WM_PLAYSOUND, 0L, 0L);

		       /* Centre dialog	on the screen			*/

		       /* Centre dialog	on the screen			*/

       WinQueryWindowPos(hWnd, (PSWP)&swp);
       WinSetWindowPos(hWnd, HWND_TOP,
		       (WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN) - swp.cx) /	2L,
		       (WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN) - swp.cy) /	2L,
		       0L, 0L, SWP_MOVE);
       break;

   case	WM_PLAYSOUND :
       if ( !DosLoadModule(szBuffer, CCHMAXPATHCOMP, "PDSSnd", &hmodSnd) )
	   {
	   VOID	(* EXPENTRY pfnPlaySound)(HWND hWnd, PSZ pszWaveFile);

	   pexi	= (PEXCEPTINFO)WinQueryWindowULong(hWnd, QWL_USER);

	   if (	!DosQueryProcAddr(hmodSnd, ORD_PLAYSOUND, NULL,
				  (PFN *)(PVOID)&pfnPlaySound) )
	       pfnPlaySound(hWnd, "flush.wav");
	   else
	       WinAlarm(HWND_DESKTOP, WA_ERROR);
	   DosFreeModule(hmodSnd);
	   }
       else
	   WinAlarm(HWND_DESKTOP, WA_ERROR);
       break;
		       /* Process push button selections		*/
   case	WM_COMMAND :
       switch (	SHORT1FROMMP(mp1) )
	   {
		       /* OK button selected, get text from edit fields	*/
		       /* and rename the file				*/
	   case	DID_OK :
	       WinDismissDlg(hWnd, FALSE);
	       break;
	   }
       break;
		       /* Close	received, exit dialog			*/
   case	WM_CLOSE :
       WinDismissDlg(hWnd, FALSE);
       break;
		       /* Pass through unhandled messages		*/
   default :
       return(WinDefDlgProc(hWnd, msg, mp1, mp2));
   }
return(0L);
}
