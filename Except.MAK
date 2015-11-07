
# MAKE file for Except.MAK     Version 3.0

# Revised:  1994-08-23

# Copyright ¸ 1987-1994  Prominare Inc.

# MAKE file created by Prominare Builder  Version 3.0


CC=ICC
RC=RC
# C_SW=-G4 -O- -Oi- -Op- -Os- -Ti -W3 -C
C_SW=-G4 -O+ -Rn -W3 -C
# L_SW=/DEBUG
L_SW=
RC_SW=-r

Except.Exe: 3DLine.Obj 3DText.Obj AppDefs.Obj\
            Dialog1.Obj Dialog2.Obj Except.Obj\
            HeapMgr.Obj Support.Obj WndProc.Obj\
            Xcept.Obj Except.Res
 Link386 $(L_SW) @OS2PM_2x.Lnk;
 rc -x Except.Res Except.Exe

3DLine.Obj: 3DLine.C
 $(CC) $(C_SW) -Fo$*.Obj 3DLine.C

3DText.Obj: 3DText.C
 $(CC) $(C_SW) -Fo$*.Obj 3DText.C

AppDefs.Obj: AppDefs.C
 $(CC) $(C_SW) -Fo$*.Obj AppDefs.C

Dialog1.Obj: Dialog1.C
 $(CC) $(C_SW) -Fo$*.Obj Dialog1.C

Dialog2.Obj: Dialog2.C
 $(CC) $(C_SW) -Fo$*.Obj Dialog2.C

Except.Obj: Except.C
 $(CC) $(C_SW) -Fo$*.Obj Except.C

Except.Res: Except.Rc
 $(RC) $(RC_SW) Except.Rc $*.Res

HeapMgr.Obj: HeapMgr.C
 $(CC) $(C_SW) -Fo$*.Obj HeapMgr.C

Support.Obj: Support.C
 $(CC) $(C_SW) -Fo$*.Obj Support.C

WndProc.Obj: WndProc.C
 $(CC) $(C_SW) -Fo$*.Obj WndProc.C

Xcept.Obj: Xcept.C
 $(CC) $(C_SW) -Fo$*.Obj Xcept.C

