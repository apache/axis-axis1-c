/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include "AxisAdminService.h"
#include <string>
#include <axis/AxisException.hpp>
#include <iostream>

using namespace std;

#define FILEBUFFSIZE 256

int main( int argc, char *argv[])
{
    int		done = 0;
    int		len;
    char	Buff[FILEBUFFSIZE];
    string	Uri = "http://";
    string	wsdd;

    if( argc < 4)
    {
        printf( "Usage: %s [server] [port] [wsdd file | STOP] <time to wait>\n", argv[0]);
        exit( 1);
    }

    Uri += argv[1];
    Uri += ":";
    Uri += argv[2];
    Uri += "/axis/AxisAdmin";

    try
    {
        axiscpp::AxisAdminService   ws( Uri.c_str());
        
        if(argc==5)
        {
            // set the timeout or else on linux it'll sit there forever.
            ws.setTransportTimeout(atoi(argv[4]));
        }
        
		if ( 0 == strcmp(argv[3], "STOP") )
		{
            if( axiscpp::true_ == ws.stopAxis())
            {
                printf( "server at %s stopped successfully\n", Uri.c_str());
            }
            else
            {
                printf( "stopping server at %s failed\n", Uri.c_str());
            }
		}
		else
		{
            wsdd = argv[3];
            FILE *	file = fopen( wsdd.c_str(), "r");
            
            if (NULL == file)
            {
                printf( "WSDD file %s cannot be opened\n", wsdd.c_str ());
                printf( "Usage: %s <server> <port> <wsdd file>\n", argv[0]);
                exit( 1);
            }
            
            wsdd = "";
            
            while( !done)
            {
                len = fread( Buff, 1, FILEBUFFSIZE - 1, file);
                
                Buff[len] = 0;
                
                if( ferror( file))
                {
                    fclose( file);
                    
                    printf( "WSDD file %s cannot be read\n", wsdd.c_str());
                    printf( "Usage: %s <server> <port> <wsdd file>\n", argv[0]);
                    exit( 1);
                }
                done = feof( file);
                wsdd += Buff;
            }

            fclose( file);

            axiscpp::xsd__base64Binary	v;
            v.set( (axiscpp::xsd__unsignedByte *) wsdd.c_str(), wsdd.length());

            if( axiscpp::true_ == ws.updateWSDD( v))
            {
                printf( "server wsdd at %s updated successfully\n", Uri.c_str());
            }
            else
            {
                printf( "wsdd update at %s failed\n", Uri.c_str());
            }
        }
    }
    catch( axiscpp::AxisException& e)
    {
        cout << "Exception : " << e.what() << endl;
    }
    catch( exception& e)
    {
        cout << "Unknown exception has occured : " << e.what() << endl;
    }
    catch( ...)
    {
        cout << "Unknown exception has occured" << endl;
    }
    return 0;
}
