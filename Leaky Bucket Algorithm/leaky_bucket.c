/*
 * Leaky Bucket Algorithm - Computer Networks Lab
 *
 * The Leaky Bucket Algorithm is a traffic shaping mechanism used
 * in computer networks to control the rate of data transmission.
 *
 * Concept:
 *   - A bucket has a fixed capacity (buffer size)
 *   - Packets arrive at varying (bursty) rates and fill the bucket
 *   - The bucket "leaks" (transmits) at a constant fixed rate
 *   - If the bucket overflows, excess packets are DROPPED
 *   - This smooths out bursty traffic into a steady output
 *
 * Compile: gcc leaky_bucket.c -o leaky_bucket
 * Run:     ./leaky_bucket
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TIME 10

int main() {
    int bucket_size, leak_rate;
    int incoming[MAX_TIME];
    int bucket_level = 0;
    int i;
    int total_received = 0, total_sent = 0, total_dropped = 0;

    printf("╔════════════════════════════════════════════════╗\n");
    printf("║       LEAKY BUCKET ALGORITHM SIMULATION       ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    /* Get bucket parameters from user */
    printf("Enter bucket size (max capacity): ");
    scanf("%d", &bucket_size);

    printf("Enter leak rate (packets sent per tick): ");
    scanf("%d", &leak_rate);

    /* Generate random incoming packet bursts */
    srand(time(NULL));
    printf("\nEnter the number of incoming packets for each time unit:\n");
    printf("(Enter %d values, or enter 0 to auto-generate random traffic)\n\n", MAX_TIME);

    printf("Use random traffic? (1=Yes, 0=No): ");
    int use_random;
    scanf("%d", &use_random);

    if (use_random) {
        printf("\nAuto-generated incoming traffic:\n");
        for (i = 0; i < MAX_TIME; i++) {
            incoming[i] = rand() % (bucket_size + 3); /* Random bursty traffic */
            printf("  Time %d: %d packets\n", i + 1, incoming[i]);
        }
    } else {
        printf("\nEnter incoming packets for each time unit:\n");
        for (i = 0; i < MAX_TIME; i++) {
            printf("  Time %d: ", i + 1);
            scanf("%d", &incoming[i]);
        }
    }

    /* Simulation */
    printf("\n============================================================\n");
    printf("   SIMULATION START\n");
    printf("   Bucket Size: %d | Leak Rate: %d packets/tick\n", bucket_size, leak_rate);
    printf("============================================================\n\n");

    printf("┌──────┬──────────┬────────┬──────────┬────────┬─────────┐\n");
    printf("│ Time │ Incoming │ In     │ Leaked   │ Bucket │ Dropped │\n");
    printf("│      │ Packets  │ Bucket │ (Output) │ Level  │ Packets │\n");
    printf("├──────┼──────────┼────────┼──────────┼────────┼─────────┤\n");

    for (i = 0; i < MAX_TIME; i++) {
        int dropped = 0;
        int leaked = 0;
        int added = 0;

        /* Step 1: Add incoming packets to the bucket */
        added = incoming[i];
        bucket_level += added;
        total_received += added;

        /* Step 2: Check for overflow — drop excess packets */
        if (bucket_level > bucket_size) {
            dropped = bucket_level - bucket_size;
            bucket_level = bucket_size;
            total_dropped += dropped;
        }

        /* Step 3: Leak (transmit) packets at the fixed rate */
        if (bucket_level > 0) {
            if (bucket_level >= leak_rate) {
                leaked = leak_rate;
            } else {
                leaked = bucket_level;
            }
            bucket_level -= leaked;
            total_sent += leaked;
        }

        /* Print the state for this time unit */
        printf("│  %2d  │    %3d   │  %3d   │    %3d   │  %3d   │   %3d   │\n",
               i + 1, incoming[i], added, leaked, bucket_level, dropped);
    }

    printf("└──────┴──────────┴────────┴──────────┴────────┴─────────┘\n");

    /* Print summary */
    printf("\n============================================================\n");
    printf("   SIMULATION SUMMARY\n");
    printf("============================================================\n");
    printf("   Total packets received  : %d\n", total_received);
    printf("   Total packets sent (out): %d\n", total_sent);
    printf("   Total packets dropped   : %d\n", total_dropped);
    printf("   Packets remaining       : %d\n", bucket_level);
    printf("============================================================\n\n");

    /* Visual representation */
    printf("   LEAKY BUCKET CONCEPT:\n\n");
    printf("     Incoming (bursty)        Output (constant rate)\n");
    printf("         │ │ │                      │\n");
    printf("         ▼ ▼ ▼                      │\n");
    printf("       ┌───────┐                    │\n");
    printf("       │~~~~~~~│ ← Bucket           │\n");
    printf("       │~~~~~~~│   (capacity=%d)     │\n", bucket_size);
    printf("       │       │                    │\n");
    printf("       └───┬───┘                    │\n");
    printf("           │                        │\n");
    printf("           ▼                        ▼\n");
    printf("     Leak rate = %d              Smooth\n", leak_rate);
    printf("     packets/tick              output\n\n");
    printf("   * Overflow packets are DROPPED\n");
    printf("   * Output rate never exceeds the leak rate\n\n");

    return 0;
}
