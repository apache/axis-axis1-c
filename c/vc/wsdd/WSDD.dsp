# Microsoft Developer Studio Project File - Name="WSDD" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=WSDD - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WSDD.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WSDD.mak" CFG="WSDD - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WSDD - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "WSDD - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WSDD - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../lib/axis"
# PROP Intermediate_Dir "../../bin/win32/wsdd"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "WSDD - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../lib/axis"
# PROP Intermediate_Dir "../../bin/win32/wsdd"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__AXISTRACE__" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/win32/axis\WSDD_D.lib"

!ENDIF 

# Begin Target

# Name "WSDD - Win32 Release"
# Name "WSDD - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\wsdd\WSDDDeployment.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wsdd\WSDDDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wsdd\WSDDHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wsdd\WSDDKeywords.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wsdd\WSDDService.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wsdd\WSDDTransport.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\axis\wsdd\WSDDDefines.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\wsdd\WSDDDeployment.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\wsdd\WSDDDocument.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\wsdd\WSDDHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\wsdd\WSDDKeywords.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\wsdd\WSDDService.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\wsdd\WSDDTransport.h
# End Source File
# End Group
# End Target
# End Project
