#include<stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

void plot_point(int x,int y,int c1,int c2, int min, int max) {
	x = x+c1-min;
	y = y+c2-min;
	float X,Y;
	X = ((float)x- min )/(max - min);
	Y = ((float)y- min)/(max - min);
	glBegin(GL_POINTS);
	glVertex3f(X,Y, 0.0);
	glEnd();
	glFlush();
}

void draw_circle(int x,int y,int c1,int c2, int min, int max) {
	plot_point(x,y,c1,c2,min,max);
	plot_point(x,-y,c1,c2,min,max);
	plot_point(-x,y,c1,c2,min,max);
	plot_point(-x,-y,c1,c2,min,max);
	plot_point(y,x,c1,c2,min,max);
	plot_point(y,-x,c1,c2,min,max);
	plot_point(-y,x,c1,c2,min,max);
	plot_point(-y,-x,c1,c2,min,max);
}

extern void midpointcircle(int radius,int c1,int c2, int min, int max) {
	int x=0;
	int y=radius;
	int d=1-radius;
	int de=3;
	int dse=-2*radius;
	draw_circle(x,y,c1,c2,min, max);
	while(y>x)
	{
	if(d<0)
	{
		d+=de;
		de+=2;
		dse+=2;
	}
	else
	{
		d+=dse;
		de+=2;
		dse+=4;
		y--;
	}
		x++;
	draw_circle(x,y,c1,c2,min,max);
	}
}

