#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int getSeperatedHTTPParts(string sClientReqStream, string& sHTTPHeaders, string& sHTTPBody) {
			
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
			if(bFirstTime) {
				sHTTPHeaders += sTmpHttpHeader;
				bFirstTime = false;
			} else {
				sHTTPHeaders += "|" + sTmpHttpHeader;
			}													
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
