/* -*- C++ -*- */

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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <iostream>
#include <stdio.h>
#include <map>
#include "ServerHelper.h"
#include "../../common/AxisUtils.h"

using namespace std;

int getSeperatedHTTPParts(string sClientReqStream, string& sHTTPHeaders, string& sHTTPBody, map<HTTP_MAP_KEYWORDS, HTTP_MAP_TYPE*> *map_HTTP_Headers) {
			
	int iFindStartLocation=0;
	string sTmpHttpHeader= "";
	int iLocation=0;
	bool bContinue= true;
	int iGap;
	bool bFirstTime= true;

	/*
	 *Extracts the HTTP Headers from the stream
	 */
	while(bContinue) {
		
		sTmpHttpHeader="";
		iLocation = 0;
		
		iLocation = sClientReqStream.find('\n', iFindStartLocation);
	
		iGap = iLocation-iFindStartLocation;
		if (iGap == 1) {
			sTmpHttpHeader = sClientReqStream.substr(iFindStartLocation, (iLocation-iFindStartLocation));		
		} else {
			sTmpHttpHeader = sClientReqStream.substr(iFindStartLocation, ((iLocation-iFindStartLocation)-1));		
		}				
		
		if(sTmpHttpHeader.size() == 1) {					
			bContinue= false;
		} else {	
			
			/*------------do we need this now ? ------------------*/
			if(bFirstTime) {
				sHTTPHeaders += sTmpHttpHeader;
				bFirstTime = false;
			} else {
				sHTTPHeaders += "|" + sTmpHttpHeader;
			}	
			/*-------------end-----------------*/
			
			initializeHeaderMap(sTmpHttpHeader, map_HTTP_Headers);
			//initializeHeaderMap(map_HTTP_Headers);
		}

		iFindStartLocation = iLocation+1;
	}

	/*
	 *Extracts the HTTP Body from the stream
	 */
	int iFullRequestLength= sClientReqStream.size();	
	sHTTPBody = sClientReqStream.substr(iFindStartLocation, iFullRequestLength);		

	// return a status code : 1- SUCCESS
	return 1;
}

int	initializeHeaderMap(const string &sHeaderLine, map<HTTP_MAP_KEYWORDS, HTTP_MAP_TYPE*> *map_HTTP_Headers) {

	bool bIsHttpHeader = true;
	int iHeaderLineLength = sHeaderLine.size();
	
	if (!AxisUtils::isCharacterAvailable(sHeaderLine, ':')) {
		bIsHttpHeader = false;
	}
	
	if (!bIsHttpHeader) {
		/* 
		Here we expect a Header line with the pattern "POST axis/Calculatoer HTTP/1.1". 
		The logic is based on this pattern
		*/

		int iLocation = 0;
		int iFindStartLocation = 0;
		int iGap= 0;		

		for (int iRoundNo= 0; iRoundNo<3; iRoundNo++) {
			/*
			 *Seperate the Method, URI, and HTTP Version from the string HeaderLine and add them to the map
			 */
			
			string *sTmpValue = new string("");
			
			if (iRoundNo == 2) {
				iGap = (iHeaderLineLength) - iFindStartLocation;
			} else {
				iLocation = sHeaderLine.find(' ', iFindStartLocation);
			
				iGap = iLocation-iFindStartLocation;
			}
			if (iGap == 0) {
				*sTmpValue = sHeaderLine.substr(iFindStartLocation, 1);		
			} else {
				*sTmpValue = sHeaderLine.substr(iFindStartLocation, iGap);		
			}

			iFindStartLocation = iLocation+1;

			uHttpMapContent* objuHttpMapContent = (uHttpMapContent*)malloc(sizeof(uHttpMapContent));
			HTTP_MAP_TYPE* objHTTP_MAP_Value = (HTTP_MAP_TYPE*)malloc(sizeof(HTTP_MAP_TYPE));

			switch (iRoundNo) {
			/*case 0:
				/*sTmpValue = AxisUtils::toLowerCase(sTmpValue);
				if (sTmpValue == "post") {*/
			/*	if (sTmpValue == "POST") {
					objuHttpMapContent.eHTTP_KEYWORD = HK_POST;
					
				/*if (sTmpValue == "get") {*/
			/*	} else if (sTmpValue == "GET") {
					objuHttpMapContent.eHTTP_KEYWORD = HK_GET;
				}
				objHTTP_MAP_Value.eCONTENT_TYPE= HTTP_KEYWORD_TYPE;
				objHTTP_MAP_Value.objuHttpMapContent =  objuHttpMapContent;
				(*map_HTTP_Headers)[HMK_METHOD] = objHTTP_MAP_Value;
				break;*/
			case 1:
				objuHttpMapContent->msValue = sTmpValue->c_str();
				objHTTP_MAP_Value->eCONTENT_TYPE= STRING_TYPE;
				objHTTP_MAP_Value->objuHttpMapContent =  objuHttpMapContent;
				(*map_HTTP_Headers)[HMK_URI] = objHTTP_MAP_Value;
				printf("in case1 = %s\n", (*map_HTTP_Headers)[HMK_URI]->objuHttpMapContent->msValue);
				break;
			/*case 2:
				/*sTmpValue = AxisUtils::toLowerCase(sTmpValue);
				if (sTmpValue == "http/1.1") {*/
		/*		if (sTmpValue == "HTTP/1.1") {
					objuHttpMapContent.eHTTP_KEYWORD = HK_HTTP_1_1;
					
				} else {
					objuHttpMapContent.eHTTP_KEYWORD = HK_HTTP_UNKNOWN_VERSION;
				}
				objHTTP_MAP_Value.eCONTENT_TYPE= HTTP_KEYWORD_TYPE;
				objHTTP_MAP_Value.objuHttpMapContent =  objuHttpMapContent;
				(*map_HTTP_Headers)[HMK_VERSION] = objHTTP_MAP_Value;
				break;*/
			}			
		}
	} else {
		/*
		 *	Seperate the Header name and value from ":" and put them to the map
		 */
		//map_HTTP_Headers[HK_URI] = "extracted Value";
	}

	return 1;
}

int getHttpHeader(HTTP_MAP_KEYWORDS eKeyWord, map<HTTP_MAP_KEYWORDS, HTTP_MAP_TYPE*> *map_HTTP_Headers, HTTP_MAP_TYPE *objMapContent) {
	
	int iStatus = FAIL;

	if (map_HTTP_Headers->find(eKeyWord) != map_HTTP_Headers->end()) {
		printf("debgu 1 = %s\n", (*map_HTTP_Headers)[eKeyWord]->objuHttpMapContent->msValue);
		objMapContent = (HTTP_MAP_TYPE*) malloc(sizeof((*map_HTTP_Headers)[eKeyWord]));
		objMapContent = (*map_HTTP_Headers)[eKeyWord];

		iStatus = SUCCESS;
	}
	
	return iStatus;
}