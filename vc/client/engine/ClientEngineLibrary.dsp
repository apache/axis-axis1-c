# Microsoft Developer Studio Project File - Name="ClientEngineLibrary" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ClientEngineLibrary - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ClientEngineLibrary.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClientEngineLibrary.mak" CFG="ClientEngineLibrary - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClientEngineLibrary - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ClientEngineLibrary - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ClientEngineLibrary - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../lib/axis"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USE_EXPAT_PARSER" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/axis\ClientEngineLibrary.lib"

!ELSEIF  "$(CFG)" == "ClientEngineLibrary - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../lib/axis"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "USE_EXPAT_PARSER" /D "AXIS_CLIENT_LIB" /FR /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/axis\ClientEngineLibrary_D.lib"

!ENDIF 

# Begin Target

# Name "ClientEngineLibrary - Win32 Release"
# Name "ClientEngineLibrary - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\engine\AppScopeHandlerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\Axis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\AxisEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\client\Call.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\client\ClientAxisEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\DeserializerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\HandlerChain.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\HandlerLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\HandlerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\RequestScopeHandlerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\SerializerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\SessionScopeHandlerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\SharedObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\SOAPTransportFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\client\Stub.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\XMLParserFactory.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\engine\AppScopeHandlerPool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\axis\server\AxisEngine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\axis\client\Call.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\client\ClientAxisEngine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\DeserializerPool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\HandlerLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\HandlerPool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\RequestScopeHandlerPool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\SerializerPool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\SessionScopeHandlerPool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\SharedObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\SOAPTransportFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\axis\client\Stub.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\engine\XMLParserFactory.h
# End Source File
# End Group
# End Target
# End Project
