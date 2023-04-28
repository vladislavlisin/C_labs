#include <stdio.h>

// if u want to check all yr reps
// Get-ChildItem . -Attributes Directory+Hidden -ErrorAction SilentlyContinue -Include ".git" -Recurse

void find_saddles(int **newmatrix, int ** matrix, int W , int H)
{
    int S = 0; // КОЛИЧЕСТВО СЕДЛОВЫХ ТОЧЕК
    int A; // СУММА ЭЛЕМЕНТОВ В СТОЛБЦЕ
    int l; // КОЛИЧЕСТВО ЭЛЕМЕНТОВ В СУММЕ

    int min,max;
    for (int i=0; i<H; i++)
    {
        min= matrix[i][0];
        for (int x=1; x<W; x++)
        {
            if ( matrix[i][x]<min )
            {
                min=matrix[i][x];
            }
        }                       //нашли минимальный элемент в строке
        for(int j=0; j<W; j++)
        {
            if (matrix[i][j]==min)
            {
                max=matrix[0][j];
                l = 1;
                A = max;
                for (int y=1; y<H; y++)
                {
                    A = A + matrix[y][j];
                    l++;
                    if ( matrix[y][j]>max )
                    {
                        max = matrix[y][j];
                    }
                }
                if (matrix[i][j]==max)
                {
                    S = S + 1;
                    newmatrix[i][j] = A / l;
                    printf("\n");
                }
            }
        }
    }
    printf("%i", S);
    printf("\n");
}


int main() {
    int H; // КОЛИЧЕСТВО СТРОК
    int W; // КОЛИЧЕСТВО СТОЛБЦОВ

    do
    {
        printf("Enter the number of rows and columns: \n");
        scanf("%d%d", &W, &H);
        if ( W > 255 || H > 255)
            printf("You entered the number of rows or columns more than 255\n");
        if ( W < 0 || H < 0)
            printf("You entered the number of rows or columns less than zero\n");
    } while (W > 255 || H > 255 || W < 0|| H < 0);

    printf("Enter the elements of matrix:\n");
    int matrix[H][W];
    int *mat[H];
    int *new_matrix[H];
    for (int t=0; t<H; t++) {
        for (int k=0; k<W; k++) {
            scanf("%i", &matrix[t][k]);
        }
        mat[t] = matrix[t];
        new_matrix[t] = matrix[t];
    }

    find_saddles(new_matrix, mat, W, H);

    for(int t=0; t<H; t++) {
        for(int k=0; k<W; k++)
            printf("%i ", new_matrix[t][k]);
    printf("\n");
    }

    return (0);
}