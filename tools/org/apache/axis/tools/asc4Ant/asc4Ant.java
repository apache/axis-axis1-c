/*
 * Created on 08-Mar-2006
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package org.apache.axis.tools.asc4Ant;

import java.io.File;


/**
 * @author Administrator
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class asc4Ant
{

    public static void main(String[] args)
    {
        if( args.length == 2)
        {
            String filename = args[0];
            String passwordFile = args[1];
        
	        try
	        {
	            if( new File( filename).exists())
	            {
                    String osName = System.getProperty("os.name");
	                String gpgCommand = "gpg --no-secmem-warning" +           // No Memory Warnings.
                                           " --yes --quiet" +                 // Answer 'yes' to questions and keep it quiet!
                                           " --armor" +                       // Armour required.
                                           " --passphrase-fd 0" +             // Pick-up an input from the input pipe (option '0').
                                           " --output " + filename + ".asc" + // Output filename.
                                           " --detach-sig " + filename +      // Input filename.
                                           " < " + passwordFile;              // Piped input file.
	                Runtime rt = Runtime.getRuntime();
                    Process proc = null;
	
	                if( osName.startsWith( "Windows"))
	                {
                        String cmdLine = "cmd /C " + gpgCommand;

	                    proc = rt.exec( cmdLine);
	                }
                    else
                    {
	                    String [] cmdLine = {"/bin/sh", "-c", gpgCommand};

	                    proc = rt.exec( cmdLine);
	                }
		            
                    proc.waitFor();
	            }
	        }
	        catch( Throwable t)
	        {
	            t.printStackTrace();
	        }
        }
    }
}
