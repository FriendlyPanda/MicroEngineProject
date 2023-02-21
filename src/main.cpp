
#include "Game/Graphics/GE.h"
#include "Game/GameConfiguration.h"
#include "Game/Nodes/NodeSystem.h"
#include "Game/Nodes/NodeSprite.h"


int main(int argc, char * args[]) {
    GameConfiguration gc;
    gc.clean();
    int gameSpeed = 30;
    gc.set(GAME_SPEED, &gameSpeed);

    GraphicsEngine * ge = new GraphicsEngine(&gc);
    ge->_init();

    NodeSprite * sprite1 = new NodeSprite();
    NodeSprite * sprite2 = new NodeSprite();


    NodeSystem ns = NodeSystem();
    ge->setNodeSystem(&ns);
    ns.getHeadNode()->setConfig(&gc);
    ns.add(ns.getHeadNode()->getName(), nullptr, "test1");
    ns.add("test1", sprite1, "sprite1");
    ns.add("test1", sprite2, "sprite2");

    sprite1->loadTexture("Assets/Err.png",4,2,2, sdlPoint(32,32));
    sprite2->loadTexture("Assets/Hello.bmp",10,2,5, sdlPoint(32,32));

    std::vector<NodeSprite *> spriteList;
    ns.getNodesOfType(&spriteList);

    if(spriteList.empty()){
        printf("No sprites found!\n");
    }else{
        printf("Sprites Found!\n");
        for(NodeSprite * i: spriteList){
            printf("Node: %s\n\t%d x %d\n", ((Node*)i->getHost())->getName().c_str(), i->getWidth(), i->getHeight());
        }
    }





    return ge->_execute();

    return 0;
}
