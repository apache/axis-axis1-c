
package com.snellspace.axis.jabber.bootstrap;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.MessageFormat;
import java.text.ParseException;
import java.util.HashMap;
import java.util.Iterator;

import org.apache.axis.client.AdminClient;
import org.apache.axis.client.Call;
import org.apache.axis.server.AxisServer;
import org.apache.axis.transport.local.LocalTransport;

import com.snellspace.axis.jabber.JabberServer;

public class Server {

  private static HashMap services = new HashMap();
  private static final String START  = "start ";
  private static final String STOP   = "stop ";
  private static final String DEPLOY = "deploy ";
  private static final String EXIT   = "exit";
  private static final String LIST   = "list";
  private static final String HELP   = "help";
  private static final String HELP_  = "?";
  
  private static final String START_PATTERN = "start {0} {1}";
  private static final String STOP_PATTERN  = "stop {0}";
  private static final String DEPLOY_PATTERN = "deploy {0}";
  
  public static void main(
    String[] args)
      throws Exception {
  
      System.out.println("Axis Jabber Server");
      System.out.println("By James Snell <jasnell@us.ibm.com>");
      System.out.println("type <help> or <?> for usage help");
      menuHandler();
  
  }
  
  private static void menuHandler()
    throws IOException, ParseException {
      BufferedReader br = new BufferedReader(
        new InputStreamReader(System.in));
      for (;;) {
        System.out.print("> ");
        String in = br.readLine();
        if (in.startsWith(HELP) ||
            in.startsWith(HELP_)) {
              showHelp();
        } else if (in.startsWith(START)) {
          try {
            MessageFormat mf = new MessageFormat(START_PATTERN);
            Object[] o = mf.parse(in);
            startService((String)o[0],(String)o[1]);
          } catch (ParseException pe) {
            showHelp();
          }
        } else if (in.startsWith(STOP)) {
          try {
            MessageFormat mf = new MessageFormat(STOP_PATTERN);
            Object[] o = mf.parse(in);
            stopService((String)o[0]);
          } catch (ParseException pe) {
            showHelp();
          }
        } else if (in.startsWith(DEPLOY)) {
          try {
            MessageFormat mf = new MessageFormat(DEPLOY_PATTERN);
            Object[] o = mf.parse(in);
            deploy((String)o[0]);
          } catch (ParseException pe) {
            showHelp();
          }
        } else if (in.startsWith(LIST)) {
          list();
        } else if (in.startsWith(EXIT)) {
          exit();
        } else {
          showHelp();
        }
      }
  }
  
  private static void exit() {
    shutDown();
    System.exit(0);
  }

  private static void showHelp() {
    System.out.println("Usage:");
    System.out.println("\tstart [service id] [password]");
    System.out.println("\tstop  [service id]");
    System.out.println("\texit ");
    System.out.println("\tlist ");
    System.out.println("\tdeploy [wsdd url]");
    System.out.println("");
  }
  
  private static void showError(
    String message,
    Exception e) {
      System.out.println(message);
      System.out.println("\t" + e);
  }
  
  private static void startService(
    String identity,
    String password) {
      try {
        System.out.println("Starting <" + identity + ">");
        services.put(
          identity, 
          new JabberServer(
            identity, 
            password));
      } catch (Exception e) {
        showError(
          "CANNOT START SERVICE",e);
      }
  }
  
  private static void stopService(
    String identity) {
      try {
        System.out.println("Stopping <" + identity + ">");
        JabberServer s = (JabberServer)services.get(identity);
        s.disconnect();
        services.remove(identity);
      } catch (Exception e) {
        showError(
          "CANNOT STOP SERVICE",e);
      }
  }
  
  private static void shutDown() {
    try {
      System.out.println("Shutting down...");
      for (
        Iterator i = services.keySet().iterator(); 
        i.hasNext();) {
          stopService((String)i.next());
      }
    } catch (Exception e) {
      showError("PROBLEM SHUTTING DOWN... FORCING EXIT", e);
      System.exit(0); 
    }
  }
  
  private static void list() {
    try {
      System.out.println("Currently Running Services:");
      if (services.size() == 0) 
        System.out.println("\tNo Running Services");
      for (
        Iterator i = services.keySet().iterator();
        i.hasNext();) {
          System.out.println("\t" + i.next() + "");
      }
      System.out.println("");
    } catch (Exception e) {
      showError(
        "PROBLEM LISTING SERVICES", e);
    }
  }
  
  private static void deploy(
    String wsdd) {
      try {
        AxisServer server = (AxisServer)JabberServer.getAxisEngine();
        LocalTransport transport = new LocalTransport(server);
        transport.setRemoteService("AdminService");
        AdminClient client = new AdminClient();
        Call call = client.getCall();
        call.setTransport(transport);
        client.process(wsdd);
        server.refreshGlobalOptions();
      } catch (Exception e) {
        showError(
          "PROBLEM DEPLOYING SERVICE", e);
      }
  }
  
}
