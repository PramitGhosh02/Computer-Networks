/*
 * Sliding Window Protocol - Computer Networks Lab
 *
 * This program simulates the Sliding Window Protocol used in
 * the Data Link Layer for flow control and reliable transmission.
 *
 * Features demonstrated:
 *   - Sender window and receiver window
 *   - Frame transmission and acknowledgment
 *   - Window sliding on receiving ACKs
 *   - Retransmission on timeout (simulated)
 *
 * Compile: gcc sliding_window.c -o sliding_window
 * Run:     ./sliding_window
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 20

void simulate_sliding_window(int total_frames, int window_size) {
    int i, j;
    int sent, acked;
    int window_start;
    int frame_status[MAX_FRAMES]; /* 0=unsent, 1=sent, 2=acked */

    /* Initialize all frames as unsent */
    for (i = 0; i < total_frames; i++)
        frame_status[i] = 0;

    printf("\n============================================================\n");
    printf("   SLIDING WINDOW PROTOCOL SIMULATION\n");
    printf("============================================================\n");
    printf("   Total Frames  : %d\n", total_frames);
    printf("   Window Size   : %d\n", window_size);
    printf("============================================================\n\n");

    srand(time(NULL));

    window_start = 0;

    while (window_start < total_frames) {
        /* Determine the current window boundaries */
        int window_end = window_start + window_size;
        if (window_end > total_frames)
            window_end = total_frames;

        printf("┌────────────────────────────────────────────────┐\n");
        printf("│  WINDOW POSITION: [%d - %d]                     \n",
               window_start, window_end - 1);
        printf("└────────────────────────────────────────────────┘\n\n");

        /* SENDER: Send all frames within the current window */
        printf("  SENDER: Transmitting frames in window...\n");
        for (i = window_start; i < window_end; i++) {
            printf("    → Sending Frame %d", i);
            frame_status[i] = 1; /* Mark as sent */

            /* Simulate random frame loss (20% chance) */
            if (rand() % 5 == 0) {
                printf("  ✗ [LOST IN TRANSIT]\n");
                frame_status[i] = 0; /* Mark as lost (needs resend) */
            } else {
                printf("  ✓ [SENT SUCCESSFULLY]\n");
            }
        }

        printf("\n  RECEIVER: Sending acknowledgments...\n");

        /* RECEIVER: Check frames and send ACKs */
        int all_acked = 1;
        for (i = window_start; i < window_end; i++) {
            if (frame_status[i] == 1) {
                /* Frame received successfully — send ACK */
                printf("    ← ACK for Frame %d received\n", i);
                frame_status[i] = 2; /* Mark as acknowledged */
            } else if (frame_status[i] == 0) {
                /* Frame was lost — no ACK, need retransmission */
                printf("    ✗ No ACK for Frame %d (lost, needs retransmission)\n", i);
                all_acked = 0;
            }
        }

        /* Retransmit lost frames */
        if (!all_acked) {
            printf("\n  SENDER: Retransmitting lost frames...\n");
            for (i = window_start; i < window_end; i++) {
                if (frame_status[i] == 0) {
                    printf("    → Retransmitting Frame %d", i);
                    frame_status[i] = 1;

                    /* Retransmission succeeds */
                    printf("  ✓ [SENT SUCCESSFULLY]\n");
                    printf("    ← ACK for Frame %d received\n", i);
                    frame_status[i] = 2;
                }
            }
        }

        /* Slide the window forward */
        printf("\n  WINDOW: Sliding forward...\n");
        window_start = window_end;

        /* Display frame status */
        printf("\n  FRAME STATUS: ");
        for (i = 0; i < total_frames; i++) {
            if (frame_status[i] == 2)
                printf("[%d:✓] ", i);
            else if (frame_status[i] == 1)
                printf("[%d:→] ", i);
            else
                printf("[%d: ] ", i);
        }
        printf("\n");

        /* Display window position visually */
        printf("  WINDOW:       ");
        for (i = 0; i < total_frames; i++) {
            if (i >= window_start && i < window_start + window_size && i < total_frames)
                printf(" ^^^  ");
            else
                printf("      ");
        }
        printf("\n\n");

        printf("  ────────────────────────────────────────────────\n\n");
    }

    printf("============================================================\n");
    printf("   ALL %d FRAMES TRANSMITTED AND ACKNOWLEDGED SUCCESSFULLY!\n", total_frames);
    printf("============================================================\n\n");
}

int main() {
    int total_frames, window_size;

    printf("╔════════════════════════════════════════════════╗\n");
    printf("║      SLIDING WINDOW PROTOCOL SIMULATION       ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    /* Get input from user */
    printf("Enter the total number of frames to send: ");
    scanf("%d", &total_frames);

    if (total_frames <= 0 || total_frames > MAX_FRAMES) {
        printf("Error: Number of frames must be between 1 and %d.\n", MAX_FRAMES);
        return 1;
    }

    printf("Enter the window size: ");
    scanf("%d", &window_size);

    if (window_size <= 0 || window_size > total_frames) {
        printf("Error: Window size must be between 1 and %d.\n", total_frames);
        return 1;
    }

    /* Run the simulation */
    simulate_sliding_window(total_frames, window_size);

    return 0;
}
