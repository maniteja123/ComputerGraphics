#include<stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

void swap( float *x, float *y)
{
    float temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


extern void drawline(float x, float y, float x1, float y1, float min, float max)
{
    glBegin(GL_POINTS);
    int i, flag=0, flag2=0;
    float temp, dx1, dy1, d, incE, incNE, z, z1;
    x = x - min;
    x1 =x1 - min;
    y = y - min;
    y1 = y1 - min;
    x =  x/(max-min) *10000;
    x1 = x1/(max-min)*10000;
    y =  y/(max-min) *10000;
    y1 = y1/(max-min)*10000;
    dx1 = x1 - x;
    dy1 = y1 - y;

    if (dx1<0)
    {
      swap (&x, &x1);
      swap (&y, &y1);
      dx1 = -dx1;
      dy1 = -dy1;
    }

    if (dx1 < abs(dy1))
    { flag = 1;
      if(dy1<0)
       {flag2=1;
       } 
      swap (&dx1,&dy1);
      swap (&x1, &y1);
      swap(&x,&y);
    }  

    d = 2*abs(dy1) - abs(dx1);
    incE = 2*abs(dy1);
    incNE = 2*(abs(dy1) - abs(dx1));
  
    z = (x>x1)? x1:x;
    z1 = (x1>x)? x1:x;
    for (i = z; i <= z1; i++)
	{
		if(d<0)
		{
			d = d+incE;
			
		}
		else
		{
			d = d+incNE;
			(dy1>0)?y++:y--;
		}
			(flag2)?x--:x++;
		if (flag==0)
		glVertex3f(x/10000, y/10000, 0.0);
                else
		glVertex3f(y/10000, x/10000, 0.0);

	}
    glEnd();
}

 void drawaxes(float min, float max, float major, float minor) {
    drawline(0,min, 0, max, min, max);
    drawline(min,0,max, 0, min, max);
    int i;
    float size;
    for( i=(int)min; i*minor <= (max - min); i++)  {
     size = 100;
     if (((int)((i*minor)/major))*(major) == i*minor)
        size = size/2;
     drawline( -max/size, i*minor, max/size, i*minor, min, max);
     drawline( i*minor, -max/size, i*minor, max/size, min, max);
    }
}


