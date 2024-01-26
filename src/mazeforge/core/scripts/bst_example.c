// C:\Tools\ghc-9.0.1\mingw\bin\gcc.exe

#include <stdlib.h>
#include <time.h>
#include "bst.h"


int main () {
    srand(time(0));
    BinaryTree* tree = create_binary_tree();
    for (int i = 0; i < 30; i++) {
        int value = rand() % 100;
        add_value(tree, value);
    }
    print_tree(tree);
    return 0;
}