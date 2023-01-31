//
// Created by User on 31/01/2023.
//

#ifndef MEP_TEXTUREMANAGER_H
#define MEP_TEXTUREMANAGER_H


#include "../Game/GameSprite.h"

class TextureManager {
private:
    GameSprite * sprites[256];
public:
    TextureManager();
    GameSprite getSprite(int index);
    void drawSprite();
};


#endif //MEP_TEXTUREMANAGER_H
