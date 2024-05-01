//
// Created by jan on 5/25/23.
//

#ifndef MEP_SHADER_H
#define MEP_SHADER_H

#include <string>
#include "../../../misc/InternalLogger.h"
#include "../../UniformVarManager.h"
#include "GL/glew.h"
#include "glm/glm.hpp"


class Shader {
public:
    /**
     * @class Shader
     * @brief The Shader class represents a shader program.
     *
     * The Shader class loads and compiles vertex and fragment shaders from file and creates a shader program.
     * It also provides functions to activate and set uniform variables in the shader program.
     */
    Shader(MessageBoard * config, const char *vertexFile, const char *fragmentFile);
    /**
     * @class Shader
     * @brief The Shader class represents a shader program.
     *
     * The Shader class loads and compiles vertex and fragment shaders from file and creates a shader program.
     * It also provides functions to activate and set uniform variables in the shader program.
     */
    Shader();
    /**
     * @fn void activate() const
     * @brief Activates the shader program.
     *
     * This function activates the shader program for rendering.
     * It binds the shader program to the current rendering context.
     * This is necessary before rendering any objects that use this shader program.
     */
    void activate() const;
    /**
     * @fn void Shader::clear() const
     * @brief Clears the shader program.
     *
     * This function deletes the shader program, effectively clearing the shader.
     * It releases any resources allocated by the shader program.
     * After calling this function, the shader program can no longer be used for rendering.
     */
    void clear() const;
    /**
     * @fn GLint Shader::getUniform(const std::string& key)
     * @brief Retrieves the location of a uniform variable in the shader program.
     *
     * This function returns the location (OpenGL ID) of a uniform variable specified by its name in the shader program.
     *
     * @param key The name of the uniform variable to retrieve the location of.
     * @return The location (OpenGL ID) of the uniform variable.
     */
    GLint getUniform(const std::string&);
    /**
     * @fn void setBool(const std::string& name, bool value)
     * @brief Sets a boolean uniform variable in the shader program.
     *
     * This function sets a uniform variable of type bool in the shader program specified by its name.
     *
     * @param name The name of the uniform variable.
     * @param value The boolean value to set.
     */
    void setBool(const std::string &name, bool value);
    /**
     * @fn void setInt(const std::string& name, int value)
     * @brief Sets an integer uniform variable in the shader program.
     *
     * This function sets the value of an integer uniform variable in the shader program.
     * It first retrieves the ID of the uniform variable using the provided name.
     * If the ID is valid, it sets the uniform variable to the specified value.
     *
     * @param name The name of the uniform variable.
     * @param value The integer value to set.
     */
    void setInt(const std::string &name, int value);
    /**
     * @brief Set a float value for a uniform variable in the shader program.
     *
     * This function sets the value of a uniform variable with the given name to the specified float value.
     *
     * @param name The name of the uniform variable.
     * @param value The float value to set.
     */
    void setFloat(const std::string &name, float value);
    /**
     * @fn void setMat4(const std::string &name, const glm::mat4 &mat)
     * @brief Sets the value of a uniform variable of type mat4 in the shader program.
     *
     * This function sets the value of a uniform variable with the given name in the shader program to the specified mat4 value.
     * The uniform variable must be a mat4 type in the shader program.
     *
     * @param name The name of the uniform variable.
     * @param mat The mat4 value to set.
     */
    void setMat4(const std::string &name, const glm::mat4 &mat);
    /**
     * @class Shader
     * @brief The Shader class represents a shader program.
     *
     * The function returns a boolean whether the creation of the shader program was a success
     * @return the success state of the shader program initialization
     */
    [[nodiscard]] bool checkSuccess() const;
    /**
     * @fn GLuint Shader::getID()
     * @brief Get an ID of the shader program.
     *
     * This function retrieves the ID of the shader program
     */
    [[nodiscard]] GLuint getID() const;

    /**
     * A simple shader program destructor
     */
    virtual ~Shader();

private:
    GLuint ID;
    bool success = true;
    InternalLogger * log = new InternalLogger("Shaders");
    GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path);
    std::string get_file_contents(const char *filename);
    void compile_shader(const std::string &sourceCode, GLuint shaderID, GLint * result, int * InforLogLength);
    UniformVarManager * uniformVarManager = nullptr;
};


#endif //MEP_SHADER_H
