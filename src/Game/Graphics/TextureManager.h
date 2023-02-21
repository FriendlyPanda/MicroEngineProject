//
// Created by User on 31/01/2023.
//

#ifndef MEP_TEXTUREMANAGER_H
#define MEP_TEXTUREMANAGER_H


#include "../Nodes/NodeSprite.h"

class TextureManager {
private:
    NodeSprite * sprites[256];
public:
    TextureManager();
    NodeSprite getSprite(int index);
    void drawSprite();
};


#endif //MEP_TEXTUREMANAGER_H
