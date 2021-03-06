# Microsoft Developer Studio Project File - Name="SoapLibrary" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=SoapLibrary - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SoapLibrary.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SoapLibrary.mak" CFG="SoapLibrary - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SoapLibrary - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SoapLibrary - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SoapLibrary - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /Od /I "../../include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USE_EXPAT_PARSER" /FD /c
# SUBTRACT CPP /Fr /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "SoapLibrary - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "USE_XERCES_PARSER" /FR /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/axis\SoapLibrary_D.lib"

!ENDIF 

# Begin Target

# Name "SoapLibrary - Win32 Release"
# Name "SoapLibrary - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\soap\apr_base64.c
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\Attribute.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\AxisSoapException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\BasicNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\CharacterElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\ComplexElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\HeaderBlock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\HexCoder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\expat\ParserLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\xerces\ParserLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\xerces\SoapBinInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapBody.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapDeSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapEnvelope.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapFault.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapHeader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapInputSource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\xerces\SoapInputSource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapKeywordMapping.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapMethod.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapParserExpat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapParserXerces.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\xerces\SoapParserXerces.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\URIMapping.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\XercesHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\xerces\XercesHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\expat\XMLParserExpat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\xerces\XMLParserXerces.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\soap\apr_base64.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\Attribute.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\AxisSoapException.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\server\BasicNode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\BasicNode.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\CharacterElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\ComplexElement.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\HeaderBlock.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\HexCoder.h
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\xerces\SoapBinInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapDeSerializer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapEnvelope.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapFault.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapHeader.h
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\xerces\SoapInputSource.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapKeywordMapping.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapMethod.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapSerializer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\URIMapping.h
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\xerces\XercesHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\expat\XMLParserExpat.h
# End Source File
# Begin Source File

SOURCE=..\..\src\xml\xerces\XMLParserXerces.h
# End Source File
# End Group
# End Target
# End Project
