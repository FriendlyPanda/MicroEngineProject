

//#include "Game/Nodes/NodeSystem.h"
//#include "Game/Graphics/GE.h"
#include <iostream>
#include "Game/graph/GX.h"
//#include "Game/Graphics/GE.cpp"


int main(int argc, char * args[]) {
    GX gx;
    gx = GX();
    std::cout << (gx.get_start_val()) << std::endl;
    /*
    GameConfiguration gc;
    gc.clean();
    int gameSpeed = 30;
    gc.set(GAME_SPEED, &gameSpeed);


    auto * ge = new GraphicsEngine(&gc);
    ge->_init();


    NodeSystem ns = NodeSystem();
    ge->setNodeSystem(&ns);

    ge->_execute();


    // clear everything and quit
    delete ge;
    gc.~GameConfiguration();
    ns.~NodeSystem();
     */

    return 0;
}
