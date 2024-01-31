// calculate binomial coefficient using divide and conquer
#include <stdio.h>
#include <time.h>
 
// Returns value of Binomial Coefficient C(n, k)
int binomialCoeff(int n, int k)
{
    // Base Cases
    if (k > n)
        return 0;
    if (k == 0 || k == n)
        return 1;
 
    // Recur
    return binomialCoeff(n - 1, k - 1)
           + binomialCoeff(n - 1, k);
}
 
int main()
{
    clock_t start, end;
    double execution_time;
    start = clock();
    int n = 10345, k = 2;
    printf("Value of C(%d, %d) is %d ", n, k,
           binomialCoeff(n, k));
    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\n%lf seconds", execution_time);
    return 0;
}