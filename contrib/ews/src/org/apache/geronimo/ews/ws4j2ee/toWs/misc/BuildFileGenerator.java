package org.apache.geronimo.ews.ws4j2ee.toWs.misc;

import org.apache.axis.components.logger.LogFactory;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.Generator;
import org.apache.geronimo.ews.ws4j2ee.toWs.dd.JaxrpcMapperGenarator;

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
            LogFactory.getLog(JaxrpcMapperGenarator.class.getName());

    public BuildFileGenerator(J2EEWebServiceContext j2eewscontext) throws GenerationFault {
        this.j2eewscontext = j2eewscontext;
    }

    public void genarate() throws GenerationFault {
        try {

            String buildfile = j2eewscontext.getMiscInfo().getOutPutPath() + "/build.xml";
            System.out.println("genarating " + buildfile + ".................");
            PrintWriter out = new PrintWriter(new FileWriter(buildfile));

            out.write("<?xml version=\"1.0\"?>\n");

            out.write("<project basedir=\".\" default=\"dist\">\n");
            out.write("	<property name=\"all.src\" location=\".\"/>\n");
            out.write("	<property name=\"ejb.src\" location=\"${all.src}/ejb\"/>\n");
            out.write("	<property name=\"jaxrpc.src\" location=\"${all.src}/jaxrpc\"/>\n");
            out.write("	<property name=\"build\" location=\"build\"/>\n");
            out.write("	<property name=\"build.classes\" location=\"${build}/classes\"/>\n");
            out.write("	<property name=\"build.lib\" location=\"${build}/lib\"/>\n");
            out.write("	<property name=\"lib\" location=\"lib\"/>\n");

            out.write("	<path id=\"classpath\">\n");
            StringTokenizer tok = getClasspathComponets();
            while (tok.hasMoreTokens()) {
                out.write("		<pathelement location=\"" + tok.nextToken() + "\"/>\n");
            }
            out.write("	</path>\n");

            out.write("	<target name=\"compile\">\n");
            out.write("	   <mkdir dir=\"${build.classes}\"/>\n");
            out.write("	   <mkdir dir=\"${build.lib}\"/>\n");
            out.write("		<javac destdir=\"${build.classes}\" debug=\"on\">\n");
            out.write("			<classpath refid=\"classpath\" />\n");
            out.write("			<src path=\"${ejb.src}\"/>\n");
            out.write("			<src path=\"${jaxrpc.src}\"/>\n");
            out.write("		</javac>\n");
            out.write("	</target>\n");

            out.write("	<target name=\"ejbJar\" depends=\"compile\">\n");
            out.write("		<mkdir dir=\"${build.classes}/META-INF/\"/>\n");
            out.write("		<copy file =\"${ejb.src}/META-INF/ejb-jar.xml\" todir=\"${build.classes}/META-INF\"/>\n");
            out.write("		<copy file =\"${ejb.src}/META-INF/jboss.xml\" todir=\"${build.classes}/META-INF\"/>\n");

            out.write("		<jar jarfile=\"${build}/lib/"
                    + j2eewscontext.getMiscInfo().getEjbName().toLowerCase() + "-ejb.jar\" basedir=\"${build.classes}\" >\n");
            out.write("		<include name=\"**\" />\n");
            out.write("		<manifest>\n");
            out.write("			<section name=\"org/apache/ws4j2ee\">\n");
            out.write("			<attribute name=\"Implementation-Title\" value=\"Apache jsr109 impl\"/>\n");
            out.write("			<attribute name=\"Implementation-Vendor\" value=\"Apache Web Services\"/>\n");
            out.write("			</section>\n");
            out.write("		</manifest>\n");
            out.write("		</jar>\n");
            out.write("		<delete dir=\"${build.classes}/META-INF/\"/>\n");
            out.write("	</target>\n");

            out.write("   <target name=\"jaxrpcJar\" depends=\"compile\">\n");
            out.write("		<mkdir dir=\"${build.classes}/META-INF/\"/> \n");
            out.write("	<!--	<copy file =\"${jaxrpc.src}/META-INF/*\" todir=\"${build.classes}/META-INF\"/> -->\n");

            out.write("		<jar jarfile=\"${build}/lib/"
                    + j2eewscontext.getMiscInfo().getEjbName().toLowerCase() + "-jaxrpc.jar\" basedir=\"${build.classes}\" >\n");
            out.write("		<include name=\"**\" />\n");
            out.write("		<manifest>\n");
            out.write("			<section name=\"org/apache/ws4j2ee\">\n");
            out.write("			<attribute name=\"Implementation-Title\" value=\"Apache jsr109 impl\"/>\n");
            out.write("			<attribute name=\"Implementation-Vendor\" value=\"Apache Web Services\"/>\n");
            out.write("			</section>\n");
            out.write("		</manifest>\n");
            out.write("		</jar>\n");
            out.write("		<delete dir=\"${build.classes}/META-INF/\"/>\n");
            out.write("	</target>\n");

            out.write("	<target name=\"dist\" depends=\"ejbJar,jaxrpcJar\"/>\n  ");

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
