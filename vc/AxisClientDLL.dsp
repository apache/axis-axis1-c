# Microsoft Developer Studio Project File - Name="AxisClient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AxisClient - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AxisClientDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AxisClientDLL.mak" CFG="AxisClient - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AxisClient - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AxisClient - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AxisClient - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../release/win32/"
# PROP Intermediate_Dir "CRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AXISCLIENTDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Od /I "../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AXISCLIENTDLL_EXPORTS" /D "USE_EXPAT_PARSER" /D "AXIS_CLIENT_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 libexpat.lib wsock32.lib /nologo /dll /pdb:none /machine:I386 /out:"../release/win32/AxisClient.dll" /libpath:"../lib/expat"

!ELSEIF  "$(CFG)" == "AxisClient - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../release/win32/"
# PROP Intermediate_Dir "CDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AXISCLIENTDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AXISCLIENTDLL_EXPORTS" /D "USE_EXPAT_PARSER" /D "AXIS_CLIENT_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libexpat.lib wsock32.lib /nologo /dll /pdb:none /debug /machine:I386 /out:"../release/win32/AxisClient.dll" /libpath:"../lib/expat"

!ENDIF 

# Begin Target

# Name "AxisClient - Win32 Release"
# Name "AxisClient - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\engine\AppScopeHandlerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\ArrayBean.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\Attribute.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\Axis.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\AxisConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\AxisEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\AxisException.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\AxisTime.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\AxisTrace.cpp
# End Source File
# Begin Source File

SOURCE=..\src\transport\axis\AxisTransport.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\AxisUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\BasicNode.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\BasicTypeSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\client\Call.cpp
# End Source File
# Begin Source File

SOURCE=..\src\transport\axis\Channel.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\CharacterElement.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\client\ClientAxisEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\ComplexElement.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\DeserializerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\Element.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\Event.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\GDefine.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\HandlerChain.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\HandlerLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\HandlerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\HeaderBlock.cpp
# End Source File
# Begin Source File

SOURCE=..\src\transport\axis\HttpTransport.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\MessageData.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\Packet.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\Param.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\QName.cpp
# End Source File
# Begin Source File

SOURCE=..\src\transport\axis\Receiver.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\RequestScopeHandlerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\src\transport\axis\Sender.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\SerializerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\SessionScopeHandlerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\SharedObject.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\SimpleAttribute.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapBody.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapDeSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapEnvelope.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapFault.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapHeader.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapKeywordMapping.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapMethod.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapParserExpat.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\StartElement.cpp
# End Source File
# Begin Source File

SOURCE=..\src\transport\axis\Transport.cpp
# End Source File
# Begin Source File

SOURCE=..\src\transport\axis\TransportFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\TypeMapping.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\URIMapping.cpp
# End Source File
# Begin Source File

SOURCE=..\src\transport\axis\Url.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdd\WSDDDeployment.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdd\WSDDDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdd\WSDDHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdd\WSDDKeywords.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdd\WSDDService.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdd\WSDDTransport.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\axis\client\Call.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
