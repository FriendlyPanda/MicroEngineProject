//
// Created by adamh on 17/01/2023.
//


#include "GameSprite.h"

/**
 * basic constructor, that sets parameters to default values.
 */
GameSprite::GameSprite(){
    gTexture = nullptr;
    dimentions.x = 1;
    dimentions.y = 1;
    frames = new SDL_Rect[1];
    frames[0] = sdlRect(0,0,0,0);
    spriteAnimationSpeed = 0;
    frameTimer = 0;
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
SDL_Texture * GameSprite::loadTexture(const std::string& path, int numbOfFrames, int numbOfFramesVer, int numbOfFramesHor, SDL_Point frameSize) {
    // the x is the width and y is the height of the point

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
unsigned int GameSprite::getTextureWidth() {
    return dimentions.x;
}

/**
 * object destructor
 */
GameSprite::~GameSprite() {
    free();
}

/**
 * returns the height of the texture
 * @return unsigned int representing height
 */
unsigned int GameSprite::getTextureHeight() {
    return dimentions.y;
}


/**
 * free the resources from the memory
 */
void GameSprite::free() {
    if(gTexture != nullptr) {
        SDL_DestroyTexture(gTexture);
        gTexture = nullptr;
    }
    delete frames;
}

/**
 * simple render
 */
void GameSprite::render() {
    if(numberOfFrames > 0){
        clock_t currentTime = clock();
        if(currentTime > frameTimer){ // this will definitely not come back to bite me later on lol [foreshadowing]
            frameTimer = currentTime + (long)(CLOCKS_PER_SEC / ((*getConfig()->get<float>(GAME_SPEED)) / spriteAnimationSpeed));

            SDL_RenderCopy(getConfig()->get<SDL_Renderer>(RENDER),gTexture,&frames[frame],&frames[frame]);
            frame++;
            if(frame >= numberOfFrames){frame = 0;}
        }
    }else{
        SDL_RenderCopy(getConfig()->get<SDL_Renderer>(RENDER),gTexture, nullptr,&frames[0]);
    }
}

/**
 * single frame texture loading
 * @param gTexture
 */
GameSprite::GameSprite(SDL_Texture *gTexture) {
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
unsigned int GameSprite::getCurrentFrame() const {
    return frame;
}

/**
 * set frame of the animation
 * @param frameIndex set frame index to the new index.
 */
void GameSprite::setFrame(int frameIndex) {
    frame = frameIndex;
}

/**
 * returns the number of the frames in the animation bank
 * @return number of frames
 */
unsigned int GameSprite::getNumberOfFrames() const {
    return numberOfFrames;
}

/**
 * get the size of the texture
 * @param texture the texture to measure
 * @return the point dimension of the given texture
 */
SDL_Point GameSprite::getsize(SDL_Texture *texture) {
    SDL_Point size;
    SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
    return size;
}

/**
 * returns the width of the frame displayed
 * @return the width of the frame
 */
unsigned int GameSprite::getWidth() {
    return frames[frame].w;
}

/**
 * returns the height of the frame displayed
 * @return the height of the frame
 */
unsigned int GameSprite::getHeight() {
    return frames[frame].h;
}

void GameSprite::setSpeed(float speed) {
    spriteAnimationSpeed = speed;
}
