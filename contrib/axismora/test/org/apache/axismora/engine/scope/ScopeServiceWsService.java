package org.apache.axismora.engine.scope;

import org.apache.axismora.MessageContext;
import org.apache.axismora.handlers.BasicHandler;
import org.apache.axismora.util.AxisUtils;
import org.apache.axismora.wrappers.simpleType.IntParam;

import org.apache.axis.AxisFault;
import org.apache.axis.Constants;
import org.apache.axis.message.SOAPFault;

public class ScopeServiceWsService extends BasicHandler{
    private SCOPETestWs ws;
    public ScopeServiceWsService() {
        ws = new SCOPETestWs();
    }

    public void invoke(MessageContext msgdata) {
        try {
            if("invokeCount".equals(msgdata.getMethodName().getLocalPart())){
               invokeCount(msgdata);
            }else
            throw AxisUtils.getTheAixsFault(Constants.FAULT_SOAP12_SENDER,
                                            "operation not found",
                                            null,null,null);
        } catch (Exception e) {
            e.printStackTrace();
            msgdata.setSoapFault(new SOAPFault(AxisUtils.getTheAixsFault(Constants.FAULT_SOAP12_SENDER,
                                            e.getMessage(),
                                            null,null,null)));
        }
    }
    public void invokeCount(MessageContext msgdata)throws AxisFault{
        msgdata.setSoapBodyContent(new IntParam(ws.invokeCount()));
    }
}
