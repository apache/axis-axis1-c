// Copyright 2003-2004 The Apache Software Foundation.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import java.util.Random;

public class GenInput
{
    public static void main(String args[])
    {
         if(2 != args.length)
         {
             System.out.println("java GetInput <string size> <number of lines>");
             System.exit(0);
         }
        int intStrSize = Integer.parseInt(args[0]);
        int intNumLines = Integer.parseInt(args[1]);
        Random objRand = new Random();
        int i = 0;
        
        while(i < intNumLines)
        {
            StringBuffer buf = new StringBuffer();
            int intLength = objRand.nextInt(intStrSize);
            if(intLength > 0)
            {
                for(int j=0; j < intLength; j++)
                    buf.append((char) (48 + (objRand.nextInt(256) % 78)));
                System.out.println(buf.toString());
                buf.append("\n");
                i++;
            }
        }
    }
}
