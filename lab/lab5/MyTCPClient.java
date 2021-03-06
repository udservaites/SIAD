
import java.net.ServerSocket;
import java.net.Socket;
import java.io.*;
import java.util.Date;


public class MyTCPClient {
    public static void main(String[] args) throws IOException {
 
        if(args.length != 2) {
            System.err.println("Usage: java MyTCPClient <host name> <port number>");
            System.exit(1);
        }
        
        System.out.println("MYTCPClient");

        String hostName = args[0];
        int portNumber = Integer.parseInt(args[1]);

        try {
            Socket socket = new Socket(hostName, portNumber);
            System.out.println("Connected to the server: " + hostName + "\' at port " + portNumber);

        //outstream to send data
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        //inputstream to read data
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        //buffer reader to read from user input
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));

        String userInput;
        while((userInput = stdIn.readLine()) != null) {
            out.println(userInput);
            System.out.println("Received from server: " + in.readLine());


          }

        } catch(IOException e) {
            System.err.println("COuldn't get I/O for the connection to " + hostName);
            System.exit(1);
        }
    }
}
/*
        //Create socket and assigne port number
        int portNumber = 8000;
        ServerSocket serverSocket = new ServerSocket(portNumber);

        System.out.println("MyTCPServer is running at port: " + serverSocket.getLocalPort());

        //Client socket. If no error, client connected
        //Test with telnet or browser
        Socket clientSocket = serverSocket.accept();
        System.out.println("A client is connected...");
        System.out.println("A client is connected from IP: " + clientSocket.getInetAddress().getHostAddress());

        //send and receive the data from client
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

        String inputLine = in.readLine();
        String receivedData = inputLine;
        while(!inputLine.isEmpty()) {
             inputLine = in.readLine();
             receivedData += inputLine;

        }
        
        System.out.println("Data received from client: " + receivedData);

        //Send message to client
        String response = "MYTCPServer\n" + (new Date()).toString() + "\n" + "You have sent: " + receivedData;

        clientSocket.getOutputStream().write(response.getBytes("UTF-8"));
    }

}*/
