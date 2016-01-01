#include <bits/stdc++.h>
#include "circle.h"
#include "line.h"
using namespace std;

const int SIZE = 1;
const int XMIN = 0;
const int XMAX = 700;
const int YMIN = 0;
const int YMAX = 700;
const int WMIN = 0;
const int WMAX = 700;
const int WIDTH = (XMAX - XMIN + SIZE);
const int HEIGHT = (YMAX - YMIN + SIZE);

double val[WIDTH][HEIGHT];

// define the function to be drawn
double f(int x, int y) {
	
	// ellipse
	double x1 = (x - 300) * (x - 300) / 40000.0;
	double y1 = (y - 300) * (y - 300) / 10000.0;
	return x1 + y1 - 1;
}

// draw the square based on the index and the coordinates
void displaySquare(int idx, int x, int y) {

	double fromx, fromy, tox, toy;
	
	switch(idx) {
	
		case 0:
		case 15:
			break;
		
		case 1:
		case 14:
			fromx = x + SIZE / 2;
			fromy = y;
			tox = x;
			toy = y + SIZE / 2;
			// drawline	
			drawline(fromx, fromy, tox, toy, WMIN, WMAX);	
			break;
		
		case 2:
		case 13:
			fromx = x + SIZE / 2;
			fromy = y;
			tox = x + SIZE;
			toy = y + SIZE / 2;
			// drawline
			drawline(fromx, fromy, tox, toy, WMIN, WMAX);	
			break;
		
		case 3:
		case 12:
			fromx = x;
			fromy = y + SIZE / 2;
			tox = x + SIZE;
			toy = y + SIZE / 2;
			// drawline
			drawline(fromx, fromy, tox, toy, WMIN, WMAX);	
			break;
		
		case 4:
		case 11:
			fromx = x + SIZE;
			fromy = y + SIZE / 2;
			tox = x + SIZE / 2;
			toy = y + SIZE;
			// drawline
			drawline(fromx, fromy, tox, toy, WMIN, WMAX);	
			break;
		
		case 5:
			fromx = x + SIZE / 2;
			fromy = y;
			tox = x + SIZE;
			toy = y + SIZE / 2;
			// drawline
			drawline(fromx, fromy, tox, toy, WMIN, WMAX);	
			
			fromx = x;
			fromy = y + SIZE / 2;
			tox = x + SIZE / 2;
			toy = y + SIZE;
			// drawline
			drawline(fromx, fromy, tox, toy, WMIN, WMAX);	
			break;
		
		case 10:
			fromx = x + SIZE / 2;
			fromy = y;
			tox = x;
			toy = y + SIZE / 2;
			// drawline
			drawline(fromx, fromy, tox, toy, WMIN, WMAX);	
			
			fromx = x + SIZE;
			fromy = y + SIZE / 2;
			tox = x + SIZE / 2;
			toy = y + SIZE;
			// drawline
			drawline(fromx, fromy, tox, toy, WMIN, WMAX);	
			break;
			break;
		
		case 6:
		case 9:
			fromx = x + SIZE / 2;
			fromy = y;
			tox = x + SIZE / 2;
			toy = y + SIZE;
			// drawline
			drawline(fromx, fromy, tox, toy, WMIN, WMAX);	
			break;
		
		case 7:
		case 8:
			fromx = x;
			fromy = y + SIZE / 2;
			tox = x + SIZE / 2;
			toy = y + SIZE;
			// drawline
			drawline(fromx, fromy, tox, toy, WMIN, WMAX);	
			break;
	}
}

// for every grid point, determine the index of the 
// square based on the function value at neighbors
void marchingSquares() {
	for (int i = XMIN; i < XMAX; i += SIZE) {
		for (int j = YMIN; j < YMAX; j += SIZE) {
			int id = 0;
			if (val[i][j] > 0) id |= 1;
			if (val[i + SIZE][j] > 0) id |= 2;
			if (val[i + SIZE][j + SIZE] > 0) id |= 4;
			if (val[i][j + SIZE] > 0) id |= 8;
			displaySquare(id, i, j);
			//cout << setw(3) << id;
		}
		// << endl;
	}
}

// fill the grid with values at differen coordinates
void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);
    for (int x = XMIN; x <= XMAX; x += SIZE) {
		for (int y = YMIN; y <= YMAX; y += SIZE) {
			val[x][y] = f(x, y);
		}
	}
	marchingSquares();
    glFlush();
}

void init (void)  {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (WMAX, WMAX); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Marching Squares");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
	return 0;
}

