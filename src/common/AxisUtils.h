/* -*- C++ -*- */
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
 *
 */

#if !defined(AXIS_AXISUTILS_H__OF_AXIS_INCLUDED_)
#define AXIS_AXISUTILS_H__OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <string>

using namespace std;


#define CONVERT_BUFFER_SIZE 1024
/**
 *   @class AxisUtils
 *   @brief interface for the AxisUtils class.
 *
 *   @author Susantha Kumara (skumara@virtusa.com)
 *   @author Roshan Weerasuriya (roshanw@jkcsworld.com, roshan@opensource.lk, roshan_444@yahoo.com)
 */

/*
 * Revision 1.1  2005/01/19 roshan
 * Added decodeFromBase64Binary
 */

AXIS_CPP_NAMESPACE_START

class xsd__base64Binary;

class STORAGE_CLASS_INFO AxisUtils
{
    friend class TypeMapping;
    friend class URIMapping;
    public:

	/**
	 * Decodes the given base64 string and returns it.
	 */
    static xsd__base64Binary* decodeFromBase64Binary(const AxisChar* pValue);

        /*
	 * Converts the given character pointer value to lowercase.
	 * @param pchWord The character pointer to be converted.
	 * @return The converted lowercase character value
	 */
        static char *toLowerCase (const char* pchWord);
        /*
	 * Converts the given string to lowercase.
	 * @param pchWord The string to be converted.
	 * @return The converted lowercase string value
	 */
        static string toLowerCase (const string sWord);
        /*
	 * Converts the given character pointer value to uppercase.
	 * @param pchWord The character pointer to be converted.
	 * @return The converted uppercase character value
	 */
        static char *toUpperCase (const char* pchWord);
        /*
	 * Converts the given string to uppercase.
	 * @param pchWord The string to be converted.
	 * @return The converted uppercase string value
	 */
        static string toUpperCase (const string sWord);
        /*
	 * Searchs for the specified character in the given character array and
	 * returns whether it is found or not.
	 * @param pchStringToSearch The character array to be searched.
	 * @param cCharacter The character to search.
	 */
        static bool isCharacterAvailable (const char* pchStringToSearch,
            const char cCharacter);
        /*
	 * Searchs for the specified character in the given string and returns 
	 * whether it is found or not.
	 * @param sString The string array to be searched.
	 * @param cCharacter The character to search.
	 */
        static bool isCharacterAvailable (const string &sString,
            const char cCharacter);
        /*
	 * Clears the content of passed character array
	 * @param arrCh The character array which is to be cleared.
	 * @param iSize The size of the array which is to be cleared.
	 */
        static int clearArray (char* arrCh, int iSize);
        static void initialize ();
        static const AxisXMLCh* ToAxisXMLCh (const AxisChar* pch);
        AxisUtils ();
        virtual ~ AxisUtils ();
        /* any usefull static const AxisXMLCh strings. */

    private:
        static const AxisXMLCh *Convert (const AxisChar * pch);
        static AxisXMLCh m_Buffer[CONVERT_BUFFER_SIZE];

};

AXIS_CPP_NAMESPACE_END

#endif 
