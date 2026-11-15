/*
 * Distance Vector Routing Algorithm - Computer Networks Lab
 * Standard Bellman-Ford implementation without emojis or decorative characters.
 */

#include <stdio.h>

struct node {
    unsigned dist[20];
    unsigned from[20];
} route[20];

int main() {
    int costmat[20][20];
    int nodes, i, j, k, count = 0;

    printf("Enter the number of nodes: ");
    if (scanf("%d", &nodes) != 1 || nodes <= 0 || nodes > 20) {
        printf("Invalid number of nodes.\n");
        return 1;
    }

    printf("Enter the cost matrix (enter 0 for self, 9999 for no direct link):\n");
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            scanf("%d", &costmat[i][j]);
            costmat[i][i] = 0;
            route[i].dist[j] = costmat[i][j];
            route[i].from[j] = j;
        }
    }

    /* Bellman-Ford iterative route calculation */
    do {
        count = 0;
        for (i = 0; i < nodes; i++) {
            for (j = 0; j < nodes; j++) {
                for (k = 0; k < nodes; k++) {
                    if (route[i].dist[j] > costmat[i][k] + route[k].dist[j]) {
                        route[i].dist[j] = costmat[i][k] + route[k].dist[j];
                        route[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    } while (count != 0);

    /* Display final routing tables */
    for (i = 0; i < nodes; i++) {
        printf("\nRouting table for router %d:\n", i + 1);
        printf("Destination\tNext Hop\tDistance\n");
        for (j = 0; j < nodes; j++) {
            printf("%d\t\t%d\t\t%d\n", j + 1, route[i].from[j] + 1, route[i].dist[j]);
        }
    }

    printf("\nRouting tables converged successfully.\n");
    return 0;
}
