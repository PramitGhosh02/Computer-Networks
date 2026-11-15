/*
 * TCP Server - Computer Networks Lab
 * 
 * This program demonstrates a TCP (Transmission Control Protocol) server
 * that listens on a specified port, accepts client connections, receives
 * messages from clients, and sends back responses.
 *
 * Transport Layer Protocol: TCP (connection-oriented, reliable delivery)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "Hello from TCP Server! Message received.";

    /* Step 1: Create a TCP socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("TCP Server socket created successfully.\n");

    /* Step 2: Configure the server address structure */
    address.sin_family = AF_INET;         /* IPv4 */
    address.sin_addr.s_addr = INADDR_ANY; /* Accept connections on any interface */
    address.sin_port = htons(PORT);       /* Convert port to network byte order */

    /* Step 3: Bind the socket to the specified IP and port */
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Socket bound to port %d.\n", PORT);

    /* Step 4: Listen for incoming connections (backlog queue = 3) */
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("TCP Server is listening on port %d...\n", PORT);
    printf("Waiting for a client to connect...\n");

    /* Step 5: Accept an incoming client connection */
    new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Client connected!\n");
    printf("Client IP  : %s\n", inet_ntoa(address.sin_addr));
    printf("Client Port: %d\n", ntohs(address.sin_port));

    /* Step 6: Receive data from the client */
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Message received from client: \"%s\"\n", buffer);

    /* Step 7: Send a response back to the client */
    send(new_socket, response, strlen(response), 0);
    printf("Response sent to client: \"%s\"\n", response);

    /* Step 8: Close the sockets */
    printf("\nClosing connection...\n");
    close(new_socket);
    close(server_fd);

    printf("TCP Server shut down successfully.\n");
    return 0;
}
