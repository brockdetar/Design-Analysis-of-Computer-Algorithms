#include <stdio.h>
#include <time.h>

typedef struct {
    int weight;
    int value;
} Item;

void knapsack_branch_bound(Item items[], int n, int capacity, int curr_index,
                           int curr_weight, int curr_value, int selected[], int* best_value, int best_selected[]) {
    // Base case: If we have reached the end of the items or the knapsack capacity is 0
    if (curr_index == n || curr_weight == 0) {
        if (curr_value > *best_value) {
            *best_value = curr_value;
            for (int i = 0; i < n; i++) {
                best_selected[i] = selected[i];
            }
        }
        return;
    }

    // Exclude the current item and proceed with the next item
    knapsack_branch_bound(items, n, capacity, curr_index + 1, curr_weight, curr_value, selected, best_value, best_selected);

    // Include the current item if it doesn't exceed the capacity
    if (curr_weight + items[curr_index].weight <= capacity) {
        selected[curr_index] = 1;
        knapsack_branch_bound(items, n, capacity, curr_index + 1, curr_weight + items[curr_index].weight,
                             curr_value + items[curr_index].value, selected, best_value, best_selected);
        selected[curr_index] = 0;
    }
}

int main() {
    clock_t start, end;
    double execution_time;
    start = clock();
    Item items[] = {{12, 2}, {4, 6}, {5, 6}, {6, 6}, {14, 9}, {4, 6}, {3, 12}, {5, 7}, {14, 5}, {2, 9}, {11, 12}, {2, 10}, {13, 15}, {6, 2}, {4, 10}, {6, 1}, {11, 6}, {7, 7}, {9, 13}, {4, 7}, {5, 6}, {3, 9}, {6, 11}, {5, 14}, {8, 1}, {12, 7}, {9, 13}, {11, 3}, {12, 7}, {4, 6}, {12, 13}, {10, 15}, {1, 2}, {3, 13}, {9, 12}, {14, 9}, {9, 7}, {5, 6}, {11, 8}, {1, 9}, {11, 3}, {13, 3}, {15, 8}, {6, 11}, {14, 8}, {2, 11}, {12, 15}, {7, 4}, {14, 34}, {9, 11}};
    int capacity = 60;
    int n = sizeof(items) / sizeof(items[0]);;

    int best_value = 0;
    int selected[10] = {0}; // Properly initialize the selected array
    int best_selected[n];
    int total = 0;

    knapsack_branch_bound(items, n, capacity, 0, 0, 0, selected, &best_value, best_selected);

    //printf("Maximum value: %d\n", best_value);
    //printf("Selected items: ");
    for (int i = 0; i < n; i++) {
        if (best_selected[i]) {
            //printf("Item %d (Weight: %d, Value: %d) ", i + 1, items[i].weight, items[i].value);
            total += items[i].value;
        }
    }
    
    //printf("\n");
    printf("Total value: %d\n", total);
    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\n%lf seconds", execution_time);

    return 0;
}
