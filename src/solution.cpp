#include "solution.h"
#include <vector>

bool isContains(Node* node, int key) {
    if (!node) {
        return false;
    }

    if (node->key > key) {
        return isContains(node->left, key);
    }

    if (node->key < key) {
        return isContains(node->right, key);
    }

    return true;
}


Node* insert(Node* node, int value) {
    if (!node) {
        return new Node(value);
    }

    if (node->key > value) {
        node->left = insert(node->left, value);
    }
    else if (node->key < value) {
        node->right = insert(node->right, value);
    }

    return node;
}


Node* getMax(Node* node) {
    if (!node) {
        return nullptr;
    }

    if (!node->right) {
        return node;
    }

    return getMax(node->right);
}


Node* getMin(Node* node) {
    if (!node) {
        return nullptr;
    }

    if (!node->left) {
        return node;
    }

    return getMin(node->left);
}


Node* remove(Node* node, int key) {
    if (!node) {
        return nullptr;
    }

    if (node->key == key && !node->left && !node->right) {
        delete node;
        return nullptr;
    }

    if (node->key == key && !node->left) {
        Node* temp = node->right;
        delete node;
        return temp;
    }
    if (node->key == key && !node->right) {
        Node* temp = node->left;
        delete node;
        return temp;
    }

    if (node->key == key) {
        Node* temp = getMin(node->right);
        node->key = temp->key;
        node->right = remove(node->right, node->key);
        return node;
    }

    if (node->key < key) {
        node->right = remove(node->right, key);
    }

    if (node->key > key) {
        node->left = remove(node->left, key);
    }

    return node;
}


void inOrderVector(const Node* tree, std::vector<int>& nodes) {
    if (!tree) {
        return;
    }

    inOrderVector(tree->left, nodes);

    nodes.push_back(tree->key);

    inOrderVector(tree->right, nodes);
}


Node* section(const Node* l, const Node* r) {
    std::vector<int> v1;
    std::vector<int> v2;
    Node* tree = nullptr;

    inOrderVector(l, v1);
    inOrderVector(r, v2);

    int i = 0;
    int j = 0;

    while (i < v1.size() && j < v2.size()) {
        if (v1[i] == v2[j]) {
            tree = insert(tree, v1[i]);
        }
        if (v1[i] < v2[j]) {
            i++;
        }
        else {
            j++;
        }
    }

    return tree;
}


int getHeightOfNode(const Node* tree, int key) {
    if (!tree) {
        return INT32_MIN;
    }

    if (tree->key == key) {
        return 0;
    }

    int left = 1 + getHeightOfNode(tree->left, key);
    int right = 1 + getHeightOfNode(tree->right, key);

    return left >= right ? left : right;
}


bool areCousins(const Node* tree, int key1, int key2) {
    if (!tree) {
        return false;
    }

    if (key1 == key2) {
        return false;
    }

    int key1Height = getHeightOfNode(tree, key1);
    int key2Height = getHeightOfNode(tree, key2);

    if (key1Height == key2Height) {
        int ancestor = LCA(tree, key1, key2);
        int ancestorHeight = getHeightOfNode(tree, ancestor);

        if (key1Height - ancestorHeight == 1) {
            return false;
        }

        return true;
    }

    return false;
}


int LCA(const Node* tree, int key1, int key2) {
    if (!tree) {
        return -1;
    }

    if (key1 > key2) {
        return LCA(tree, key2, key1);
    }

    if (tree->key == key1) {
        if (isContains(tree->right, key2)) {
            return key1;
        }
        else {
            return -1;
        }
    }

    if (tree->key == key2) {
        if (isContains(tree->left, key1)) {
            return key2;
        }
        else {
            return -1;
        }
    }

    if (isContains(tree->left, key1) && isContains(tree->right, key2)) {
        return tree->key;
    }

    if (tree->key < key1 && tree->key < key2) {
        return LCA(tree->right, key1, key2);
    }
    else if (tree->key > key1 && tree->key > key2) {
        return LCA(tree->left, key1, key2);
    }

    return -1;
}