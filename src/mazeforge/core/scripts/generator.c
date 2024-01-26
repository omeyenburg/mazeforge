#include "bst.h" // implements binary search trees
#include <stdio.h> // implements printf
#include <stdlib.h> // implements malloc, calloc and realloc
#include <stdint.h> // implements int8_t

void c_print() {
    printf("Hello World from C!\n");
}

void print_maze1(int **array, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int value = array[i][j];
            printf("%d ", value);
        }
        printf("\n");
    }
}

void print_maze(int8_t *array, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int value = array[i + j * width];
            printf("%d ", value);
        }
        printf("\n");
    } 
}


void add_adjacent_cells(int x, int y, int* adjacent_cells, int adjacent_cells_count, int8_t* array, int width, int height) {
    if (x > 0) {
        if (array[x - 1 + y * width] == -1) {

        }
    }
}


void generate_maze(int8_t *array, int width, int height) {

    // calloc(number of elements, size per element) -> allocates space + fills with 0
    // malloc(number of elements * size per element) -> allocates space (maybe prefered)
    BinaryTree* adjacent_cells = bst_create();
    int adjacent_cells_count = 0;


    // Create starting point
    int center[2] = {width / 2, height / 2};
    array[center[0] + center[1] * width];


    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int value = array[i + j * width];
            printf("%d ", value);
        }
        printf("\n");
    } 
}