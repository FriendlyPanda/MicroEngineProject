//
// Created by User on 24/01/2023.
//

#ifndef MEP_NODEEMPTY_H
#define MEP_NODEEMPTY_H

#include "../GameConfiguration.h"
#include "../misc/GameMisc.h"
#include <ctime>
#include <vector>

/**
 * GameNodes, the game will be made up out of nodes, each objNode can have a single parent, and multiple children,
 * positionAndDimension can be global (relative to the window) or relative (to the parent)
 */
class NodeEmpty {
protected:
    void * host;
public:
    NodeEmpty();
    GameConfiguration * getConfig();
    void setHost(void * hostNode);
    void * getHost();
    virtual const std::type_info & getType() =0;
    ~NodeEmpty();
};




#endif //MEP_NODEEMPTY_H
