//
// Created by adamh on 17/01/2023.
//


#include "NodeSprite.h"

/**
 * basic constructor, that sets parameters to default values.
 */
NodeSprite::NodeSprite(){
    gTexture = nullptr;
    frames = new SDL_Rect[1];
    frames[0] = sdlRect(0,0,0,0);
}


/**
 * load texture from path, and create frames for animated sprite.
 * @param path the path to the Texture
 * @param numbOfFrames the total number of the frames.
 * @param numbOfFramesVer number of frames in the vertical orientation
 * @param numbOfFramesHor number of frames in the horizontal orientation.
 * @param frameSize the width (x) and height (y) of a single frame
 * @return the pointer to a texture
 */
SDL_Texture * NodeSprite::loadTexture(const std::string& path, int numbOfFrames, int numbOfFramesVer, int numbOfFramesHor, SDL_Point frameSize) {
    free();

    if(numbOfFrames > (numbOfFramesHor * numbOfFramesVer)){
        printf("Warning, more frames than possible combinations, defoulting to maximum");
        numbOfFrames = (numbOfFramesHor * numbOfFramesVer);
    }

    numberOfFrames = numbOfFrames;

    if(numberOfFrames > 1){
        this->numberOfFrames = numbOfFrames;
        frames = new SDL_Rect[numberOfFrames];

        for(int yy = 0; yy < numbOfFramesVer; yy++){
            for(int xx = 0; xx < numbOfFramesHor; xx++){
                frames[(yy * numbOfFramesHor)+(xx)] = sdlRect(xx * frameSize.x, yy * frameSize.y, frameSize.x, frameSize.y);
                if(((yy * numbOfFramesHor)+(xx)) > numbOfFrames){
                    break;
                }
            }
        }
    }else{
        this->numberOfFrames = 0;
        frames = new SDL_Rect[1];
        frames[0] = sdlRect(0, 0, frameSize.x, frameSize.y);
    }

    GameConfiguration * coolGC = getConfig();
    SDL_Texture * finalTexture = IMG_LoadTexture(coolGC->get<SDL_Renderer>(RENDER), path.c_str());
    if(finalTexture == nullptr){
        printf("ERROR:\t\tCould not create texture.\nSDL_ERROR: %s\n", SDL_GetError());
    }
    gTexture = finalTexture;
    dimentions = getsize(gTexture);

    return finalTexture;
}

/**
 * return the width of the texture
 * @return width of the Texture in pixels
 */
unsigned int NodeSprite::getTextureWidth() const {
    return dimentions.x;
}

/**
 * object destructor
 */
NodeSprite::~NodeSprite() {
    free();
}

/**
 * returns the height of the texture
 * @return unsigned int representing height
 */
unsigned int NodeSprite::getTextureHeight() const {
    return dimentions.y;
}


/**
 * free the resources from the memory
 */
void NodeSprite::free() {
    if(gTexture != nullptr) {
        SDL_DestroyTexture(gTexture);
        gTexture = nullptr;
    }
    delete frames;
}


/**
 * change the frame to the next one, if reached the end, loop back to the first frame
 */
void NodeSprite::nextFrame(){
    frame++;
    if(frame >= numberOfFrames){frame = 0;}
}

/**
 * single frame texture loading
 * @param gTexture
 */
NodeSprite::NodeSprite(SDL_Texture *gTexture) {
    numberOfFrames = 0;
    frame = 0;
    this->gTexture = gTexture;
    dimentions = getsize(gTexture);
    frames = new SDL_Rect[numberOfFrames + 1];
    frames[frame] = sdlRect(0, 0, dimentions.x, dimentions.y);
}

/**
 * returns current frame that is being displayed.
 * @return index of a frame.
 */
unsigned int NodeSprite::getCurrentFrame() const {
    return frame;
}

/**
 * set frame of the animation
 * @param frameIndex set frame index to the new index.
 */
void NodeSprite::setFrame(int frameIndex) {
    frame = frameIndex;
}

/**
 * returns the number of the frames in the animation bank
 * @return number of frames
 */
unsigned int NodeSprite::getNumberOfFrames() const {
    return numberOfFrames;
}

/**
 * get the size of the texture
 * @param texture the texture to measure
 * @return the point dimension of the given texture
 */
SDL_Point NodeSprite::getsize(SDL_Texture *texture) {
    SDL_Point size;
    SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
    return size;
}

/**
 * returns the width of the frame displayed
 * @return the width of the frame
 */
unsigned int NodeSprite::getWidth() {
    return frames[frame].w;
}

/**
 * returns the height of the frame displayed
 * @return the height of the frame
 */
unsigned int NodeSprite::getHeight() {
    return frames[frame].h;
}

/**
 * simple render command
 * @param pos the position at which to render the texture at
 */
void NodeSprite::render(SDL_Rect * pos) {
    SDL_RenderCopy(getConfig()->get<SDL_Renderer>(RENDER),gTexture, &frames[frame],pos);
}
