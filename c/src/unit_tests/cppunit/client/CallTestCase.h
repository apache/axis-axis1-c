// allTestCase.h: interface for the CallTestCase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALLTESTCASE_H__2F6B4B2E_EACB_4F61_93ED_AEB3DE5943DD__OF_AXIS_INCLUDED_)
#define AFX_ALLTESTCASE_H__2F6B4B2E_EACB_4F61_93ED_AEB3DE5943DD__OF_AXIS_INCLUDED_

#include "cppunit\TestCase.h"
#include "cppunit\TestSuite.h"
#include "cppunit\TestCaller.h"
#include <string>
#include <list>
#include "axis/client/Call.h"
#include "axis/soap/SoapDeSerializer.h"


using namespace CppUnit;
using namespace std;


class CallTestCase  : public TestCase
{
private:
	Call* pCall;
	//SoapDeSerializer* pSoap;
public:
	void testGetElementAsInt();
	
	void tearDown();
	void setUp();
	CallTestCase();
	virtual ~CallTestCase();
	static Test* suite();

};

#endif // !defined(AFX_ALLTESTCASE_H__2F6B4B2E_EACB_4F61_93ED_AEB3DE5943DD__OF_AXIS_INCLUDED_)
