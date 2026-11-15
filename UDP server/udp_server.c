/*
 * UDP Server - Computer Networks Lab
 * 
 * This program demonstrates a UDP (User Datagram Protocol) server
 * that receives datagrams from clients and sends back responses.
 *
 * Transport Layer Protocol: UDP (connectionless, unreliable, fast)
 *
 * Key difference from TCP:
 *   - No connection setup (no listen/accept)
 *   - Uses recvfrom() and sendto() instead of read/send
 *   - Each message is an independent datagram
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int main() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "Hello from UDP Server! Datagram received.";

    /* Step 1: Create a UDP socket (SOCK_DGRAM for datagrams) */
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("UDP Server socket created successfully.\n");

    /* Step 2: Configure the server address structure */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;         /* IPv4 */
    server_addr.sin_addr.s_addr = INADDR_ANY; /* Accept from any interface */
    server_addr.sin_port = htons(PORT);       /* Convert port to network byte order */

    /* Step 3: Bind the socket to the specified IP and port */
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Socket bound to port %d.\n", PORT);

    /* No listen() or accept() needed — UDP is connectionless! */

    printf("UDP Server is running on port %d...\n", PORT);
    printf("Waiting for a datagram from client...\n");

    /* Step 4: Receive a datagram from the client */
    int n = recvfrom(server_fd, buffer, BUFFER_SIZE, 0,
                     (struct sockaddr *)&client_addr, &client_len);
    buffer[n] = '\0';

    printf("\n========================================\n");
    printf("Datagram received!\n");
    printf("Client IP  : %s\n", inet_ntoa(client_addr.sin_addr));
    printf("Client Port: %d\n", ntohs(client_addr.sin_port));
    printf("========================================\n\n");
    printf("Message from client: \"%s\"\n", buffer);

    /* Step 5: Send a response back to the client */
    sendto(server_fd, response, strlen(response), 0,
           (struct sockaddr *)&client_addr, client_len);
    printf("Response sent to client: \"%s\"\n", response);

    /* Step 6: Close the socket */
    printf("\nClosing server...\n");
    close(server_fd);

    printf("UDP Server shut down successfully.\n");
    return 0;
}
