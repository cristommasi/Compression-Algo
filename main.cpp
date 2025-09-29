#include "compression.h"

struct MinHeapNode {

    char data;
    bool is_leaf;
    unsigned freq;

    struct MinHeapNode *left;
    struct MinHeapNode *right;
};

class Compare {public:bool operator() (MinHeapNode* a, MinHeapNode* b) {return a->freq > b->freq;}};

bool cmp(const std::pair<char,int> &a, const std::pair<char,int> &b) {return a.second < b.second;}

void    printDataFrequency(std::vector<std::pair<char, int> > data_freq) {

    for (size_t j = 0; j < data_freq.size(); j++) {

        std::cout << "(" << data_freq[j].second << ", \'" << data_freq[j].first << "\'), ";
    }
    std::cout << std::endl;
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


void preOrder(MinHeapNode* root, std::vector<std::pair<char,std::string> > &codes, std::string cur) {

	if (root == NULL)
        return ;

	if (root->left == NULL && root->right == NULL) {
		codes.push_back(std::make_pair(root->data, cur));
		return ;
	}

	preOrder(root->left, codes, cur + '0');
	preOrder(root->right, codes, cur + '1');
}

MinHeapNode* createTree(std::vector<std::pair<char, int> > data_freq) {

    std::priority_queue<MinHeapNode*, std::vector<MinHeapNode *>, Compare> nodes;
    for (size_t i = 0; i < data_freq.size(); i++) {

        MinHeapNode* node = new MinHeapNode();
        node->data = data_freq[i].first;
        node->freq = data_freq[i].second;
        node->left = node->right = NULL;
        nodes.push(node);
    }

    while (nodes.size() > 1) {

        MinHeapNode* left = nodes.top();
        nodes.pop();

        MinHeapNode* right = nodes.top();
        nodes.pop();

        MinHeapNode* new_node = new MinHeapNode();
        new_node->data = '$';
        new_node->freq = left->freq + right->freq;
        new_node->left = left;
        new_node->right = right;

        nodes.push(new_node);
    }
    return (nodes.top());
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
    std::cout << "string length = " << line.size() << std::endl;
    std::vector<std::pair<char,int> > data_freq;

    for (std::map<char,int>::iterator it = data_freq_map.begin(); it != data_freq_map.end(); ++it) {
        data_freq.push_back(*it);
    }
    std::sort(data_freq.begin(), data_freq.end(), cmp);

    printDataFrequency(data_freq);

    MinHeapNode *root = createTree(data_freq);
    printTree(root); std::cout << std::endl;
    std::vector<std::pair<char,std::string> > codes;
    preOrder(root, codes, "");
    for (size_t i = 0; i < codes.size(); i++) {

        std::cout  << codes[i].first << "(" << data_freq_map[codes[i].first] << ")"<< " = " << codes[i].second << std::endl;
    }
    return (0);
        
}
