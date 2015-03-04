#ifndef __renderer_h_
#define __renderer_h_

#include "objparser.h"

class Renderer
{
 public:
  Renderer();
  void render(OBJMesh *mesh);

 private:
  OBJMesh *mMesh;
  std::vector<OBJMeshTriangle> displayList;

  void updateDisplayList();
  void debugDrawTriangles();
};

#endif /* __renderer_h_ */
