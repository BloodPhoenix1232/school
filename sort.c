#include <stdio.h>

#define NMAX 10

int input(int *a, int n);
void output(int *a, int n);
void sort(int *a, int n);
void swap(int *a, int *b);

int main()
{
    int data[NMAX];
    
    if (input(data, NMAX) != 0) {
        printf("n/a");
        return 1;
    }
    
    sort(data, NMAX);
    output(data, NMAX);
    
    return 0;
}

int input(int *a, int n)
{
    for (int i = 0; i < n; i++) {
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

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int *a, int n)
{
    // Используем сортировку пузырьком (Bubble Sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}
