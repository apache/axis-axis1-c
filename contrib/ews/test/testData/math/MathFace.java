package testData.math;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface MathFace extends Remote {
  public int add(int a, int b) throws RemoteException;
}

