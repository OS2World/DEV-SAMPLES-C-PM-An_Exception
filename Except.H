#define	WIN_EXCEPTIONEXAMPLE   1
#define	IDM_FILE	       256
#define	IDM_DIALOGUE1EXCEPTION 257
#define	IDM_DIALOGUE2EXCEPTION 258
#define	DLG_DIALOGUE1EXCEPTION 259
#define	DLG_DIALOGUE2EXCEPTION 260

/* --- Dialog Box Definitions -- Exceptions ---------------------------	*/

#define	DLG_EXCEPTION	    6000   /* Exception	Display	Dialogue	*/
#define	IT_CSEIP	    6001   /* CS:EIP Text Field			*/
#define	IT_EXCEPTTYPE	    6002   /* Exception	Type Text Field		*/
#define	IT_EAX		    6003   /* EAX Register Text	Field		*/
#define	IT_EBX		    6004   /* EBX Register Text	Field		*/
#define	IT_ECX		    6005   /* ECX Register Text	Field		*/
#define	IT_EDX		    6006   /* EDX Register Text	Field		*/
#define	IT_EBP		    6007   /* EBP Register Text	Field		*/
#define	IT_EDI		    6008   /* EDI Register Text	Field		*/
#define	IT_ESI		    6009   /* ESI Register Text	Field		*/
#define	IT_ESP		    6010   /* ESP Register Text	Field		*/
#define	IT_CS		    6011   /* CS Segment Text Field		*/
#define	IT_DS		    6012   /* DS Segment Text Field		*/
#define	IT_ES		    6013   /* ES Segment Text Field		*/
#define	IT_FS		    6014   /* FS Segment Text Field		*/
#define	IT_GS		    6015   /* GS Segment Text Field		*/
#define	IT_SS		    6016   /* SS Segment Text Field		*/
#define	IT_FLAGS	    6017   /* Flags Text Field			*/
#define	IT_FILE		    6018   /* File Text	Field			*/
#define	IT_DEBUGINFO	    6019   /* Debug Info Text Field		*/
#define	IT_PFNSTART	    6020   /* Function Start Address Text Field	*/
#define	IT_PFNEND	    6021   /* Function End Address Text	Field	*/
#define	IT_PID		    6022   /* Process ID Text Field		*/
#define	IT_TID		    6023   /* Thread ID	Text Field		*/
#define	IT_DETAIL	    6024   /* Details Text Field		*/
#define	IT_STATUS	    6025   /* Status Text Field			*/

#define	WM_PLAYSOUND   WM_USER

/* --- Styles ---------------------------------------------------------	*/

#define	LNS_VERTICAL		1
#define	LNS_HORIZONTAL		2

#define	TS_DEPRESSED		0
#define	TS_RAISED	      256

#define	DS_DEPRESSED		0
#define	DS_RAISED	       64
#define	DS_VERTICAL	      128

#define	SBRS_TEXT		0
#define	SBRS_NOTEXT		1

#define	ORD_PLAYSOUND		      1
#define	ORD_PLAYSOUNDASYNC	      2
#define	ORD_QUERYWAVEPATH	      3
#define	ORD_LOADSOUND		      4
#define	ORD_UNLOADSOUND		      5
#define	ORD_PLAYLOADEDSOUNDASYNC      6

/* --- Internal	Debug Support -----------------------------------------	*/

typedef	INT (_PFNINTADD)();
typedef	_PFNINTADD *PFNINTADD;

typedef	struct _INTERNALADDRESSLIST
   {
   PFNINTADD pfn;		   /* Function Address			*/
   PSZ	     pszFunction;	   /* Function Name			*/
   } INTERNALADDRESSLIST ; /* pfnial */

typedef	struct _INTERNALADDRESS
   {
   CHAR	     *pszModule;	   /* Module Name			*/
   INT	     cFunctions;	   /* Functions	Count			*/
   INTERNALADDRESSLIST *aial;	   /* Functions	Array			*/
   } INTERNALADDRESS ;	   /* intadd */
#define	IDB_CAT	10
