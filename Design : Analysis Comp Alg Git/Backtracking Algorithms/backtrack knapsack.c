#include <stdio.h>
#include <time.h>

void knapsack_backtrack(int weights[], int values[], int capacity, int n, int curr_index,
                        int curr_weight, int curr_value, int selection[], int* best_value, int best_selection[]) {
    // If no items left or weight is 0
    if (curr_index == n || curr_weight == 0) {
        if (curr_value > *best_value) {
            *best_value = curr_value;
            for (int i = 0; i < n; i++) {
                best_selection[i] = selection[i];
            }
        }
        return;
    }

    // Ignore current item and proceed with the next item
    knapsack_backtrack(weights, values, capacity, n, curr_index + 1, curr_weight, curr_value, selection, best_value, best_selection);

    // Include the current item if it doesn't exceed the capacity
    if (curr_weight + weights[curr_index] <= capacity) {
        selection[curr_index] = 1;
        knapsack_backtrack(weights, values, capacity, n, curr_index + 1, curr_weight + weights[curr_index],
                           curr_value + values[curr_index], selection, best_value, best_selection);
        selection[curr_index] = 0;
    }
}

void printKnapsackItems(int weights[], int values[], int best_value, int best_selection[], int n, int tester123) {
    //printf("Maximum value: %d\n", best_value);
    //printf("Selected items: ");
    for (int i = 0; i < n; i++) {
        if (best_selection[i]) {
            printf("Item %d (Weight: %d, Value: %d) ", i + 1, weights[i], values[i]);
            tester123 = tester123 + values[i];
            //printf("tester123: %d\n", tester123);
        }
    }
    printf("\n");
    printf("Total value: %d\n", tester123);
}

int main() {
    clock_t start, end;
    double execution_time;
    start = clock();
    int weights[] = {9,7,14,4,1,3,2,3,5,8};
    int values[] = {7,8,1,5,9,10,13,14,29,10};
    // 9 7 7 8 14 1 4 5 1 9 13 4 2 3 3 14 5 15 8 10
    int capacity = 10;
    int n = sizeof(weights) / sizeof(weights[0]);

    int best_value = 0;
    int selection[10] = {0};
    int best_selection[n];
    int tester123 = 0;

    knapsack_backtrack(weights, values, capacity, n, 0, 0, 0, selection, &best_value, best_selection);

    printKnapsackItems(weights, values, best_value, best_selection, n, tester123);
    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\n%lf seconds", execution_time);

    return 0;
}
