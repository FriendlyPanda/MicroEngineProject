//
// Created by janha on 01/05/2024.
//

#ifndef MEP_NODE_MESH_H
#define MEP_NODE_MESH_H


#include "BaseNode.h"
#include "../../../../default_libs/Model/Mesh/Mesh.h"

class Node_Mesh : public Node{
private:
    Mesh * mesh3D;
public:
    explicit Node_Mesh(unsigned int id);

    void setMesh3D(Mesh *mesh3D);

    void draw(Shader * shader);
};


#endif //MEP_NODE_MESH_H
