#include <stdlib.h> // implements malloc, calloc and realloc
#include <stdint.h> // implements int8_t
#include <stdio.h>  // implements printf
#include <time.h>   // implements time
#include "bst.h"    // implements binary search trees


void init() {
    srand(time(NULL));
}

void test() {
    printf("Hello World from C!\n");
}

bool get_bit(int8_t* array, int coord, int index) {
    return (array[coord] >> index) & 1;
}

void set_bit(int8_t* array, int coord, int index, bool value) {
    if (value == true) {
        array[coord] |= (1 << index);
    } else {
        array[coord] &= ~(1 << index);
    }
}

void printBinary(int num) {
    // Loop through each bit starting from the most significant bit (leftmost)
    for (int i = 3; i >= 0; i--) {
        // Check if the i-th bit is set (1) or unset (0)
        int bit = (num >> i) & 1;

        // Print the bit
        printf("%d", bit);
    }
    printf("\n");
}

void print_raw_maze(int8_t* array, int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int value = array[y + x * width]; // x/y swapped cuz working
            printf("%d ", value);
        }
        printf("\n");
    }
}

void print_maze(int8_t* array, int width, int height) {
    printf("┌");
    for (int i = 0; i < width - 1; i++) {
        printf("───┬");
    }
    printf("───┐\n");
    for (int y = 0; y < height - 1; y++) {
        printf("│");
        for (int x = 0; x < width - 1; x++) {
            if (get_bit(array, x + y * width, 0) == true) {
                printf("   │");
            } else {
                printf("    ");
            }
        }
        printf("   │\n");

        printf("├");
        for (int x = 0; x < width - 1; x++) {
            if (get_bit(array, x + y * width, 1) == true) {
                printf("───┼");
            } else {
                printf("   ┼");
            }
        }
        if (get_bit(array, width - 1 + y * width, 1) == true) {
            printf("───┤\n");
        } else {
            printf("   ┤\n");
        }
    }
    printf("│");
    for (int x = 0; x < width - 1; x++) {
        if (get_bit(array, x + (height - 1) * width, 0) == true) {
            printf("   │");
        } else {
            printf("    ");
        }
    }
    printf("   │\n");

    printf("└");
    for (int i = 0; i < width - 1; i++) {
        printf("───┴");
    }
    printf("───┘\n");
}

void add_adjacent_cells(int x, int y, BinaryTree* adjacent_cells, int8_t* array, int width, int height) {
    int coord = x + y * width;

    if (x > 0 && array[coord - 1] == -1) {
        bst_insert(adjacent_cells, coord - 1);
    }
    if (x < width - 1 && array[coord + 1] == -1) {
        bst_insert(adjacent_cells, coord + 1);
    }
    if (y > 0 && array[coord - width] == -1) {
        bst_insert(adjacent_cells, coord - width);
    }
    if (y < height - 1 && array[coord + width] == -1) {
        bst_insert(adjacent_cells, coord + width);
    }
}

void create_connection(int8_t* array, int x, int y, int width, int height) {
    int coord = x + y * width;
    int neighbours[4];

    if (x < width - 1 && array[coord + 1] != -1) {
        neighbours[0] = 1;
    } else {
        neighbours[0] = 0;
    }

    if (y < height - 1 && array[coord + width] != -1) {
        neighbours[1] = 1;
    } else {
        neighbours[1] = 0;
    }

    if (x > 0 && array[coord - 1] != -1) {
        neighbours[2] = 1;
    } else {
        neighbours[2] = 0;
    }

    if (y > 0 && array[coord - width] != -1) {
        neighbours[3] = 1;
    } else {
        neighbours[3] = 0;
    }

    int sum = neighbours[0] + neighbours[1] + neighbours[2] + neighbours[3];
    if (sum == 0) {
        return;
    }
    int index = rand() % sum;

    if (neighbours[0] == 1) {
        if (index == 0) {
            set_bit(array, coord, 0, false);
            set_bit(array, coord + 1, 2, false);
            return;
        } else {
            index--;
        }
    }

    if (neighbours[1] == 1) {
        if (index == 0) {
            set_bit(array, coord, 1, false);
            set_bit(array, coord + width, 3, false);
            return;
        } else {
            index--;
        }
    }

    if (neighbours[2] == 1) {
        if (index == 0) {
            set_bit(array, coord, 2, false);
            set_bit(array, coord - 1, 0, false);
            return;
        } else {
            index--;
        }
    }

    if (neighbours[3] == 1) {
        set_bit(array, coord, 3, false);
        set_bit(array, coord - width, 1, false);
    }
}

void generate_maze(int8_t* array, int width, int height) {
    // Fill array with -1
    for (int i = 0; i < width * height; i++) {
        array[i] = -1;
    }

    // Create binary search tree
    BinaryTree* adjacent_cells = bst_create();

    // Create starting point
    int center[2] = {width / 2, height / 2};
    array[center[0] + center[1] * width] = 15;
    add_adjacent_cells(center[0], center[1], adjacent_cells, array, width, height);

    // Create new cells
    while (adjacent_cells->size > 0) {
        // Choose random adjacent cell
        int new_cell = bst_get_random(adjacent_cells);
        int x = new_cell % width;
        int y = new_cell / width;

        // Update adjacent cells
        bst_remove(adjacent_cells, new_cell);
        add_adjacent_cells(x, y, adjacent_cells, array, width, height);

        // Adjust cell walls
        array[new_cell] = 15;
        create_connection(array, x, y, width, height);
    }

    // Clean up
    bst_delete(adjacent_cells);
    print_maze(array, width, height);
    return 0;
}
