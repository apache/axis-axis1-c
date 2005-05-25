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

#if !defined(_AXIS_SECURECHANNEL_H)
#define _AXIS_SECURECHANNEL_H
#include "ISecureChannel.hpp"
//#include "ChannelFactory.hpp"
//#include "../SSLChannel.hpp"
#include "Channel.h"
#include <iostream>
using namespace std;

class SecureChannel: public Channel, public ISecureChannel
{
public:
	SecureChannel();
	virtual ~SecureChannel();

	virtual bool open() throw (AxisTransportException&);
	virtual void close();

	virtual const Channel& operator >> (std::string&) throw (AxisTransportException);
	virtual const Channel& operator << (const char *) throw (AxisTransportException);

	bool setServerName( std::string);
	string getServerName();

	virtual void setSecureProperties( const char *);
	virtual const char * getSecureProperties();
        virtual int setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE
            type, const char* value);

private:
    bool openConnection();
    bool closeConnection();

    virtual int openSecureSocket(){ return 0;};
    virtual int closeSecureSocket(){ return 0;};

    virtual bool writeSecureSocket(const char *p1){return true;};
    virtual bool readSecureSocket( char *p1, int p2){return true;};

    virtual void setSecureError(int iError){};
    virtual char* getSecureError(){ return NULL;};

protected:
	string sServerName;
        //SecureChannel* m_pSecureChannel;
};

#endif

