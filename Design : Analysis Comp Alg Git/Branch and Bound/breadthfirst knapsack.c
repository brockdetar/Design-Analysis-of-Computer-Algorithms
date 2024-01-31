#include <stdio.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int weight;
    int value;
} Item;

typedef struct {
    int level;
    int weight;
    int value;
    int* taken;
} Node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack_upper_bound(Node node, Item* items, int num_items, int capacity) {
    int total_value = node.value;
    int total_weight = node.weight;
    int remaining_capacity = capacity - total_weight;

    for (int i = node.level; i < num_items; i++) {
        if (items[i].weight <= remaining_capacity) {
            total_value += items[i].value;
            total_weight += items[i].weight;
            remaining_capacity -= items[i].weight;
        } else {
            double fraction = (double)remaining_capacity / items[i].weight;
            total_value += fraction * items[i].value;
            break;
        }
    }

    return total_value;
}

int knapsack_bf_bb(Item* items, int num_items, int capacity, int* best_taken) {
    int max_value = 0;
    Node stack[num_items];
    int top = -1;

    Node root = {0, 0, 0, NULL};
    root.taken = best_taken;
    stack[++top] = root;

    while (top >= 0) {
        Node node = stack[top--];
        if (node.value > max_value) {
            max_value = node.value;
            for (int i = 0; i < num_items; i++) {
                best_taken[i] = node.taken[i];
            }
        }

        if (node.level < num_items) {
            // Explore the left child (with the item included)
            Node left_child = {node.level + 1,
                               node.weight + items[node.level].weight,
                               node.value + items[node.level].value,
                               node.taken};
            left_child.taken[node.level] = 1;
            if (left_child.weight <= capacity &&
                knapsack_upper_bound(left_child, items, num_items, capacity) > max_value) {
                stack[++top] = left_child;
            }

            // Explore the right child (with the item excluded)
            Node right_child = {node.level + 1, node.weight, node.value, node.taken};
            right_child.taken[node.level] = 0;
            if (knapsack_upper_bound(right_child, items, num_items, capacity) > max_value) {
                stack[++top] = right_child;
            }
        }
    }

    return max_value;
}

int main() {
    clock_t start, end;
    double execution_time;
    start = clock();
    Item items[] = {{12, 2}, {4, 6}, {5, 6}, {6, 6}, {14, 9}, {4, 6}, {3, 12}, {5, 7}, {14, 5}, {2, 9}, {11, 12}, {2, 10}, {13, 15}, {6, 2}, {4, 10}, {6, 1}, {11, 6}, {7, 7}, {9, 13}, {4, 7}, {5, 6}, {3, 9}, {6, 11}, {5, 14}, {8, 1}, {12, 7}, {9, 13}, {11, 3}, {12, 7}, {4, 6}, {12, 13}, {10, 15}, {1, 2}, {3, 13}, {9, 12}, {14, 9}, {9, 7}, {5, 6}, {11, 8}, {1, 9}, {11, 3}, {13, 3}, {15, 8}, {6, 11}, {14, 8}, {2, 11}, {12, 15}, {7, 4}, {14, 1}, {9, 11}};
    int num_items = sizeof(items) / sizeof(items[0]);
    int capacity = 60;
    int best_taken[num_items];

    int max_value = knapsack_bf_bb(items, num_items, capacity, best_taken);

    printf("Maximum value: %d\n", max_value);
    /*printf("Items taken (0/1 for excluded/included): ");
    for (int i = 0; i < num_items; i++) {
        printf("%d ", best_taken[i]);
    }
    */
    printf("\n");

    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\n%lf seconds", execution_time);

    return 0;
}
