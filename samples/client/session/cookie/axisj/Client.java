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

/*
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */


package axisj; 

import org.apache.axis.AxisFault;
import org.apache.axis.client.Stub;

class Client {

public static void main(String args[]) throws Exception {
        Total client = new TotalServiceLocator().getTotal(new java.net.URL("http://localhost:9090/axis/services/Total"));
        ((TotalSoapBindingStub)client).setMaintainSession (true);
        System.out.println( "setMaintainSession = true" );
        System.out.println( client.inc(10) );
        System.out.println( client.inc(10) );
        ((TotalSoapBindingStub)client).setMaintainSession (false);
        System.out.println( "setMaintainSession = false" );
        System.out.println( client.inc(10) );
        System.out.println( client.inc(10) );
        ((TotalSoapBindingStub)client).setMaintainSession (true);
        System.out.println( "setMaintainSession = true" );
        System.out.println( client.inc(10) );
        System.out.println( client.inc(10) );
}

}

