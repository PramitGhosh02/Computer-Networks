/*
 * Distance Vector Routing Algorithm - Computer Networks Lab
 *
 * This program simulates the Distance Vector Routing Algorithm
 * (Bellman-Ford) used in network routing protocols like RIP.
 *
 * Concept:
 *   - Each router maintains a distance table to all destinations
 *   - Routers exchange distance vectors with their neighbors
 *   - Each router updates its table using the Bellman-Ford equation:
 *       D(x,y) = min { cost(x,v) + D(v,y) } for all neighbors v
 *   - Process repeats until no more changes (convergence)
 *
 * Compile: gcc distance_vector.c -o distance_vector
 * Run:     ./distance_vector
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 20
#define INFINITY 9999

int cost[MAX_NODES][MAX_NODES];      /* Cost/adjacency matrix */
int dist[MAX_NODES][MAX_NODES];      /* Distance vector table */
int next_hop[MAX_NODES][MAX_NODES];  /* Next hop for routing */
int n;                                /* Number of nodes */

void initialize() {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            dist[i][j] = cost[i][j];
            if (cost[i][j] != INFINITY && i != j)
                next_hop[i][j] = j;   /* Direct neighbor */
            else if (i == j)
                next_hop[i][j] = i;   /* Self */
            else
                next_hop[i][j] = -1;  /* Unknown */
        }
    }
}

void print_distance_table(int node) {
    int j;
    printf("  ┌──────────────┬──────────┬──────────┐\n");
    printf("  │ Destination  │ Distance │ Next Hop │\n");
    printf("  ├──────────────┼──────────┼──────────┤\n");
    for (j = 0; j < n; j++) {
        if (dist[node][j] >= INFINITY)
            printf("  │    Node %d    │   INF    │    -     │\n", j);
        else
            printf("  │    Node %d    │   %3d    │    %d     │\n",
                   j, dist[node][j], next_hop[node][j]);
    }
    printf("  └──────────────┴──────────┴──────────┘\n");
}

int main() {
    int i, j, k;
    int iteration = 0;
    int updated;

    printf("╔════════════════════════════════════════════════╗\n");
    printf("║   DISTANCE VECTOR ROUTING ALGORITHM           ║\n");
    printf("║   (Bellman-Ford)                               ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    /* Get number of nodes */
    printf("Enter the number of nodes in the network: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_NODES) {
        printf("Error: Nodes must be between 1 and %d.\n", MAX_NODES);
        return 1;
    }

    /* Get the cost/adjacency matrix */
    printf("\nEnter the cost matrix (%d x %d):\n", n, n);
    printf("(Enter 0 for self, actual cost for neighbors,\n");
    printf(" and %d for no direct link)\n\n", INFINITY);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("  Cost from Node %d to Node %d: ", i, j);
            scanf("%d", &cost[i][j]);
        }
        printf("\n");
    }

    /* Initialize distance vectors */
    initialize();

    /* Print initial cost matrix */
    printf("============================================================\n");
    printf("   INITIAL COST MATRIX\n");
    printf("============================================================\n\n");
    printf("        ");
    for (j = 0; j < n; j++)
        printf("Node %-3d", j);
    printf("\n        ");
    for (j = 0; j < n; j++)
        printf("--------");
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("Node %d: ", i);
        for (j = 0; j < n; j++) {
            if (cost[i][j] >= INFINITY)
                printf("  INF   ");
            else
                printf("  %3d   ", cost[i][j]);
        }
        printf("\n");
    }

    /* Print initial distance tables */
    printf("\n============================================================\n");
    printf("   INITIAL DISTANCE TABLES (Before Exchange)\n");
    printf("============================================================\n\n");
    for (i = 0; i < n; i++) {
        printf("  Router %d:\n", i);
        print_distance_table(i);
        printf("\n");
    }

    /* Run the Distance Vector Algorithm */
    printf("============================================================\n");
    printf("   RUNNING DISTANCE VECTOR ALGORITHM...\n");
    printf("============================================================\n\n");

    do {
        updated = 0;
        iteration++;
        printf("────────────────────────────────────────────────\n");
        printf("  ITERATION %d\n", iteration);
        printf("────────────────────────────────────────────────\n\n");

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                for (k = 0; k < n; k++) {
                    /* Bellman-Ford: check if going through node k is shorter */
                    if (cost[i][k] + dist[k][j] < dist[i][j]) {
                        printf("  Node %d: Shorter path to %d found via %d"
                               " (old=%d, new=%d)\n",
                               i, j, k,
                               dist[i][j],
                               cost[i][k] + dist[k][j]);

                        dist[i][j] = cost[i][k] + dist[k][j];
                        next_hop[i][j] = k;
                        updated = 1;
                    }
                }
            }
        }

        if (!updated) {
            printf("  No changes — algorithm has CONVERGED.\n\n");
        } else {
            /* Print updated tables for this iteration */
            printf("\n  Updated Distance Tables:\n\n");
            for (i = 0; i < n; i++) {
                printf("  Router %d:\n", i);
                print_distance_table(i);
                printf("\n");
            }
        }

    } while (updated);

    /* Print final routing tables */
    printf("============================================================\n");
    printf("   FINAL ROUTING TABLES (After Convergence)\n");
    printf("   Converged in %d iteration(s)\n", iteration);
    printf("============================================================\n\n");

    for (i = 0; i < n; i++) {
        printf("  Router %d Routing Table:\n", i);
        print_distance_table(i);
        printf("\n");
    }

    /* Print shortest paths */
    printf("============================================================\n");
    printf("   SHORTEST PATHS SUMMARY\n");
    printf("============================================================\n\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j) {
                if (dist[i][j] >= INFINITY)
                    printf("  Node %d → Node %d : UNREACHABLE\n", i, j);
                else
                    printf("  Node %d → Node %d : Cost = %d, Next Hop = %d\n",
                           i, j, dist[i][j], next_hop[i][j]);
            }
        }
    }

    printf("\n============================================================\n");
    printf("   ALGORITHM COMPLETE\n");
    printf("============================================================\n\n");

    return 0;
}
