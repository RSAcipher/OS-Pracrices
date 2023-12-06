#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    int **data;
} Matrix;

Matrix createMatrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    mat.data = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        mat.data[i] = (int *)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = 0;
        }
    }

    return mat;
}

void freeMatrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
}

void printMatrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%d ", mat->data[i][j]);
        }
        printf("\n");
    }
}

void resizeMatrix(Matrix *mat, int newRows, int newCols) {

    int **tempData = (int **)malloc(newRows * sizeof(int *));
    for (int i = 0; i < newRows; i++) {
        tempData[i] = (int *)malloc(newCols * sizeof(int));
    }

    for (int i = 0; i < mat->rows && i < newRows; i++) {
        for (int j = 0; j < mat->cols && j < newCols; j++) {
            tempData[i][j] = mat->data[i][j];
        }
    }

    freeMatrix(mat);

    mat->rows = newRows;
    mat->cols = newCols;
    mat->data = tempData;
}

int main() {
    Matrix matrix = createMatrix(3, 3);
    matrix.data[0][0] = 1;
    matrix.data[0][1] = 2;
    matrix.data[0][2] = 3;
    matrix.data[1][0] = 4;
    matrix.data[1][1] = 5;
    matrix.data[1][2] = 6;
    matrix.data[2][0] = 7;
    matrix.data[2][1] = 8;
    matrix.data[2][2] = 9;

    printf("Original Matrix:\n");
    printMatrix(&matrix);

    resizeMatrix(&matrix, 4, 4);

    printf("\nResized Matrix:\n");
    printMatrix(&matrix);

    freeMatrix(&matrix);

    return 0;
}
