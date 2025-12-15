#include <stdio.h>

#define LEN 100

int input(int *buffer, int *length);
void output(int *buffer, int length);
void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
int compare(int *buff1, int len1, int *buff2, int len2);
void remove_leading_zeros(int *buffer, int *length);

int main()
{
    int buff1[LEN], buff2[LEN];
    int len1, len2;
    
    // Ввод первого числа
    if (input(buff1, &len1) != 0) {
        printf("n/a");
        return 1;
    }
    
    // Ввод второго числа
    if (input(buff2, &len2) != 0) {
        printf("n/a");
        return 1;
    }
    
    // Удаляем ведущие нули
    remove_leading_zeros(buff1, &len1);
    remove_leading_zeros(buff2, &len2);
    
    // Если после удаления ведущих нулей длина стала 0, значит число было 0
    if (len1 == 0) {
        len1 = 1;
        buff1[0] = 0;
    }
    if (len2 == 0) {
        len2 = 1;
        buff2[0] = 0;
    }
    
    // Сложение
    int result_sum[LEN];
    int result_sum_len;
    sum(buff1, len1, buff2, len2, result_sum, &result_sum_len);
    output(result_sum, result_sum_len);
    printf("\n");
    
    // Вычитание
    int result_sub[LEN];
    int result_sub_len;
    
    // Проверяем, что уменьшаемое больше или равно вычитаемому
    if (compare(buff1, len1, buff2, len2) < 0) {
        printf("n/a");
    } else {
        sub(buff1, len1, buff2, len2, result_sub, &result_sub_len);
        output(result_sub, result_sub_len);
    }
    
    return 0;
}

int input(int *buffer, int *length)
{
    *length = 0;
    int temp;
    
    // Читаем числа пока не конец строки или не достигнут максимум
    while (scanf("%d", &temp) == 1) {
        // Проверяем, что цифра от 0 до 9
        if (temp < 0 || temp > 9) {
            return 1;
        }
        
        // Проверяем, что не превысили максимальную длину
        if (*length >= LEN) {
            return 1;
        }
        
        buffer[*length] = temp;
        (*length)++;
        
        // Проверяем следующий символ
        char next_char = getchar();
        if (next_char == '\n' || next_char == EOF) {
            break;
        }
        if (next_char != ' ') {
            return 1;
        }
    }
    
    // Если ничего не прочитали
    if (*length == 0) {
        return 1;
    }
    
    return 0;
}

void output(int *buffer, int length)
{
    for (int i = 0; i < length; i++) {
        printf("%d", buffer[i]);
        if (i < length - 1) {
            printf(" ");
        }
    }
}

// Сравнение двух чисел
// Возвращает: 1 если buff1 > buff2, 0 если равны, -1 если buff1 < buff2
int compare(int *buff1, int len1, int *buff2, int len2)
{
    // Сначала сравниваем длины
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;
    
    // Если длины равны, сравниваем поразрядно
    for (int i = 0; i < len1; i++) {
        if (buff1[i] > buff2[i]) return 1;
        if (buff1[i] < buff2[i]) return -1;
    }
    
    return 0;  // Числа равны
}

// Удаление ведущих нулей
void remove_leading_zeros(int *buffer, int *length)
{
    int i = 0;
    // Находим первую ненулевую цифру
    while (i < *length - 1 && buffer[i] == 0) {
        i++;
    }
    
    // Сдвигаем массив в начало
    if (i > 0) {
        for (int j = 0; j < *length - i; j++) {
            buffer[j] = buffer[j + i];
        }
        *length = *length - i;
    }
}

// Сложение двух больших чисел
void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length)
{
    int carry = 0;  // Перенос
    int i = len1 - 1, j = len2 - 1, k = LEN - 1;
    
    // Складываем с конца
    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? buff1[i] : 0;
        int digit2 = (j >= 0) ? buff2[j] : 0;
        
        int sum = digit1 + digit2 + carry;
        result[k] = sum % 10;
        carry = sum / 10;
        
        i--;
        j--;
        k--;
    }
    
    // Определяем длину результата
    *result_length = LEN - k - 1;
    
    // Копируем результат в начало массива
    for (int i = 0; i < *result_length; i++) {
        result[i] = result[k + 1 + i];
    }
}

// Вычитание двух больших чисел (buff1 >= buff2)
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length)
{
    int borrow = 0;  // Заем
    int i = len1 - 1, j = len2 - 1, k = LEN - 1;
    
    // Вычитаем с конца
    while (i >= 0) {
        int digit1 = buff1[i];
        int digit2 = (j >= 0) ? buff2[j] : 0;
        
        int diff = digit1 - digit2 - borrow;
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result[k] = diff;
        
        i--;
        j--;
        k--;
    }
    
    // Определяем длину результата (пропускаем ведущие нули)
    int start_index = k + 1;
    while (start_index < LEN && result[start_index] == 0) {
        start_index++;
    }
    
    // Если все цифры нули, результат = 0
    if (start_index == LEN) {
        result[0] = 0;
        *result_length = 1;
    } else {
        *result_length = LEN - start_index;
        
        // Копируем результат в начало массива
        for (int i = 0; i < *result_length; i++) {
            result[i] = result[start_index + i];
        }
    }
}
