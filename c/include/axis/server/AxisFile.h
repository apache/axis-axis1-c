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
 
#if !defined(__AXIS_AXISFILE_H_OF_AXIS_INCLUDED__)
#define __AXIS_AXISFILE_H_OF_AXIS_INCLUDED__
#include <axis/server/GDefine.h>
#include <stdio.h>

/**
 *   @class AxisFile
 *   @brief class for allocating file resources for Axis C++
 *   
 *   The purpose of this class is to provide a mechanism which allows Axis C++
 *   to use file resources without worrying about releasing resources.
 *   How to use this class:
 *   When you need the file resource inside a method do as following
 *   AxisFile fileConfig;
 *   fileConfig.fileOpen("char* file name parameter", "<char* file Permission parameter")
 *   fileGet(<char* line>, <int buffersize>) etc
 *   No need to worry about file closing because when fileConfig go out of local scope
 *   it's destructor is called and inside it fclose is called
 *
 *   @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 */
class AxisFile
{
public:
    /**
     *   Default constructor
     */
    AxisFile()
    {
    }

    /**
     *    Constructor with one paratmer
     *    @param pointer to a FILE 
     */ 
    AxisFile(FILE* pFILEParamFile)
    {
        pFILEFile = pFILEParamFile;
    }

    /**   Use this to open a file
     *    @param file name
     *    @param file permission
     *    @return error code
     */
    int fileOpen(const char* sFileName, const char* sFilePerm)
    {
        if ((pFILEFile = fopen (sFileName, sFilePerm)) == NULL)
            return AXIS_FAIL;
        return AXIS_SUCCESS;
    }

    /**   Use this to read a line from the file
     *    @param char buffer into which line is read
     *    @param buffer size
     *    @return error code
     */
    int fileGet(char* sLine, int iBufferSize)
    {
        if(fgets (sLine, iBufferSize, pFILEFile) != NULL)
            return AXIS_SUCCESS;
        return AXIS_FAIL;
    }

    /**   Use this to write a line to the file
     *    @param char buffer to be written to the file
     */
    int filePuts (const char* pcWrite)
    {
        if (-1 < fputs(pcWrite, pFILEFile))
			return AXIS_SUCCESS;
		return AXIS_FAIL;
    }

    /**   Use this flush the buffer 
     */
    int fileFlush ()
    {
        if (0 == fflush(pFILEFile))
			return AXIS_SUCCESS;
		return AXIS_FAIL;
    }
    
    ~AxisFile()
    {
        if(pFILEFile)
            fclose(pFILEFile);
    }

private:
    FILE* pFILEFile;    
};
#endif

