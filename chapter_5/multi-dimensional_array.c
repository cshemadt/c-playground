#include <stdlib.h>
#include <stdio.h>
#define MATRIX_ROWS 3
#define MATRIX_COLUMNS 2
#define MAX_SIZE 5
void print_matrix(int m[][MATRIX_COLUMNS]) {
    for(int i=0;i<MATRIX_ROWS;i++) {
        for(int j=0;j<MATRIX_COLUMNS;j++)
            printf("%d %p ",m[i][j],&m[i][j]);
        printf("\n");
    }
}
void print_matrix_ptr(int *m) {
    for(int *p=m;p<m+MATRIX_COLUMNS*MATRIX_ROWS;p++) 
        printf("%d ",*p);
}
char *month_name(int n) {
    static char* names[] = {
        "Illegal month",
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };
    return (n>0 && n<=12) ? names[n] : names[0];
}
int **dynamic_allocated_array() {
    int **pm;
    pm=(int**)malloc(MATRIX_ROWS * sizeof(int*));
    for(int i=0;i<MATRIX_ROWS;i++) {
        pm[i] = malloc(MATRIX_ROWS* sizeof(int));
    }
    return pm;
}
void free_dynamic_allocated_array(int **m) {
    for(int i=0;i<MATRIX_ROWS;i++)
        free(m[i]);
}
int main() {
    int m[][MATRIX_COLUMNS] = {
        {2,3},
        {7,9},
        {8,8}
    };
    /* dynamic allocated 2d array */
    int **pm=dynamic_allocated_array();
    for(int i=0;i<MATRIX_ROWS;i++)
        for(int j=0;j<MATRIX_COLUMNS;j++)
            pm[i][j]=i*j;
    for(int i=0;i<MATRIX_ROWS;i++)
        for(int j=0;j<MATRIX_COLUMNS;j++)
            printf("%d ",pm[i][j]);
        printf("\n");
    free_dynamic_allocated_array(pm);
}