/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */
/* AxisUserAPI.h: interface for the AxisUserAPI class. */

#if !defined(AFX_AXISWRAPPERAPI_H__6E27008D_DCA0_4F28_AC82_FEEBE1A1CBBB__INCLUDED_)
#define AFX_AXISWRAPPERAPI_H__6E27008D_DCA0_4F28_AC82_FEEBE1A1CBBB__INCLUDED_

#include "GDefine.h"
#include "IWrapperSoapDeSerializer.h"
#include "IWrapperSoapSerializer.h"
#include "BasicHandler.h"

/**
 * Function that deserializes a custom type 
 */
typedef int (* AXIS_DESERIALIZE_FUNCT)(void*, IWrapperSoapDeSerializer*);
/**
 * Function used to create a custom type. bArray is true if array of objects to be
 * created. Then nSize is the size of that array.
 */
typedef void* (* AXIS_OBJECT_CREATE_FUNCT)(bool bArray, int nSize);
/**
 * Function used to delete a custom type. bArray is true if void* is a pointer to an array. 
 * Then nSize is the size of that array.
 */
typedef void (* AXIS_OBJECT_DELETE_FUNCT)(void*, bool bArray, int nSize);
/**
 * Function that serializes a custom type. bArray indicates that the object in void* is 
 * an element of an array (note that void* is not itself an array).
 */
typedef int (* AXIS_SERIALIZE_FUNCT)(void*, IWrapperSoapSerializer*, bool bArray);
/**
 * Function that is used to get the size of an object of a custom type.
 */
typedef int (* AXIS_OBJECT_SIZE_FUNCT)(void);


#endif /* !defined(AFX_AXISWRAPPERAPI_H__6E27008D_DCA0_4F28_AC82_FEEBE1A1CBBB__INCLUDED_) */
