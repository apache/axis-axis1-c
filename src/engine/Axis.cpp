#include "AxisEngine.h"

unsigned char chEBuf[1024];

extern "C" int process(soapstream *str)
{
  
	AxisEngine* engine = AxisEngine::GetAxisEngine();	
	int ret = FAIL;
	if (engine)
	{
		ret = engine->Process(str);
	}
	//str->op_soap = chEBuf;
	return ret;
}

