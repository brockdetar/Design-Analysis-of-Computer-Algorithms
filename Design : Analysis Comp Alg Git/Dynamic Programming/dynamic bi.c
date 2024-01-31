
#include <stdio.h>
#include <time.h>


// returns minimum of two integers
int min(int a, int b);

// Returns value of Binomial Coefficient C(n, k)
int binomialCoeff(int n, int k)
{
	int C[n + 1][k + 1];
	int i, j;

	// Calculate value of Binomial Coefficient
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= min(i, k); j++) {
			// Base Cases
			if (j == 0 || j == i)
				C[i][j] = 1;

			else
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}

	return C[n][k];
}


// minimum of two integers
int min(int a, int b) { return (a < b) ? a : b; }


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
