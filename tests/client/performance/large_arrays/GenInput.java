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
