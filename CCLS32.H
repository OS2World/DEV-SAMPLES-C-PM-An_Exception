
/* ccls32.h	   Created:    1990-10-30  Revised:    1993-11-30	*/

/* Prominare Designer Custom Control Library Specification (CCLS32)	*/
/* Version 2.1c								*/
/* Definitions Header							*/

/* Consult Section 2 within the	Prominare Development System		*/
/* Programming Guide for complete description of Custom	Control		*/
/* Library Specification						*/

/* Changes are denoted by a 2.1	 in comments beside the	changes		*/
/* Changes are denoted by a 2.1c in comments beside the	changes		*/

/* Copyright ¸ 1989-1994  Prominare Inc.  All Rights Reserved.		*/

/* --------------------------------------------------------------------	*/

/* Function Prototypes (16-bit definition)				*/
/* -------------------							*/
/*									*/
/*     Control Initialization:						*/
/*									*/
/*	   BOOL	EXPENTRY XxxxInit(HAB hAB, HMODULE hmodDLL);		*/
/*									*/
/*     Styles Dialog Procedures:					*/
/*									*/
/*	   MRESULT EXPENTRY XxxxDlgProc(HWND hWnd, ULONG msg,		*/
/*					MPARAM mp1, MPARAM mp2);	*/
/*	   MRESULT EXPENTRY XxxxAnalystDlgProc(HWND hWnd, ULONG	msg,	*/
/*					       MPARAM mp1, MPARAM mp2);	*/
/*									*/
/*     Window Procedure:						*/
/*									*/
/*	   MRESULT EXPENTRY XxxxWndProc(HWND hWnd, ULONG msg,		*/
/*					MPARAM mp1, MPARAM mp2);	*/
/*									*/
/*     Control Information Procedure:					*/
/*									*/
/*	   BOOL	EXPENTRY XxxxQueryInfo(PUSERINFO pUserInfo);		*/
/*									*/
/* Function Prototypes (32-bit definition)				*/ /* 2.1c */
/* -------------------							*/ /* 2.1c */
/*									*/ /* 2.1c */
/*     Control Initialization:						*/ /* 2.1c */
/*									*/ /* 2.1c */
/*	   BOOL	EXPENTRY XxxxRegister(HAB hAB);				*/ /* 2.1c */
/*									*/ /* 2.1c */
/*     Styles Dialog Procedures:					*/ /* 2.1c */
/*									*/ /* 2.1c */
/*	   MRESULT EXPENTRY XxxxStyles(HWND hWnd, ULONG	msg,		*/ /* 2.1c */
/*				       MPARAM mp1, MPARAM mp2);		*/ /* 2.1c */
/*	   MRESULT EXPENTRY XxxxAnalystStyles(HWND hWnd, ULONG msg,	*/ /* 2.1c */
/*					      MPARAM mp1, MPARAM mp2);	*/ /* 2.1c */
/*									*/ /* 2.1c */
/*     Window Procedure:						*/ /* 2.1c */
/*									*/ /* 2.1c */
/*	   MRESULT EXPENTRY XxxxWndProc(HWND hWnd, ULONG msg,		*/ /* 2.1c */
/*					MPARAM mp1, MPARAM mp2);	*/ /* 2.1c */
/*									*/ /* 2.1c */
/*     Control Information Procedure:					*/ /* 2.1c */
/*									*/ /* 2.1c */
/*	   BOOL	EXPENTRY XxxxQuery(PUSERINFO32 pUserInfo);		*/ /* 2.1c */

/* --- Constant	Definitions -------------------------------------------	*/

#define	USERTYPES	   32	   /* Maximum Number of	User Types	*/
#define	CTYPES		    1	   /* Maximum Number of	User Types	*/ /* 2.1c */
#define	CCHCLASS	   32	   /* Maximum Classname	Length		*/
#define	CCHNAME		   32	   /* Maximum Name Length		*/
#define	CCHAUTHOR	   64	   /* Maximum Author Name Length	*/
#define	CCHDESC		   32	   /* Maximum Type Description Length	*/
#define	CCHID		   32	   /* Maximum ID Symbol	Length		*/
#define	CCHTEXT		  128	   /* Maximum Control Text Length	*/
#define	CCHTEXTMAX	  512	   /* Maximum Control Text Length	*/ /* 2.1c */

#define	UTYPE_PRIVATE  0x0002	   /* Type:  Private			*/
#define	UTYPE_PUBLIC   0x0004	   /* Type:  Public			*/

#define	USER_RESERVED	   16	   /* Control Reserved Memory Size	*/
#define	USER_CWINDOWWORDS   8UL	   /* Control Reserved Memory Size	*/ /* 2.1c */

#define	QUCWP_STYLE (QWL_USER +	 4)/* Pointer to Styles	Flag		*/
#define	QUCWP_HEAP  (QWL_USER +	 8)/* Pointer to Heap Handle		*/
#define	QUCWP_WNDP  (QWL_USER +	12)/* Pointer to Heap Pointer		*/

#define	QWW_USER  (QWL_USER + 0UL) /* Pointer to User Data		*/ /* 2.1c */
#define	QWW_CDATA (QWL_USER + 4UL) /* Pointer to Private Data Pointer	*/ /* 2.1c */

#define	SAACHK_MNEMONIC	   0	   /* SAA Check:  Mnemonic		*/
#define	SAACHK_CAPS	   1	   /* SAA Check:  Capitalization	*/
#define	SAACHK_ELLIPSIS	   2	   /* SAA Check:  Ellipsis		*/

#define	STYLETYPE_BITFLAGS 0x0001  /* Style Type:  Bit Flags		*/
#define	STYLETYPE_SEQUENCE 0x0002  /* Style Type:  Sequential		*/

#define	CCLSOPT_NONE	  0x00000000UL					   /* 2.1 */
#define	CCLSOPT_REFRESH	  0x00000001UL					   /* 2.1 */
#define	CCLSOPT_VARICDATA 0x00000002UL					   /* 2.1 */
#define	CCLSOPT_STYLECHG  0x00000004UL					   /* 2.1c */
#define	CCLSOPT_TABABLE	  0x00000008UL					   /* 2.1c */
#define	CCLSOPT_HELP	  0x00000010UL					   /* 2.1c */

/************************************************************************/
/************************************************************************/
/*									*/
/*     CCLS 32-Bit Structure Definitions				*/
/*									*/
/************************************************************************/
/************************************************************************/

/* --- User Control Styles Structure ----------------------------------	*/ /* 2.1c */
									   /* 2.1c */
typedef	struct _STYLE32		   /* st32 */				   /* 2.1c */
   {				   /* Size:    8 bytes			*/ /* 2.1c */
   ULONG    flStyleMask;	   /* Style Flag Mask			*/ /* 2.1c */
   ULONG    idStyle;		   /* Resource String ID		*/ /* 2.1c */
   } STYLE32 ;								   /* 2.1c */
									   /* 2.1c */
/* --- User Control Type Structure ------------------------------------	*/ /* 2.1c */
									   /* 2.1c */
typedef	struct _USERTYPE32	   /* ut32 */				   /* 2.1c */
   {				   /* Size:  348 bytes			*/ /* 2.1c */
   LONG	    cx;			   /* Suggested	Width of Control	*/ /* 2.1c */
   LONG	    cy;			   /* Suggested	Height of Control	*/ /* 2.1c */
   ULONG    flStyle;		   /* Initial Style Flags		*/ /* 2.1c */
   ULONG    flOptions;		   /* Options Flag			*/ /* 2.1c */
   ULONG    cMaxText;		   /* Maximum Text Required		*/ /* 2.1c */
   ULONG    idDlg;		   /* Dialog ID				*/ /* 2.1c */
   ULONG    idDlgAnalyst;	   /* Dialog ID	(Analyst Version)	*/ /* 2.1c */
   ULONG    flStyleType;	   /* Style Type			*/ /* 2.1c */
   ULONG    cCtlData;		   /* Control Data Count		*/ /* 2.1c */
   ULONG    ulType;		   /* Control Type			*/ /* 2.1c */
   ULONG    cMasks;		   /* Style Masks Count			*/ /* 2.1c */
   CHAR	    szDescription[CCHDESC];/* Control Name			*/ /* 2.1c */
   STYLE32  stMasks[32];	   /* Style Masks Array			*/ /* 2.1c */
   ULONG    aulReserved[4];	   /* Reserved				*/ /* 2.1c */
   } USERTYPE32	;							   /* 2.1c */
									   /* 2.1c */
/* --- User Control Information	Structure -----------------------------	*/ /* 2.1c */
									   /* 2.1c */
typedef	struct _USERINFO32	   /* ui32 */				   /* 2.1c */
   {				   /* Size:  512 bytes			*/ /* 2.1c */
   ULONG      ulMajor;		   /* Control Version Number:  Major	*/ /* 2.1c */
   ULONG      ulMinor;		   /* Control Version Number:  Minor	*/ /* 2.1c */
   CHAR	      szAuthor[CCHAUTHOR]; /* Control Author			*/ /* 2.1c */
   CHAR	      szClassname[CCHCLASS];   /* Classname			*/ /* 2.1c */
   CHAR	      szName[CCHNAME];	   /* Library Name			*/ /* 2.1c */
   ULONG      aulReserved[6];	   /* Reserved				*/ /* 2.1c */
   ULONG      cTypes;		   /* Number of	Control	Types Supported	*/ /* 2.1c */
   USERTYPE32 utDefined[CTYPES];   /* Define User Types	Array		*/ /* 2.1c */
   } USERINFO32	;							   /* 2.1c */
									   /* 2.1c */
typedef	USERINFO32 *PUSERINFO32;					   /* 2.1c */
									   /* 2.1c */
/* --- User Control Style Structure -----------------------------------	*/ /* 2.1c */
									   /* 2.1c */
typedef	struct _USERSTYLE32	   /* ust32 */				   /* 2.1c */
   {				   /* Size:  112 bytes			*/ /* 2.1c */
   PFN	    pfnLookupSymbol;	   /* Lookup Symbol Function Address	*/ /* 2.1c */
   PFN	    pfnValidateSymbol;	   /* Validate Symbol Function Address	*/ /* 2.1c */
   PFN	    pfnGetPresParams;	   /* Pres Params Function Address	*/ /* 2.1c */
   PFN	    pfnSAACheck;	   /* SAA Compliance Function Address	*/ /* 2.1c */
   PFN	    pfnRealloc;		   /* Reallocation Function Address	*/ /* 2.1c */
   ULONG    flStyle;		   /* Style				*/ /* 2.1c */
   ULONG    id;			   /* ID Value				*/ /* 2.1c */
   CHAR	    szid[CCHID];	   /* ID Symbol				*/ /* 2.1c */
   PSZ	    pszText;		   /* Text Pointer			*/ /* 2.1c */
   ULONG    cText;		   /* Text Count (Including NULL)	*/ /* 2.1c */
   ULONG    aulReserved[9];	   /* Reserved				*/ /* 2.1c */
   PBYTE    pbCtlData;		   /* Variable Control Data Pointer	*/ /* 2.1c */
   ULONG    cbCtlData;		   /* Control Data Size			*/ /* 2.1c */
   BYTE	    abCtlData[1];	   /* Control Data			*/ /* 2.1c */
   } USERSTYLE32 ;							   /* 2.1c */
									   /* 2.1c */
typedef	USERSTYLE32 *PUSERSTYLE32;					   /* 2.1c */

#define	IDBM_SETIDSYMBOLVALUE	    0x019bUL

/* ====================================================================	*/
/* === CCLS 16-Bit Structure Definitions ==============================	*/
/* ====================================================================	*/

#pragma	pack(1)

/* --- User Control Styles Structure ----------------------------------	*/

typedef	struct _STYLE		   /* st */
   {
   ULONG    flStyleMask;	   /* Style Flag Mask			*/
   SHORT    idStyle;		   /* Resource String ID		*/
   } STYLE ;

/* --- User Control Type Structure ------------------------------------	*/

typedef	struct _USERTYPE	   /* ut */
   {
   SHORT    cx;			   /* Suggested	Width of Control	*/
   SHORT    cy;			   /* Suggested	Height of Control	*/
   ULONG    flStyle;		   /* Initial Style Flags		*/
   SHORT    idDlg;		   /* Dialog ID				*/
   CHAR	    szDescription[CCHDESC];/* Control Name			*/
   ULONG    aulReserved[2];	   /* Reserved				*/ /* 2.1 */
   ULONG    flOptions;		   /* Options Flag			*/ /* 2.1 */
   USHORT   cMaxText;		   /* Maximum Text Required		*/
   SHORT    idDlgAnalyst;	   /* Dialog ID	(Analyst Version)	*/
   USHORT   fsStyleType;	   /* Style Type			*/
   USHORT   usReserved;		   /* Reserved				*/
   SHORT    cCtlData;		   /* Control Data Count		*/
   USHORT   usType;		   /* Control Type			*/
   USHORT   cMasks;		   /* Style Masks Count			*/
   STYLE    stMasks[32];	   /* Style Masks Array			*/
   } USERTYPE ;

/* --- User Control Information	Structure -----------------------------	*/

typedef	struct _USERINFO	   /* ui */
   {
   BYTE	    bMajor;		   /* Control Version Number:  Major	*/
   BYTE	    bMinor;		   /* Control Version Number:  Minor	*/
   CHAR	    szAuthor[CCHAUTHOR];   /* Control Author			*/
   CHAR	    szClassname[CCHCLASS]; /* Classname				*/
   CHAR	    szName[CCHNAME];	   /* Library Name			*/
   ULONG    aulReserved[4];	   /* Reserved				*/
   USHORT   cTypes;		   /* Number of	Control	Types Supported	*/
   USERTYPE utDefined[USERTYPES];  /* Define User Types	Array		*/
   } USERINFO ;

typedef	USERINFO *PUSERINFO;

/* --- User Control Style Structure -----------------------------------	*/

typedef	struct _USERSTYLE	   /* ust */
   {
   PFN	    pfnLookupSymbol;	   /* Lookup Symbol Function Address	*/
   PFN	    pfnValidateSymbol;	   /* Validate Symbol Function Address	*/
   PFN	    pfnGetPresParams;	   /* Pres Params Function Address	*/
   PFN	    pfnSAACheck;	   /* SAA Compliance Function Address	*/
   PFN	    pfnRealloc;		   /* Reallocation Function Address	*/ /* 2.1 */
   ULONG    aulReserved1[3];	   /* Reserved				*/ /* 2.1 */
   ULONG    flStyle;		   /* Style				*/
   SHORT    id;			   /* ID Value				*/
   CHAR	    szid[CCHID];	   /* ID Symbol				*/
   PSZ	    pszText;		   /* Text Pointer			*/
   USHORT   cText;		   /* Text Count (Including NULL)	*/
   ULONG    aulReserved2[8];	   /* Reserved				*/ /* 2.1 */
   PBYTE    pbCtlData;		   /* Variable Control Data Pointer	*/ /* 2.1 */
   ULONG    cbCtlData;		   /* Control Data Size			*/ /* 2.1 */
   BYTE	    abCtlData[1];	   /* Control Data			*/
   } USERSTYLE ;

typedef	USERSTYLE *PUSERSTYLE;

#pragma	pack( )

/* --- Macro Helpers for Setting or Retrieving User Style Pointer ------ */

#define	PDATATODLG(hwndClient) ((WinSetWindowPtr(hwndClient, QWL_USER,\
	(PVOID)mp2)))

#define	PDATAFROMDLG(hwndClient) (((PUSERSTYLE)WinQueryWindowPtr(hwndClient,\
	QWL_USER)))

#define	PDATA32FROMDLG(hwndClient) (((PUSERSTYLE32)WinQueryWindowPtr(hwndClient,\
	QWL_USER)))

#ifdef __IBMC__

typedef	VOID  (* EXPENTRY PFNLOOKUPSYMBOL)(HWND, SHORT,	SHORT);
typedef	BOOL  (* EXPENTRY PFNVALIDATESYMBOL)(HWND, SHORT, SHORT);
typedef	VOID  (* EXPENTRY PFNGETPRESPARAMS)(HWND);
typedef	BOOL  (* EXPENTRY PFNSAACHECK)(HWND, SHORT, INT);
typedef	PVOID (* EXPENTRY PFNREALLOC)(PVOID, INT);

#else

typedef	VOID  (EXPENTRY	*PFNLOOKUPSYMBOL)(HWND,	SHORT, SHORT);
typedef	BOOL  (EXPENTRY	*PFNVALIDATESYMBOL)(HWND, SHORT, SHORT);
typedef	VOID  (EXPENTRY	*PFNGETPRESPARAMS)(HWND);
typedef	BOOL  (EXPENTRY	*PFNSAACHECK)(HWND, SHORT, INT);
typedef	PVOID (EXPENTRY	*PFNREALLOC)(PVOID, INT);

#endif
