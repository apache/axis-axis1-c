Axis J2ME RPC - JSR 172 J2ME Web Services RPC implementation

This implementation uses kXML2 hosted at http://sourceforge.net/projects/kxml/. 

kXML2's license is BSD. You can read it at kXML2.LICENSE in this directory.

Here's some hints for you to build an runtime implementation from source codes for a specific J2ME platform.

1. Choose CLDC 1.0 or else. 
2. Compile src/shared and configuration/your_choice together with kxml2.jar and xmlpull_1_1_3_1.jar.
3. Deploy the compiled classes, kxml2.jar and xmlpull_1_1_3_1.jar to your desired J2ME platform.

src/tool has WsdlToJ2me and its necessary classes. In order to build it, make your own build.properties from build.properties.sample and simply run "ant" with the latest Axis from CVS HEAD.

How to use WsdlToJ2me is basically the same as WSDL2Java in Axis. Please refer to the user guide of Axis.

Note: some emulation environments and real devices prohibit you from deploying java.rmi package for security. Please consult with their providers on the issue, or you can use a less-constrained development kit such as XVM from http://www.developerzone.co.kr/ENGLISH/ . 

Axis J2ME RPC is tested on XVM 1.3.1 (emulator, CLDC 1.0) and Zaurus SL760 (device, CDC 1.0).

More documentation will be post for building and testing.

Looking forward to your help,

Ias