//
// Created by janha on 14/03/2024.
// Documentation Generated by Jetbrains AI
//

#ifndef MEP_TEXTURE_H
#define MEP_TEXTURE_H


#include "GL/glew.h"

class Texture {
public:
    GLuint ID;

    /**
     * @brief The Texture class represents a texture object.
     *
     * This class provides functions to create, bind, unbind, resize, and clear a texture object.
     */
    Texture();

    /**
     * @brief Create a texture with the specified width and height.
     *
     * This function generates a texture object using glGenTextures() and resizes
     * the texture using the provided width and height parameters. The texture ID
     * is stored in the 'ID' member variable of the Texture struct.
     *
     * @param width The width of the texture.
     * @param height The height of the texture.
     */
    void texture_create(GLsizei width, GLsizei height);
    /**
         * @brief Binds the texture to the current context.
         *
         * This function binds the texture identified by `ID` to the current texture unit in the current rendering context.
         * After binding, subsequent rendering calls will use this texture for rendering operations.
         */
    void bind();
    /**
        * \brief Unbinds the texture from the OpenGL context.
        *
        * This function unbinds the texture from the OpenGL context by setting the active texture unit
        * to zero for the currently bound texture type.
        *
        * \see bind()
        * \see Texture::bind()
        */
    void unbind();
    /**
     * @brief Clears the texture by deleting it.
     *
     * This function deletes the texture specified by the ID.
     */
    void clear();
    /**
     * @brief Resizes the texture to the specified width and height.
     *
     * This function resize the texture to the specified width and height. It binds the texture,
     * updates the texture data with glTexImage2D, sets the texture filtering parameters, and then
     * unbinds the texture.
     *
     * @param width The new width of the texture.
     * @param height The new height of the texture.
     */
    void resize(GLsizei width, GLsizei height);

};


#endif //MEP_TEXTURE_H
