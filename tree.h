#include <bits/stdc++.h>
using namespace std;

const int SIZE = 10;

struct Node {
    int data;
    int level                                                                                                                                                                                                                                                                                                                                                                                       ;
    Node* left;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
    Node(int d, int l) {
        data = d; level = l;                                                                                                                                                    
        left = right = NULL;
    }
};

pair <Node*, int> create() {                                                                                                    
    Node* root = new Node(1, 0      
    root->left = new Node(2, 1);
    root->right = new Node(3, 1);
    root->left->left = new Node(4, 2);
    root->left->right = new Node(5, 2);
    root->right->left = new Node(6, 2);
    root->right->right = new Node(7, 2);
    root->left->right->left = new Node(8,                                                                                                                                                                                                                   3);
    root->left->right->right = new Node(9, 3);
    root->right->right->left = new Node(10, 3);
    root->right->right->right = new Node(11, 3);
    return make_pair(root, 4);
}

void bfs(pair <Node*, int> root) {
    queue <Node*> Q;
    int maxlevel = root.second;
    int x[root.second];
    fill(begin(x), end(x), 1);
    Q.push(root.first);
    while (!Q.empty()) {
        Node* temp = Q.front();
        Q.pop();
        //cout << temp->data << ' ';
        int y = temp->level;
        midpointcircle(10, x[y]++, SIZE * (maxlevel - y), 0, 100);
        if (temp->left) Q.push(temp->left);
        if (temp->right) Q.push(temp->right);
    }
}

void dfs(Node* root) {
    if (root == NULL) return;
    dfs(root->left);
    cout << root->data << ' ';
    dfs(root->right);
}

