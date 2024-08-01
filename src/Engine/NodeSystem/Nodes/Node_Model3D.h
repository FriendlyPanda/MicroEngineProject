//
// Created by janha on 05/03/2024.
//

#ifndef MEP_NODE_MODEL3D_H
#define MEP_NODE_MODEL3D_H


#include "BaseNode.h"
#include "../../../../default_libs/Model/Model/Model.h"

class Node_Model3D : Node {
private:
    Model * model3D;
public:
    explicit Node_Model3D(unsigned int id);

    void setModel(Model * newModel);
    void draw(Shader * shader);
};


#endif //MEP_NODE_MODEL3D_H
