// File.h: interface for the File class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILE_H__E30356C1_DD4A_4FCF_A529_713455BB6E02__INCLUDED_)
#define AFX_FILE_H__E30356C1_DD4A_4FCF_A529_713455BB6E02__INCLUDED_

#include <string>
#include <fstream>
using namespace std;

class File : public ofstream
{
public:
	int Write(char* pChars);
	File(const string& sFileName);
	virtual ~File();
};

#endif // !defined(AFX_FILE_H__E30356C1_DD4A_4FCF_A529_713455BB6E02__INCLUDED_)
