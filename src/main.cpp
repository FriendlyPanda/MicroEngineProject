

#include "Graphics/GE.h"
#include "Game/GameConfiguration.h"
#include "Game/GameObject.h"
#include "Game/NodeSystem.h"
#include "Game/GameSprite.h"


int main(int argc, char * args[]) {
    GameNode node1 = GameNode();
    GameSprite sprite1 = GameSprite();
    GameSprite sprite2 = GameSprite();

    NodeSystem ns = NodeSystem();
    ns.add(ns.getHeadNode()->getNodeID(), &node1);
    ns.add(node1.getNodeID(), &sprite1);
    ns.add(ns.getHeadNode()->getNodeID(), &sprite2);
    ns.print();


    GameConfiguration gc;
    gc.clean();
    int gameSpeed = 10;
    gc.set(GAME_SPEED, &gameSpeed);



    GraphicsEngine * ge = new GraphicsEngine(&gc);
    return ge->_execute();

    return 0;
}
