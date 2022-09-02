#include <stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

#include <GL/freeglut.h>



typedef struct
{
    float cordX1 = 0;
    float cordX2 = 0;
    float cordY = 0;
    float cor = 255;
    int abatido = 0;
} aliens;

typedef struct
{
    float cordX1 = 0;
    float cordX2 = 0;
    float cordY = 0;
    float cor = 255;
    int abatido = 0;
} plantas;

aliens listas[18];
plantas listas1[18];

GLfloat escala = 1;
GLfloat lado = 0;
GLfloat altura = 0;
GLfloat graus = 0;
GLfloat trajetoriaY = 0;
GLfloat trajetoriaX = 0;
GLfloat cor = 0;
GLfloat contador = 0;

int controle = 0;
int controle2 = 0;

GLfloat corInimigo = 255;

void desenha();
void listeningKey (unsigned char tecla, GLint x, GLint y);
void disparo();
void nave();
void inimigos();
void amigos();
void cadastrarAliens();
void cadastrarPlantas();

int main(int argc, char* argv[])
{

    cadastrarAliens();
    cadastrarPlantas();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1600,900);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Ola Glut");
    glutKeyboardFunc(listeningKey);
    glutDisplayFunc(desenha);
    glClearColor(0,0,0,0);

    glutMainLoop();



    return 0;
}


void desenha()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-15,15,-15,15);

    //glTranslatef(lado, altura, 0);
    glScalef(escala, escala,0);
    //glRotatef(graus,lado,altura,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    disparo();
    nave();
    inimigos();
    amigos();


    if(contador==18)
    {
        printf("VC GANHOU");
        contador++;
    }
}

void listeningKey (unsigned char tecla, GLint x, GLint y)
{
    int i;
    if(escala>0)
    {
    switch(tecla)
    {
        case '-': escala--;
        break;
        case '+': escala++;
        break;
        case 'a':
            if(lado>-10)
            {
                lado-=0.7;
            }
        break;
        case 'd':
            if(lado<10)
            {
                lado+=0.7;
            }

        break;

        case 32:
        cor=255;
        while(trajetoriaY<=20 && controle2==0)
        {
            trajetoriaY+=0.3;
            controle=1;
            Sleep(5);
            desenha();

            for(i=0;i<18;i++)
            {
                if(trajetoriaY>=listas[i].cordY && lado > listas[i].cordX1 && lado < listas[i].cordX2 && listas[i].abatido == 0)
                {
                listas[i].abatido = 1;
                listas[i].cor = 0;
                cor=0;
                controle2=1;
                contador++;
                break;
                }
            }
        }
        trajetoriaY=0;
        controle=0;
        controle2=0;
        break;

    }
    }

    if(escala == 0)
        escala++;
    if(escala==9)
        escala=1;
    desenha();
}


void disparo()
{
    glBegin(GL_TRIANGLES);
    glColor3d(cor,0,0);
    glVertex2d(-0.1+lado,(-4+trajetoriaY));  // DISPARO
    glVertex2d(0.1+lado,(-4+trajetoriaY));
    glVertex2d(0+lado,(-3.7+trajetoriaY));
    glEnd();
    glFlush();
}

void nave()
{
    glBegin(GL_TRIANGLES);
    glColor3d(211,211,211);
    glVertex2d(-0.8+lado,-6);
    glVertex2d(0+lado,-6);
    glColor3d(211,211,211);
    glVertex2d(-0.4+lado,-5);

    glColor3d(211,211,211);
    glVertex2d(0+lado,-6);
    glVertex2d(0.8+lado,-6);
    glColor3d(211,211,211);
    glVertex2d(0.4+lado,-5);

    glColor3d(211,211,211);
    glVertex2d(-0.4+lado,-5);
    glVertex2d(0.4+lado,-5);
    glColor3d(211,211,211);
    glVertex2d(0+lado,-6);


    glColor3d(211,211,211);
    glVertex2d(-0.2+lado,-5);
    glVertex2d(0.2+lado,-5);
    glColor3d(211,211,211);
    glVertex2d(0+lado,-4);


    glColor3d(211,211,211);
    glVertex2d(-0.2+lado,-6.5);
    glVertex2d(0.2+lado,-6.5);
    glColor3d(211,211,211);
    glVertex2d(0+lado,-5);
    glEnd();
    glFlush();



}

void inimigos()
{
    int i;
    glBegin(GL_TRIANGLES);
    for(i=0;i<18;i++)
    {
    glColor3d(0,0,listas[i].cor);
    glVertex2d(listas[i].cordX1,listas[i].cordY-3);
    glVertex2d(listas[i].cordX2,listas[i].cordY-3);
    glVertex2d(((listas[i].cordX1+listas[i].cordX2)/2),listas[i].cordY-3.5);
    }
    glEnd();
    glFlush();
}

void amigos()
{
    int i;
    glBegin(GL_TRIANGLES);
    for(i=0;i<18;i++)
    {
    glColor3d(0,listas1[i].cor,0);
    glVertex2d(listas1[i].cordX1,listas1[i].cordY-3);
    glVertex2d(listas1[i].cordX2,listas1[i].cordY-3);
    glVertex2d(((listas1[i].cordX1+listas1[i].cordX2)/2),listas1[i].cordY-2.9);
    }
    glEnd();
    glFlush();
}

void cadastrarAliens()
{
    int i; int cord1=0, cord2=0;

    for(i=0;i<18;i++)
    {
    cord1 += 2;
    if(i<9)
    {
    listas[i].cordX1 = -10.5+cord1;
    listas[i].cordX2 = -9.5+cord1;
    listas[i].cordY = 14;
    }
    else
    {
    cord2 += 2;
    listas[i].cordX1 = -10.5+cord2;
    listas[i].cordX2 = -9.5+cord2;
    listas[i].cordY = 11;
    }

    }
}


void cadastrarPlantas()
{
    int i; int cord1=0, cord2=0;

    for(i=0;i<18;i++)
    {
    cord1 += 2;
    if(i<9)
    {
    listas1[i].cordX1 = -10.5+cord1;
    listas1[i].cordX2 = -9.5+cord1;
    listas1[i].cordY = -6;
    }
    else
    {
    cord2 += 2;
    listas1[i].cordX1 = -10.5+cord2;
    listas1[i].cordX2 = -9.5+cord2;
    listas1[i].cordY = -9;
    }

    }
}



