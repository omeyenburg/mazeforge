#include "bst.h"    // implements binary search trees
#include <stdint.h> // implements int8_t
#include <stdio.h>  // implements printf
#include <stdlib.h> // implements malloc, calloc and realloc
#include <time.h>   // implements time
#include <wchar.h>

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64)
#include <Windows.h>
#define OS_Windows 1
#else
#define OS_Windows 0
#endif

void init() {
    srand(time(NULL));
#if OS_Windows
    SetConsoleOutputCP(CP_UTF8);
#endif
}

void test() {
    printf("Hello World from C!\n");
}

bool get_bit(int8_t *array, int coord, int index) {
    return (array[coord] >> index) & 1;
}

void set_bit(int8_t *array, int coord, int index, bool value) {
    if (value == true) {
        array[coord] |= (1 << index);
    } else {
        array[coord] &= ~(1 << index);
    }
}

void print_binary(int num) {
    for (int i = 3; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}

void print_raw_maze(int8_t *array, int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int value = array[y + x * width]; // x/y swapped cuz working
            printf("%d\t", value);
        }
        printf("\n");
    }
}

void print_maze_deprecated(int8_t *array, int width, int height) {
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

wchar_t *print_maze2(int8_t *array, int width, int height) {
    bool output_array[width * 2 + 2][height * 2 + 2];
    // wchar_t *buffer = (wchar_t *)malloc(((width * 2 + 2) * (height * 2 + 2) + height * 2 + 1) * sizeof(wchar_t));
    wchar_t *buffer = (wchar_t *)malloc(120 * sizeof(wchar_t));
    int index = 0;

    for (int x = 0; x <= width; x++) {
        for (int y = 0; y <= height; y++) {
            if (x == width && y == height) {
                output_array[x * 2][y * 2 + 1] = false;
                output_array[x * 2 + 1][y * 2] = false;
                output_array[x * 2 + 1][y * 2 + 1] = false;
                output_array[x * 2][y * 2] = true;
            } else if (x == width) {
                output_array[x * 2][y * 2 + 1] = true;
                output_array[x * 2 + 1][y * 2] = false;
                output_array[x * 2 + 1][y * 2 + 1] = false;
                output_array[x * 2][y * 2] = true;
            } else if (y == height) {
                output_array[x * 2][y * 2 + 1] = false;
                output_array[x * 2 + 1][y * 2] = true;
                output_array[x * 2 + 1][y * 2 + 1] = false;
                output_array[x * 2][y * 2] = true;
            } else {
                output_array[x * 2][y * 2 + 1] = get_bit(array, x + y * width, 2);
                output_array[x * 2 + 1][y * 2] = get_bit(array, x + y * width, 3);
                output_array[x * 2 + 1][y * 2 + 1] = false;
                output_array[x * 2][y * 2] = true;
            }
        }
    }

    printf("%d\n", true + true + false);

    for (int y = 0; y < height * 2 + 1; y++) {
        for (int x = 0; x <= width * 2 + 1; x++) {
            int value = 0;
            if (output_array[x][y] == true) {
                if (output_array[x + 1][y] == true) {
                    value += 1;
                }
                if (output_array[x][y + 1] == true) {
                    value += 2;
                }
                if (x > 0 && output_array[x - 1][y] == true) {
                    value += 4;
                }
                if (y > 0 && output_array[x][y - 1] == true) {
                    value += 8;
                }
            }

            /*
            switch (value) {
            case 0:
                printf("  ");
                break;
            case 1:
                printf("╶─");
                break;
            case 2:
                printf("╷ ");
                break;
            case 3:
                printf("┌─");
                break;
            case 4:
                printf("╴ ");
                break;
            case 5:
                printf("──");
                break;
            case 6:
                printf("┐ ");
                break;
            case 7:
                printf("┬─");
                break;
            case 8:
                printf("╵ ");
                break;
            case 9:
                printf("└─");
                break;
            case 10:
                printf("│ ");
                break;
            case 11:
                printf("├─");
                break;
            case 12:
                printf("┘ ");
                break;
            case 13:
                printf("┴─");
                break;
            case 14:
                printf("┤ ");
                break;
            case 15:
                printf("┼─");
                break;
            }*/

            /*switch (value) {
            case 0:
                printf("  ");
                break;
            case 1:
                wprintf(L"\u2576\u2500");
                break;
            case 2:
                wprintf(L"\u2577 ");
                break;
            case 3:
                wprintf(L"\u250c\u2500");
                break;
            case 4:
                wprintf(L"\u2574 ");
                break;
            case 5:
                wprintf(L"\u2500\u2500");
                break;
            case 6:
                wprintf(L"\u2510 ");
                break;
            case 7:
                wprintf(L"\u252c\u2500");
                break;
            case 8:
                wprintf(L"\u2575 ");
                break;
            case 9:
                wprintf(L"\u2514\u2500");
                break;
            case 10:
                wprintf(L"\u2502 ");
                break;
            case 11:
                wprintf(L"\u251c\u2500");
                break;
            case 12:
                wprintf(L"\u2518 ");
                break;
            case 13:
                wprintf(L"\u2534\u2500");
                break;
            case 14:
                wprintf(L"\u2524 ");
                break;
            case 15:
                wprintf(L"\u253c\u2500");
                break;
            }*/

            /*switch (value) {
            case 0:
                buffer[index++] = ' ';
                buffer[index++] = ' ';
                break;
            case 1:
                buffer[index++] = '\u2576';
                buffer[index++] = '\u2500';
                break;
            case 2:
                buffer[index++] = '\u2577';
                buffer[index++] = ' ';
                break;
            case 3:
                buffer[index++] = '\u250c';
                buffer[index++] = '\u2500';
                break;
            case 4:
                buffer[index++] = '\u2574';
                buffer[index++] = ' ';
                break;
            case 5:
                buffer[index++] = '\u2500';
                buffer[index++] = '\u2500';
                break;
            case 6:
                buffer[index++] = '\u2510';
                buffer[index++] = ' ';
                break;
            case 7:
                buffer[index++] = '\u252c';
                buffer[index++] = '\u2500';
                break;
            case 8:
                buffer[index++] = '\u2575';
                buffer[index++] = ' ';
                break;
            case 9:
                buffer[index++] = '\u2514';
                buffer[index++] = '\u2500';
                break;
            case 10:
                buffer[index++] = '\u2502';
                buffer[index++] = ' ';
                break;
            case 11:
                buffer[index++] = '\u251c';
                buffer[index++] = '\u2500';
                break;
            case 12:
                buffer[index++] = '\u2518';
                buffer[index++] = ' ';
                break;
            case 13:
                buffer[index++] = '\u2534';
                buffer[index++] = '\u2500';
                break;
            case 14:
                buffer[index++] = '\u2524';
                buffer[index++] = ' ';
                break;
            case 15:
                buffer[index++] = '\u253c';
                buffer[index++] = '\u2500';
                break;
            }*/

            switch (value) {
            case 0:
                buffer[index++] = ' ';
                buffer[index++] = ' ';
                break;
            case 1:
                buffer[index++] = L'╶';
                buffer[index++] = L'─';
                break;
            case 2:
                buffer[index++] = L'╷';
                buffer[index++] = L' ';
                break;
            case 3:
                buffer[index++] = L'┌';
                buffer[index++] = L'─';
                break;
            case 4:
                buffer[index++] = L'╴';
                buffer[index++] = L' ';
                break;
            case 5:
                buffer[index++] = L'─';
                buffer[index++] = L'─';
                break;
            case 6:
                buffer[index++] = L'┐';
                buffer[index++] = L' ';
                break;
            case 7:
                buffer[index++] = L'┬';
                buffer[index++] = L'─';
                break;
            case 8:
                buffer[index++] = L'╵';
                buffer[index++] = L' ';
                break;
            case 9:
                buffer[index++] = L'└';
                buffer[index++] = L'─';
                break;
            case 10:
                buffer[index++] = L'│';
                buffer[index++] = L' ';
                break;
            case 11:
                buffer[index++] = L'├';
                buffer[index++] = L'─';
                break;
            case 12:
                buffer[index++] = L'┘';
                buffer[index++] = L' ';
                break;
            case 13:
                buffer[index++] = L'┴';
                buffer[index++] = L'─';
                break;
            case 14:
                buffer[index++] = L'┤';
                buffer[index++] = L' ';
                break;
            case 15:
                buffer[index++] = L'┼';
                buffer[index++] = L'─';
                break;
            }
        }
        buffer[index++] = '\n';
    }
    printf("%d\n", index);
    buffer[index] = '\0'; // Null-terminate the string
    return buffer;
}

void print_maze(int8_t *array, int8_t *buffer, int width, int height) {
    bool output_array[width * 2 + 2][height * 2 + 2];
    int index = 0;

    for (int x = 0; x <= width; x++) {
        for (int y = 0; y <= height; y++) {
            if (x == width && y == height) {
                output_array[x * 2][y * 2 + 1] = false;
                output_array[x * 2 + 1][y * 2] = false;
                output_array[x * 2 + 1][y * 2 + 1] = false;
                output_array[x * 2][y * 2] = true;
            } else if (x == width) {
                output_array[x * 2][y * 2 + 1] = true;
                output_array[x * 2 + 1][y * 2] = false;
                output_array[x * 2 + 1][y * 2 + 1] = false;
                output_array[x * 2][y * 2] = true;
            } else if (y == height) {
                output_array[x * 2][y * 2 + 1] = false;
                output_array[x * 2 + 1][y * 2] = true;
                output_array[x * 2 + 1][y * 2 + 1] = false;
                output_array[x * 2][y * 2] = true;
            } else {
                output_array[x * 2][y * 2 + 1] = get_bit(array, x + y * width, 2);
                output_array[x * 2 + 1][y * 2] = get_bit(array, x + y * width, 3);
                output_array[x * 2 + 1][y * 2 + 1] = false;
                output_array[x * 2][y * 2] = true;
            }
        }
    }

    for (int y = 0; y < height * 2 + 1; y++) {
        for (int x = 0; x <= width * 2 + 1; x++) {
            int value = 0;
            if (output_array[x][y] == true) {
                // value = output_array[x][y] + 2 * output_array[x][y + 1] + 4 * (x > 0 && output_array[x - 1][y]) + 8 * (y > 0 && output_array[x][y - 1]);
                if (output_array[x + 1][y] == true) {
                    value += 1;
                }
                if (output_array[x][y + 1] == true) {
                    value += 2;
                }
                if (x > 0 && output_array[x - 1][y] == true) {
                    value += 4;
                }
                if (y > 0 && output_array[x][y - 1] == true) {
                    value += 8;
                }
            }
            buffer[index++] = value;
        }
        buffer[index++] = 16;
    }
}

void add_adjacent_cells(int x, int y, BinaryTree *adjacent_cells, int8_t *array, int width, int height) {
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

void create_connection(int8_t *array, int x, int y, int width, int height) {
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

void generate_maze(int8_t *array, int width, int height) {
    if (width + height <= 2) {
        return;
    }

    // Fill array with -1
    for (int i = 0; i < width * height; i++) {
        array[i] = -1;
    }

    // Create binary search tree
    BinaryTree *adjacent_cells = bst_create();

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
    // print_maze(array, width, height);
}
