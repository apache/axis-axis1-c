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
 */
/**
 * @file ISoapAttachment.hpp
 */
#ifndef ISOAPATTACHMENT_INCLUDED
#define ISOAPATTACHMENT_INCLUDED

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE C APIS.                                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifdef __cplusplus
 extern "C" {
#endif


#include <axis/AxisUserAPI.h>

/**
 * @enum AXIS_ATTACHMENT_ENCODING_TYPE
 * Enumeration of Attachment encoding types.
 */
typedef enum 
{ 
    /**
     * Base64 encoding
     */
    AXISC_BASE64=0,
    
    /**
     * Binary encoding
     */
    AXISC_BINARY = 1
} AXISC_AXISC_ATTACHMENT_ENCODING_TYPE;


/**
 * @class ISoapAttachment
 *
 * Interface class for SOAP attachments.
 */
/**
 * Get and return ID associated with the current instance.
 *
 * @return Attachment ID.
 */
AXISC_STORAGE_CLASS_INFO
const char * axiscSoapAttachmentGetAttachmentId(AXISCHANDLE soapAttachment);

/**
 * Allows the user to add the Body to the current attachment.
 *
 * @param objBody Base64Binary encoded attachment body.
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapAttachmentAddBody(AXISCHANDLE soapAttachment, xsdc__base64Binary * objBody);

/**
 * Allows the user to add headers to the current attachments.
 *
 * @param pchName header name.
 * @param pchValue header value.
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapAttachmentAddHeader(AXISCHANDLE soapAttachment, const char * pchName, 
	const char * pchValue);

/**
 * Allows the user to get the Attachment Body
 *
 * @return Base64Binary encoded body.
 */
AXISC_STORAGE_CLASS_INFO
xsdc__base64Binary * axiscSoapAttachmentGetBody(AXISCHANDLE soapAttachment);

/**
 * Allows the user to get the required Attachment Header
 *
 * @param pchName The name of the required Attachment Header
 * @return Value of the required attachment header.
 */
AXISC_STORAGE_CLASS_INFO
const char * axiscSoapAttachmentGetHeader(AXISCHANDLE soapAttachment, const char * pchName);

/**
 * Destructor
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapAttachmentDestroy(AXISCHANDLE soapAttachment);


#ifdef __cplusplus
 }
#endif

#endif /* ISOAPATTACHMENT_INCLUDED */
