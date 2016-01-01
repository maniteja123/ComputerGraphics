#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "generate_tree.h"
#include "circle.h"
#include "line.h"

const double density = 0.7;
const int maxheight = 5;
const int XJUMP = 40;
const int YJUMP = 50;
const int R = 5;
const int YMAX = 700;
const int WMIN = 0;
const int WMAX = 700;
const int OFFSET = 20;
int Next[10002] = {0};

pair < Node*, pair <int, int> > Tree;

void Draw(Node* root) {
/*
	Inorder traversal to draw the tree
*/
    if (root == NULL) return;
    Draw(root->left);
    root->x = Next[root->depth]++;			// Increment the next x coordinate for the level before storing value in the node
    int fromx = root->x * XJUMP + OFFSET;	// OFFSET since x starts from 0, i.e, left corner of window
    int fromy = WMAX - 10 - YJUMP * root->depth;	// y coordinate based on the depth of node
    midpointcircle(R, fromx, fromy, WMIN, WMAX);
    if (root != Tree.first) {
        int tox = root->parent->x * XJUMP + OFFSET;
        int toy = WMAX - 10 - YJUMP * root->parent->depth;
        drawline(fromx, fromy, tox, toy, WMIN, WMAX);
    }
    Draw(root->right);
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    drawaxes(WMIN, WMAX, 100,10);
    memset(Next, 0, sizeof(Next));
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
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (WMAX, WMAX); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("TREE DRAWING ASSIGNMENT 1 ALGO 1");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}

