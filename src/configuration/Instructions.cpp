#include "Instructions.hpp"

void Instructions( char * pszPackageName)
{

	cout << "Usage" << endl <<
			"-----" << endl << endl;

	cout << "AxisConfiguration Client [params1]\tConfigure the client side." << endl;
	cout << "AxisConfiguration Server [params2]\tConfigure the server side." << endl;
	cout << "AxisConfiguration Both [params3]\tConfigure the client and server side." << endl << endl;
	cout << "The param list is as follows:-" << endl;
	cout << "-acd directory to write axiscpp.conf once it has been configured.  This" << endl <<
			"     overrides the '-a' value (which defines where axiscpp.conf would normally" << endl <<
			"     reside)." << endl <<
#if WIN32
			"     example: -acd c:\\Axis\\Different" << endl << endl;
#else
			"     example: -a /home/userid/Axis/Different" << endl << endl;
#endif
	cout << "-a   root directory of Axis download (AXISCPP_HOME)" << endl <<
#if WIN32
			"     example: -a c:\\Axis" << endl << endl;
#else
			"     example: -a /home/userid/Axis" << endl << endl;
#endif
	cout << "-o   directory offset from AXISCPP_HOME to object files" <<
#if WIN32
			"     example: -o " << pszPackageName << endl << endl;
#else
			"     example: -o " << pszPackageName << endl << endl;
#endif
	cout << "-th  transport library name" << endl <<
			"     if -a and -o have both already been defined, then only the filename is" << endl <<
			"     required.  Otherwise the fully qualified path will be required (NB: You" << endl <<
			"     can still override the -a and -o definitions by using a fully qulified" << endl <<
			"     path)." << endl <<
			"     example (with -a and -o defined): " << endl <<
#if WIN32
			"     -th HTTPTransport.dll" << endl << endl <<
			"     example (without -a and -o defined): " << endl <<
			"     -th c:\\Axis\\" << pszPackageName << "\\HTTPTransport.dll" << endl << endl;
#else
			"     -th libhttp_transport.so" << endl <<
			"     example (without -a and -o defined): " << endl <<
			"     -th /home/userid/Axis/" << pszPackageName << "/libhttp_transport.so" << endl << endl;
#endif
	cout << "-c   channel library name" << endl <<
			"     if -a and -o have both already been defined, then only the filename is" << endl <<
			"     required.  Otherwise the fully qualified path will be required (NB: You" << endl <<
			"     can still override the -a and -o definitions by using a fully qulified" << endl <<
			"     path)." << endl <<
			"     example (with -a and -o defined): " << endl <<
#if WIN32
			"     -c HTTPChannel.dll" << endl <<
			"     example (without -a and -o defined):" << endl <<
			"     -c c:\\Axis\\" << pszPackageName << "\\HTTPChannel.dll" << endl << endl;
#else
			"     -c libhttp_channel.so" << endl;
			"     example (without -a and -o defined):" << endl;
			"     -c /home/userid/Axis/" << pszPackageName << "/libhttp_channel.so" << endl << endl;
#endif
	cout << "-cs  ssl channel library name" << endl <<
			"     if -a and -o have both already been defined, then only the filename is" << endl <<
			"     required.  Otherwise the fully qualified path will be required (NB: You" << endl <<
			"     can still override the -a and -o definitions by using a fully qulified" << endl <<
			"     path)." << endl <<
			"     example (with -a and -o defined):" << endl <<
#if WIN32
			"     -cs HTTPSSLChannel.dll" << endl << endl <<
			"     example (without -a and -o defined):" << endl <<
			"     -cs c:\\Axis\\" << pszPackageName << "\\HTTPSSLChannel.dll" << endl << endl;
#else
			"     -cs libhttp_channelssl.so" << endl << endl <<
			"     example (without -a and -o defined):" << endl <<
			"     -cs /home/userid/Axis/" << pszPackageName << "/libhttp_channelssl.so" << endl << endl;
#endif
	cout << "-x   xerces library name" << endl <<
			"     if -a and -o have both already been defined, then only the filename is" << endl <<
			"     required.  Otherwise the fully qualified path will be required (NB: You" << endl <<
			"     can still override the -a and -o definitions by using a fully qulified" << endl <<
			"     path)." << endl <<
			"     example (with -a and -o defined):" << endl <<
#if WIN32
			"     -x AxisXMLParserXerces.dll" << endl << endl <<
			"     example (without -a and -o defined):" << endl <<
			"     -x c:\\Axis\\" << pszPackageName << "\\AxisXMLParserXerces.dll" << endl << endl;
#else
			"     -x libaxis_xerces.so" << endl << endl <<
			"     example (without -a and -o defined):" << endl <<
			"     -x /home/userid/Axis/" << pszPackageName << "/libaxis_xerces.so" << endl << endl;
#endif
	cout << "-m   merge with existing configuration file" << endl <<
			"     example: -m on|off (the default is 'off' meaning 'overwrite')" << endl << endl;

	cout << "-pi  change the progress information output during the construction of the" << endl <<
			"     configuration file." << endl <<
			"     example: -pi normal|quiet (the default is 'normal' meaning \"give full" << endl <<
			"     descriptions\")." << endl << endl;

	cout << "-b   backup the existing configuration file before creating the new one." << endl <<
			"     example: -b true|false (the default is 'true')." << endl << endl;

	cout << "-qmf query for missing files." << endl <<
			"     When no parameter for a filename is provided on the command line, the" << endl <<
			"     application will list the file options and the user then selects which" << endl <<
			"     file to use in the configuration file.  This can be turned off using this" << endl <<
			"     parameter." << endl <<
			"     example: -qmf on|off (the default is 'on' meaning \"list and then ask for" << endl <<
			"                           file to include\")." << endl << endl;
     
	cout << "-so  SSL options." << endl <<
			"     Used to add a string of parameters (if) required by the version SSL." << endl <<
			"     example: -so \"...parameter list...\"" << endl << endl;

	cout << "Client Specific" << endl <<
			"---------------" << endl;
	cout << "-cl  client log filename" << endl <<
			"     if -a has been defined, then only the filename is required.  Otherwise the" << endl <<
			"     fully qualified path will be required.  (NB: You can still override the -a" << endl <<
			"     and -o definitions by using a fully qulified path).  To ignore the client" << endl <<
			"     log, using 'ignore' instead of a filename." << endl <<
			"     -cl client.log" << endl << endl <<
			"     example (without -a defined): " << endl <<
#if WIN32
			"     -cl c:\\Axis\\client.log" << endl << endl;
#else
			"     -cl /home/userid/Axis/client.log" << endl << endl;
#endif
	cout << "-cw  client WSDD filename" << endl <<
			"     if -a and -o have both already been defined, then only the filename is" << endl <<
			"     required.  Otherwise the fully qualified path will be required (NB: You" << endl <<
			"     can still override the -a and -o definitions by using a fully qulified" << endl <<
			"     path)." << endl <<
			"     example (with -a and -o defined):" << endl <<
			"     -cw client.wsdd" << endl << endl <<
			"     example (without -a and -o defined):" << endl <<
#if WIN32
			"     -cw c:\\Axis\\WSDD\\client.wsdd" << endl << endl;
#else
			"     -cw /home/userid/Axis/WSDD/client.wsdd" << endl << endl;
#endif
	cout << "Server Specific" << endl <<
			"---------------" << endl;

	cout << "-sl  server log filename" << endl <<
			"     if -a has been defined, then only the filename is required.  Otherwise the" << endl <<
			"     fully qualified path will be required.  (NB: You can still override the -a" << endl <<
			"     and -o definitions by using a fully qulified path)." << endl <<
			"     example (with -a defined):" << endl <<
			"     -sl server.log" << endl << endl <<
			"     example (without -a defined):" << endl <<
#if WIN32
			"     -sl c:\\Axis\\server.log" << endl << endl;
#else
			"     -sl /home/userid/Axis/server.log" << endl << endl;
#endif
	cout << "-sw  server WSDD filename" << endl <<
			"     if -a and -o have both already been defined, then only the filename is" << endl <<
			"     required.  Otherwise the fully qualified path will be required (NB: You" << endl <<
			"     can still override the -a and -o definitions by using a fully qulified" << endl <<
			"     path)." << endl <<
			"     example (with -a and -o defined):" << endl <<
			"     -sw server.wsdd" << endl << endl <<
			"     example (without -a and -o defined):" << endl <<
#if WIN32
			"     -sw c:\\Axis\\WSDD\\server.wsdd" << endl << endl;
#else
			"     -sw /home/userid/Axis/WSDD/server.wsdd" << endl << endl;
#endif
}
