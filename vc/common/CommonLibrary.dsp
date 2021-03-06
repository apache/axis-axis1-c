# Microsoft Developer Studio Project File - Name="CommonLibrary" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CommonLibrary - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CommonLibrary.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CommonLibrary.mak" CFG="CommonLibrary - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CommonLibrary - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "CommonLibrary - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CommonLibrary - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USE_EXPAT_PARSER" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "CommonLibrary - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "USE_EXPAT_PARSER" /FR /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/axis\CommonLibrary_D.lib"

!ENDIF 

# Begin Target

# Name "CommonLibrary - Win32 Release"
# Name "CommonLibrary - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\common\AdminUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\ArrayBean.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\Attribute.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisSocketUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisTrace.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\BasicTypeSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\GDefine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\MessageData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\Namespace.cpp
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

SOURCE=..\..\src\common\AdminUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\ArrayBean.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\Attribute.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisConfigException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisConfigException.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\AxisException.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisFile.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisGenException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisMessage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisMessage.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisSocketUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisTime.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisTrace.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\AxisUserAPI.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\AxisUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\AxisWrapperAPI.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\BasicTypeSerializer.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\GDefine.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IAdminUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IArrayBean.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\IAttribute.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IDeployerUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\IHandlerSoapDeSerializer.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\IHandlerSoapDeSerializer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\IHandlerSoapSerializer.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\IHandlerSoapSerializer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\IHeaderBlock.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\IHeaderBlock.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\IMessageData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\INamespace.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\IParam.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\ISoapHeader.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\ISoapMethod.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\IWrapperSoapDeSerializer.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\IWrapperSoapSerializer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\MessageData.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\Namespace.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\Packet.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\Param.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\SoapEnvVersions.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\TypeMapping.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\WrapperClassHandler.h
# End Source File
# End Group
# End Target
# End Project
