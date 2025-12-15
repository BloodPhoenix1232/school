#include <stdio.h>
#include <math.h>

#define NMAX 30

int input(int *a, int *n);
void output(int result);
int search(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

int main()
{
    int n, data[NMAX];
    
    if (input(data, &n) != 0) {
        printf("n/a");
        return 1;
    }
    
    int result = search(data, n);
    output(result);
    
    return 0;
}

int input(int *a, int *n)
{
    if (scanf("%d", n) != 1) {
        return 1;
    }
    
    if (*n <= 0 || *n > NMAX) {
        return 1;
    }
    
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            return 1;
        }
    }
    
    return 0;
}

void output(int result)
{
    printf("%d", result);
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
        sum_squares += (a[i] - m) * (a[i] - m);
    }
    
    return sum_squares / n;
}

int search(int *a, int n)
{
    double m = mean(a, n);
    double v = variance(a, n);
    double sigma = sqrt(v);
    double upper_bound = m + 3 * sigma;
    
    for (int i = 0; i < n; i++) {
        int value = a[i];
        
        // Проверяем все условия:
        // 1. Число четное (value % 2 == 0)
        // 2. Больше или равно среднему (value >= m)
        // 3. Меньше или равно среднему + 3*сигма (value <= upper_bound)
        // 4. Не равно 0 (value != 0)
        if (value % 2 == 0 && 
            value >= m && 
            value <= upper_bound && 
            value != 0) {
            return value;  // Первое подходящее число
        }
    }
    
    return 0;  // Ничего не нашли
}
