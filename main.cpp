#include "compression.h"

struct MinHeapNode {

    char data;
    bool is_leaf;
    unsigned freq;

    struct MinHeapNode *left;
    struct MinHeapNode *right;
};



bool cmp(const std::pair<char,int> &a, const std::pair<char,int> &b) {
    return a.second < b.second;
}

void    printDataFrequency(std::vector<std::pair<char, int> > data_freq) {

    for (size_t j = 0; j < data_freq.size(); j++) {

        std::cout << "(" << data_freq[j].second << ", \'" << data_freq[j].first << "\'), ";
    }
}

void printTree(MinHeapNode* node, std::string prefix = "", bool isLeft = true) {
    if (node == NULL)
        return;

    std::cout << prefix;

    std::cout << (isLeft ? "├──" : "└──" );

    if (node->data == '$')
        std::cout << "[$," << node->freq << "]" << std::endl;
    else
        std::cout << "(" << node->data << "," << node->freq << ")" << std::endl;

    std::string newPrefix = prefix + (isLeft ? "│   " : "    ");

    printTree(node->left, newPrefix, true);
    printTree(node->right, newPrefix, false);
}


void createTree (std::vector<std::pair<char, int> > data_freq) {

    std::vector<MinHeapNode*> nodes;
    for (size_t i = 0; i < data_freq.size(); i++) {

        MinHeapNode* node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
        node->data = data_freq[i].first;
        node->freq = data_freq[i].second;
        node->left = node->right = NULL;
        nodes.push_back(node);
    }

    while (nodes.size() > 1) {

        size_t min1 = 0, min2 = 1;
        if (nodes[min2]->freq < nodes[min1]->freq)
            std::swap(min1, min2);
        for (size_t i = 2; i < nodes.size(); i++) {

            if (nodes[i]->freq < nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->freq < nodes[min2]->freq) {
                min2 = i;
            }
        }
        MinHeapNode* new_node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
        new_node->data = '$';
        new_node->freq = nodes[min1]->freq + nodes[min2]->freq;
        new_node->left = nodes[min1];
        new_node->right = nodes[min2];

        if (min1 > min2)
            std::swap(min1, min2);

        nodes.erase(nodes.begin() + min2);
        nodes.erase(nodes.begin() + min1);
        nodes.push_back(new_node);
    }

    MinHeapNode *root = nodes[0];
    printTree(root);
}

int main(int argc, char **argv) {

    if (argc != 2) 
        return (std::cerr << "Error: Wrong amount of arguments." << std::endl, 1);


    std::ifstream file(argv[1]);
    if (!file.is_open())
        return (std::cerr << "Error: could not open file." << std::endl, 1);

    std::string line;
    std::map<char, int> data_freq_map;

    while (std::getline(file, line)) {

        for (size_t i = 0; i < line.size(); i++) {
            data_freq_map[line[i]]++;
        }
    }
    file.close();
    std::vector<std::pair<char,int> > data_freq;

    for (std::map<char,int>::iterator it = data_freq_map.begin(); it != data_freq_map.end(); ++it) {
        data_freq.push_back(*it);
    }
    std::sort(data_freq.begin(), data_freq.end(), cmp);

    // printDataFrequency(data_freq);

    createTree(data_freq);
    return (0);
        
}

    //          (13)
    //         /    \
    //    rfo(3)  esgk(10)
    //     /   \      /   \
    //  r(1)  fo(2)  e(4) sgk(6)
    //          /   \       /   \
    //        f(1)  o(1)  s(2)  gk(4)
    //                    /   \
    //                  g(2)  k(2)
    