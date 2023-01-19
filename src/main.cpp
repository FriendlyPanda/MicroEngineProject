

#include "Graphics/GE.h"
#include "Game/GameConfiguration.h"

int main(int argc, char * args[]) {
    GameConfiguration gc;
    std::string message1 = "Hello";
    std::string message2 = "World";
    int val = 69;
    gc.set("FirstMessage", &message1);
    gc.set("SecondMessage", &message2);
    gc.set("intVal", &val);
    gc.print();

    std::cout <<  *gc.get<std::string>("FirstMessage") << " " <<  *gc.get<std::string>("SecondMessage") << " " << *(gc.get<int>("intVal"))<< std::endl;
    gc.clean();
    //GraphicsEngine ge;
    //ge._close();
    return 0;
    //return ge._execute();;
}
