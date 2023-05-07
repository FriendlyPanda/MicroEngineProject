//
// Created by janha on 12/03/2023.
//

#ifndef MEP_NODE_2_H
#define MEP_NODE_2_H

#include <vector>
#include <queue>
#include <string>
#include <sstream>



class Node {
private:
    int id;
    static int nextId;
    std::vector <Node *> children;

public:
    Node() : id(nextId++){}

    explicit Node(int id){
        this->id = id;
    }

    void addChild(Node * child){
        children.push_back(child);
    }

    virtual void update(){
        // default implementation, will do nothing by itself
    }

    std::vector<Node *> getChildren(){
        return children;
    }

    template<class T>
    std::vector<T*> getNodesOfType() {
        std::vector<T*> result;
        if (dynamic_cast<T*>(this) != nullptr) {
            result.push_back(dynamic_cast<T*>(this));
        }
        for (auto child : getChildren()) {
            auto childResult = getNodesOfType<T>(child);
            result.insert(result.end(), childResult.begin(), childResult.end());
        }
        return result;
    }

    int getId() const{
        return id;
    }
};

int Node::nextId = 0;

/*
class SpriteNode : public Node {
private:
    SDL_Texture * texture;
public:
    double x;
    double y;
    double rotation;


    SpriteNode(int id, SDL_Texture * texture, double x, double y, double rotation) : Node(id){
        this->texture = texture;
        this->x = x;
        this->y = y;
        this->rotation = rotation;
    }

    SDL_Texture * getTexture(){
        return texture;
    }

    ~SpriteNode() {
        SDL_DestroyTexture(texture);
    }
};

class AnimationNode : public SpriteNode {
private:
    std::vector<SDL_Rect> frames_;
    int currentFrameIndex_;
    float framesPerSecond_;
    float timeSinceLastFrame_;
    SDL_Renderer* renderer_;
    int frameCount_;

public:
    AnimationNode(int id, SDL_Texture* texture, double x, double y, double rotation, int frameCount, SDL_Rect* frames, SDL_Renderer* renderer) : SpriteNode(id, texture, x, y, rotation) {
        this->frameCount_ = frameCount;
        this->currentFrame = 0;
        this->frames = frames;
        this->renderer = renderer;
    }

    ~AnimationNode() {
        delete[] frames;
    }

    void setFramesPerSecond(float fps){

    }
    void setFrameData(const std::vector<SDL_Rect>& frames);
    const std::vector<SDL_Rect>& getFrameData() const;
    void setCurrentFrameIndex(int index);
    int getCurrentFrameIndex() const;

    void update() override {
        currentFrame = (currentFrame + 1) % frameCount;
        SDL_Rect currentFrameRect = frames[currentFrame];
        SDL_Rect dstRect = { (int)x, (int)y, currentFrameRect.w, currentFrameRect.h };
        SDL_RenderCopyEx(renderer, getTexture(), &currentFrameRect, &dstRect, rotation, nullptr, SDL_FLIP_NONE);
    }
};


class AudioNode : public Node {
private:
    Mix_Chunk* sound;
public:
    AudioNode(int id, Mix_Chunk* sound) : Node(id) {
        this->sound = sound;
    }

    void playSound() {
        Mix_PlayChannel(-1, sound, 0);
    }

    void update() override {}

    ~AudioNode() {
        Mix_FreeChunk(sound);
    }
};

std::string serializeNodes(Node* rootNode) {
    std::stringstream ss;
    std::queue<Node*> nodeQueue;
    nodeQueue.push(rootNode);

    while (!nodeQueue.empty()) {
        Node* currentNode = nodeQueue.front();
        nodeQueue.pop();

        ss << typeid(*currentNode).name() << "," << currentNode->getId() << ";";

        if (typeid(*currentNode) == typeid(SpriteNode)) {
            SpriteNode* spriteNode = dynamic_cast<SpriteNode*>(currentNode);
            ss << spriteNode->x << "," << spriteNode->y << "," << spriteNode->rotation << ";";
        }
        else if (typeid(*currentNode) == typeid(AnimationNode)) {
            AnimationNode* animNode = dynamic_cast<AnimationNode*>(currentNode);
            ss << animNode->getCurrentFrameIndex() << ",";
            for (auto& frame : animNode->getFrameData()) {
                ss << frame.x << "," << frame.y << ",";
            }
            ss << ";";
        }

        for (auto& child : currentNode->getChildren()) {
            nodeQueue.push(child);
        }
    }

    return ss.str();
}
 */



#endif //MEP_NODE_2_H
