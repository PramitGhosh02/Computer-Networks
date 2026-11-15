/*
 * TCP Client - Computer Networks Lab
 * 
 * Continuous communication TCP Client.
 * Connects to TCP server on port 8080 and continuously takes input
 * from the user, sends messages to the server, and prints responses
 * until the user types "exit" or closes the program.
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
    char message[BUFFER_SIZE] = {0};

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
    printf("Connected to server successfully!\n");
    printf("Type your messages below (type 'exit' to quit):\n");
    printf("===================================================\n\n");

    /* Step 4: Continuous communication loop */
    while (1) {
        printf("Enter message: ");
        memset(message, 0, BUFFER_SIZE);
        if (fgets(message, BUFFER_SIZE, stdin) == NULL) {
            /* End of input or closed window */
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
            send(sock_fd, message, strlen(message), 0);
            printf("Exiting chat...\n");
            break;
        }

        /* Send message to server */
        send(sock_fd, message, strlen(message), 0);
        printf("Message sent to server: \"%s\"\n", message);

        /* Receive server response */
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(sock_fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read <= 0) {
            printf("Server disconnected.\n");
            break;
        }
        printf("Response from server  : \"%s\"\n\n", buffer);
    }

    /* Step 5: Close socket */
    printf("\nClosing connection...\n");
    close(sock_fd);

    printf("TCP Client shut down successfully.\n");
    return 0;
}
