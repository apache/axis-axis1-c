/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */
package javax.xml.soap;

import javax.activation.DataHandler;

import java.io.IOException;
import java.io.OutputStream;

import java.util.Iterator;

/**
 * <P>The root class for all SOAP messages. As transmitted on the
 * "wire", a SOAP message is an XML document or a MIME message
 * whose first body part is an XML/SOAP document.</P>
 *
 * <P>A <CODE>SOAPMessage</CODE> object consists of a SOAP part
 * and optionally one or more attachment parts. The SOAP part for
 * a <CODE>SOAPMessage</CODE> object is a <CODE>SOAPPart</CODE>
 * object, which contains information used for message routing and
 * identification, and which can contain application-specific
 * content. All data in the SOAP Part of a message must be in XML
 * format.</P>
 *
 * <P>A new <CODE>SOAPMessage</CODE> object contains the following
 * by default:</P>
 *
 * <UL>
 *  <LI>A <CODE>SOAPPart</CODE> object</LI>
 *
 *  <LI>A <CODE>SOAPEnvelope</CODE> object</LI>
 *
 *  <LI>A <CODE>SOAPBody</CODE> object</LI>
 *
 *  <LI>A <CODE>SOAPHeader</CODE> object</LI>
 * </UL>
 * The SOAP part of a message can be retrieved by calling the
 * method <CODE>SOAPMessage.getSOAPPart()</CODE>. The <CODE>
 * SOAPEnvelope</CODE> object is retrieved from the <CODE>
 * SOAPPart</CODE> object, and the <CODE>SOAPEnvelope</CODE>
 * object is used to retrieve the <CODE>SOAPBody</CODE> and <CODE>
 * SOAPHeader</CODE> objects.
 * <PRE>
 * SOAPPart sp = message.getSOAPPart();
 * SOAPEnvelope se = sp.getEnvelope();
 * SOAPBody sb = se.getBody();
 * SOAPHeader sh = se.getHeader();
 * </PRE>
 *
 * <P>In addition to the mandatory <CODE>SOAPPart</CODE> object, a
 * <CODE>SOAPMessage</CODE> object may contain zero or more <CODE>
 * AttachmentPart</CODE> objects, each of which contains
 * application-specific data. The <CODE>SOAPMessage</CODE>
 * interface provides methods for creating <CODE>
 * AttachmentPart</CODE> objects and also for adding them to a
 * <CODE>SOAPMessage</CODE> object. A party that has received a
 * <CODE>SOAPMessage</CODE> object can examine its contents by
 * retrieving individual attachment parts.</P>
 *
 * <P>Unlike the rest of a SOAP message, an attachment is not
 * required to be in XML format and can therefore be anything from
 * simple text to an image file. Consequently, any message content
 * that is not in XML format must be in an <CODE>
 * AttachmentPart</CODE> object.</P>
 *
 * <P>A <CODE>MessageFactory</CODE> object creates new <CODE>
 * SOAPMessage</CODE> objects. If the <CODE>MessageFactory</CODE>
 * object was initialized with a messaging Profile, it produces
 * <CODE>SOAPMessage</CODE> objects that conform to that Profile.
 * For example, a <CODE>SOAPMessage</CODE> object created by a
 * <CODE>MessageFactory</CODE> object initialized with the ebXML
 * Profile will have the appropriate ebXML headers.</P>
 * @see MessageFactory MessageFactory
 * @see AttachmentPart AttachmentPart
 */
public abstract class SOAPMessage {

    /**  */
    public SOAPMessage() {}

    /**
     * Retrieves a description of this <CODE>SOAPMessage</CODE>
     * object's content.
     * @return  a <CODE>String</CODE> describing the content of this
     *     message or <CODE>null</CODE> if no description has been
     *     set
     * @see #setContentDescription(java.lang.String) setContentDescription(java.lang.String)
     */
    public abstract String getContentDescription();

    /**
     * Sets the description of this <CODE>SOAPMessage</CODE>
     * object's content with the given description.
     * @param  description a <CODE>String</CODE>
     *     describing the content of this message
     * @see #getContentDescription() getContentDescription()
     */
    public abstract void setContentDescription(String description);

    /**
     * Gets the SOAP part of this <CODE>SOAPMessage</CODE> object.
     *
     *
     *   <P>If a <CODE>SOAPMessage</CODE> object contains one or
     *   more attachments, the SOAP Part must be the first MIME body
     *   part in the message.</P>
     * @return the <CODE>SOAPPart</CODE> object for this <CODE>
     *     SOAPMessage</CODE> object
     */
    public abstract SOAPPart getSOAPPart();

    /**
     * Removes all <CODE>AttachmentPart</CODE> objects that have
     *   been added to this <CODE>SOAPMessage</CODE> object.
     *
     *   <P>This method does not touch the SOAP part.</P>
     */
    public abstract void removeAllAttachments();

    /**
     * Gets a count of the number of attachments in this
     * message. This count does not include the SOAP part.
     * @return  the number of <CODE>AttachmentPart</CODE> objects
     *     that are part of this <CODE>SOAPMessage</CODE>
     *     object
     */
    public abstract int countAttachments();

    /**
     * Retrieves all the <CODE>AttachmentPart</CODE> objects
     * that are part of this <CODE>SOAPMessage</CODE> object.
     * @return  an iterator over all the attachments in this
     *     message
     */
    public abstract Iterator getAttachments();

    /**
     * Retrieves all the <CODE>AttachmentPart</CODE> objects
     * that have header entries that match the specified headers.
     * Note that a returned attachment could have headers in
     * addition to those specified.
     * @param   headers a <CODE>MimeHeaders</CODE>
     *     object containing the MIME headers for which to
     *     search
     * @return an iterator over all attachments that have a header
     *     that matches one of the given headers
     */
    public abstract Iterator getAttachments(MimeHeaders headers);

    /**
     * Adds the given <CODE>AttachmentPart</CODE> object to this
     * <CODE>SOAPMessage</CODE> object. An <CODE>
     * AttachmentPart</CODE> object must be created before it can be
     * added to a message.
     * @param  attachmentpart an <CODE>
     *     AttachmentPart</CODE> object that is to become part of
     *     this <CODE>SOAPMessage</CODE> object
     * @throws java.lang.IllegalArgumentException
     */
    public abstract void addAttachmentPart(AttachmentPart attachmentpart);

    /**
     * Creates a new empty <CODE>AttachmentPart</CODE> object.
     * Note that the method <CODE>addAttachmentPart</CODE> must be
     * called with this new <CODE>AttachmentPart</CODE> object as
     * the parameter in order for it to become an attachment to this
     * <CODE>SOAPMessage</CODE> object.
     * @return  a new <CODE>AttachmentPart</CODE> object that can be
     *     populated and added to this <CODE>SOAPMessage</CODE>
     *     object
     */
    public abstract AttachmentPart createAttachmentPart();

    /**
     * Creates an <CODE>AttachmentPart</CODE> object and
     * populates it using the given <CODE>DataHandler</CODE>
     * object.
     * @param   datahandler  the <CODE>
     *     javax.activation.DataHandler</CODE> object that will
     *     generate the content for this <CODE>SOAPMessage</CODE>
     *     object
     * @return a new <CODE>AttachmentPart</CODE> object that
     *     contains data generated by the given <CODE>
     *     DataHandler</CODE> object
     * @throws java.lang.IllegalArgumentException if
     *     there was a problem with the specified <CODE>
     *     DataHandler</CODE> object
     * @see DataHandler DataHandler
     * @see DataContentHandler DataContentHandler
     */
    public AttachmentPart createAttachmentPart(DataHandler datahandler) {

        AttachmentPart attachmentpart = createAttachmentPart();

        attachmentpart.setDataHandler(datahandler);

        return attachmentpart;
    }

    /**
     * Returns all the transport-specific MIME headers for this
     * <CODE>SOAPMessage</CODE> object in a transport-independent
     * fashion.
     * @return a <CODE>MimeHeaders</CODE> object containing the
     *     <CODE>MimeHeader</CODE> objects
     */
    public abstract MimeHeaders getMimeHeaders();

    /**
     * Creates an <CODE>AttachmentPart</CODE> object and
     * populates it with the specified data of the specified content
     * type.
     * @param   content  an <CODE>Object</CODE>
     *     containing the content for this <CODE>SOAPMessage</CODE>
     *     object
     * @param   contentType a <CODE>String</CODE>
     *     object giving the type of content; examples are
     *     "text/xml", "text/plain", and "image/jpeg"
     * @return a new <CODE>AttachmentPart</CODE> object that
     *     contains the given data
     * @throws java.lang.IllegalArgumentException if the contentType does not match the type of the content
     *     object, or if there was no <CODE>
     *     DataContentHandler</CODE> object for the given content
     *     object
     * @see DataHandler DataHandler
     * @see DataContentHandler DataContentHandler
     */
    public AttachmentPart createAttachmentPart(Object content,
                                               String contentType) {

        AttachmentPart attachmentpart = createAttachmentPart();

        attachmentpart.setContent(content, contentType);

        return attachmentpart;
    }

    /**
     * Updates this <CODE>SOAPMessage</CODE> object with all the
     *   changes that have been made to it. This method is called
     *   automatically when a message is sent or written to by the
     *   methods <CODE>ProviderConnection.send</CODE>, <CODE>
     *   SOAPConnection.call</CODE>, or <CODE>
     *   SOAPMessage.writeTo</CODE>. However, if changes are made to
     *   a message that was received or to one that has already been
     *   sent, the method <CODE>saveChanges</CODE> needs to be
     *   called explicitly in order to save the changes. The method
     *   <CODE>saveChanges</CODE> also generates any changes that
     *   can be read back (for example, a MessageId in profiles that
     *   support a message id). All MIME headers in a message that
     *   is created for sending purposes are guaranteed to have
     *   valid values only after <CODE>saveChanges</CODE> has been
     *   called.
     *
     *   <P>In addition, this method marks the point at which the
     *   data from all constituent <CODE>AttachmentPart</CODE>
     *   objects are pulled into the message.</P>
     * @throws  SOAPException if there
     *     was a problem saving changes to this message.
     */
    public abstract void saveChanges() throws SOAPException;

    /**
     * Indicates whether this <CODE>SOAPMessage</CODE> object
     * has had the method <CODE>saveChanges</CODE> called on
     * it.
     * @return <CODE>true</CODE> if <CODE>saveChanges</CODE> has
     *     been called on this message at least once; <CODE>
     *     false</CODE> otherwise.
     */
    public abstract boolean saveRequired();

    /**
     * Writes this <CODE>SOAPMessage</CODE> object to the given
     *   output stream. The externalization format is as defined by
     *   the SOAP 1.1 with Attachments specification.
     *
     *   <P>If there are no attachments, just an XML stream is
     *   written out. For those messages that have attachments,
     *   <CODE>writeTo</CODE> writes a MIME-encoded byte stream.</P>
     * @param   out the <CODE>OutputStream</CODE>
     *     object to which this <CODE>SOAPMessage</CODE> object will
     *     be written
     * @throws  SOAPException  if there was a problem in
     *     externalizing this SOAP message
     * @throws  IOException  if an I/O error
     *     occurs
     */
    public abstract void writeTo(OutputStream out)
        throws SOAPException, IOException;
}
