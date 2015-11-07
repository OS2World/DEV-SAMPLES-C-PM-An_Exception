
/* heapmem.h	   Created:    1992-07-04  Revised:    1993-12-19	*/

/* Prominare Builder Build Session Constant Definition Header		*/

/* Functions are defined with strong typing to insure correct usage	*/
/* within the final program and	correct	linkage				*/

/* Copyright ¸ 1987-1995  Prominare Inc.  All Rights Reserved.		*/


/* --- Memory Types ---------------------------------------------------	*/

typedef	ULONG HHEAPMEM;
#define	HALLOC_DEFAULT	0xffffffffUL

/* --- Memory.C	Prototype Definitions ---------------------------------	*/

HHEAPMEM HeapAlloc(ULONG cbInitial, ULONG cbNewBlks);
VOID	 HeapRelease(HHEAPMEM hHeap);
VOID	 HeapLock(HHEAPMEM hHeap);
VOID	 HeapUnLock(HHEAPMEM hHeap);
ULONG	 HeapSize(HHEAPMEM hHeap);

VOID	 HeapStatus(HHEAPMEM hHeap, PULONG pcBlocks, PULONG pulSize,
		    PULONG pulUsed, PULONG pulFree, PULONG pulUnused, PULONG pulOverhead);
VOID	 HeapDisplayStatus(HHEAPMEM hHeap);

PVOID	 HeapMalloc(HHEAPMEM hHeap, ULONG cbSize);
PVOID	 HeapCalloc(HHEAPMEM hHeap, ULONG cItems, ULONG	cbSize);
PVOID	 HeapRealloc(HHEAPMEM hHeap, PVOID pv, ULONG cbSize);
VOID	 HeapFree(HHEAPMEM hHeap, PVOID	pv);
