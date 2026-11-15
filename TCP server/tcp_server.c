/*
 * TCP Server - Computer Networks Lab
 * 
 * Continuous communication TCP Server.
 * Listens on port 8080, accepts a client connection, and continuously
 * receives and processes messages in a loop until the client disconnects
 * or types "exit".
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
    char response[BUFFER_SIZE * 2] = {0};
    int opt = 1;

    /* Step 1: Create a TCP socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("TCP Server socket created successfully.\n");

    /* Prevent "Address already in use" error on restart */
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

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

    /* Step 4: Listen for incoming connections */
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
    printf("Ready to receive continuous messages...\n\n");

    /* Step 6: Continuous communication loop */
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(new_socket, buffer, BUFFER_SIZE - 1);

        /* Check if client closed connection or error occurred */
        if (bytes_read <= 0) {
            printf("\nClient disconnected.\n");
            break;
        }

        /* Check for exit command */
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("\nClient requested termination (exit).\n");
            break;
        }

        printf("Message received from client: \"%s\"\n", buffer);

        /* Send acknowledgment/echo response back to client */
        snprintf(response, sizeof(response), "Server ACK: Received '%s'", buffer);
        send(new_socket, response, strlen(response), 0);
        printf("Response sent to client: \"%s\"\n\n", response);
    }

    /* Step 7: Close the sockets */
    printf("Closing connection...\n");
    close(new_socket);
    close(server_fd);

    printf("TCP Server shut down successfully.\n");
    return 0;
}
