#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "generate_tree.h"
#include "circle.h"
#include "line.h"

const double density = 1.0;
const int maxheight = 4;
const int XJUMP = 20;
const int YJUMP = 50;
const int R = 5;
const int YMAX = 700;
const int WMIN = 0;
const int WMAX = 700;
int x = 1;

pair < Node*, pair <int, int> > Tree;

void Fetch(Node* root) {
/*
	This extra pass is an inorder traversal to store the x since drawing a line
	would be different for left and right children.
*/
    if (root == NULL) return;
    Fetch(root->left);
    root->x = x++;   
    Fetch(root->right);
}

void Draw(Node* root) {
/*
	Inorder traversal to draw the tree
*/
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
    Fetch(Tree.first);
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (WMAX, WMAX); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("TREE DRAWING ASSIGNMENT 1 ALGO 2");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}

