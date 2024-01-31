#include <stdio.h>
# include<time.h>
 
// maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }
 
// Returns the maximum value that can be put in a knapsack of capacity
int knapSack(int W, int wt[], int val[], int n)
{
    
    if (n == 0 || W == 0)
        return 0;
 
    if (wt[n - 1] > W)
        return knapSack(W, wt, val, n - 1);
 
    // Return the maximum of two cases:
    else
        return max(
            val[n - 1]
                + knapSack(W - wt[n - 1], wt, val, n - 1),
            knapSack(W, wt, val, n - 1));
}
 
int main()
{
    clock_t start, end;
    double execution_time;
    start = clock();
    int profit[] = { 16, 13, 9, 20, 1, 6, 11, 18, 13, 19 };
    int weight[] = {9, 10, 11, 3, 13, 17, 19, 11, 3, 9, };
    int W = 60;
    int n = sizeof(profit) / sizeof(profit[0]);
    printf("Maximum Profit: %d", knapSack(W, weight, profit, n));
    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\n%lf seconds", execution_time);
    return 0;
}