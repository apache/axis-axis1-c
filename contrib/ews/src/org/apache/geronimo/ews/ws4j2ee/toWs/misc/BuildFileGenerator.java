/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2004 The Apache Software Foundation.  All rights
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
 
 package org.apache.geronimo.ews.ws4j2ee.toWs.misc;

import org.apache.axis.components.logger.LogFactory;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.Generator;
import org.apache.geronimo.ews.ws4j2ee.toWs.dd.JaxrpcMapperGenerator;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class BuildFileGenerator implements Generator {
	private J2EEWebServiceContext j2eewscontext;

	protected static Log log =
			LogFactory.getLog(JaxrpcMapperGenerator.class.getName());

	public BuildFileGenerator(J2EEWebServiceContext j2eewscontext) throws GenerationFault {
		this.j2eewscontext = j2eewscontext;
	}

	public void generate() throws GenerationFault {
		try {
			String buildfile = j2eewscontext.getMiscInfo().getOutPutPath() + "/build.xml";
			if(j2eewscontext.getMiscInfo().isVerbose())
				log.info("genarating " + buildfile + ".................");
            
			PrintWriter out = new PrintWriter(new FileWriter(buildfile));

			out.write("<?xml version=\"1.0\"?>\n");

			out.write("<project basedir=\".\" default=\"dist\">\n");
			out.write("	<property name=\"src\" location=\".\"/>\n");
			out.write("	<property name=\"build\" location=\"build\"/>\n");
			out.write("	<property name=\"build.classes\" location=\"${build}/classes\"/>\n");
			out.write("	<property name=\"build.lib\" location=\"${build}/lib\"/>\n");
			out.write("	<property name=\"lib\" location=\"lib\"/>\n");

			out.write("	<path id=\"classpath\">\n");
			StringTokenizer tok = getClasspathComponets();
			String jarfile = j2eewscontext.getMiscInfo().getJarFileName();
			if(jarfile != null){
				out.write("		<pathelement location=\"" + jarfile + "\"/>\n");
			}
			while (tok.hasMoreTokens()) {
				out.write("		<pathelement location=\"" + tok.nextToken() + "\"/>\n");
			}
			out.write("	</path>\n");

			out.write("	<target name=\"compile\">\n");
			out.write("	   <mkdir dir=\"${build.classes}\"/>\n");
			out.write("	   <mkdir dir=\"${build.lib}\"/>\n");
			out.write("		<javac destdir=\"${build.classes}\" debug=\"on\">\n");
			out.write("			<classpath refid=\"classpath\" />\n");
			out.write("			<src path=\"${src}\"/>\n");
			out.write("		</javac>\n");
			out.write("	</target>\n");

			out.write("	<target name=\"jar\" depends=\"compile\">\n");
			out.write("		<mkdir dir=\"${build.classes}/META-INF/\"/>\n");
			
			File jaxrpcFile = new File(j2eewscontext.getMiscInfo().getJaxrpcfile());
			File wsdlfile = new File(j2eewscontext.getMiscInfo().getWsdlFile());
			File wscffile = null;

			if(jaxrpcFile.exists())
				out.write("		<copy file =\""+jaxrpcFile.getAbsolutePath()+"\" todir=\"${build.classes}/META-INF\"/>\n");
			if(wsdlfile.exists())	
				out.write("		<copy file =\""+wsdlfile.getAbsolutePath()+"\" todir=\"${build.classes}/META-INF\"/>\n");

			if(j2eewscontext.getMiscInfo().getWsconffile()!= null){
				wscffile = new File(j2eewscontext.getMiscInfo().getWsconffile());
				if(wscffile.exists())	
					out.write("		<copy file =\""+wscffile.getAbsolutePath()+"\" todir=\"${build.classes}/META-INF\"/>\n");
			}
			
			if(j2eewscontext.getMiscInfo().isImplwithEJB()){
				File ejbDD = 	new File(j2eewscontext.getMiscInfo().getOutPutPath()+"/META-INF/ejb-jar.xml");
				if(ejbDD.exists())
					out.write("		<copy file =\""+ejbDD.getAbsolutePath()+"\" todir=\"${build.classes}/META-INF\"/>\n");
				
				File contianerDD = null;	
				if(GenerationConstants.JBOSS_CONTAINER.equals(j2eewscontext.getMiscInfo().getTargetJ2EEContainer())){
					contianerDD = new File(j2eewscontext.getMiscInfo().getOutPutPath()+"/META-INF/"+GenerationConstants.JBOSS_DD);
				}else if(GenerationConstants.JONAS_CONTAINER.equals(j2eewscontext.getMiscInfo().getTargetJ2EEContainer())){
					contianerDD = new File(j2eewscontext.getMiscInfo().getOutPutPath()+"/META-INF/"+GenerationConstants.JONAS_DD);
				}else if(GenerationConstants.GERONIMO_CONTAINER.equals(j2eewscontext.getMiscInfo().getTargetJ2EEContainer())){
					contianerDD = new File(j2eewscontext.getMiscInfo().getOutPutPath()+"/META-INF/"+GenerationConstants.GERONIMO_DD);
				}	
				if(contianerDD.exists()){
						out.write("		<copy file =\""+contianerDD.getAbsolutePath()+"\" todir=\"${build.classes}/META-INF\"/>\n ");
				}
				
									
			}else{
				out.write("		<copy file =\"${src}/META-INF/web.xml\" todir=\"${build.classes}/META-INF\"/>\n ");
			}


			String jarName = j2eewscontext.getMiscInfo().getTargetPortType().getName().toLowerCase();
			int index = jarName.lastIndexOf(".");
			if(index>0){
				jarName = jarName.substring(index+1);
			} 
            
			out.write("		<jar jarfile=\"${build}/lib/"
					+ jarName + "-impl.jar\" basedir=\"${build.classes}\" >\n");
			out.write("		<include name=\"**\" />\n");
			out.write("		<manifest>\n");
			out.write("			<section name=\"org/apache/ws4j2ee\">\n");
			out.write("			<attribute name=\"Implementation-Title\" value=\"Apache jsr109 impl\"/>\n");
			out.write("			<attribute name=\"Implementation-Vendor\" value=\"Apache Web Services\"/>\n");
			out.write("			</section>\n");
			out.write("		</manifest>\n");
			out.write("		</jar>\n");
			out.write("     <java classname=\"org.apache.geronimo.ews.ws4j2ee.utils.packager.Packager\" fork=\"yes\" >\n");
			out.write("     	<classpath refid=\"classpath\" />\n");
			out.write("     	<arg value=\""+jarName+".jar\"/> \n");
			out.write("     	<arg value=\"${build}/lib/"
					+ jarName + "-impl.jar\"/>\n"); 
			out.write("     	<arg value=\""+jarfile+"\"/>\n"); 
			out.write("     </java>\n");

			out.write("		<delete dir=\"${build}\"/>\n");
//			out.write("		<delete dir=\"${build.classes}/META-INF/\"/>\n");
//			out.write("		<delete file=\"${build}/lib/"
//					+ jarName + "-impl.jar\"/>\n");
			out.write("	</target>\n");


			out.write("	<target name=\"dist\" depends=\"jar\"/>\n  ");

			out.write("	<target name=\"clean\">\n");
			out.write("		<delete dir=\"${build}\"/>\n");
			out.write("	</target>\n");

			out.write("</project>\n");
			out.close();
		} catch (IOException e) {
			throw GenerationFault.createGenerationFault(e);
		}

	}

	private StringTokenizer getClasspathComponets() {
		String classpath = System.getProperty("java.class.path");
		String spearator = ";";
		if (classpath.indexOf(';') < 0) {
			//then it is UNIX
			spearator = ":";
		}

		return new StringTokenizer(classpath, spearator);
	}

}
