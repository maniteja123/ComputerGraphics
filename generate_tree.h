#include <bits/stdc++.h>
using namespace std;

enum Status {NIL, FIRST, LEFT, RIGHT};

struct Node {
	int depth;
	int x;
	Node* left;
	Node* right;
	Node* parent;
	int modifier;
    Status status;
	
	Node(int d) {
		depth = d;
		x = 0;
		modifier = 0;
		status = NIL;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
};

void print(Node* root) {
/*
	Print the tree using BFS - level order traversal
*/

	queue <Node*> Q;
	Q.push(root);
	while (!Q.empty()) {
		Node* temp = Q.front();
		Q.pop();
		cout << temp->depth << ' ';
		if (temp->left) Q.push(temp->left);
		if (temp->right) Q.push(temp->right);
	}
	cout << endl;
}

pair <Node*, pair <int, int> > generate(double density, int limit) {

/*
	Use BFS to generate tree for a given maximum height with given branching density
*/

	Node* root = new Node(0);
	int nos = 1;
	int maxdepth = 0;
	queue <Node*> Q;
	Q.push(root);
	srand(time(NULL));
	int lim = (int) floor(density * 100);		// get limit ranging from 1 to 100
	while (!Q.empty()) {
		Node* temp = Q.front();
		Q.pop();
		int d = temp->depth;
		if (d == limit) continue;				// max height reached
		int toss = rand() % 100;
		if (toss < lim) {						// If within limit, generate let child
			temp->left = new Node(d + 1);
			temp->left->parent = temp;
			Q.push(temp->left);
			maxdepth = max(maxdepth, d + 1);
			nos++;
		}
		toss = rand() % 100;
		if (toss < lim) {     					// If within limit, generate right child
			temp->right = new Node(d + 1);
			temp->right->parent = temp;
			Q.push(temp->right);
			maxdepth = max(maxdepth, d + 1);
			nos++;
		}
	}
	return make_pair(root, make_pair(maxdepth, nos));
}

