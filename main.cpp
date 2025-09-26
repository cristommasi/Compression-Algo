#include "compression.h"




struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return (temp);
}

struct MinHeap* createMinHeap(unsigned capacity) {

    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
}

void    printDataFrequency(std::map<char, int> data_freq) {

    int width = 0;
    for (std::map<char, int>::iterator it = data_freq.begin(); it != data_freq.end(); ++it) {

        width++;
        std::cout << "(" <<it->second << ", \'" << it->first << "\'), ";
        if (width >= 10) {
            width = 0;
            std::cout << std::endl;
        }
    }
}


struct MinHeadNode* buildTree(std::map<char, int> data_freq, int size) {

    struct MinHeapNode *left, *right, *top;

    struct MinHeap *minHeap = create

}


int main(int argc, char **argv) {

    if (argc != 2) 
        return (std::cerr << "Error: Wrong amount of arguments." << std::endl, 1);


    std::ifstream file(argv[1]);
    if (!file.is_open())
        return (std::cerr << "Error: could not open file." << std::endl, 1);

    std::string line;
    std::map<char, int> data_freq;

    while (std::getline(file, line)) {

        for (size_t i = 0; i < line.size(); i++) {
            data_freq[line[i]]++;
        }
    }

    printDataFrequency(data_freq);

    struct MinHeapNode *root = buildTree(data_freq, data_freq.size());

    file.close();
    return (0);
        
}