# Microsoft Developer Studio Generated NMAKE File, Based on MuMsg.dsp
!IF "$(CFG)" == ""
CFG=MuMsg - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MuMsg - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MuMsg - Win32 Release" && "$(CFG)" != "MuMsg - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MuMsg.mak" CFG="MuMsg - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MuMsg - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MuMsg - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MuMsg - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\MuMsg.dll"


CLEAN :
	-@erase "$(INTDIR)\MuMsg.obj"
	-@erase "$(INTDIR)\MuMsg.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MuMsg.dll"
	-@erase "$(OUTDIR)\MuMsg.exp"
	-@erase "$(OUTDIR)\MuMsg.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MUMSG_EXPORTS" /Fp"$(INTDIR)\MuMsg.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MuMsg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\MuMsg.pdb" /machine:I386 /out:"$(OUTDIR)\MuMsg.dll" /implib:"$(OUTDIR)\MuMsg.lib" 
LINK32_OBJS= \
	"$(INTDIR)\MuMsg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MuMsg.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MuMsg - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MuMsg.dll"


CLEAN :
	-@erase "$(INTDIR)\MuMsg.obj"
	-@erase "$(INTDIR)\MuMsg.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\MuMsg.dll"
	-@erase "$(OUTDIR)\MuMsg.exp"
	-@erase "$(OUTDIR)\MuMsg.ilk"
	-@erase "$(OUTDIR)\MuMsg.lib"
	-@erase "$(OUTDIR)\MuMsg.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MUMSG_EXPORTS" /Fp"$(INTDIR)\MuMsg.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MuMsg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\MuMsg.pdb" /debug /machine:I386 /out:"$(OUTDIR)\MuMsg.dll" /implib:"$(OUTDIR)\MuMsg.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\MuMsg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MuMsg.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MuMsg.dep")
!INCLUDE "MuMsg.dep"
!ELSE 
!MESSAGE Warning: cannot find "MuMsg.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MuMsg - Win32 Release" || "$(CFG)" == "MuMsg - Win32 Debug"
SOURCE=.\MuMsg.cpp

"$(INTDIR)\MuMsg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MuMsg.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MuMsg - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MUMSG_EXPORTS" /Fp"$(INTDIR)\MuMsg.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MuMsg.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MuMsg - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MUMSG_EXPORTS" /Fp"$(INTDIR)\MuMsg.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MuMsg.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

