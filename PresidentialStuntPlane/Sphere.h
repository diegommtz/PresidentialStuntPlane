#pragma once
#include <Windows.h> //Comment this line if linux
#include <GL/gl.h>
#include <glut.h> // Use "glut.h" if local 
#include <cmath>
#include <math.h>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include<iostream>
using namespace std;

//##########3####PARA LA ESFERA#################
bool relojFlag = false;

int reloj = 0;

struct Vertex
{
    float x, y, z;
};

struct Faces
{
    int a, b, c, d;
};

Vertex vertices[8];
Faces faces[6];
Vertex normals[8];
Vertex centro;
Vertex offset;

GLfloat s[4], t[4];

int depth = 2;
float radio;

float myPos[3];

void Normalize(Vertex* vectorIn)
{
    GLfloat xsq = (vectorIn[0].x) * (vectorIn[0].x);
    GLfloat ysq = (vectorIn[0].y) * (vectorIn[0].y);
    GLfloat zsq = (vectorIn[0].z) * (vectorIn[0].z);
    GLfloat mag = sqrt(xsq + ysq + zsq);

    vectorIn[0].x /= mag;
    vectorIn[0].y /= mag;
    vectorIn[0].z /= mag;
}

class Sphere
{

private:

public:
    Sphere();
    ~Sphere();
    void setCube();
    void sphereEnergy(float,float,float);

    bool collision(float*);

    float* getPos();
};

Sphere::Sphere() {
    radio = sqrt(0.25 + 0.25 + 0.25);
    // Texture coords
   /* GLfloat s[4], t[4];*/

    s[0] = 0.0f;
    t[0] = 0.0f;

    s[1] = 1.0f;
    t[1] = 0.0f;

    s[2] = 1.0f;
    t[2] = 1.0f;

    s[3] = 0.0f;
    t[3] = 1.0f;
    srand(time(NULL));

}
Sphere::~Sphere() {}

void Sphere::setCube()
{
        vertices[0].x = 0.0f;
        vertices[0].y = 0.0f;
        vertices[0].z = 0.0f;

        vertices[1].x = 1.0f;
        vertices[1].y = 0.0f;
        vertices[1].z = 0.0f;

        vertices[2].x = 1.0f;
        vertices[2].y = 1.0f;
        vertices[2].z = 0.0f;

        vertices[3].x = 0.0f;
        vertices[3].y = 1.0f;
        vertices[3].z = 0.0f;

        vertices[4].x = 0.0f;
        vertices[4].y = 0.0f;
        vertices[4].z = 1.0f;

        vertices[5].x = 1.0f;
        vertices[5].y = 0.0f;
        vertices[5].z = 1.0f;

        vertices[6].x = 1.0f;
        vertices[6].y = 1.0f;
        vertices[6].z = 1.0f;

        vertices[7].x = 0.0;
        vertices[7].y = 1.0;
        vertices[7].z = 1.0;

        offset.x = -0.5f;
        offset.y = -0.5f;
        offset.z = -0.5f;

        for (int i = 0; i < 8; i++)
        {
            vertices[i].x += offset.x;
            vertices[i].y += offset.y;
            vertices[i].z += offset.z;
        }

        centro.x = 0.0f;
        centro.y = 0.0f;
        centro.z = 0.0f;

        for (int i = 0; i < 8; i++)
        {
            normals[i].x = vertices[i].x - centro.x;
            normals[i].y = vertices[i].y - centro.y;
            normals[i].z = vertices[i].z - centro.z;

            Normalize(&normals[i]);
        }

        faces[0].a = 3;
        faces[0].b = 2;
        faces[0].c = 1;
        faces[0].d = 0;

        faces[1].a = 6;
        faces[1].b = 5;
        faces[1].c = 1;
        faces[1].d = 2;

        faces[2].a = 2;
        faces[2].b = 3;
        faces[2].c = 7;
        faces[2].d = 6;

        faces[3].a = 7;
        faces[3].b = 3;
        faces[3].c = 0;
        faces[3].d = 4;

        faces[4].a = 4;
        faces[4].b = 5;
        faces[4].c = 6;
        faces[4].d = 7;

        faces[5].a = 0;
        faces[5].b = 1;
        faces[5].c = 5;
        faces[5].d = 4;

}
//
//void Timer(int value) {
//    //respawnFlag = !respawnFlag;
//
//    /* initialize random seed: */
//    srand(time(NULL));
//    rp1 = (float)(1 + rand() % 100) / 10;         // rp1 in the range 0.0 to 5.0
//    rp2 = (float)(1 + rand() % 100) / 10;         // rp2 in the range 0.0 to 5.0
//    rp3 = (float)(1 + rand() % 100) / 10;         // rp3 in the range 0.0 to 5.0
//    glutPostRedisplay();
//    // 100 milliseconds
//    glutTimerFunc(7000, Timer, 0);
//}


void subdivide(Vertex v0, Vertex v1, Vertex v2, Vertex v3, Vertex n0, Vertex n1, Vertex n2, Vertex n3, GLfloat* s, GLfloat* t, int depth)
{
    if (depth == 0)
    {
        glBegin(GL_QUADS);

        glTexCoord2f(s[0], t[0]);
        glNormal3f(n0.x, n0.y, n0.z);
        glVertex3f(v0.x, v0.y, v0.z);

        glTexCoord2f(s[1], t[1]);
        glNormal3f(n1.x, n1.y, n1.z);
        glVertex3f(v1.x, v1.y, v1.z);

        glTexCoord2f(s[2], t[2]);
        glNormal3f(n2.x, n2.y, n2.z);
        glVertex3f(v2.x, v2.y, v2.z);

        glTexCoord2f(s[3], t[3]);
        glNormal3f(n3.x, n3.y, n3.z);
        glVertex3f(v3.x, v3.y, v3.z);

        glEnd();
    }
    else
    {
        // Calculate NEW POINTS
        Vertex v01, v12, v23, v30, vc;
        Vertex n01, n12, n23, n30, nc;

        //// Parametric Representation of a line
        //v01.x = v0.x + 0.5 * (v1.x - v0.x) + (float)(rand()%100)/1000.0;
        //v01.y = v0.y + 0.5 * (v1.y - v0.y)+ (float)(rand()%100)/1000.0;;
        //v01.z = v0.z + 0.5 * (v1.z - v0.z)+ (float)(rand()%100)/1000.0;;

        //v12.x = v1.x + 0.5 * (v2.x - v1.x)+ (float)(rand()%100)/1000.0;
        //v12.y = v1.y + 0.5 * (v2.y - v1.y)+ (float)(rand()%100)/1000.0;
        //v12.z = v1.z + 0.5 * (v2.z - v1.z)+ (float)(rand()%100)/1000.0;

        //v23.x = v2.x + 0.5 * (v3.x - v2.x)+ (float)(rand()%100)/1000.0;
        //v23.y = v2.y + 0.5 * (v3.y - v2.y)+ (float)(rand()%100)/1000.0;
        //v23.z = v2.z + 0.5 * (v3.z - v2.z)+ (float)(rand()%100)/1000.0;

        //v30.x = v3.x + 0.5 * (v0.x - v3.x)+ (float)(rand()%100)/1000.0;
        //v30.y = v3.y + 0.5 * (v0.y - v3.y)+ (float)(rand()%100)/1000.0;
        //v30.z = v3.z + 0.5 * (v0.z - v3.z)+ (float)(rand()%100)/1000.0;

        //vc.x = v30.x + 0.5 * (v12.x - v30.x)+ (float)(rand()%100)/1000.0;
        //vc.y = v30.y + 0.5 * (v12.y - v30.y)+ (float)(rand()%100)/1000.0;
        //vc.z = v30.z + 0.5 * (v12.z - v30.z)+ (float)(rand()%100)/1000.0;

        // Calculate NEW NORMALS
        n01.x = (n0.x + n1.x) / 2.0;
        n01.y = (n0.y + n1.y) / 2.0;
        n01.z = (n0.z + n1.z) / 2.0;

        Normalize(&n01);

        n12.x = (n1.x + n2.x) / 2.0;
        n12.y = (n1.y + n2.y) / 2.0;
        n12.z = (n1.z + n2.z) / 2.0;

        Normalize(&n12);

        n23.x = (n2.x + n3.x) / 2.0;
        n23.y = (n2.y + n3.y) / 2.0;
        n23.z = (n2.z + n3.z) / 2.0;

        Normalize(&n23);

        n30.x = (n3.x + n0.x) / 2.0;
        n30.y = (n3.y + n0.y) / 2.0;
        n30.z = (n3.z + n0.z) / 2.0;

        Normalize(&n30);

        nc.x = (n30.x + n12.x) / 2.0;
        nc.y = (n30.y + n12.y) / 2.0;
        nc.z = (n30.z + n12.z) / 2.0;

        Normalize(&nc);


        // Calculate POINTS
        v01.x = centro.x + n01.x * radio;// + (float)(rand()%50)/1000.0;;
        v01.y = centro.y + n01.y * radio;//+ (float)(rand()%50)/1000.0;;
        v01.z = centro.z + n01.z * radio;//+ (float)(rand()%50)/1000.0;

        v12.x = centro.x + n12.x * radio;//+ (float)(rand()%50)/1000.0;
        v12.y = centro.y + n12.y * radio;//+ (float)(rand()%50)/1000.0;
        v12.z = centro.z + n12.z * radio;//+ (float)(rand()%50)/1000.0;

        v23.x = centro.x + n23.x * radio;//+ (float)(rand()%50)/1000.0;
        v23.y = centro.y + n23.y * radio;//+ (float)(rand()%50)/1000.0;
        v23.z = centro.z + n23.z * radio;//+ (float)(rand()%50)/1000.0;

        v30.x = centro.x + n30.x * radio;//+ (float)(rand()%50)/1000.0;
        v30.y = centro.y + n30.y * radio;//+ (float)(rand()%50)/1000.0;
        v30.z = centro.z + n30.z * radio;//+ (float)(rand()%50)/1000.0;

        vc.x = centro.x + nc.x * radio;//+ (float)(rand()%50)/1000.0;
        vc.y = centro.y + nc.y * radio;//+ (float)(rand()%50)/1000.0;
        vc.z = centro.z + nc.z * radio;//+ (float)(rand()%50)/1000.0;

        // New Texture Coords
        GLfloat s01, s12, s23, s30, t01, t12, t23, t30, sc, tc;
        GLfloat s1[4], t1[4];
        GLfloat s2[4], t2[4];
        GLfloat s3[4], t3[4];
        GLfloat s4[4], t4[4];

        s01 = s[0] + (s[1] - s[0]) * 0.5f;
        s12 = s[1] + (s[2] - s[1]) * 0.5f;
        s23 = s[2] + (s[3] - s[2]) * 0.5f;
        s30 = s[3] + (s[0] - s[3]) * 0.5f;
        sc = s30 + (s12 - s30) * 0.5f;

        t01 = t[0] + (t[1] - t[0]) * 0.5f;
        t12 = t[1] + (t[2] - t[1]) * 0.5f;
        t23 = t[2] + (t[3] - t[2]) * 0.5f;
        t30 = t[3] + (t[0] - t[3]) * 0.5f;
        tc = t30 + (t12 - t30) * 0.5f;

        // first subdivsion call
        s1[0] = s[0];
        s1[1] = s01;
        s1[2] = sc;
        s1[3] = s30;

        t1[0] = t[0];
        t1[1] = t01;
        t1[2] = tc;
        t1[3] = t30;

        // second subdivsion call
        s2[0] = s01;
        s2[1] = s[1];
        s2[2] = s12;
        s2[3] = sc;

        t2[0] = t01;
        t2[1] = t[1];
        t2[2] = t12;
        t2[3] = tc;

        // Third subdivison call
        s3[0] = sc;
        s3[1] = s12;
        s3[2] = s[2];
        s3[3] = s23;

        t3[0] = tc;
        t3[1] = t12;
        t3[2] = t[2];
        t3[3] = t23;

        // fourth Subdivison call
        s4[0] = s30;
        s4[1] = sc;
        s4[2] = s23;
        s4[3] = s[3];

        t4[0] = t30;
        t4[1] = tc;
        t4[2] = t23;
        t4[3] = t[3];

        // Recursive call to subdivide
        // depth -= 1
        subdivide(v0, v01, vc, v30, n0, n01, nc, n30, &s1[0], &t1[0], depth - 1);
        subdivide(v01, v1, v12, vc, n01, n1, n12, nc, &s2[0], &t2[0], depth - 1);
        subdivide(vc, v12, v2, v23, nc, n12, n2, n23, &s3[0], &t3[0], depth - 1);
        subdivide(v30, vc, v23, v3, n30, nc, n23, n3, &s4[0], &t4[0], depth - 1);
    }

}

void subdivide(Vertex v0, Vertex v1, Vertex v2, Vertex v3, Vertex n0, Vertex n1, Vertex n2, Vertex n3, int depth)
{
    if (depth == 0)
    {
        glBegin(GL_QUADS);

        glNormal3f(n0.x, n0.y, n0.z);
        glVertex3f(v0.x, v0.y, v0.z);

        glNormal3f(n1.x, n1.y, n1.z);
        glVertex3f(v1.x, v1.y, v1.z);

        glNormal3f(n2.x, n2.y, n2.z);
        glVertex3f(v2.x, v2.y, v2.z);

        glNormal3f(n3.x, n3.y, n3.z);
        glVertex3f(v3.x, v3.y, v3.z);

        glEnd();
    }
    else
    {
        // Calculate NEW POINTS
        Vertex v01, v12, v23, v30, vc;
        Vertex n01, n12, n23, n30, nc;

        //// Parametric Representation of a line
        //v01.x = v0.x + 0.5 * (v1.x - v0.x) + (float)(rand()%100)/1000.0;
        //v01.y = v0.y + 0.5 * (v1.y - v0.y)+ (float)(rand()%100)/1000.0;;
        //v01.z = v0.z + 0.5 * (v1.z - v0.z)+ (float)(rand()%100)/1000.0;;

        //v12.x = v1.x + 0.5 * (v2.x - v1.x)+ (float)(rand()%100)/1000.0;
        //v12.y = v1.y + 0.5 * (v2.y - v1.y)+ (float)(rand()%100)/1000.0;
        //v12.z = v1.z + 0.5 * (v2.z - v1.z)+ (float)(rand()%100)/1000.0;

        //v23.x = v2.x + 0.5 * (v3.x - v2.x)+ (float)(rand()%100)/1000.0;
        //v23.y = v2.y + 0.5 * (v3.y - v2.y)+ (float)(rand()%100)/1000.0;
        //v23.z = v2.z + 0.5 * (v3.z - v2.z)+ (float)(rand()%100)/1000.0;

        //v30.x = v3.x + 0.5 * (v0.x - v3.x)+ (float)(rand()%100)/1000.0;
        //v30.y = v3.y + 0.5 * (v0.y - v3.y)+ (float)(rand()%100)/1000.0;
        //v30.z = v3.z + 0.5 * (v0.z - v3.z)+ (float)(rand()%100)/1000.0;

        //vc.x = v30.x + 0.5 * (v12.x - v30.x)+ (float)(rand()%100)/1000.0;
        //vc.y = v30.y + 0.5 * (v12.y - v30.y)+ (float)(rand()%100)/1000.0;
        //vc.z = v30.z + 0.5 * (v12.z - v30.z)+ (float)(rand()%100)/1000.0;

        // Calculate NEW NORMALS
        n01.x = (n0.x + n1.x) / 2.0;
        n01.y = (n0.y + n1.y) / 2.0;
        n01.z = (n0.z + n1.z) / 2.0;

        Normalize(&n01);

        n12.x = (n1.x + n2.x) / 2.0;
        n12.y = (n1.y + n2.y) / 2.0;
        n12.z = (n1.z + n2.z) / 2.0;

        Normalize(&n12);

        n23.x = (n2.x + n3.x) / 2.0;
        n23.y = (n2.y + n3.y) / 2.0;
        n23.z = (n2.z + n3.z) / 2.0;

        Normalize(&n23);

        n30.x = (n3.x + n0.x) / 2.0;
        n30.y = (n3.y + n0.y) / 2.0;
        n30.z = (n3.z + n0.z) / 2.0;

        Normalize(&n30);

        nc.x = (n30.x + n12.x) / 2.0;
        nc.y = (n30.y + n12.y) / 2.0;
        nc.z = (n30.z + n12.z) / 2.0;

        Normalize(&nc);


        // Calculate POINTS
        v01.x = centro.x + n01.x * radio;// + (float)(rand()%50)/1000.0;;
        v01.y = centro.y + n01.y * radio;//+ (float)(rand()%50)/1000.0;;
        v01.z = centro.z + n01.z * radio;//+ (float)(rand()%50)/1000.0;

        v12.x = centro.x + n12.x * radio;//+ (float)(rand()%50)/1000.0;
        v12.y = centro.y + n12.y * radio;//+ (float)(rand()%50)/1000.0;
        v12.z = centro.z + n12.z * radio;//+ (float)(rand()%50)/1000.0;

        v23.x = centro.x + n23.x * radio;//+ (float)(rand()%50)/1000.0;
        v23.y = centro.y + n23.y * radio;//+ (float)(rand()%50)/1000.0;
        v23.z = centro.z + n23.z * radio;//+ (float)(rand()%50)/1000.0;

        v30.x = centro.x + n30.x * radio;//+ (float)(rand()%50)/1000.0;
        v30.y = centro.y + n30.y * radio;//+ (float)(rand()%50)/1000.0;
        v30.z = centro.z + n30.z * radio;//+ (float)(rand()%50)/1000.0;

        vc.x = centro.x + nc.x * radio;//+ (float)(rand()%50)/1000.0;
        vc.y = centro.y + nc.y * radio;//+ (float)(rand()%50)/1000.0;
        vc.z = centro.z + nc.z * radio;//+ (float)(rand()%50)/1000.0;


        // Recursive call to subdivide
        // depth -= 1
        subdivide(v0, v01, vc, v30, n0, n01, nc, n30, depth - 1);
        subdivide(v01, v1, v12, vc, n01, n1, n12, nc, depth - 1);
        subdivide(vc, v12, v2, v23, nc, n12, n2, n23, depth - 1);
        subdivide(v30, vc, v23, v3, n30, nc, n23, n3, depth - 1);
    }

}

void Sphere::sphereEnergy(float rp1, float rp2, float rp3 ) {

    myPos[0] = rp1;
    myPos[1] = rp2;
    myPos[2] = rp3;
    //radio = sqrt(0.25 + 0.25 + 0.25);
    //// Texture coords
    //GLfloat s[4], t[4];

    //s[0] = 0.0f;
    //t[0] = 0.0f;

    //s[1] = 1.0f;
    //t[1] = 0.0f;

    //s[2] = 1.0f;
    //t[2] = 1.0f;

    //s[3] = 0.0f;
    //t[3] = 1.0f;
    
    //if (reloj >= 5000) {
    //    //srand(time(NULL));
    //    rp1 = (float)(1 + rand() % 100) / 10;         // rp1 in the range 0.0 to 5.0
    //    rp2 = (float)(1 + rand() % 100) / 10;         // rp2 in the range 0.0 to 5.0
    //    rp3 = (float)(1 + rand() % 100) / 10;         // rp3 in the range 0.0 to 5.0
    //    relojFlag = !relojFlag;
    //    reloj = 0;
    //}
    //reloj++;
    
    int i = 0;
    // Define material properties
    GLfloat mat_spec[] = { 3000.0, 3000.0, 3000.0, 3000.0 };
    GLfloat mat_shiny[] = { 100.0 };
    GLfloat mat_surf[] = { 1.0, 1.0, 0.0, 0.0 };
    glPushMatrix();
    glTranslated(rp1, rp2, rp3);

    for (int i = 0; i < 6; i++) {
        //SetMaterials(&mat_surf[0], &mat_spec[0], &mat_shiny[0]);
        //subdivide(vertices[faces[i].a], vertices[faces[i].b], vertices[faces[i].c], vertices[faces[i].d], normals[faces[i].a], normals[faces[i].b], normals[faces[i].c], normals[faces[i].d], depth);

        //SetMaterials(&mat_surf[0], &mat_spec[0], &mat_shiny[0]);
        ////subdivide( vertices[ faces[i].a ],  vertices[ faces[i].b ],  vertices[ faces[i].c ],  vertices[ faces[i].d ], normals[ faces[i].a ], normals[ faces[i].b ], normals[ faces[i].c ], normals[ faces[i].d ], depth);
        subdivide(vertices[faces[i].a], vertices[faces[i].b], vertices[faces[i].c], vertices[faces[i].d], normals[faces[i].a], normals[faces[i].b], normals[faces[i].c], normals[faces[i].d], &s[0], &t[0], depth);
    }
    glPopMatrix();


}


float* Sphere::getPos() {

    return myPos;
}

bool Sphere::collision(float* otherPos) {
    
    return true;
}