#include <stdio.h>
#define MATRIX_ROWS 3
#define MATRIX_COLUMNS 2
void print_matrix(int m[][MATRIX_COLUMNS]) {
    for(int i=0;i<MATRIX_ROWS;i++) {
        for(int j=0;j<MATRIX_COLUMNS;j++)
            printf("%d %p ",m[i][j],&m[i][j]);
        printf("\n");
    }
}
void print_matrix_ptr(int m[][MATRIX_COLUMNS]) {
    int *p=&m[0][0];
    for(int i=0;i<MATRIX_ROWS;i++) {
        for(int j=0;j<MATRIX_COLUMNS;j++)
            printf("%d ",*(p+(i*MATRIX_COLUMNS+j)));
        printf("\n");
    }
}
int main() {
    int matrix[MATRIX_ROWS][MATRIX_COLUMNS] = {
        {2,2},
        {3,5},
        {7,9},
    };
    print_matrix_ptr(matrix);
}