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

/*
 *
 *
 * @author Lilantha Darshana (lilantha@virtusa.com)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */
#include "Platform.hpp"
#include "Sender.hpp"


Sender::Sender(Transport *pTr)
    : m_pTrChannel(pTr)
{

}

Sender::~Sender()
{

}

void Sender::ClearAdditionalHeaders()
{
    m_pTrChannel->ClearAdditionalHeaders();
}

bool Sender::Send(const char* what) throw (AxisException)
{
    try
    {
        *m_pTrChannel << what;
    }
    catch(...)
    {
        throw AxisException(SERVER_TRANSPORT_SENDINGEXCEPTION);
    }

    return true;
}

void Sender::SetProperty(const char* sProperty, const char* sValue)
{
    m_pTrChannel->SetProperty(sProperty, sValue);
}


