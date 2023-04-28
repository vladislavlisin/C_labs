#include <stdio.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

#define NN 100 // максимальное количество матриц
#define k 64 // максимальная размерность матриц

// сортировка бистрая
void fastsort(int* arr, int left, int right) {

    int i = left, j = right;
    int temp, pivot = arr[(left+right)/2];

    while (i <= j) {

        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
            i++; j--;
        }
    }

    if (left < j) {
        fastsort(arr, left, j);
    }
    if (i < right) {
        fastsort(arr, i, right);
    }
}

// сортировка пузырьком
void bubblesort(int *arr, int trash, int size) {
    size++;
    int i, j;
    int tmp;
    for (i = 1; i < size; i++) {
        for (j = 1; j <= size-i; j++) {
            if (arr[j] < arr[j-1]) {
                tmp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = tmp;
            }
        }
    }
}

void swap(int const * farray, int * sarray, int N) {
    for (int i = 0; i < N; i++) {
        sarray[i] = farray[i];
    }
}

void timer(int times_to_run, int const array[NN], int N, void (*sort) (int*, int, int)) { // считает время сортировки матрицы n раз, вычисляет отклонение, среднее арифметическое и лучший, худший случай

    int temp_array[NN];
    swap(array, temp_array, N);

    double time_array[NN];
    double sum = 0;
    double temp;
    double sorts_count = 0;

        for (int i = 0; i < times_to_run; i++) {
            while (time_array[i] < 2) {
                clock_t start = clock();
                sort(temp_array, 0, N - 1); // сортировка
                clock_t end = clock();
                temp = (double) (end - start) / CLOCKS_PER_SEC;
                time_array[i] += temp;
                sorts_count += 1;
                swap(array, temp_array, N);
            }
            time_array[i] = sorts_count / time_array[i]; // количество сортировок за секунду
            sorts_count = 0;
            printf("Sorts per second %i: %.10f\n", i+1, time_array[i]);
            sum += time_array[i]; // общее количество сортировок всех запусков
        }

    double average = sum / times_to_run; // среднеее арифметическое всех запусков алгоритма
    double sqrsum = 0;
    double best = average;
    double worst = average;

    for (int i = 0; i < times_to_run; i++) { // находим наилучший, наихудший запуск и вычисляем сумму для подсчета стандартного отклонения
        if (time_array[i] > best) {
            best = time_array[i];
        } else if (time_array[i] < worst) {
            worst = time_array[i]; }
        sqrsum = sqrsum + pow(time_array[i] - average, 2); // сумма для подсчета стандартного отклонения
    }

    double std_deviation = sqrt(sqrsum/times_to_run);

    printf("\nOutput array of sorted determinants? Enter 'yes' to output, enter any character to not\n");
    char answer[10];
    scanf("%s", answer);

    if (strcmp(answer, "yes") == 0) {
        sort(temp_array, 0, N - 1);
        for (int i = 0; i < N; i++) {
            printf("%i ", temp_array[i]);
        }
    }

    printf("\nWorst run: %.10f\n", worst);
    printf("Best run: %.10f\n", best);
    printf("Arithmetic mean time of all runs: %.10f\n", average);
    printf("Standard deviation: %.10f\n", std_deviation);
}

//Возвращает матрицу matrix без row-ой строки и col-того столбца, результат в newMatrix
void removeRowAndCol(int matrix[][k][k], int x, int size, int row, int col, int newmatrix[][k][k]) {
    int offsetRow = 0; //Смещение индекса строки в матрице
    int offsetCol = 0; //Смещение индекса столбца в матрице
    for (int i = 0; i < size-1; i++) {
        //Пропустить row-ую строку
        if (i == row) {
            offsetRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
        }
        for (int j = 0; j < size-1; j++) {
            //Пропустить col-ый столбец
            if (j == col) {
                offsetCol = 1; //Встретили нужный столбец, проускаем его смещением
            }
            newmatrix[x][i][j] = matrix[x][i + offsetRow][j + offsetCol];
        }
        offsetCol = 0;
    }
}

int newmatrix[NN][k][k];

//считаем определитель разложением по первой строке
int matrixDet(int matrix[][k][k], int i, int size) { //матрица, номер матрицы, размерность матрицы
    int det = 0;
    int sign = 1; // (-1)^(1+j) из формулы определителя

    if (size == 1) {
        return matrix[i][0][0];
    }
    else if(size == 2) {
        return matrix[i][0][0]*matrix[i][1][1] - matrix[i][0][1]*matrix[i][1][0];
    }
    else {
        //Раскладываем по 0-ой строке, цикл бежит по столбцам
        for (int j = 0; j < size; j++) {
            //Удалить из матрицы 0-ю строку и j-ый столбец
            //Результат в newmatrix
            removeRowAndCol(matrix, i, size, 0, j, newmatrix); // старая матрица, номер матрицы, размерность, строка, столбец, новая матрица
            //где minor_j - дополнительный минор элемента matrix[i][0][j]

            det = det + (sign * matrix[i][0][j] * matrixDet(newmatrix, i, size - 1));
            sign = -sign;
        }
    }
    return det;
}

int array_of_matrices[NN][k][k]; // массив матриц
int r_array_of_matrices[NN][k][k]; // случайные элементы матрицы

int main() {

    int array_of_determinants[NN]; // массив определителей матриц
    int array_of_sizes[NN]; // размерность матрицы
    int N = 0; // количество матриц

    //ввод данных
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &array_of_sizes[i]);
        for (int j = 0; j < array_of_sizes[i]; j++) {
            for (int q = 0; q < array_of_sizes[i]; q++) {
                scanf("%d", &array_of_matrices[i][j][q]);
            }
        }
    }

    int oarray_of_determinants[NN]; // матрица для сравнения и вывода в конце

    //считаем определители для каждой из матриц и записываем их в отдельный массив
    for (int i = 0; i < N; i++) {
        array_of_determinants[i] = matrixDet(array_of_matrices, i, array_of_sizes[i]);
        oarray_of_determinants[i] = array_of_determinants[i];
    }

    fastsort(array_of_determinants, 0, N - 1);

    // вывод матриц в порядке возростания их определителей
    for (int i = 0; i < N; i++) {
        int x = 0;
        for (int j = 0; j < N; j++) {
            if (array_of_determinants[i] == oarray_of_determinants[j] && x == 0) {
                for (int l = 0; l < array_of_sizes[j]; l++) {
                    printf("\n");
                    for (int q = 0; q < array_of_sizes[j]; q++) {
                        printf("%d ", array_of_matrices[j][l][q]);
                    }
                }
                oarray_of_determinants[j] = 1000000000;
                x++;
            }
        }
    }

        // ***ДОПОЛНИТЕЛЬНОЕ ЗАДАНИЕ***
        // Генерация случайных данных (кол-во матриц, размерность матриц, элементы матриц) и их вывод в консоль

        int rN; // Случайное кол-во матриц
        int r_array_of_sizes[NN]; // случайная размерность матрицы
        int r_array_of_determinants[NN]; // массив определителей случайных матриц

        // Кол-во матриц от 5 до 100, размерность от 1 до 5, Значение элементов от - 100 до 100
        char option[5];
        printf("\nOutput generated random arrays? Enter 'yes' to output, enter any character not to\n");
        scanf("%s", option);
        int option1 = strcmp(option, "yes");

        srand(time(NULL));
        rN = 5 + rand() % 94;
        printf("\nthe number of arrays %i\n", rN); // количество массивов
        for (int i = 0; i < rN; i++) {
            r_array_of_sizes[i] = 1 + rand() % 5; // размерность не может быть нулевой (максимальная матрица 5*5)
            if (option1 == 0) { printf("%i\n", r_array_of_sizes[i]); }
            for (int j = 0; j < r_array_of_sizes[i]; j++) {
                for (int q = 0; q < r_array_of_sizes[i]; q++) {
                    r_array_of_matrices[i][j][q] = -100 + rand() % 201;
                    if (option1 == 0) { printf("%i ", r_array_of_matrices[i][j][q]); }
                }
                if (option1 == 0) { printf("\n"); }
            }
        }

        printf("\nOutput array of determinants? Enter 'yes' to output, enter any character to not\n");
        scanf("%s", option);
        option1 = strcmp(option, "yes");

        // Вычисление определителей матриц
        for (int i = 0; i < rN; i++) {
            r_array_of_determinants[i] = matrixDet(r_array_of_matrices, i, r_array_of_sizes[i]);
            if (option1 == 0) { printf("%i ", r_array_of_determinants[i]); }
        }

        char action[10] = "next";

        while (strcmp(action, "next") ==
               0) { // возможность запустить алгоритм несколько раз для разных сортировок и рахных массивов

            int times_to_run = 0;
            printf("\nHow many times do we run the algorithm?\n");
            scanf("%d", &times_to_run); // возможность несколько раз запускать алгоритм на одних и тех же данных

            char sort[10];
            void (*sort_pointer)(int *, int, int);

            printf("Enter the sort type: fast or bubble\n");
            scanf("%s", sort); // выбор сортировки
            while (strcmp(sort, "fast") != 0 &&
                   strcmp(sort, "bubble") != 0) { // проверка на корректность введённых данных
                printf("Wrong name\n");
                scanf("%s", sort);
            }
            if (strcmp(sort, "fast") == 0) {
                sort_pointer = &fastsort;
            } else { sort_pointer = &bubblesort; }


            printf("Array of random numbers - 1, array of input data - 2\n");
            int or;
            scanf("%i", &or); // выбор массива
            while (or != 1 && or != 2) { // проверка на корректность введённых данных
                printf("Wrong number\n");
                scanf("%i", &or);
            }

            if (or == 1) {
                timer(times_to_run, r_array_of_determinants, rN, sort_pointer);
            } else {
                timer(times_to_run, array_of_determinants, N, sort_pointer);
            }

            printf("\nEnter any character to end the program.\nTo start from the beginning - next\n");
            scanf("%s", action);
        }

    return 0;
}