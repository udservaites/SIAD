
import java.net.ServerSocket;
import java.net.Socket;
import java.io.*;
import java.util.Date;


public class MyTCPServer {

    
    public static void main(String[] args) throws IOException {
 
        
        System.out.println("MYTCPServer");

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


}
