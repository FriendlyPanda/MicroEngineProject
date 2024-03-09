//
// Created by jan on 5/25/23.
//

#ifndef MEP_SHADER_H
#define MEP_SHADER_H

#include <string>
#include "GL/glew.h"
#include "../../InternalLogger.h"
#include "../UniformVarManager.h"


class Shader {
public:
    GLuint ID;

    Shader(const char *vertexFile, const char *fragmentFile);

    Shader();

    void activate() const;

    void clear() const;

    bool success = true;

    GLint getUniform(const std::string&);

    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);


private:
    InternalLogger log = InternalLogger("Shaders");

    GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path);

    std::string get_file_contents(const char *filename);

    void compile_shader(const std::string &sourceCode, GLuint shaderID, GLint * result, int * InforLogLength);

    UniformVarManager uniformVarManager;
};


#endif //MEP_SHADER_H
