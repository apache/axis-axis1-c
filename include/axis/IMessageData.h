/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
#ifndef IMESSAGEDATA_INCLUDED
#define IMESSAGEDATA_INCLUDED

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


#include <axis/GDefine.h>
#include <axis/IWrapperSoapDeSerializer.h>
#include <axis/IWrapperSoapSerializer.h>

/**
 * @file IMessageData.hpp
 */
/**
 *   @class IMessageData
 *   @brief interface for the IMessageData class.
 */
/**
 * Destructor
 */
AXISC_STORAGE_CLASS_INFO
void axiscMessageDataDestroy(AXISCHANDLE messageData);

/**
 * This method provides access to the AdminUtils, providing a mechanism for
 * deploying and undeploying services.
 *
 * It is intended that only the AdminService will make use of this API.
 *
 * @param pIAdminUtils will be updated with an IAdminUtils object
 */
AXISC_STORAGE_CLASS_INFO
void axiscMessageDataGetAdminUtils(AXISCHANDLE messageData, AXISC_IAdminUtils * * pIAdminUtils);

/**
 *  This method stores the given property value with the key, inside the
 *  MessageData object.
 *
 *   @param pachName is the key of the property.
 *   @param pachValue is the value of the property.
 *   @param len is the size of value (pachValue).
 *   @return AXIS_SUCCESS to indicate successfull operation.
 */
AXISC_STORAGE_CLASS_INFO
int axiscMessageDataSetProperty(AXISCHANDLE messageData, const AxiscChar * pachName, 
	const void * pachValue, 
	int len);

/**
 *  This method stores the given property value with the key, inside the
 *  MessageData object. The value is a complex object.
 *
 *   @param pachName is the key of the property.
 *   @param pachValue is the value of the property.
 *   @param iObjectSize is the size of value (pachValue).
 */
AXISC_STORAGE_CLASS_INFO
void axiscMessageDataSetComplexProperty(AXISCHANDLE messageData, const AxiscChar * pachName, 
	void * pachValue, 
	int iObjectSize);

/**
 *  This method returns the matching property value (to the given
 *  corresponding key)
 *
 *  @param sName is the key of the required property.
 *  @return If it is found then matching property value is returned. If not found then it
 *      will return an empty string.
 */
AXISC_STORAGE_CLASS_INFO
const void * axiscMessageDataGetProperty(AXISCHANDLE messageData, const AxiscChar * sName);

/**
 *  This method returns the matching property value (to the given
 *  corresponding key)
 *
 *   @param  pachName is the key of the required property.
 *   @return If it is found then matching property value is returned.
 *      If not found NULL is returned.
 */
AXISC_STORAGE_CLASS_INFO
void * axiscMessageDataGetComplexProperty(AXISCHANDLE messageData, const AxiscChar * pachName);

/**
 *  Returns the current operation name.
 *
 *   @return This method will return the OperationName.
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscMessageDataGetOperationName(AXISCHANDLE messageData);

/**
 *  This method will assign the current instance of SoapSerializer
 *  to the given IWrapperSoapSerializer pointer-to-pointer.By calling this
 *  method a caller will have access to the SoapSerializer.
 *
 *  @param pIWSS is a pointer to pointer used to get access to the
 *      current instance of soapSerializer.
 */
AXISC_STORAGE_CLASS_INFO
void axiscMessageDataGetSoapSerializer(AXISCHANDLE messageData, AXISCHANDLE pIWSS);

/**
 *  This method will assign the current instance of SoapDeSerializer
 *  to the given IWrapperSoapDeSerializer pointer-to-pointer. By calling this
 *  method a caller will have access to the SoapDeSerializer.
 *
 *   @param pIWSDS is a pointer to pointer used to store the
 *      current instance of SoapDeSerializer.
 */
AXISC_STORAGE_CLASS_INFO
void axiscMessageDataGetSoapDeSerializer(AXISCHANDLE messageData, AXISCHANDLE pIWSDS);

/**
 *  This method will assign the current instance of SoapSerializer
 *  to the given IHandlerSoapSerializer pointer-to-pointer. By calling this
 *  method a caller will have access to the SoapSerializer.
 *
 *   @param  pIHandlerSoapSerializer is a pointer to pointer used to store the
 *      current instance of soapSerializer.
 */
AXISC_STORAGE_CLASS_INFO
void axiscMessageDataGetSoapSerializer(AXISCHANDLE messageData, AXISC_IHandlerSoapSerializer * * pIHandlerSoapSerializer);

/**
 *  This method will assign the current instance of SoapDeSerializer
 *  to the given IHandlerSoapDeSerializer pointer-to-pointer. By calling this
 *  method a caller will have access to the SoapDeSerializer.
 *
 *   @param pIHandlerSoapDeSerializer is a pointer to pointer used to store the
 *      current instance of soapDeSerializer.
 */
AXISC_STORAGE_CLASS_INFO
void axiscMessageDataGetSoapDeSerializer(AXISCHANDLE messageData, AXISC_IHandlerSoapDeSerializer * * pIHandlerSoapDeSerializer);

/**
 *   This method will store the given username inside the MessageData object.
 *
 *   @param m_sUserName is the value that is passed to be set.
 */
AXISC_STORAGE_CLASS_INFO
void axiscMessageDataSetUserName(AXISCHANDLE messageData, char*  m_sUserName);

/**
 * This method returns the user name.
 *
 *   @return this method will return the UserName.
 */
AXISC_STORAGE_CLASS_INFO
char*  axiscMessageDataGetUserName(AXISCHANDLE messageData);

/**
 *  This method will return a boolean value which will say whether at the time
 *  of calling this method has already passed the pivot point.
 *
 *   @return Returns true if the pivot point is past. Returns false if not.
 */
AXISC_STORAGE_CLASS_INFO
AxiscBool axiscMessageDataIsPastPivot(AXISCHANDLE messageData);

/**
 *   This method is used to set the pivot point status.
 *
 *  @param bState is the value of the state that should be set. Set true if
 *      pivot point is past. Set false if pivot point is not past yet.
 *  @return will return AXIS_SUCCESS to indicate successful operation.
 */
AXISC_STORAGE_CLASS_INFO
int axiscMessageDataSetPastPivotState(AXISCHANDLE messageData, AxiscBool bState);


#ifdef __cplusplus
 }
#endif

#endif /* IMESSAGEDATA_INCLUDED */
