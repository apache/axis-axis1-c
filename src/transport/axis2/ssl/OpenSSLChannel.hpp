// Copyright 2003-2004 The Apache Software Foundation.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#if !defined(_AXIS_OPENSSLCHANNEL_H)
#define _AXIS_OPENSSLCHANNEL_H
#include "../SecureChannel.hpp"
#include "AxisSSLChannelException.hpp"
#include <iostream>
using namespace std;

class OpenSSLChannel: public SecureChannel
{
public:
	OpenSSLChannel();
	~OpenSSLChannel();

	bool open() throw (AxisTransportException&);
	void close();

	const Channel& operator >> (std::string&) throw (AxisTransportException);
	const Channel& operator << (const char *) throw (AxisTransportException);

	bool setServerName( std::string) { return true;};
	string getServerName(){ return NULL;};

	void setSecureProperties( const char *){};
	const char * getSecureProperties(){ return NULL;};
        int setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE
            type, const char* value){ return 0;};

private:
    bool openConnection(){ return true;};
    bool closeConnection(){ return true;};

    int openSecureSocket();
    int closeSecureSocket();

    bool writeSecureSocket(const char *);
    bool readSecureSocket( char *, int);

    void setSecureError(int iError);
    char* getSecureError();

protected:
	string sServerName;
};

#endif

