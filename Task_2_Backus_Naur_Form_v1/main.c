#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define W 256

typedef enum {
    ARG, //0
    OP, //1
    OTHER //2
} type;

type get_type(const char str) {

    if (('a' <= str && str <= 'z') || ('0' <= str && str <= '9') ||
       ('A' <= str && str <= 'Z') || str == '_') {
        return ARG;
    }
    if (str == '+' || str == '-' || str == '/' || str == '*') {
        return OP;
    }
    return OTHER;
}

void find_and_replace(char *source, char *pattern, char *replacement, char *result) {
    unsigned int patternLength = strlen(pattern);
    unsigned int replacementLength = strlen(replacement);

    char *tail = source;
    char *temp = result;
    char *next = strstr(tail, pattern);

    while(next != NULL) {
        long long int k = next - tail;

        if (get_type(tail[k + patternLength]) == OP || tail[k + patternLength] == ')') {
            if (get_type(tail[k - 1]) == OP || tail[k - 1] == '(') {

                strncpy(result, tail, k); // копируем в result из tail (next-tail) символов
                result += k;
                strcpy(result, replacement);
                result = result + replacementLength;
                tail = next + patternLength;
                next = strstr(tail, pattern);
            } else {
                strncpy(result, tail, 1); // копируем в result из tail 1 символ
                next = strstr(&next[1], pattern);
            }
        } else {
            strncpy(result, tail, 1); // копируем в result из tail 1 символ
            next = strstr(&next[1], pattern);
        }
    }
    strcpy(result, tail);
    strcpy(source, temp);
}

int sign (char beg) {
    if (get_type(beg) == OP) {
        return 1;
    }
    return 0;
}

int identr (char* beg) {
    char* p = beg;
    while (get_type(*p) == ARG) {
        p++;
    }
    return p - beg;
}

int check_expression(char* str, int count_exp, int brackets) { // исходная строка, количество простых выражений, количество парных скобок

    char* start = str;

    if (*str == '(') {
        int bracket_check_1 = check_expression(str + 1, 0, ++brackets);
        if (bracket_check_1 == 0) {
            return 0;
        }

        str += bracket_check_1 + 1;

        if (*str == ')') {
            brackets--;
            str++;
            if (*str != 0 && brackets == 0) {
                return 0;
            }
            if (count_exp == 1) {
                return str - start;
            }
        }
        count_exp++;
        if (brackets == 0) {
            return 1;
        }
    }

    int simple_check = identr(str);

    if (simple_check) {
        str += simple_check;
        if (brackets == 0 && *str == 0) { // супер простое выражение
            return 1000;
        }
        count_exp++;
    }

    if (sign(*str) && count_exp == 1 && brackets > 0) {
        int bracket_check_2 = check_expression(str + 1, 1, brackets);
        if (bracket_check_2 == 0) {
            return 0;
        }
        str += bracket_check_2 + 1;
        if (*str != ')') {
            return 0;
        }
        return str - start;
    }

    if (count_exp == 2 && *str == ')') {
        return str - start;
    }
    return 0;
}

int plus_and_minus(char *, unsigned *);
int multiply_and_div(char *, unsigned *);
int number(const char *, unsigned *);
int brackets(char *, unsigned *);

FILE *input, *output;

int main() {
    char oldstr[W]; // проверяемая строка
    char newstr[W]; // новая строчка
    int lines_count; // количество строк идентификаторов и чисел
    char numb_array[W][W]; // массив индентификаторов
    char ids_array[W][W]; // массив чисел

    output = fopen("output.txt", "w");
    input = fopen("input.txt", "r");

    // ввод данных
    fscanf(input, "%i", &lines_count);
    for (int i = 0; i < lines_count; i++) {
        fscanf(input, "%s", &ids_array[i][W]);
        fscanf(input, "%s", &numb_array[i][W]);
    }
    fscanf(input, "%s", oldstr);
    int temp = check_expression(oldstr, 0, 0);
    printf("%i",temp);

    // Простое выражение (да или нет) и замена идентификаторов
    if (temp == 0) {
        fprintf(output, "INCORRECT");
        return 0;
    }
    if (temp == 1000) { // если выражение без скобок
            for (int i = 0; i < lines_count; i++) { // замена идентификаторов
                if (strstr(oldstr, &ids_array[i][W]) != NULL && strlen(&ids_array[i][W]) == strlen(oldstr)) {
                    strcpy(newstr, &numb_array[i][W]);
                    lines_count = 0;
                }
            }
            if (lines_count != 0) {
                strcpy(newstr, oldstr);
            }
        } else {
        for (int i = 0; i < lines_count; i++) { // замена идентификаторов
            find_and_replace(oldstr, &ids_array[i][W], &numb_array[i][W], newstr);
        }
    }

    fprintf(output, "%s\n", newstr); // вывод изменённой строки

    // часть с подсчетом
    if(0) {
        unsigned int idx = 0;
        for (int i = 0; i < strlen(newstr); i++) { // проверка, может ли быть посчитано выражение
            if (((newstr[i] <= 'z' && newstr[i] >= 'a') || (newstr[i] <= 'Z' && newstr[i] >= 'A') ||
                 newstr[i] == '_')) {
                fprintf(output, "Can't be calculated");
                exit(0);
            }
        }

        fprintf(output, "Result: %d\n", plus_and_minus(newstr, &idx)); // вывод вычисления
    }

    fclose(input);
    fclose(output);
    return 0;
}

int plus_and_minus(char *str, unsigned int *idx) { // операции сложения и вычитания

    int result = multiply_and_div(str, idx); // приоритет у умножения и деления выше чем у сложения и вычитания

    while (str[*idx] == '+' || str[*idx] == '-') {
        switch (str[*idx]) {
            case '+':
                ++*idx;
                result += multiply_and_div(str, idx);
                break;

            case '-':
                ++*idx;
                result -= multiply_and_div(str, idx);
                break;
        }
    }
    return result;
}

int multiply_and_div(char *str, unsigned int *idx) { //операции умножения и желения

    int result = brackets(str, idx); // приоритет у выражения в скобках выше
    int div;

    while (str[*idx] == '*' || str[*idx] == '/') {
        switch (str[*idx]) {
            case '*':
                ++*idx;
                result *= brackets(str, idx);
                break;

            case '/':
                ++*idx;
                div = brackets(str, idx);

                if (div != 0) {
                    result /= div;
                }
                else {
                    fprintf(output, "Division by zero!\n");
                    exit(1);
                }
                break;
        }
    }
    return result;
}

int brackets(char *str, unsigned int *idx) { // скобки

    int result;
    int sign = 1;

    if (str[*idx] == '(') {
        ++*idx;
        result = plus_and_minus(str, idx);
        ++*idx;
    } else { result = number(str, idx); }

    return sign * result;
}

int number(const char *str, unsigned int *idx) { // числа

    int result = 0;

    while (str[*idx] >= '0' && str[*idx] <= '9') {
        result = result * 10 + (str[*idx] - '0');
        ++*idx;
    }
    return result;
}