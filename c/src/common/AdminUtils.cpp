#include <axis/server/AdminUtils.h>
#include "../wsdd/WSDDDeployment.h"

extern WSDDDeployment* g_pWSDDDeployment;

AdminUtils::AdminUtils()
{

}

AdminUtils::~AdminUtils()
{

}

int AdminUtils::UpdateWSDD(AxisChar* wsdd)
{
	return g_pWSDDDeployment->UpdateWSDD(wsdd);	
}