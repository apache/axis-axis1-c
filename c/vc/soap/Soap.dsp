# Microsoft Developer Studio Project File - Name="Soap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Soap - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Soap.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Soap.mak" CFG="Soap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Soap - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Soap - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Soap - Win32 Release"

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

!ELSEIF  "$(CFG)" == "Soap - Win32 Debug"

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
# ADD LIB32 /nologo /out:"../../lib/axis\Soap_D.lib"

!ENDIF 

# Begin Target

# Name "Soap - Win32 Release"
# Name "Soap - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\soap\Attribute.cpp
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

SOURCE=..\..\src\soap\SoapKeywordMapping.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapMethod.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapParserExpat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\SoapSerializer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\soap\URIMapping.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\axis\soap\Attribute.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\BasicNode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\CharacterElement.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\ComplexElement.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\HeaderBlock.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\SoapBody.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\SoapDeSerializer.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\SoapEnvelope.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\SoapEnvVersions.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\SoapFault.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\SoapFaults.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\SoapHeader.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\SoapKeywordMapping.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\SoapMethod.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\SoapParserExpat.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\SoapSerializer.h
# End Source File
# Begin Source File

SOURCE=..\..\include\axis\soap\URIMapping.h
# End Source File
# End Group
# End Target
# End Project
