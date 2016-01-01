#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include "circle.h"
#include "line.h"
using namespace std;

#define INSERT 1
#define DELETE 2
#define MODIFY 3

const int N = 15;
const int K = 15;
const int SCALE = 50;		// scaling parameter to make the curve fit the display
const int STEP = 2;			// control separation of display points on the curve
const int DELTA = 2;		// control the angle of rotation while creating the 3D object
const int R = 3;			// radius of the cirle used to display a point on the curve
const int WMIN = 0;
const int WMAX = 700;		// window limit
const double PI = 3.1415926;
int n;
FILE* fp = NULL;

int choose[N + 1][N + 1];
vector < pair <int, int> > point;		// store the control points

// calculating n choose k
void preprocess() {
	for (int i = 0; i <= N; i++) choose[0][i] = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0 || j == i) choose[i][j] = 1;
			else choose[i][j] = choose[i - 1][j] + choose[i - 1][j - 1];
		}
	}
}

// function to calculate the rotated coordinates
// and add them to the off file
void rotate(int x, int y) {
	int z = 0;
	for (int theta = 0; theta < 360; theta += DELTA) {
		double alpha = theta * PI / 180.0;
		double X = x * cos(alpha) + z * sin(alpha);
		double Z = -x * sin(alpha) + z * cos(alpha);
		fprintf(fp, "%lf %lf %lf\n", X, 1.0 * y, Z);
	}
}

// function to draw the curve in 2D using the control points
// also add the face list in the off file
void plotCurve() {
	glBegin(GL_POINTS);
	int N = 1 + 100 / STEP;
	int K = 360 / DELTA;
	fp = fopen("input.off", "w");
	fprintf(fp, "%s\n", "OFF");
	int vertices = N * K;
	int faces = (N - 1) * K;
	int edges = vertices + faces;
	fprintf(fp, "%d %d %d\n", vertices, faces, edges);
	
	for (int t = 0; t <= 100; t += STEP) {
		double x = 0, y = 0;
		 for (int i = 0; i <= n; i++) {
			double b = choose[n][i] * pow(1 - t / 100.0, n - i) * pow(t / 100.0, i);
			x += b * point[i].first;
			y += b * point[i].second;
		}
		midpointcircle(R, x, y, WMIN, WMAX);
		
		rotate(x, y);		// rotate the obtained point about Y-axis to obtain a latitude
	}
	
	// appending the face list to the off file
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < K; j++) {
			int idx = i * K + j;
			int c = idx;
			int b = c + K;
			int d = (j == K - 1 ? c - K + 1 : c + 1);
			int a = d + K;
			fprintf(fp, "4 %d %d %d %d 0.2 0.2 0.2 0.75\n", a, b, c, d);
		}
	}
	
	fclose(fp);
	glEnd();
}

// function to draw the control lines
void plotControlLines() {
	for (int i = 0; i < n; i++) {
    	drawline(point[i].first, point[i].second, point[i + 1].first, point[i + 1].second, WMIN, WMAX);
    }
}

void plot() {
	glClear(GL_COLOR_BUFFER_BIT);
	plotControlLines();
	plotCurve();
}

// user interaction
void query() {
	while (true) {
	
		/*
			1: Insert
			2: Delete
			3: Modify
			-1: Exit
		*/
		
		int type;
		cin >> type;
		
		if (type == -1) exit(0);
		
		if (type == INSERT) {				// insert a point
			int x, y;
			cin >> x >> y;
			x *= SCALE;
			y *= SCALE;
			
			// find the index of the input point based
			// on the sum of its distances from two already
			// adjacent points in control points list
			double best = INT_MAX;
			int idx, dx, dy;
			
			for (int i = 0; i < n; i++) {
				int x1 = point[i].first;
				int y1 = point[i].second;
				int x2 = point[i + 1].first;
				int y2 = point[i + 1].second;
				dx = abs(x - x1);
				dy = abs(y - y1);
				double dist = 0;
				dist += sqrt(dx * dx + dy * dy);
				dx = abs(x - x2);
				dy = abs(y - y2);
				dist += sqrt(dx * dx + dy * dy);
				if (dist < best) {
					best = dist;
					idx = i;
				}
			}
			
			// insert at the correct index
			point.insert(point.begin() + idx + 1, make_pair(x, y));
			n++;
			plot();			// update the curve
			
		} else if (type == DELETE) {		// delete a point
			int x, y;
			cin >> x >> y;
			x *= SCALE;
			y *= SCALE;
			
			// find the point and remove it from the control points list
			point.erase(find(point.begin(), point.end(), make_pair(x, y)));
			n--;
			
			plot();			// update the curve
			
		} else if (type == MODIFY) {		// modify a point
			int x0, y0, x1, y1;
			
			// input the initial x and y coordinates
			// and the final x and y coordinates
			// of the point to be moved
			cin >> x0 >> y0 >> x1 >> y1;
			x0 *= SCALE;
			x1 *= SCALE;
			y0 *= SCALE;
			y1 *= SCALE;
			
			// find the point and update it
			pair <int, int> p = make_pair(x0, y0);
			for (int i = 0; i <= n; i++) {
				if (point[i] == p) {
					point[i] = make_pair(x1, y1);
					break;
				}
			}
			plot();		// update the curves
			
		} else {
			cout << "Invalid choice!\n";
		}
	}
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    plot();
    query();
    glFlush ();
}

void init (void)  {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
	preprocess();
	int x, y;
	
	// order of curve
	cin >> n;
	point.resize(n + 1);
	
	for (int i = 0; i <= n; i++) {
		cin >> x >> y;
		x *= SCALE; y *= SCALE;
		point[i] = make_pair(x, y);
	}
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (WMAX, WMAX); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("TREE DRAWING ASSIGNMENT 1 ALGO 1");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

