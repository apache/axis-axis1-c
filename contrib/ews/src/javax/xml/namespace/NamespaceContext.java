/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights 
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
 * 4. The name "Apache Software Foundation" must
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
 */
package javax.xml.namespace;

/** <p>The <code>NamespaceContext</code> interface is a helper tool for
 * XML parsing applications which need to know the mappings between XML
 * namespace prefixes and namespace URI's. As such, it is closely related
 * to the events
 * {@link org.xml.sax.ContentHandler#startPrefixMapping(String,String)},
 * and {@link org.xml.sax.ContentHandler#endPrefixMapping(String)} in
 * {@link org.xml.sax.ContentHandler}.</p>
 * <p>In what follows, it is important to note, that a single prefix
 * can only be mapped to a single namespace URI at any time. However,
 * the converse is not true: Multiple prefixes can be mapped to the
 * same namespace URI's.</p>
 * <p>For example, in the case of an XML Schema parser, an instance
 * of <code>NamespaceContext</code> might be used to resolve the namespace
 * URI's of referenced data types, and element or attribute names, which
 * are typically given as qualified names, including a prefix and a local
 * name.</p>
 *
 * @author JSR-31
 * @since JAXB 1.0
 */
public interface NamespaceContext {
  /** <p>Given a prefix, returns the namespace URI associated with the prefix.
   * More precisely, the following rules apply:
   * <table border="1">
   *   <tr><th>Prefix (Input)</th><th>Namespace URI (Output)</th></tr>
   *   <tr><th>{@link javax.xml.XMLConstants#DEFAULT_NS_PREFIX} ("")</th>
   *     <td>The current default namespace URI or null, if there is no
   *       such default. (In which case the absence of a prefix indicates
   *       the absence of a namespace URI.)</td></tr>
   *   <tr><th>{@link javax.xml.XMLConstants#XML_NS_PREFIX} ("xml")</th>
   *     <td>{@link javax.xml.XMLConstants#XML_NS_URI} ("http://www.w3.org/XML/1998/namespace")</td></tr>
   *   <tr><th>{@link javax.xml.XMLConstants#XMLNS_ATTRIBUTE} ("xmlns")</th>
   *     <td>{@link javax.xml.XMLConstants#XMLNS_ATTRIBUTE_NS_URI} ("http://www.w3.org/2000/xmlns/")</td>
   *   </tr>
   *   <tr><th>Any other prefix</th><td>The namespace URI currently mapped to the
   *     prefix or null, if no such mapping is established.</td></tr>
   * </table></p>
   * @throws IllegalArgumentException The input prefix is null.
   * @param pPrefix The prefix being looked up in the list of mappings.
   * @return The Namespace URI to which the input prefix is currently mapped
   *   or null, if there is no such mapping.
   */
  public String getNamespaceURI(String pPrefix);


  /** <p>This method returns a prefix, which is currently mapped to the given
   * namespace URI. Note, that multiple prefixes may be mapped to the namespace
   * URI, in which case the returned prefix is undetermined. Do not make any
   * assumptions on the order in such cases. It is a better choice to use
   * {@link #getPrefixes(String)} instead, if you depend on some order
   * <table border="1">
   *   <tr><th>Namespace URI (Input)</th><th>Prefix (Output)</th></tr>
   *   <tr><th>Current default namespace URI</th>
   *     <td>{@link javax.xml.XMLConstants#DEFAULT_NS_PREFIX} ("")</td></tr>
   *   <tr><th>{@link javax.xml.XMLConstants#XML_NS_URI} ("http://www.w3.org/XML/1998/namespace")</th>
   *     <td>{@link javax.xml.XMLConstants#XML_NS_PREFIX} ("xml")</td></tr>
   *   <tr><th>{@link javax.xml.XMLConstants#XMLNS_ATTRIBUTE_NS_URI} ("http://www.w3.org/2000/xmlns/")</th>
   *     <td>{@link javax.xml.XMLConstants#XMLNS_ATTRIBUTE}</td></tr>
   * </table></p>
   *
   * @throws IllegalArgumentException The input URI is null
   * @param pNamespaceURI The namespace URI being looked up in the list of mappings.
   * @return A prefix currently mapped to the given namespace URI or null, if there
   *   is no such mapping
   * 
   */
  public java.lang.String getPrefix(java.lang.String pNamespaceURI);


  /** <p>This method returns a collection of prefixes, which are currently mapped
   * to the given namespace URI. Note, that the collection may contain more than
   * one prefix, in which case the order is undetermined. If you do not depend
   * on a certain order and any prefix will do, you may choose to use
   * {@link #getPrefix(String)} instead. The following table describes the
   * returned values in more details:
   * <table border="1">
   *   <tr><th>Namespace URI (Input)</th><th>Prefix collection (Output)</th></tr>
   *   <tr><th>{@link javax.xml.XMLConstants#XML_NS_URI} ("http://www.w3.org/XML/1998/namespace")</th>
   *     <td>Collection with a single element: {@link javax.xml.XMLConstants#XML_NS_PREFIX} ("xml")</td></tr>
   *   <tr><th>{@link javax.xml.XMLConstants#XMLNS_ATTRIBUTE_NS_URI} ("http://www.w3.org/2000/xmlns/")</th>
   *     <td>Collection with a single element: {@link javax.xml.XMLConstants#XMLNS_ATTRIBUTE}</td></tr>
   * </table></p>
   *
   * @throws IllegalStateException The input URI is null
   * @param pNamespaceURI The namespace URI being looked up in the list of
   *   mappings or null, if there is no such mapping.
   * @return An unmodifiable {@link java.util.Iterator}: Using it's
   *   {@link java.util.Iterator#remove()} method throws an
   *   {@link UnsupportedOperationException}.
   */
  public java.util.Iterator getPrefixes(java.lang.String pNamespaceURI);
}
