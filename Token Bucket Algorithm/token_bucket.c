/*
 * Token Bucket Algorithm - Computer Networks Lab
 * Standard lab implementation without emojis or decorative characters.
 */

#include <stdio.h>

int main() {
    int bucket_size, token_rate, n;
    int incoming, tokens = 0, sent, dropped;
    int i;

    printf("Enter token bucket capacity: ");
    if (scanf("%d", &bucket_size) != 1 || bucket_size <= 0) {
        printf("Invalid bucket capacity.\n");
        return 1;
    }

    printf("Enter token arrival rate: ");
    if (scanf("%d", &token_rate) != 1 || token_rate <= 0) {
        printf("Invalid token rate.\n");
        return 1;
    }

    printf("Enter number of time units: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of time units.\n");
        return 1;
    }

    int packet[50];
    printf("Enter packets arriving at each time unit: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &packet[i]);
    }

    printf("\nTime\tIncoming\tTokens\tSent\tRemaining Tokens\tDropped\n");

    for (i = 0; i < n; i++) {
        incoming = packet[i];
        tokens += token_rate;
        if (tokens > bucket_size) {
            tokens = bucket_size;
        }

        int available_tokens = tokens;

        if (incoming <= tokens) {
            sent = incoming;
            tokens -= incoming;
            dropped = 0;
        } else {
            sent = tokens;
            dropped = incoming - tokens;
            tokens = 0;
        }

        printf("%d\t%d\t\t%d\t%d\t%d\t\t\t%d\n", i + 1, incoming, available_tokens, sent, tokens, dropped);
    }

    printf("\nAll packets processed successfully.\n");
    return 0;
}
