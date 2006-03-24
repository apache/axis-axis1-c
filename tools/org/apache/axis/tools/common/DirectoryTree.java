/*
 * Copyright 2003-2004 The Apache Software Foundation. // (c) Copyright IBM
 * Corp. 2004, 2005 All Rights Reserved Licensed under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0 Unless required by applicable law
 * or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 */
package org.apache.axis.tools.common;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.StringTokenizer;

public class DirectoryTree
{
    private FileActor actor;
    private Set       extensions;

    public DirectoryTree(FileActor actor, Set extensions)
    {
        this.actor=actor;
        this.extensions=extensions;
    }

    /**
     * Starts adding trace into the given file. If the given file is a directory
     * then this the starting directory and all code beneath and in this
     * directory will be given trace.
     * 
     * @param source - either the starting directory or one file to add trace
     *            to.
     */
    public void walkTree(File source, File target, int depth) throws Exception
    {
        depth++;
        boolean noTarget=(null==target);

        if (!source.canRead( ))
            Utils.rude("Cannot read from source directory "+source);
        if (!noTarget&&!target.canWrite( ))
            Utils.rude("Cannot write to target directory "+target);

        if (source.isDirectory( ))
        {
            // we only want to look at this directory if it's not a .svn directory.
            // If it is then let's call this the end of the branch and return.
            if(source.toString().indexOf(".svn")==-1 && source.toString().indexOf("apache1_3")==-1 && source.toString().indexOf("apache2_0")==-1)
            {
            File[] filesInDirectory=source.listFiles( );
            for(int i=0; i<filesInDirectory.length; i++)
            {
                File file=filesInDirectory[i];
                String name=file.getName( );
                int dot=name.lastIndexOf('.');
                String ext=null;
                if (-1!=dot)
                    ext=name.substring(dot+1);

                if (file.isDirectory( ) && !name.equals(".svn") && !name.equals("apache1_3") && !name.equals("apache2_0"))
                {
                    File newTarget=null;
                    if (!noTarget)
                    {
                        StringTokenizer st=new StringTokenizer(file.getPath( ),
                                "\\/");
                        String newdir=null;
                        while (st.hasMoreTokens( ))
                            newdir=st.nextToken( );
                        String targetName=maybeAppendSeparator(target
                                .toString( ));
                        newTarget=new File(targetName+newdir);
                        if (!newTarget.mkdir( ))
                            Utils.rude("Failed to create target directory "
                                    +newTarget);
                    }

                    walkTree(file, newTarget, depth);
                }
                else
                {
                    if (file.isFile( )
                            &&(extensions==null||(!file.isHidden( )&&extensions
                                    .contains(ext))))
                    {
                        // this is a file and we need to add trace into it !
                        actor.actOnFile(file, target, depth);
                    }
                }
            }
            }
            else
            {
                System.out.println( "Not walking "+source.toString());
            }
        }
        else
        {
            actor.actOnFile(source, target, depth);
        }
    }

    public static String maybeAppendSeparator(String name)
    {
        if (!name.endsWith("/")&&!name.endsWith("\\"))
            name+="/";
        return name;
    }
}