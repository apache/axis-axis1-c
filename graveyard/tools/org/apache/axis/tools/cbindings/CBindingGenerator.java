/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
package org.apache.axis.tools.cbindings;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.StringTokenizer;
import java.util.Hashtable;
import java.util.*;


import org.apache.axis.tools.common.CParsingTool;
import org.apache.axis.tools.common.Configuration;
import org.apache.axis.tools.common.DirectoryTree;
import org.apache.axis.tools.common.FileActor;
import org.apache.axis.tools.common.FilePart;
import org.apache.axis.tools.common.InputCppSourceCode;
import org.apache.axis.tools.common.MethodPart;
import org.apache.axis.tools.common.Parameter;
import org.apache.axis.tools.common.ParsingException;
import org.apache.axis.tools.common.PrototypePart;
import org.apache.axis.tools.common.Signature;
import org.apache.axis.tools.common.Utils;

/**
 * This class is a tool that generates C bindings (header files) from C++
 * header files. It contains a main program:-
 * 
 * usage: Java CBindingGenerator -config <file> -source <dir> -target <dir>
 */
public class CBindingGenerator extends CParsingTool implements FileActor 
{
    private static Hashtable classMapping = new Hashtable();
    
    static{ 
        classMapping.put("AxisCPPConfigDefaults",   "axiscConfigDefaults");
        classMapping.put("AxisException",           "axiscException");
        classMapping.put("BasicHandler",            "axiscBasicHandler");
        classMapping.put("BasicNode",               "axiscBasicNode");
        classMapping.put("IAttribute",              "axiscAttribute");
        classMapping.put("IHandlerSoapDeSerializer","axiscHandlerSoapDeSerializer");
        classMapping.put("IHandlerSoapSerializer",  "axiscHandlerSoapSerializer");
        classMapping.put("IHeaderBlock",            "axiscHeaderBlock");
        classMapping.put("IMessageData",            "axiscMessageData");
        classMapping.put("INamespace",              "axiscNamespace");
        classMapping.put("ISoapAttachment",         "axiscSoapAttachment");
        classMapping.put("ISoapFault",              "axiscSoapFault");
        classMapping.put("IWrapperSoapDeSerializer","axiscSoapDeSerializer");
        classMapping.put("IWrapperSoapSerializer",  "axiscSoapSerializer");
        classMapping.put("OtherFaultException",     "axiscOtherFaultException");
        classMapping.put("SoapFaultException",      "axiscSoapFaultException");
        classMapping.put("TypeMapping",             "axiscTypeMapping");
     }
    
    private CBindingGenerator(String[] args) throws Exception 
    {
        super(args);
    }
    
    /** 
     * This method is used to determine the prefix to use for the class 
     * methods. All class methods should be prefixed with "axisc + classname".
     * We use mapping table to try to shorten long names or to remove the 'I'
     * from the class name. See mapping table above.
     */
    public static String getClassMapping(String theClass)
    {
        String val = (String)classMapping.get(theClass);
        if (val == null)
            val = "axisc" + theClass;

        return val;
    }

    /**
     * This method is called by the DirectoryTree with two files: the
     * input (source) file and the output (target) file. This method parses 
     * the source (header) file and writes out the C bindings to the target 
     * file. The depth is how deep in the source directory tree we are. 
     */
    public void actOnFile(File source, File target, int depth) throws Exception 
    {
        if (Configuration.fileExcluded(source.getName()))
            return;
        Utils.outputDebugString("parsing " + source + "...");
        String targetName = DirectoryTree.maybeAppendSeparator(target.toString());
        targetName += source.getName().substring(0, source.getName().lastIndexOf(".")) + ".h";
        FileWriter fw = new FileWriter(new File(targetName), false);
        BufferedWriter bw = new BufferedWriter(fw);
        FileReader fr = new FileReader(source);
        BufferedReader inputFile = new BufferedReader(fr);

        try 
        {
            InputCppSourceCode sourceCode = new InputCppSourceCode(inputFile, source.getName());
            generateHeader(sourceCode, bw);
        } 
        catch (ParsingException pe) 
        {
            failed = true;
        }

        bw.flush();
        bw.close();
        inputFile.close();
    }

    /**
     * Generates a C header file from a C++ header file.
     */
    private void generateHeader(InputCppSourceCode inputFile, BufferedWriter outputFile) throws Exception 
    {
        boolean foundCopyright = false;
        String define = inputFile.getName();
        define = define.toUpperCase();
        define = define.substring(0, define.indexOf("."));
        define += "_INCLUDED";
        
        String syncComment = 
            "/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */\n" +
            "/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */\n" +
            "/* ----------------------------------------------------------------   */\n" +
            "/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */\n" +
            "/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */\n" +
            "/* THE IMPLEMEMTATION OF THE C APIS.                                  */\n" +
            "/*                                                                    */\n" +
            "/* THIS FILE GENERATED BY CBINDINGGENERATOR TOOL.                     */\n" +
            "/* ----------------------------------------------------------------   */\n" +
            "/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */\n" +
            "/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */\n";
        
        String cplusplusStart = "#ifdef __cplusplus\n extern \"C\" {\n#endif\n"; 
        String cplusplusEnd   = "#ifdef __cplusplus\n }\n#endif\n"; 

        int prevPart = FilePart.COMMENT; // Suppresse newline before copyright
        String text;
        Iterator it = inputFile.getPartIterator();
        while (it.hasNext()) 
        {
            FilePart fp = (FilePart) (it.next());
            if (!foundCopyright
                && (FilePart.DIRECTIVE == fp.getType()
                    || FilePart.ENUM == fp.getType()
                    || FilePart.PROTOTYPE == fp.getType())) 
            {
                outputFile.write("#ifndef " + define);
                outputFile.newLine();
                outputFile.write("#define " + define);
                outputFile.newLine();
                outputFile.newLine();
                outputFile.write(syncComment);  
                outputFile.newLine();
                outputFile.write(cplusplusStart);  
                outputFile.newLine();                
                foundCopyright = true;
            }

            switch (fp.getType()) 
            {
                case FilePart.COMMENT :
                    if (FilePart.COMMENT != prevPart)
                        outputFile.newLine();
                    prevPart = fp.getType();
                    text = fp.toString().trim();
                    StringTokenizer tkzr = new StringTokenizer(text, "\n\r");
                    while (tkzr.hasMoreTokens()) 
                    {
                        String line = tkzr.nextToken().trim();
                        if (-1 == line.indexOf("@author")) 
                        {
                            if (line.startsWith("*"))
                                outputFile.write(" ");
                            outputFile.write(line);
                            outputFile.newLine();
                        }
                    }
                    break;

                case FilePart.DIRECTIVE :
                    if (FilePart.DIRECTIVE != prevPart)
                        outputFile.newLine();
                    prevPart = fp.getType();
                    generateDirective(fp, outputFile, inputFile.getName());
                    break;

                case FilePart.TYPEDEF :
                    prevPart = fp.getType();
                    generateTypedef(fp, outputFile);
                    break;

                case FilePart.METHOD :
                case FilePart.PROTOTYPE :
                    if (FilePart.COMMENT != prevPart
                        && FilePart.METHOD != prevPart
                        && FilePart.PROTOTYPE != prevPart)
                        outputFile.newLine();
                    prevPart = fp.getType();
                    generateFunctionPrototype(fp, outputFile);
                    break;

                case FilePart.ENUM :
                    Utils.rude(
                        "Enums should be wrappered with a typedef so "
                            + "they appear the same in C and C++",
                        inputFile.getName(), 0, fp.toString());
                    break;
                    // do nothing for other file parts
            }
        }
 
        outputFile.newLine();
        
        outputFile.write(cplusplusEnd);  
        outputFile.newLine();                

        outputFile.write("#endif /* " + define + " */");
        outputFile.newLine();
    }

    private boolean keepIfdef = false;
    private void generateDirective(FilePart fp, BufferedWriter outputFile,String filename) throws Exception 
    {
        String text = fp.toString().trim();
        if (-1 != text.indexOf("include")) 
        {
            if (-1 != text.indexOf("axis/"))
            {
                // We currently do not support handlers for C bindings
                if (-1 == text.indexOf("BasicHandler") && 
                    -1 == text.indexOf("IHandlerSoap") &&
                    -1 == text.indexOf("AxisUserAPIArrays")) // no equivalent
                {
                    // Change .hpp files to .h files and dump out include
                    text = text.replaceAll(".hpp",".h");
                    outputFile.write(text);
                    outputFile.newLine();  
                }
            }
            else if (-1 != text.indexOf(".h>"))
            {
                // Just dump out .h include statements
                outputFile.write(text);
                outputFile.newLine();               
            }
        } 
        // DEAD CODE? In AxisUserAPI.h we must keep a #ifdef WIN32/#else/#endif
        else if (keepIfdef || ("AxisUserAPI.hpp".equals(filename) && -1 != text.indexOf("WIN32"))) 
        {
            outputFile.write(text);
            outputFile.newLine();
            if (!keepIfdef)
                keepIfdef = true;
            else if (-1 != text.indexOf("endif"))
                keepIfdef = false;
        }
    }

    private void generateTypedef(FilePart fp, BufferedWriter outputFile) throws Exception 
    {
        // Look to see if this is a typedef of a function pointer
        // or a typedef of a datatype. Function pointer typedefs
        // end with a ) before the last semicolon and do not have 
        // their typedef name at the end so don't attempt to prefix
        // the last token with AXISC_
        String text = fp.toString().trim();
        String lasttok = null;
        for (int i=0; i<text.length(); i++) 
        {
            String s = "" + text.charAt(i);
            if (!";".equals(s) && -1 == Utils.whitespace.indexOf(s))
                lasttok = s;
        }

        text = changeAxisToAxisc(text);
        text = replaceInString(text,"bool","AxiscBool",null);

        if (!")".equals(lasttok)) 
        {
            // Put AXISC_ on to the front of the typedef name which is always at the end.
            StringTokenizer st = new StringTokenizer(text);
            String tok = null;
            while (st.hasMoreTokens()) tok = st.nextToken();
            text = replaceInString(text,tok,"AXISC_"+tok,null);
        }

        outputFile.write(text);
        outputFile.newLine();
    }

    private void generateFunctionPrototype(FilePart fp, BufferedWriter outputFile) throws Exception 
    {
        Signature sign = null;
        if (FilePart.PROTOTYPE == fp.getType()) 
        {
            PrototypePart pp = (PrototypePart) fp;
            sign = pp.getSignature();
        } 
        else 
        {
            MethodPart mp = (MethodPart) fp;
            sign = mp.getSignature();
        }
        
        // Ignore private methods.
        if (!sign.getScope().equals("public") &&
            !sign.getScope().equals("protected"))
            return;
        
        String classname = sign.getClassName();
        if (null != classname && classname.endsWith("::"))
            classname = classname.substring(0, classname.length() - 2);
        
        String method = sign.getMethodName();
        if (Configuration.methodExcluded(classname, method))
            return;
        
        Parameter[] parms = sign.getParameters();
                
        String text = new String();

        // Look to see if this method is overloaded by another method
        // in the same class. If methods are overloaded in the same class then
        // convert the longest method prototype to C. We should really 
        // superset the parameters in the two prototypes instead of
        // picking the longest one.
        List overloads = headers.getMethods(method);
        boolean sameClass = true;
        if (overloads.size() > 1) 
        {
            Iterator it = overloads.iterator();
            while (it.hasNext()) 
            {
                Signature s = (Signature) it.next();
                if (s.getTrimClassName().equals(classname))
                {
                    int n1 = 0;
                    int n2 = 0;
                    if (null != s.getParameters())
                        n1 = s.getParameters().length;
                    if (null != sign.getParameters())
                        n2 = sign.getParameters().length;
                    if (n1 > n2)
                        return;
                }
            }
        }

        String classMapping = getClassMapping(classname);
        
        text += "AXISC_STORAGE_CLASS_INFO\n";
        if (sign.isConstructor()) 
            text += "AXISCHANDLE " + classMapping + "Create(";
        else if (sign.isDestructor()) 
        {
            text += "void " + classMapping + "Destroy(AXISCHANDLE ";
            String prettyClass = classNamePretty(classname);
            text += Character.toLowerCase(prettyClass.charAt(0));
            text += prettyClass.substring(1);
            if (null != parms)
                text += ", ";
        } 
        else 
        {
            String retType = toCType(sign.getReturnType());
            
            // OS/400 C compiler has a problem with "const xsdc__string" as return type, 
            // so just replace that with "const char *"
            if (System.getProperty("os.name").equals("OS/400"))
                retType = retType.replaceAll("const xsdc__string","const char *");

            text += retType + " ";
            text += getClassMapping(classname);
            text += Character.toUpperCase(method.charAt(0));
            text += method.substring(1);
            
            String retClass = getClassFromRetType(sign);
            if ("AXISCHANDLE".equals(retType) && -1 == method.indexOf(retClass))
                text += retClass;
            
            text += "(";

            if (null != classname && -1 == sign.getAttributes().indexOf("static")) 
            {
                text += "AXISCHANDLE ";
                String prettyClass = classNamePretty(classname);
                text += Character.toLowerCase(prettyClass.charAt(0));
                text += prettyClass.substring(1);
                if (null != parms)
                    text += ", ";
            }
        }
        
        // For now, ignore operator-type methods
        if (-1 != text.indexOf("Operator="))
            return;

        if (parms != null) 
        {
            for (int i = 0; i < parms.length; i++) 
            { 
                // Do not include prototypes with va_list...since these functions have
                // probably been added in support of C binding.
                if (parms[i].isVaListArg())
                    return;
                
                if (0 != i) 
                {
                    text += ", ";
                    // wrap long lines at 50 chars
                    if (text.length() > 50) 
                        text += "\n\t";
                }
                text += toCType(parms[i]) + " ";
                String name = parms[i].getName();
                if (null != name) // "..." has no parm name
                    text += name;
            }
        }
        text += ");";
        
        outputFile.write(text);
        outputFile.newLine();
    }

    private static String classNamePretty(String className) 
    {
        if (className == null)
            return null;
        // namespace is a reserved word so make sure we never return namespace
        if (className.equals("INamespace"))
            return className;
        if (className.startsWith("I"))
            return className.substring(1);
        return className;
    }

    /**
     * Converts a C++ datatype to a C-style datatype. 
     * References are converted to pointers.
     * STL strings are converted to char* C-style strings
     * String& is converted to char* (not char**)
     * AXIS, Axis and axis are converted to AXISC, Axisc and axisc
     */
    private String toCType(Parameter p) throws Exception 
    {
        if (p.isVoid())
            return "void";

        String type = new String();
        Iterator it = p.iterator();
        String prev = new String();
        while (it.hasNext()) 
        {
            String tok = (String) it.next();
            if ("&".equals(tok)) 
            {
                if (!"string".equals(prev))
                    type += "*";
            } 
            else if ("string".equals(tok)) 
            {
                type += "char*";
                prev = tok;
            } 
            else if (headers.isClassName(tok)) 
                return "AXISCHANDLE";
            else if ("AnyType".equals(tok)) 
                type += "AxiscAnyType";
            else if ("bool".equals(tok)) 
                type += "AxiscBool";
            else if ("XML_String".equals(tok)) 
                type += "AXISC_XML_String";
            else if (tok.startsWith("xsd__")) 
                type += replaceInString(tok,"xsd__","xsdc__",null);
            else if (-1 != tok.toLowerCase().indexOf("axis")) 
                type += changeAxisToAxisc(tok);
            else if (!Utils.cTypeQualifiers.contains(tok) && 
                     !Utils.cPrimitives.contains(tok) && 
                     !tok.equals("tm") &&         // Leave struct tm alone
                     !tok.equals("...") &&         // Leave ... alone
                     !tok.equals("va_list") &&     // Leave ... alone
                     !tok.startsWith("xsd")) 
                type += "AXISC_"+tok;
            else 
                type += tok;
            
            if (it.hasNext())
                type += " ";
        }
        return type;
    }

    private String getClassFromRetType(Signature sign) 
    {
        Parameter p = sign.getReturnType();
        if (p.isVoid())
            return null;

        Iterator it = p.iterator();
        while (it.hasNext()) 
        {
            String tok = (String) it.next();
            if (headers.isClassName(tok))
                return classNamePretty(tok);
        }
        return null;
    }

    /**
     * Converts AXIS, axis and Axis to AXISC, axisc and Axisc.
     * Does not convert Axisc, axisc or AXISC_
     */
    private static String changeAxisToAxisc(String text) throws Exception 
    {
        text = replaceInString(text,"axis","axisc",null);
        text = replaceInString(text,"Axis","Axisc","Axisc");
        text = replaceInString(text,"AXIS","AXISC","AXISC_");
        return text;
    }

    /**
     * Replaces from with to in text, excluding strings that start with exclude.
     */
    private static String replaceInString(String text, String from, String to, String exclude) throws Exception 
    {
        int idx = 0;
        while (-1 != text.indexOf(from, idx)) 
        {
            int start = text.indexOf(from, idx);
            if (null == exclude || text.indexOf(exclude, idx) != start) 
            {
                text = text.substring(0, start) + to + text.substring(start + from.length());
                idx = start + to.length();
            } 
            else 
                idx = start + exclude.length();
        }
        return text;
    }

    public static void main(String[] args) 
    {
        boolean failed = false;
        try 
        {
            CBindingGenerator gen = new CBindingGenerator(args);
            File source = gen.checkFile("-source");
            File target = gen.maybeCreateDirectory("-target");
            gen.headers = gen.preparseHeaders("-source");

            DirectoryTree tree = new DirectoryTree(gen, new HashSet(Arrays.asList(new Object[] { "hpp" })));
            tree.walkTree(source, target, 0);
            failed = gen.failed;
        } 
        catch (Exception exception) 
        {
            exception.printStackTrace();
            failed = true;
        }

        if (failed) 
        {
            Utils.outputDebugString("Finished! (but encountered problems)");
            System.exit(-2);
        } 
        
        Utils.outputDebugString("Finished!");
    }

    protected void printUsage() 
    {
        System.out.println("usage: Java CBindingGenerator -config <file> -source <dir> -target <dir>");
    }

}
