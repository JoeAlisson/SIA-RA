#include "renderer.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <GL/glut.h>

using namespace std;


Renderer::Renderer()
{
  mMesh = NULL;

}

void Renderer::render(OBJMesh *mesh)
{
  mMesh = mesh;
  //update display list from the mesh
  updateDisplayList();
  debugDrawTriangles();
}

void Renderer::updateDisplayList()
{
  //fetch updated list from the mesh
  displayList = mMesh->getTriangles();
  //sort
  std::sort(displayList.begin(), displayList.end());
}

void Renderer::debugDrawTriangles()
{
  std::vector<OBJMeshTriangle>::iterator i;
  for (i = displayList.begin(); i != displayList.end(); ++i)
  {
    glBegin(GL_TRIANGLES);
    glColor3f(abs((*i).n1.k),0.5,0.5);
    glVertex3f((*i).v1.x, (*i).v1.y, (*i).v1.z);
    glColor3f(abs((*i).n2.k),0.5,0.5);
    glVertex3f((*i).v2.x, (*i).v2.y, (*i).v2.z);
    glColor3f(abs((*i).n3.k),0.5,0.5);
    glVertex3f((*i).v3.x, (*i).v3.y, (*i).v3.z);
    glEnd();
  }
}


