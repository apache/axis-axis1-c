import java.io.*;

/**
 * Axis C++ JNI delegator.
 *
 * @author Lilantha Darshana
 */

public class AxisCppHandler
{
	static {
             System.loadLibrary("axis_cpp");
         }
	static native void Delegate(InputStream in, OutputStream out);
	
}



