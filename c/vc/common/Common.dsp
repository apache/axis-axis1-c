# Microsoft Developer Studio Project File - Name="Common" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Common - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Common.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Common.mak" CFG="Common - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Common - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Common - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Common - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../lib/win32/axis"
# PROP Intermediate_Dir "../../bin/win32/common"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Common - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../lib/win32/axis"
# PROP Intermediate_Dir "../../bin/win32/common"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Common - Win32 Release"
# Name "Common - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\common\AccessBean.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\ArrayBean.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\BasicTypeSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\Debug.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\MessageData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\Packet.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\Param.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\TypeMapping.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\common\AccessBean.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\ArrayBean.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisException.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisLog.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\BasicHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\BasicTypeSerializer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\Debug.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\GDefine.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IAccessBean.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IArrayBean.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IMessageData.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IParam.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\ISoapDeserializer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\ISoapMethod.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\ISoapSerializer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\MessageData.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\Packet.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\Param.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\TypeMapping.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\WrapperClassHandler.h
# End Source File
# End Group
# End Target
# End Project
