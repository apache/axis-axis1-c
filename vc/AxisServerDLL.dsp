# Microsoft Developer Studio Project File - Name="AxisServerDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AxisServerDLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AxisServerDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AxisServerDLL.mak" CFG="AxisServerDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AxisServerDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AxisServerDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AxisServerDLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../release/win32/"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DYNALIB_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DYNALIB_EXPORTS" /D "USE_EXPAT_PARSER" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 libexpat.lib /nologo /dll /machine:I386 /libpath:"../lib/expat"

!ELSEIF  "$(CFG)" == "AxisServerDLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../release/win32/"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DYNALIB_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DYNALIB_EXPORTS" /D "USE_EXPAT_PARSER" /FD /GZ /c
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
# ADD LINK32 libexpat.lib /nologo /dll /debug /machine:I386 /out:"../release/win32/AxisServer.dll" /pdbtype:sept /libpath:"../lib/expat"

!ENDIF 

# Begin Target

# Name "AxisServerDLL - Win32 Release"
# Name "AxisServerDLL - Win32 Debug"
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

SOURCE=..\src\common\AxisUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\BasicNode.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\BasicTypeSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\CharacterElement.cpp
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

SOURCE=..\src\engine\RequestScopeHandlerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\SerializerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\server\ServerAxisEngine.cpp
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

SOURCE=..\src\common\TypeMapping.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\URIMapping.cpp
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

SOURCE=..\include\axis\xml\AnyElement.h
# End Source File
# Begin Source File

SOURCE=..\src\engine\AppScopeHandlerPool.h
# End Source File
# Begin Source File

SOURCE=..\src\common\ArrayBean.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\soap\Attribute.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\AxisConfig.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\engine\AxisEngine.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\AxisException.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\AxisTime.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\AxisTrace.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\AxisUserAPI.h
# End Source File
# Begin Source File

SOURCE=..\src\common\AxisUtils.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\AxisWrapperAPI.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\BasicHandler.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\soap\BasicNode.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\BasicTypeSerializer.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\soap\CharacterElement.h
# End Source File
# Begin Source File

SOURCE=..\src\soap\ComplexElement.h
# End Source File
# Begin Source File

SOURCE=..\src\engine\DeserializerPool.h
# End Source File
# Begin Source File

SOURCE=..\src\xml\Element.h
# End Source File
# Begin Source File

SOURCE=..\src\xml\Event.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\GDefine.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\Handler.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\engine\HandlerChain.h
# End Source File
# Begin Source File

SOURCE=..\src\engine\HandlerLoader.h
# End Source File
# Begin Source File

SOURCE=..\src\engine\HandlerPool.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\soap\HeaderBlock.h
# End Source File
# Begin Source File

SOURCE=..\src\common\IArrayBean.h
# End Source File
# Begin Source File

SOURCE=..\src\common\IDeployerUtils.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\IHandlerSoapDeSerializer.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\IHandlerSoapSerializer.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\IHeaderBlock.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\IMessageData.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\IParam.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\ISoapDeSerializer.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\ISoapHeader.h
# End Source File
# Begin Source File

SOURCE=..\src\common\ISoapMethod.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\ISoapSerializer.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\IWrapperSoapDeSerializer.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\IWrapperSoapSerializer.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\MessageData.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\Packet.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\Param.h
# End Source File
# Begin Source File

SOURCE=..\src\xml\QName.h
# End Source File
# Begin Source File

SOURCE=..\src\engine\RequestScopeHandlerPool.h
# End Source File
# Begin Source File

SOURCE=..\src\engine\SerializerPool.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\engine\ServerAxisEngine.h
# End Source File
# Begin Source File

SOURCE=..\src\engine\ServerAxisEngine.h
# End Source File
# Begin Source File

SOURCE=..\src\engine\SessionScopeHandlerPool.h
# End Source File
# Begin Source File

SOURCE=..\src\engine\SharedObject.h
# End Source File
# Begin Source File

SOURCE=..\src\xml\SimpleAttribute.h
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapBody.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\soap\SoapDeSerializer.h
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapEnvelope.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\soap\SoapEnvVersions.h
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapFault.h
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapFaults.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\soap\SoapHeader.h
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapKeywordMapping.h
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapMethod.h
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapParserExpat.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\soap\SoapSerializer.h
# End Source File
# Begin Source File

SOURCE=..\src\xml\StartElement.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\TypeMapping.h
# End Source File
# Begin Source File

SOURCE=..\src\soap\URIMapping.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\common\WrapperClassHandler.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\wsdd\WSDDDefines.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdd\WSDDDeployment.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdd\WSDDDocument.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\wsdd\WSDDHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdd\WSDDKeywords.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\wsdd\WSDDService.h
# End Source File
# Begin Source File

SOURCE=..\src\wsdd\WSDDTransport.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\xml\XMLParser.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
