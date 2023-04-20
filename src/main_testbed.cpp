//
// Created by User on 08/03/2023.
#include <dirent.h>
#include "Game/Graphics_V2/GraphicalEngine.h"

std::string current_working_directory()
{
    char* cwd = _getcwd( nullptr, 0 ) ; // **** microsoft specific ****
    string working_directory(cwd) ;
    free(cwd) ;
    return working_directory ;
}

int main(int argc, char * args[]){
    MessageBoard messages(current_working_directory() + R"(\assets\properties\messages_en.properties)");

    GraphicalEngine graphics{};
    try {
        graphics.setMessageBoard(&messages);
        graphics.run();
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }



    cout << messages.get("test_bed.hello", {"World"}) << endl;
    cout << messages.get("test_bed.hello") << endl;
    cout << messages.get("missing.message") << endl;

    cout << current_working_directory() << endl;
}