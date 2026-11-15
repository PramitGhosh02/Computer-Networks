/*
 * Leaky Bucket Algorithm - Computer Networks Lab
 * Standard lab implementation without emojis or decorative characters.
 */

#include <stdio.h>

int main() {
    int bucket_size, output_rate, n;
    int incoming, current = 0, dropped, sent;
    int i;

    printf("Enter bucket size: ");
    if (scanf("%d", &bucket_size) != 1 || bucket_size <= 0) {
        printf("Invalid bucket size.\n");
        return 1;
    }

    printf("Enter output rate: ");
    if (scanf("%d", &output_rate) != 1 || output_rate <= 0) {
        printf("Invalid output rate.\n");
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

    printf("\nTime\tIncoming\tSent\tRemaining\tDropped\n");

    for (i = 0; i < n; i++) {
        incoming = packet[i];
        if (incoming + current > bucket_size) {
            dropped = (incoming + current) - bucket_size;
            current = bucket_size;
        } else {
            dropped = 0;
            current += incoming;
        }

        if (current <= output_rate) {
            sent = current;
            current = 0;
        } else {
            sent = output_rate;
            current -= output_rate;
        }

        printf("%d\t%d\t\t%d\t%d\t\t%d\n", i + 1, incoming, sent, current, dropped);
    }

    while (current > 0) {
        i++;
        if (current <= output_rate) {
            sent = current;
            current = 0;
        } else {
            sent = output_rate;
            current -= output_rate;
        }
        printf("%d\t0\t\t%d\t%d\t\t0\n", i, sent, current);
    }

    printf("\nAll packets processed successfully.\n");
    return 0;
}
