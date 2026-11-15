/*
 * UDP Client - Computer Networks Lab
 * 
 * Continuous communication UDP Client.
 * Continuously takes input from the user, sends datagrams to the
 * UDP server at port 9090, and receives acknowledgments until the
 * user types "exit" or closes the window.
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

int main(int argc, char *argv[]) {
    int sock_fd;
    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE] = {0};
    char *server_ip = "127.0.0.1"; /* Default: localhost */

    /* Accept Server IP as command-line argument (e.g., ./udp_client 192.168.1.15) */
    if (argc > 1) {
        server_ip = argv[1];
    }

    /* Step 1: Create a UDP socket (SOCK_DGRAM) */
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
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid IP address: %s\n", server_ip);
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("Ready to send datagrams to %s:%d\n", server_ip, PORT);
    printf("Type your messages below (type 'exit' to quit):\n");
    printf("===================================================\n\n");

    /* Step 3: Continuous communication loop */
    while (1) {
        printf("Enter message: ");
        memset(message, 0, BUFFER_SIZE);
        if (fgets(message, BUFFER_SIZE, stdin) == NULL) {
            break;
        }

        /* Remove trailing newline character */
        message[strcspn(message, "\r\n")] = 0;

        /* Skip empty messages */
        if (strlen(message) == 0) {
            continue;
        }

        /* Check for exit command */
        if (strcmp(message, "exit") == 0) {
            sendto(sock_fd, message, strlen(message), 0,
                   (struct sockaddr *)&server_addr, server_len);
            printf("Exiting UDP client...\n");
            break;
        }

        /* Send datagram to server */
        sendto(sock_fd, message, strlen(message), 0,
               (struct sockaddr *)&server_addr, server_len);
        printf("Datagram sent to server: \"%s\"\n", message);

        /* Receive server response */
        memset(buffer, 0, BUFFER_SIZE);
        int n = recvfrom(sock_fd, buffer, BUFFER_SIZE - 1, 0,
                         (struct sockaddr *)&server_addr, &server_len);
        if (n > 0) {
            buffer[n] = '\0';
            printf("Response from server   : \"%s\"\n\n", buffer);
        }
    }

    /* Step 4: Close socket */
    printf("\nClosing UDP client...\n");
    close(sock_fd);

    printf("UDP Client shut down successfully.\n");
    return 0;
}
