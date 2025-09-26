#ifndef COMPRESSION_H
# define COMPRESSION_H

# include <iostream>
# include <unistd.h>
# include <fstream>
# include <string>
# include <map>


struct MinHeapNode {

    char data;

    unsigned freq;

    struct MinHeapNode *left, *right;
};

struct MinHeap {

    unsigned size;

    unsigned capacity;

    struct MinHeapNode** array;
};

#endif