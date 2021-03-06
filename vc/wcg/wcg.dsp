# Microsoft Developer Studio Project File - Name="wcg" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=wcg - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wcg.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wcg.mak" CFG="wcg - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wcg - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "wcg - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wcg - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../release/win32"
# PROP Intermediate_Dir "../../bin/win32/wcg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O1 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "wcg - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../release/win32"
# PROP Intermediate_Dir "../../bin/win32/wcg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /ML /W3 /Gm /GX /ZI /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libcpd.lib /nologo /subsystem:console /pdb:none /machine:I386
# SUBTRACT LINK32 /debug

!ENDIF 

# Begin Target

# Name "wcg - Win32 Release"
# Name "wcg - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\wcg\actions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\BeanClass.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\cpplex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\cppyacc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\Deploy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\File.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\Method.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\TranslationUnit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\Variable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\WCGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\WSClass.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\wcg\actions.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\BeanClass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\File.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\Method.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\TranslationUnit.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\Variable.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\WCGenerator.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\WSClass.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\..\src\wcg\cpp.l
# End Source File
# Begin Source File

SOURCE=..\..\src\wcg\cpp.y
# End Source File
# End Target
# End Project
