#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main()
{
    int n, data[NMAX];
    if (input(data, &n) != 0) {  // Передаем адрес n
        printf("n/a");
        return 1;
    }
    squaring(data, n);
    output(data, n);

    return 0;
}

int input(int *a, int *n)
{
    if (scanf("%d", n) != 1) {  // Читаем в *n, проверяем успешность
        return 1;  // Ошибка ввода
    }
    
    if (*n <= 0 || *n > NMAX) {  // Проверяем корректность n
        return 1;
    }
    
    for(int *p = a; p - a < *n; p++)
    {
        if (scanf("%d", p) != 1) {  // Проверяем успешность чтения каждого числа
            return 1;
        }
    }
    return 0;  // Успешный ввод
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

void squaring(int *a, int n)
{
    for (int i = 0; i < n; i++) {
        a[i] = a[i] * a[i];
    }
}
