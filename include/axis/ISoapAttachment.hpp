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
 * @author Nithyakala Thangarajah (nithya@opensource.lk)
 * @author Rangika Mendis (rangika@opensource.lk) 
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshan@jkcsworld.com)
 *
 */

/**
 * @file ISoapAttachment.hpp
 */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED TO THE        */
/* C-EQUIVALENT HEADER FILE IN SUPPORT OF THE C-BINDING INTERFACES.   */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */


#if !defined(AFX_ISOAPATTACHMENT_H__8B3A65FD_40A6_45B2_A8C5_295DE4222952__INCLUDED_)
#define AFX_ISOAPATTACHMENT_H__8B3A65FD_40A6_45B2_A8C5_295DE4222952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <axis/AxisUserAPI.hpp>

AXIS_CPP_NAMESPACE_START

/**
 * @enum AXIS_ATTACHMENT_ENCODING_TYPE
 * Enumeration of Attachment encoding types.
 */
typedef enum 
{ 
    /**
     * Base64 encoding
     */
    AXIS_BASE64=0,
    
    /**
     * Binary encoding
     */
    AXIS_BINARY = 1
} AXIS_ATTACHMENT_ENCODING_TYPE;

#define AXIS_CONTENT_ID                  "Content-Id"
#define AXIS_CONTENT_TYPE                "Content-Type"
#define AXIS_CONTENT_TRANSFER_ENCODING   "Content-Transfer-Encoding"
#define AXIS_CONTENT_LOCATION            "Content-Location"

/**
 * @class ISoapAttachment
 * 
 * Interface class for SOAP attachments.
 */
class STORAGE_CLASS_INFO ISoapAttachment  
{
public:
    /**
     * Get and return ID associated with the current instance.
     * 
     * @return Attachment ID.
     */
    virtual const char* getAttachmentId()=0;

    /**
     * Allows the user to add the Body to the current attachment.
     * 
     * @param objBody Base64Binary encoded attachment body.
     */
    virtual void addBody(xsd__base64Binary* objBody)=0;    

    /**
     * Allows the user to add headers to the current attachments.
     * 
     * @param pchName header name.
     * @param pchValue header value.
     */
    virtual void addHeader(const char* pchName, 
                           const char* pchValue)=0;

    /**
     * Allows the user to get the Attachment Body
     * 
     * @return Base64Binary encoded body.
     */
    virtual xsd__base64Binary* getBody()=0;    

    /**
     * Allows the user to get the required Attachment Header
     *
     * @param pchName The name of the required Attachment Header
     * @return Value of the required attachment header.
     */
    virtual const char* getHeader(const char* pchName)=0;

    /**
     * Destructor
     */
    virtual ~ISoapAttachment() {};

};

AXIS_CPP_NAMESPACE_END

#endif // !defined(AFX_ISOAPATTACHMENT_H__8B3A65FD_40A6_45B2_A8C5_295DE4222952__INCLUDED_)

