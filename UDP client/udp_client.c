/*
 * UDP Client - Computer Networks Lab
 * 
 * This program demonstrates a UDP (User Datagram Protocol) client
 * that sends a datagram to a UDP server and receives a response.
 *
 * Transport Layer Protocol: UDP (connectionless, unreliable, fast)
 *
 * Key difference from TCP client:
 *   - No connect() needed (connectionless)
 *   - Uses sendto() and recvfrom() instead of send/read
 *
 * Run the UDP server first, then run this client.
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
    int sock_fd;
    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE] = {0};
    char *message = "Hello from UDP Client!";

    /* Step 1: Create a UDP socket (SOCK_DGRAM for datagrams) */
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("UDP Client socket created successfully.\n");

    /* Step 2: Configure the server address to send to */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;       /* IPv4 */
    server_addr.sin_port = htons(PORT);     /* Server port */

    /* Convert IP address from text to binary form */
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    /* No connect() needed — UDP is connectionless! */

    /* Step 3: Send a datagram to the server */
    printf("Sending datagram to server at 127.0.0.1:%d...\n", PORT);
    sendto(sock_fd, message, strlen(message), 0,
           (struct sockaddr *)&server_addr, server_len);
    printf("Message sent to server: \"%s\"\n", message);

    /* Step 4: Receive the server's response */
    int n = recvfrom(sock_fd, buffer, BUFFER_SIZE, 0,
                     (struct sockaddr *)&server_addr, &server_len);
    buffer[n] = '\0';
    printf("Response from server : \"%s\"\n", buffer);

    /* Step 5: Close the socket */
    printf("\nClosing client...\n");
    close(sock_fd);

    printf("UDP Client shut down successfully.\n");
    return 0;
}
