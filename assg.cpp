#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

struct point{
	float x, y, z;
};

struct point eye, look, up, u, v, n, temp;
int flag=-1, color=0, flip=0;
float fsize =1, vec=0.0, theta=0, theta1=0, vect=0.0, angle=40, length = 15, width=12, height=10;

// calculate a cross b
struct point cross(struct point a,struct point b) {
	struct point c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return c;
} 

// assign functions to keys for camera translation
void keyboard(unsigned char key, int x, int y) {

    switch(key){
		case 'z': flag = 2 ; break;			// zoom in
		case 'x': flag = 3 ; break;			// zoom out
		case 'a': flag = 4 ; break;			// shift left
		case 'd': flag = 5 ; break;			// shift right
		case 'w': flag = 6 ; break;			// shift up
		case 's': flag = 7 ; break;			// shift down
		//case '1': flip=1 ; break;
		//case '0': flip=0 ; break;
		case '+': flag=8 ; break;			// zoom in
		case '-': flag=9 ; break;			// zoom out
	}
}

// assign functions to keys for camera rotation
void spkeyboard(int key, int x, int y) {
    switch(key) {
	    case GLUT_KEY_RIGHT : flag = 22 ; break;	// rotate camera right
	    case GLUT_KEY_LEFT : flag = 11 ; break;		// rotate camera left
	    case GLUT_KEY_UP : flag = 1 ; break;		// rotate camera up
	    case GLUT_KEY_DOWN : flag = 10 ; break;		// rotate camera down
	    //case 13 : flag = 0; break;
	}
}

// create door
void door() {
	glColor3ub(225, 169, 90);
	glBegin(GL_QUADS);
		glVertex3f(0,0,2);
		glVertex3f(0,0,6);
   		glVertex3f(0,7,6);
		glVertex3f(0,7,2);
	glEnd();
	
	// see-through glass
	glColor3ub(0,204,204);
	glBegin(GL_QUADS);
		glVertex3f(0.1,5,3);
		glVertex3f(0.1,6,3);
   		glVertex3f(0.1,6,5);
		glVertex3f(0.1,5,5);
	glEnd();
}

// create window
void window() {
	glColor3ub(0, 128, 0);
	glBegin(GL_QUADS);
		glVertex3f(15,4,9);
		glVertex3f(15,4,3);
   		glVertex3f(15,8,3);
		glVertex3f(15,8,9);
	glEnd();

}

// create a cube with given dimensions
void cube(double len, double width, double thick) {
	glTranslated(0, thick/2, 0);
	glScaled(len, thick, width);
	//glColor3ub(139,69,19);
	glutSolidCube(fsize);
	glColor3d(0,0,0);
	glutWireCube(fsize);
}

// create lappy
void lappy(double len, double width, double thick, double height) {
	
	// laptop base
	glPushMatrix();
		glTranslated(0, thick/2, 0);
		glScaled(len, thick, width);
		glColor3ub(10, 10, 10);
		glutSolidCube(fsize);
		glColor3d(0,0,0);
		glutWireCube(fsize);
	glPopMatrix();
	
	// laptop screen
	glPushMatrix();
		glTranslated(0, height/2 + thick/2, -width/2);
		glRotated(-20,1.0,0,0);
		glScaled(width, height, thick);
		glColor3ub(50, 50, 50);
		glutSolidCube(fsize);
		glColor3d(0,0,0);
		glutWireCube(fsize);
	glPopMatrix();	
	
}

// create table
void table(double len, double width, double thick, double height, double legDim) {
	double distLength = len/2 - legDim/2, distWidth = width/2 - legDim/2;
	
	// table top
	glColor3ub(153, 76, 0);
	glPushMatrix();
		glTranslated(8.5, height, 1);
		cube(len,width,thick);
	glPopMatrix();
	
	// table leg 1
	glColor3ub(153, 76, 0);
	glPushMatrix();
		glTranslated(8.5+distLength, 0, 1+distWidth);
		cube(legDim,legDim,height);
	glPopMatrix();
	
	// table leg 2
	glColor3ub(153, 76, 0);
	glPushMatrix();
		glTranslated(8.5-distLength, 0, 1+distWidth);
		cube(legDim,legDim,height);
	glPopMatrix();
	
	// table leg 3
	glColor3ub(153, 76, 0);
	glPushMatrix();
		glTranslated(8.5+distLength, 0, 1-distWidth);	
		cube(legDim,legDim,height);
	glPopMatrix();
	
	// table leg 4
	glColor3ub(153, 76, 0);
	glPushMatrix();
		glTranslated(8.5-distLength, 0, 1-distWidth);	
		cube(legDim,legDim,height);
	glPopMatrix();
	
	// translation for laptop creation
	glPushMatrix();
		glColor3ub(10, 10, 10);
		glTranslated(8.5, height+thick, 1);	
		lappy(1,1,0.05,1);
	glPopMatrix();
}

// create chair
void chair(double len, double width, double thick, double height, double legDim) {
	double distLength = len/2 - legDim/2, distWidth = width/2 - legDim/2;
	
	// chair base
	glColor3ub(255, 0, 255);
	glPushMatrix();
		glTranslated(9, height, 3.5);
		cube(len,width,thick);
	glPopMatrix();
	
	// chair leg 1
	glColor3ub(51, 52, 255);
	glPushMatrix();
		glTranslated(9+distLength, 0, 3.5+distWidth);
		cube(legDim,legDim,height);
	glPopMatrix();
	
	// chair leg 2
	glColor3ub(153, 0, 153);
	glPushMatrix();
		glTranslated(9-distLength, 0, 3.5+distWidth);
		cube(legDim,legDim,height);
	glPopMatrix();
	
	// chair leg 3
	glColor3ub(0, 204, 0);
	glPushMatrix();
		glTranslated(9+distLength, 0, 3.5-distWidth);	
		cube(legDim,legDim,height);
	glPopMatrix();
	
	// chair leg 4
	glColor3ub(102, 255, 255);
	glPushMatrix();
		glTranslated(9-distLength, 0, 3.5-distWidth);	
		cube(legDim,legDim,height);
	glPopMatrix();
	
	// chair support
	glColor3ub(255, 255, 51);
	glPushMatrix();
		glTranslated(9, height, 3.5+distWidth);
		cube(len, 0.1, height+len/2);
	glPopMatrix();

}

// create bed
void bed(double len, double width, double thick, double height) {
	glPushMatrix();
		glColor3ub(222,188,133);
		glTranslated(5+len/2, 0.075, 10.5);
		cube(len,width,height);
	glPopMatrix();
	
	// create mattress
	glPushMatrix();
		glColor3ub(218,165,32);
		glTranslated(5+len/2, height + thick/2 - 0.03, 10.5);	
		cube(len,width,thick);
	glPopMatrix();
	
	// bed suupport
	glPushMatrix();
		glColor3ub(222,188,133);
		glTranslated(5+len - 0.05, height + 0.06, 10.5);	
		cube(0.1,3,1);
	glPopMatrix();
}

void floor() {	
		int i=0,k=0;
	for(i=0; i<length; i++) {
		for(k=0; k<width; k++){
			if(((int)(i+k))%2==0)
				glColor3ub(0,0,0);
			else
				glColor3ub(255,255,255);
			glBegin(GL_QUADS);
				glVertex3f(i,0.01,k);
	    		glVertex3f(i+1,0.01,k);
		   		glVertex3f(i+1,0.01,k+1);
	    		glVertex3f(i,0.01,k+1);
			glEnd();
		}
	}
}

void room(){
		glColor3ub(200, 200, 255);
		glTranslated(length/2, height/2 , width/2);	
		glScaled(length+0.1, height+0.1, width+0.1);
		glutSolidCube(fsize);
}

void boundary(){
		glColor3ub(0,0,0);
		glTranslated(length/2, height/2 , width/2);	
		glScaled(length-0.05, height-0.05, width-0.05);
		glutWireCube(fsize);
}

void display() {
	int i,j;
	vect=sqrt(pow(look.x-eye.x,2)+pow(look.y-eye.y,2)+pow(look.z-eye.z,2));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle,1.5,1,100);
	glMatrixMode(GL_MODELVIEW);
	if (flag == -1) {
		eye.x=5.0 ; eye.y=2.0; eye.z=5.0; look.x=0.0; look.y=1.0; look.z=0.0;
		flag=0;
	}
	if(flag!=0) //&& checkin(look.x,look.y,look.z))
	{
		vec = sqrt((look.x-eye.x)*(look.x-eye.x) + (look.z-eye.z)*(look.z-eye.z));
		n.x = eye.x - look.x;
		n.y = eye.y - look.y;
		n.z = eye.z - look.z;
		up.x=0 ;up.y =1; up.z=0;
		u = cross(up, n);
		v = cross(n , u);

		if(flag==1) 	{
				 float id[9]={0};
				float c = cos(.1*180/3.14);
				float s = sin(.1*180/3.14);
				float t = 1-c;
				float vect = sqrt(u.x*u.x+u.y*u.y+u.z*u.z);
				u.x =u.x/vect;
				u.y =u.y/vect;
				u.z =u.z/vect;
				id[0] = (1-c)*u.x*u.x+c;
				id[1] = (1-c)*u.x*u.y-s*u.z;
				id[2] = t*u.x*u.z + s*u.y;
				id[3] = t*u.x*u.y + s*u.z;
				id[4] = t*u.y*u.y + c;
				id[5] = t*u.y*u.z - s*u.x;
				id[6] = t*u.x*u.z - s*u.y;
				id[7] = t*u.y*u.z + s*u.x;
				id[8] = t*u.z*u.z + c;
				temp = n;
				n.x = id[0]*temp.x+id[3]*temp.y+id[6]*temp.z;
				n.y = id[1]*temp.x+id[4]*temp.y+id[7]*temp.z;
				n.z = id[2]*temp.x+id[5]*temp.y+id[8]*temp.z;
				look.x = eye.x - n.x;
				look.y = eye.y - n.y;
				look.z = eye.z - n.z;
				flag =0;

			}
		if(flag==10) {
								 
				float id[9]={0};
				float c = cos(-0.1*180/3.14);
				float s = sin(-0.1*180/3.14);
				float t = 1-c;
				float vect = sqrt(u.x*u.x+u.y*u.y+u.z*u.z);
				u.x =u.x/vect;
				u.y =u.y/vect;
				u.z =u.z/vect;
				id[0] = (1-c)*u.x*u.x+c;
				id[1] = (1-c)*u.x*u.y-s*u.z;
				id[2] = t*u.x*u.z + s*u.y;
				id[3] = t*u.x*u.y + s*u.z;
				id[4] = t*u.y*u.y + c;
				id[5] = t*u.y*u.z - s*u.x;
				id[6] = t*u.x*u.z - s*u.y;
				id[7] = t*u.y*u.z + s*u.x;
				id[8] = t*u.z*u.z + c;
				temp = n;
				n.x = id[0]*temp.x+id[3]*temp.y+id[6]*temp.z;
				n.y = id[1]*temp.x+id[4]*temp.y+id[7]*temp.z;
				n.z = id[2]*temp.x+id[5]*temp.y+id[8]*temp.z;
				look.x = eye.x - n.x;
				look.y = eye.y - n.y;
				look.z = eye.z - n.z;
				flag =0;
				
			}
		if(flag==2)	//Zoom (Translate in line with normal vector)
			{
			eye.x-=(n.x/vect)*0.1;
			eye.y-=(n.y/vect)*0.1;
			eye.z-=(n.z/vect)*0.1;
			flag=0;
			}
		if(flag==3)	//Zoom (Translate back n line with normal vector)
			{
			eye.x+=(n.x/vect)*0.1;
			eye.y+=(n.y/vect)*0.1;
			eye.z+=(n.z/vect)*0.1;
			flag=0;
			}

		if(flag==4)	//Slide the camera
			{
			u = cross(up, n);
			eye.x -= u.x/vec*0.1;
			eye.y -= u.y/vec*0.1;
			eye.z -= u.z/vec*0.1;
			look.x -= u.x/vec*0.1;
			look.y -= u.y/vec*0.1;
			look.z -= u.z/vec*0.1;
			flag=0;	
			}
		if(flag==5)
			{
			u = cross(up, n);
			eye.x += u.x/vec*0.1;
			eye.y += u.y/vec*0.1;
			eye.z += u.z/vec*0.1;
			look.x += u.x/vec*0.1;
			look.y += u.y/vec*0.1;
			look.z += u.z/vec*0.1;
			flag=0;
			}
		if(flag==6)
			{
			vec = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
			u = cross(up, n);
			eye.x+=v.x/vec*0.1;
			eye.y+=v.y/vec*0.1;
			eye.z+=v.z/vec*0.1;
			look.x+=v.x/vec*0.1;
			look.y+=v.y/vec*0.1;
			look.z+=v.z/vec*0.1;
			flag=0;	
			}
		if(flag==7)
			{
			vec = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
			u = cross(up, n);
			eye.x-=v.x/vec*0.1;
			eye.y-=v.y/vec*0.1;
			eye.z-=v.z/vec*0.1;
			look.x-=v.x/vec*0.1;
			look.y-=v.y/vec*0.1;
			look.z-=v.z/vec*0.1;
			flag=0;
			}		
		if(flag==8&&angle>10){                         //zoom in with +
				angle=angle-1;
			}
		if(flag==9&&angle<90) {
				angle=angle+1;     //zoom out with -
			}
		if (flag ==11)
		{	
			vec = sqrt((look.x-eye.x)*(look.x-eye.x) + (look.z-eye.z)*(look.z-eye.z));
			theta+=0.001;
			look.x = vec*cos(theta*180/3.14)+eye.x;
			look.z= -1*vec*sin(theta*180/3.14)+eye.z;
			
		}
		if (flag ==22)
		{
			vec = sqrt((look.x-eye.x)*(look.x-eye.x)+ (look.z-eye.z)*(look.z-eye.z));
			theta-=0.001;
			look.x = vec*cos(theta*180/3.14)+eye.x;
			 look.z= -1*vec*sin(theta*180/3.14)+eye.z;
		}

		flag =0;
	}
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		boundary();
	glPopMatrix();
	glPushMatrix();
		room();
	glPopMatrix();
	glPushMatrix();
		door();
	glPopMatrix();
	glPushMatrix();
		table(5,2,0.1,2,0.1);
	glPopMatrix();
	glPushMatrix();
		chair(1.5,1.5,0.1,1,0.1);
	glPopMatrix();
	glPushMatrix();
		window();	
	glPopMatrix();
	glPushMatrix();
		bed(6,3,0.2,1);
	glPopMatrix();
	glPushMatrix();
		floor();	
	glPopMatrix();
	glFlush();
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	srand(100);
	glutCreateWindow("3D viewing");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(spkeyboard);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	//	init();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glViewport(0, 0, 640, 480);
	  glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}

