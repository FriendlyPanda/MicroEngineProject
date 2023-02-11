

#include "Graphics/GE.h"
#include "Game/GameConfiguration.h"
#include "Game/NodeSystem.h"
#include "Game/GameSprite.h"


int main(int argc, char * args[]) {
    GameNode * node1 = new GameNode();
    GameSprite * sprite1 = new GameSprite();
    GameSprite * sprite2 = new GameSprite();

    NodeSystem ns = NodeSystem();
    ns.add(ns.getHeadNode()->getNodeID(), node1);
    ns.add(node1->getNodeID(), sprite1);
    ns.add(node1->getNodeID(), sprite2);
    ns.print();


    GameConfiguration gc;
    gc.clean();
    int gameSpeed = 1;
    gc.set(GAME_SPEED, &gameSpeed);



    GraphicsEngine * ge = new GraphicsEngine(&gc);
    return ge->_execute();
}
