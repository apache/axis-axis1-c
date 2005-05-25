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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */


#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4101)
#endif

#include "IPV6Transport.hpp"
#include "IPV6Channel.hpp"

#include <stdio.h>
#include <iostream>

/*
 * IPV6Transport constuctor
 */
IPV6Transport::IPV6Transport ()
{
    m_pChannel  = new IPV6Channel();
}

/*
 * IPV6Transport destuctor
 */
IPV6Transport::~IPV6Transport ()
{}

/*
 * IPV6Transport::setEndpointUri( EndpointURI) sets the URI for the message.
 * Everytime the endpoint changes then currently connected channel is closed
 * and a new channel connection is opened.
 *
 * @param	EndpointURI - char * to a null terminated string that holds the
 *			new URI. 
 */
void
IPV6Transport::setEndpointUri (const char *pcEndpointUri)
throw (AxisTransportException)
{
    bool bUpdateURL = false;

    // Get the current channel URI
    if (m_pChannel->getURL ())
    {
        // Does the new URI equal the existing channel URI?
        if (strcmp (m_pChannel->getURL (), pcEndpointUri) != 0)
        {
            // There is a new URI.
            bUpdateURL = true;
        }
    }
    else
    {
        bUpdateURL = true;
    }


    // If there is a new URI, then this flag will be set.  Depending on whether
    // GSKit is available, if the new URI is a secure connection, a secure
    // channel will be opened.  If GSKit is not available and the URL requires
    // a secure connection then an exeption will be thrown.
    if (bUpdateURL)
    {
        m_pChannel->setURL (pcEndpointUri);

        m_bReopenConnection = true;

        /*
        // Check if the new URI requires SSL (denoted by the https prefix).
        if ((m_pChannel->getURLObject ()).getProtocol () == URL::https)
        {
            m_bChannelSecure = false;

            // URI requires a secure channel.  Delete the existing channel
            // (as it may not be secure) and create a new secure channel.
            delete m_pChannel;

            m_pChannel = (Channel *) new SecureChannel ();

            m_pChannel->setURL (pcEndpointUri);

            m_bChannelSecure = true;

            if (!m_bChannelSecure)
            {
                throw
                AxisTransportException
                (CLIENT_TRANSPORT_HAS_NO_SECURE_TRANSPORT_LAYER);
            }
        }
        else
        {
            // URI does not require a secure channel.  Delete the existing
            // channel if it is secure and create a new unsecure
            // channel.
            if (m_bChannelSecure)
            {
                delete m_pChannel;

                m_pChannel = new Channel ();
                m_pChannel->setURL (pcEndpointUri);
                m_bChannelSecure = false;
            }
        }
        */
    }
}

