# Microsoft Developer Studio Project File - Name="client" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=client - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "client.mak" CFG="client - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "client - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "client - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "client - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../lib/axis"
# PROP Intermediate_Dir "../../bin/win32/client"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../../include" /I "../../src/common" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "client - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../lib/axis"
# PROP Intermediate_Dir "../../bin/win32/client"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/axis\client_D.lib"

!ENDIF 

# Begin Target

# Name "client - Win32 Release"
# Name "client - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\client\transport\axis\AxisTransport.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\client\Call.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\client\transport\axis\Channel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\client\transport\axis\HttpTransport.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\client\transport\axis\Receiver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\client\transport\axis\Sender.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\client\transport\axis\Transport.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\client\transport\axis\TransportFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\client\transport\axis\Url.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\axis\client\transport\AxisTransport.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\client\Call.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\client\transport\axis\Channel.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\client\transport\axis\HttpTransport.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\client\transport\axis\Platform.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\client\transport\axis\Receiver.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\client\transport\axis\Sender.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\client\transport\axis\Transport.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\client\transport\axis\TransportFactory.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\client\transport\axis\Url.hpp
# End Source File
# End Group
# End Target
# End Project
