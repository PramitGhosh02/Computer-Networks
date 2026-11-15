/*
 * Token Bucket Algorithm - Computer Networks Lab
 *
 * The Token Bucket Algorithm is a traffic shaping mechanism that
 * controls the rate of data transmission while ALLOWING SHORT BURSTS.
 *
 * Concept:
 *   - Tokens are added to the bucket at a fixed rate
 *   - The bucket has a maximum token capacity
 *   - Each packet requires one token to be transmitted
 *   - If tokens are available → packet is SENT (token consumed)
 *   - If no tokens available → packet is DROPPED / queued
 *   - Unlike Leaky Bucket, bursts ARE allowed (up to token count)
 *
 * Key difference from Leaky Bucket:
 *   Leaky Bucket  → constant output, drops excess
 *   Token Bucket  → allows bursts, more flexible
 *
 * Compile: gcc token_bucket.c -o token_bucket
 * Run:     ./token_bucket
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TIME 10

int main() {
    int bucket_size, token_rate;
    int incoming[MAX_TIME];
    int tokens = 0;
    int i;
    int total_received = 0, total_sent = 0, total_dropped = 0;

    printf("╔════════════════════════════════════════════════╗\n");
    printf("║      TOKEN BUCKET ALGORITHM SIMULATION        ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    /* Get bucket parameters from user */
    printf("Enter token bucket size (max tokens): ");
    scanf("%d", &bucket_size);

    printf("Enter token arrival rate (tokens added per tick): ");
    scanf("%d", &token_rate);

    /* Generate incoming packet traffic */
    srand(time(NULL));
    printf("\nUse random traffic? (1=Yes, 0=No): ");
    int use_random;
    scanf("%d", &use_random);

    if (use_random) {
        printf("\nAuto-generated incoming traffic:\n");
        for (i = 0; i < MAX_TIME; i++) {
            incoming[i] = rand() % (bucket_size + 3);
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
    printf("   Bucket Size: %d | Token Rate: %d tokens/tick\n", bucket_size, token_rate);
    printf("============================================================\n\n");

    printf("┌──────┬──────────┬────────┬──────────┬────────┬─────────┐\n");
    printf("│ Time │ Incoming │ Tokens │ Packets  │ Tokens │ Dropped │\n");
    printf("│      │ Packets  │ Avail  │ Sent     │ Left   │ Packets │\n");
    printf("├──────┼──────────┼────────┼──────────┼────────┼─────────┤\n");

    for (i = 0; i < MAX_TIME; i++) {
        int dropped = 0;
        int sent = 0;

        /* Step 1: Add tokens at the fixed rate */
        tokens += token_rate;

        /* Step 2: Cap tokens at bucket capacity */
        if (tokens > bucket_size) {
            tokens = bucket_size;
        }

        int tokens_before = tokens;
        total_received += incoming[i];

        /* Step 3: Transmit packets (one token per packet) */
        if (incoming[i] <= tokens) {
            /* Enough tokens for all packets — send all (burst allowed!) */
            sent = incoming[i];
            tokens -= sent;
        } else {
            /* Not enough tokens — send what we can, drop the rest */
            sent = tokens;
            dropped = incoming[i] - tokens;
            tokens = 0;
        }

        total_sent += sent;
        total_dropped += dropped;

        /* Print the state for this time unit */
        printf("│  %2d  │    %3d   │  %3d   │    %3d   │  %3d   │   %3d   │\n",
               i + 1, incoming[i], tokens_before, sent, tokens, dropped);
    }

    printf("└──────┴──────────┴────────┴──────────┴────────┴─────────┘\n");

    /* Print summary */
    printf("\n============================================================\n");
    printf("   SIMULATION SUMMARY\n");
    printf("============================================================\n");
    printf("   Total packets received : %d\n", total_received);
    printf("   Total packets sent     : %d\n", total_sent);
    printf("   Total packets dropped  : %d\n", total_dropped);
    printf("   Tokens remaining       : %d\n", tokens);
    printf("============================================================\n\n");

    /* Visual representation */
    printf("   TOKEN BUCKET CONCEPT:\n\n");
    printf("     Token Generator           Incoming Packets\n");
    printf("         │                         │ │ │\n");
    printf("         ▼ (%d tokens/tick)         ▼ ▼ ▼\n", token_rate);
    printf("       ┌───────┐               ┌───────────┐\n");
    printf("       │ T T T │               │  Packets  │\n");
    printf("       │ T T   │ Token         │  waiting  │\n");
    printf("       │ T     │ Bucket        └─────┬─────┘\n");
    printf("       └───┬───┘ (max=%d)            │\n", bucket_size);
    printf("           │                         │\n");
    printf("           └─────────┬───────────────┘\n");
    printf("                     │\n");
    printf("                     ▼\n");
    printf("              ┌─────────────┐\n");
    printf("              │ Has token?  │\n");
    printf("              └──┬───────┬──┘\n");
    printf("            YES  │       │  NO\n");
    printf("                 ▼       ▼\n");
    printf("              SEND     DROP\n");
    printf("            (consume  (no token\n");
    printf("             token)   available)\n\n");

    /* Comparison table */
    printf("   LEAKY BUCKET vs TOKEN BUCKET:\n");
    printf("   ┌────────────────┬──────────────────┬──────────────────┐\n");
    printf("   │ Feature        │ Leaky Bucket     │ Token Bucket     │\n");
    printf("   ├────────────────┼──────────────────┼──────────────────┤\n");
    printf("   │ Output rate    │ Always constant  │ Variable (burst) │\n");
    printf("   │ Bursts allowed │ No               │ Yes              │\n");
    printf("   │ Mechanism      │ Fixed leak rate   │ Token consumed   │\n");
    printf("   │ Overflow       │ Packets dropped  │ Tokens capped    │\n");
    printf("   │ Idle periods   │ Wasted capacity  │ Tokens saved up  │\n");
    printf("   └────────────────┴──────────────────┴──────────────────┘\n\n");

    return 0;
}
