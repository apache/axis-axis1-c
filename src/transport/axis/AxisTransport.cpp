#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include "../../../common/Packet.h"
#include "AxisTransport.h"

AxisTransport::AxisTransport(Ax_soapstream* pSoap)
{
    m_pSoap = pSoap;
    m_pSender = NULL;
    m_pReceiver = NULL;
    m_pHttpTransport = NULL;       
}

AxisTransport::~AxisTransport()
{
    if(m_pSender)
        delete m_pSender;
    if(m_pReceiver)
        delete m_pReceiver;
    if(m_pHttpTransport)
        delete m_pHttpTransport;
}

int AxisTransport::OpenConnection()
{
    //Step 1 - Open Transport layer connection taking into account protocol and endpoint URI in m_Soap
    Url objUrl(m_pSoap->so.http.uri_path);
    TransportFactory objTransportFactory;
    m_pHttpTransport = objTransportFactory.getTransport(objUrl);
    if(m_pHttpTransport->Init())
    {
       m_pSender = new Sender(m_pHttpTransport);
       m_pReceiver = new Receiver(m_pHttpTransport);
       //Step 2 - Set Created streams to m_Soap.str.ip_stream and m_Soap.str.op_stream
       m_pSoap.str.op_stream = m_pSender;
       m_pSoap.str.ip_stream = m_pReceiver;
       
       //Step 3 - Add function pointers to the m_Soap structure
       m_pSoap.transport.pGetFunct = Get_bytes;
       m_pSoap.transport.pSendFunct = Send_bytes;
       m_pSoap.transport.pGetTrtFunct = Receive_transport_information;
       m_pSoap.transport.pSendTrtFunct = Send_transport_information; 
    }
    else
        return FAIL;
}        

void AxisTransport::CloseConnection()
{
//Step 1 - Close 2 streams
	//Step 2 - Possibly delete the streams
	//Step 3 - Set function pointers in the m_Soap structure to NULL;
	m_Soap.transport.pGetFunct = NULL;
	m_Soap.transport.pSendFunct = NULL;
	m_Soap.transport.pGetTrtFunct = NULL;
	m_Soap.transport.pSendTrtFunct = NULL;
}

int AxisTransport::Send_bytes(const char* pSendBuffer, const void* pStream)
{
    Sender* pSender = (Sender*) pStream;
    if(pSender->Send(pSendBuffer))
        return SUCCESS;
    return FAIL;
    
}

int AxisTransport::Get_bytes(char* pRecvBuffer, int nBuffSize, int* pRecvSize, const void* pStream)
{
    Receiver* pReceiver = (Receiver*) pStream;
    const string& strReceive =  pReceiver->Recv();
    int nLen = strlen(strReceive.c_str());
    if(nLen < nBuffSize)
    {
        strcpy(pRecvBuffer, strReceive.c_str());
        *pRecvSize = nLen;
        return SUCCESS;
    }
    else
        return FAIL;
    
}

int AxisTransport::Send_transport_information(void* pSoapStream)
{
    Ax_soapstream* pSoapStream = (Ax_soapstream*) pSoapStream;    
    
}

int AxisTransport::Receive_transport_information(void* pSoapStream)
{
}