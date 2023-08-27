#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>

const int MAX_CONNECTIONS = 10;  
const int BUFFER_SIZE = 1024;    
const int THREAD_POOL_SIZE = 4;  

void* handleRequest(void* arg) {
    int clientSocket = *(int*)arg;
    delete (int*)arg;  

    char buffer[BUFFER_SIZE];
    std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nHello, World!,this is srujan rai";

    
    memset(buffer, 0, BUFFER_SIZE);
    ssize_t bytesRead = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
    if (bytesRead < 0) {
        std::cerr << "Error receiving request from client" << std::endl;
    }

  
    ssize_t bytesSent = send(clientSocket, response.c_str(), response.length(), 0);
    if (bytesSent < 0) {
        std::cerr << "Error sending response to client" << std::endl;
    }

    close(clientSocket);

    return nullptr;
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientAddressLength;
    std::vector<pthread_t> threadPool(THREAD_POOL_SIZE);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating server socket" << std::endl;
        return 1;
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080); 

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding server socket" << std::endl;
        return 1;
    }


    if (listen(serverSocket, MAX_CONNECTIONS) < 0) {
        std::cerr << "Error listening for connections" << std::endl;
        return 1;
    }

    std::cout << "Server started. Listening on port 8080..." << std::endl;

    while (true) {

        clientAddressLength = sizeof(clientAddress);
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            std::cerr << "Error accepting client connection" << std::endl;
            continue;
        }


        pthread_t* thread = nullptr;
        for (pthread_t& t : threadPool) {
            if (!t) {
                thread = &t;
                break;
            }
        }

        if (thread) {
            int* arg = new int(clientSocket);
            pthread_create(thread, nullptr, handleRequest, arg);
        } else {

            std::cerr << "All threads busy. Unable to handle new request." << std::endl;
            close(clientSocket);
        }
    }

    close(serverSocket);

    return 0;
}
