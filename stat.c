#include <stdio.h>
#include <math.h>  // Для pow()

#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v,
                   int min_v,
                   double mean_v,
                   double variance_v);

int main()
{
    int n, data[NMAX];
    
    // Проверяем корректность ввода
    if (input(data, &n) != 0) {
        printf("n/a");
        return 1;
    }
    
    output(data, n);
    printf("\n");
    output_result(max(data, n),
                  min(data, n),
                  mean(data, n),
                  variance(data, n));

    return 0;
}

int input(int *a, int *n)
{
    // Читаем размер массива
    if (scanf("%d", n) != 1) {
        return 1;
    }
    
    // Проверяем корректность размера
    if (*n <= 0 || *n > NMAX) {
        return 1;
    }
    
    // Читаем элементы массива
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            return 1;
        }
    }
    
    return 0;
}

void output(int *a, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
}

int max(int *a, int n)
{
    int max_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max_val) {
            max_val = a[i];
        }
    }
    return max_val;
}

int min(int *a, int n)
{
    int min_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min_val) {
            min_val = a[i];
        }
    }
    return min_val;
}

double mean(int *a, int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum / n;
}

double variance(int *a, int n)
{
    double m = mean(a, n);
    double sum_squares = 0.0;
    
    for (int i = 0; i < n; i++) {
        sum_squares += pow(a[i] - m, 2);
    }
    
    return sum_squares / n;
}

void output_result(int max_v,
                   int min_v,
                   double mean_v,
                   double variance_v)
{
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}
