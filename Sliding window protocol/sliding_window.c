/*
 * Sliding Window Protocol - Computer Networks Lab
 * Standard lab implementation without emojis or decorative characters.
 */

#include <stdio.h>

int main() {
    int window_size, total_frames;
    int frames[50];
    int i, j;

    printf("Enter window size: ");
    if (scanf("%d", &window_size) != 1 || window_size <= 0) {
        printf("Invalid window size.\n");
        return 1;
    }

    printf("Enter total number of frames: ");
    if (scanf("%d", &total_frames) != 1 || total_frames <= 0) {
        printf("Invalid number of frames.\n");
        return 1;
    }

    printf("Enter %d frames: ", total_frames);
    for (i = 0; i < total_frames; i++) {
        scanf("%d", &frames[i]);
    }

    printf("\nSliding Window Protocol Simulation:\n");
    printf("Sender transmits up to %d frames before waiting for acknowledgement.\n\n", window_size);

    i = 0;
    while (i < total_frames) {
        int end = i + window_size;
        if (end > total_frames) {
            end = total_frames;
        }

        /* Sending frames in the current window */
        for (j = i; j < end; j++) {
            printf("Sending frame: %d\n", frames[j]);
        }

        /* Receiving acknowledgments for the sent window */
        for (j = i; j < end; j++) {
            printf("Acknowledgement received for frame: %d\n", frames[j]);
        }

        i = end;
        printf("\n");
    }

    printf("All frames transmitted and acknowledged successfully.\n");
    return 0;
}
