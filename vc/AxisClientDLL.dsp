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
# PROP Output_Dir "../bin"
# PROP Intermediate_Dir "CRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AXISCLIENTDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Od /I "../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AXISCLIENTDLL_EXPORTS" /D "AXIS_CLIENT_LIB" /D "ENABLE_AXIS_EXCEPTION" /FR /FD /c
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
# ADD LINK32 /nologo /dll /pdb:none /machine:I386 /out:"../bin/AxisClient.dll" /libpath:"../lib/expat"

!ELSEIF  "$(CFG)" == "AxisClient - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../bin"
# PROP Intermediate_Dir "CDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AXISCLIENTDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AXISCLIENTDLL_EXPORTS" /D "AXIS_CLIENT_LIB" /D "ENABLE_AXIS_EXCEPTION" /FR /FD /GZ /c
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
# ADD LINK32 /nologo /dll /pdb:none /debug /machine:I386 /out:"../bin/AxisClient_D.dll" /libpath:"../lib/expat"

!ENDIF 

# Begin Target

# Name "AxisClient - Win32 Release"
# Name "AxisClient - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\common\AdminUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\AnyURI.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\AppScopeHandlerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\apr_base64.c
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

SOURCE=..\src\common\AxisConfigException.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\AxisEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\AxisEngineException.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\AxisGenException.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\AxisParseException.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\AxisSoapException.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\AxisTime.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\AxisTrace.cpp
# End Source File
# Begin Source File

SOURCE=..\src\transport\axis2\AxisTransportException.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\AxisUserAPI.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\AxisUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wsdd\AxisWsddException.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Base64Binary.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\BasicNode.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\BasicTypeSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Boolean.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Byte.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\client\Call.cpp
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

SOURCE=..\src\soap\xsd\Date.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\DateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Decimal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\DeserializerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Double.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Duration.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\Element.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\ENTITIES.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\ENTITY.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\Event.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Float.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\constraints\FractionDigits.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\GDay.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\GDefine.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\GMonth.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\GMonthDay.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\GYear.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\GYearMonth.cpp
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

SOURCE=..\src\soap\xsd\HexBinary.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\HexCoder.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\IAnySimpleType.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\constraints\IConstrainingFacet.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\ID.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\IDREF.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\IDREFS.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Int.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Integer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Language.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\constraints\Length.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Long.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\constraints\MaxExclusive.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\constraints\MaxInclusive.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\constraints\MaxLength.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\MessageData.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\constraints\MinExclusive.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\constraints\MinInclusive.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\constraints\MinLength.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Name.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\Namespace.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\NCName.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\NegativeInteger.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\NMTOKEN.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\NMTOKENS.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\NonNegativeInteger.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\NonPositiveInteger.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\NormalizedString.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\NOTATION.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\Param.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\constraints\Pattern.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\PositiveInteger.cpp
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

SOURCE=..\src\engine\SessionScopeHandlerPool.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\SharedObject.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Short.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\SimpleAttribute.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapAttachementHeaders.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\SoapAttachment.cpp
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

SOURCE=..\src\common\SoapEnvVersions.cpp
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

SOURCE=..\src\soap\SoapSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\SOAPTransportFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\src\xml\StartElement.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\String.cpp
# End Source File
# Begin Source File

SOURCE=..\src\engine\client\Stub.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Time.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\Token.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\constraints\TotalDigits.cpp
# End Source File
# Begin Source File

SOURCE=..\src\common\TypeMapping.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\UnsignedByte.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\UnsignedInt.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\UnsignedLong.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\UnsignedShort.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\URIMapping.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\constraints\WhiteSpace.cpp
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
# Begin Source File

SOURCE=..\src\engine\XMLParserFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\xsd\XSD_QName.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\axis\Axis.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\AxisException.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\AxisGenException.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\AxisUserAPI.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\AxisWrapperAPI.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\BasicHandler.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\BasicNode.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\client\Call.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\GDefine.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\Handler.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\IAttribute.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\IHandlerSoapDeSerializer.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\IHandlerSoapSerializer.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\IHeaderBlock.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\IMessageData.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\ISoapFault.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\IWrapperSoapDeSerializer.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\IWrapperSoapSerializer.hpp
# End Source File
# Begin Source File

SOURCE=..\src\soap\Namespace.h
# End Source File
# Begin Source File

SOURCE=..\include\axis\SoapEnvVersions.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\client\Stub.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\TypeMapping.hpp
# End Source File
# Begin Source File

SOURCE=..\include\axis\WSDDDefines.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
