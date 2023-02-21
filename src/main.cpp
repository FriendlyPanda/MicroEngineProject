
#include "Game/Graphics/GE.h"
#include "Game/GameConfiguration.h"
#include "Game/Nodes/NodeSystem.h"
#include "Game/Nodes/NodeSprite.h"


int main(int argc, char * args[]) {
    NodeSprite * sprite1 = new NodeSprite();
    NodeSprite * sprite2 = new NodeSprite();

    NodeSystem ns = NodeSystem();
    ns.add(ns.getHeadNode()->getName(), nullptr, "test1");
    ns.add("test1", sprite1, "sprite1");
    ns.add("test1", sprite2, "sprite2");
    ns.print();

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

    GameConfiguration gc;
    gc.clean();
    int gameSpeed = 1;
    gc.set(GAME_SPEED, &gameSpeed);


    GraphicsEngine * ge = new GraphicsEngine(&gc);
    return ge->_execute();

    return 0;
}
