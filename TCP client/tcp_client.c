/*
 * TCP Client - Computer Networks Lab
 * 
 * This program demonstrates a TCP (Transmission Control Protocol) client
 * that connects to a TCP server, sends a message, and receives a response.
 *
 * Transport Layer Protocol: TCP (connection-oriented, reliable delivery)
 *
 * Run the TCP server first, then run this client.
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
    int sock_fd;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE] = {0};
    char *message = "Hello from TCP Client!";

    /* Step 1: Create a TCP socket */
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("TCP Client socket created successfully.\n");

    /* Step 2: Configure the server address to connect to */
    server_address.sin_family = AF_INET;       /* IPv4 */
    server_address.sin_port = htons(PORT);     /* Server port */

    /* Convert IP address from text to binary form */
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    /* Step 3: Connect to the server */
    printf("Connecting to server at 127.0.0.1:%d...\n", PORT);
    if (connect(sock_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server successfully!\n\n");

    /* Step 4: Send a message to the server */
    send(sock_fd, message, strlen(message), 0);
    printf("Message sent to server: \"%s\"\n", message);

    /* Step 5: Receive the server's response */
    read(sock_fd, buffer, BUFFER_SIZE);
    printf("Response from server : \"%s\"\n", buffer);

    /* Step 6: Close the socket */
    printf("\nClosing connection...\n");
    close(sock_fd);

    printf("TCP Client shut down successfully.\n");
    return 0;
}
