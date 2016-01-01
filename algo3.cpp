#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "generate_tree.h"
#include "circle.h"
#include "line.h"

const double density = 1.0;
const int maxheight = 10;
const int XJUMP = 20;
const int YJUMP = 50;
const int R = 5;
const int YMAX = 700;
const int WMIN = 0;
const int WMAX = 700;
int x = 1;
int Next[10002];
int Mod[10002];

pair < Node*, pair <int, int> > Tree;

// this pass is to compute the x co-ordinates
// and the modifier values

void Pass1(Node* root) {
    Node* curr = root;
    curr->status = FIRST;
    while (curr) {
        switch(curr->status) {
        	// change status and move to left child if any
            case FIRST:					
                curr->status = LEFT;		
                if (curr->left) {		
                    curr = curr->left;
                    curr->status = FIRST;
                }
                break;
                
            case LEFT:					
	        	// change status and move to right child if any
            	curr->status = RIGHT;
            	if (curr->right) {		
            		curr = curr->right;
            		curr->status = FIRST;
            	}
            	break;
            	
            case RIGHT:	
            	// calculate x and modifier values				
            	int h = curr->depth;
            	int place;
            	bool isleaf = (!curr->left && !curr->right);
            	if (isleaf) place = Next[h];
            	else if (!curr->left) place = curr->right->x - 1;
            	else if (!curr->right) place = curr->left->x + 1;
            	else place = (curr->left->x + curr->right->x) >> 1;
            	Mod[h] = max(Mod[h], Next[h] - place);
            	if (isleaf) curr->x = place;
            	else curr->x = place + Mod[h];
            	Next[h] = curr->x + 2;
            	curr->modifier = Mod[h];
            	curr = curr->parent;
        }
    }
}

void Pass2(Node* root) {
	Node* curr = root;
	curr->status = FIRST;
	
	// store the total shift from root to the current node
	int sum = 0;
	while (curr) {
		switch(curr->status) {
			case FIRST:
				// add shift to current x value
				curr->x += sum;
				// update total shift and move to left child
				sum += curr->modifier;
				curr->status = LEFT;
				if (curr->left) {
					curr = curr->left;
					curr->status = FIRST;
				}
				break;
			
			case LEFT:
				// move to right child
				curr->status = RIGHT;
				if (curr->right) {
					curr = curr->right;
					curr->status = FIRST;
				}
				break;
			
			case RIGHT:
				// remove the contribution of current node while moving back to the parent
				sum -= curr->modifier;
				curr = curr->parent;
		}
	}
}

// inorder traversal to draw the tree
// from each node draw the line to the parent (except if the node is the root)
void Draw(Node* root) {
    if (root == NULL) return;
    Draw(root->left);
    int fromx = root->x * XJUMP;
    int fromy = WMAX - 10 - YJUMP * root->depth;
    midpointcircle(R, fromx, fromy, WMIN, WMAX);
    if (root != Tree.first) {
        int tox = root->parent->x * XJUMP;
        int toy = WMAX - 10 - YJUMP * root->parent->depth;
        drawline(fromx, fromy, tox, toy, WMIN, WMAX);
    }
    Draw(root->right);
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    drawaxes(WMIN, WMAX, 100,10);
    memset(Mod, 0, sizeof(Mod));
    for (int i = 0; i < 10002; i++) Next[i] = 1;
    Pass1(Tree.first);
    Pass2(Tree.first);
    Draw(Tree.first);
    //midpointcircle(10, 100, 100 , 0, WMAX);
    //drawline(10, 40, 30, 100, 0, 200);
    glFlush ();
}

void init (void)  {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    Tree = generate(density, maxheight);
    /*
    
    //Hard coded the example given in the paper to verify correctness of the code
    
    Node* root = new Node(0);
    root->left = new Node(1);
    root->right = new Node(1);
    root->left->left = new Node(2);
    root->left->right = new Node(2);
    root->right->right = new Node(2);
    root->left->right->left = new Node(3);
    root->left->right->right = new Node(3);
    root->right->right->right = new Node(3);
    root->right->right->right->left = new Node(4);
    root->right->right->right->left->left = new Node(5);
    root->right->right->right->left->right= new Node(5);
    root->right->right->right->left->left->left = new Node(6);
    root->right->right->right->left->left->right = new Node(6);
    
    root->parent = NULL;
    root->left->parent = root;
    root->right->parent = root;
    root->left->left->parent = root->left;
    root->left->right->parent = root->left;
    root->right->right->parent = root->right;
    root->left->right->left->parent = root->left->right;
    root->left->right->right->parent = root->left->right;
    root->right->right->right->parent = root->right->right;
    root->right->right->right->left->parent = root->right->right->right;
    root->right->right->right->left->left->parent = root->right->right->right->left;
    root->right->right->right->left->right->parent = root->right->right->right->left;
    root->right->right->right->left->left->left->parent = root->right->right->right->left->left;
    root->right->right->right->left->left->right->parent = root->right->right->right->left->left;
    
    Tree.first = root;
    
    */

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (WMAX, WMAX); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("TREE DRAWING ASSIGNMENT 1 ALGO 3");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}

