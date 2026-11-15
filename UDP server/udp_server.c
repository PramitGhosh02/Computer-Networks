/*
 * UDP Server - Computer Networks Lab
 * 
 * Continuous communication UDP Server.
 * Listens on port 9090 and continuously receives datagrams in a loop
 * from clients, sending acknowledgments until client sends "exit"
 * or server is stopped.
 *
 * Transport Layer Protocol: UDP (connectionless, unreliable, fast)
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
    char response[BUFFER_SIZE * 2] = {0};
    int opt = 1;

    /* Step 1: Create a UDP socket (SOCK_DGRAM) */
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("UDP Server socket created successfully.\n");

    /* Prevent "Address already in use" on restart */
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

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

    /* UDP is connectionless — no listen() or accept() */
    printf("UDP Server is running on port %d...\n", PORT);
    printf("Ready to receive continuous datagrams...\n\n");

    /* Step 4: Continuous communication loop */
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int n = recvfrom(server_fd, buffer, BUFFER_SIZE - 1, 0,
                         (struct sockaddr *)&client_addr, &client_len);
        if (n <= 0) {
            continue;
        }
        buffer[n] = '\0';

        /* Check for exit command */
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("\nClient at %s:%d requested termination (exit).\n",
                   inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            break;
        }

        printf("Datagram from [%s:%d]: \"%s\"\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        /* Step 5: Send acknowledgment response back to client */
        snprintf(response, sizeof(response), "UDP Server ACK: Received '%s'", buffer);
        sendto(server_fd, response, strlen(response), 0,
               (struct sockaddr *)&client_addr, client_len);
        printf("ACK sent back to client: \"%s\"\n\n", response);
    }

    /* Step 6: Close the socket */
    printf("Closing UDP server...\n");
    close(server_fd);

    printf("UDP Server shut down successfully.\n");
    return 0;
}
