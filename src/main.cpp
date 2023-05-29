

#include "Game/Graphics/GE.h"
#include "Game/Graphics/GE.cpp"


int main(int argc, char * args[]) {

    GraphicsEngine ge;

    ge._init();
    ge._run();
    ge._close();

    return 0;
}
