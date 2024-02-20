//
// Created by janha on 19/02/2024.
//

#include "UniformVarManager.h"
#include <iostream>
#include <fstream>
#include <regex>

UniformVarManager::UniformVarManager() {
    uniformLength = 0;
}

void UniformVarManager::scanFile(const std::string& filename, GLuint shaderID) {

    int newUniformsFound = 0;

    // Read shader source file
    std::ifstream shaderFile(filename);
    if (!shaderFile.is_open()) {
        std::cerr << "Error opening shader file." << std::endl;
    }

    // Read the entire file into a string
    const std::string shaderSource((std::istreambuf_iterator<char>(shaderFile)),
                                   std::istreambuf_iterator<char>());
    shaderFile.close();

    // Define a regular expression to match uniform declarations
    const std::regex uniformRegex(R"(\buniform\s+\w+\s+(\w+);)");

    // Search for matches in the shader source
    std::smatch match;
    auto it = shaderSource.cbegin();
    const auto end = shaderSource.cend();

    while (std::regex_search(it, end, match, uniformRegex)) {
        // Extract the variable name from the match
        const GLchar *variableName;
        variableName = match[1].str().c_str();

        // check if the uniform already exists, skip if so
        auto uniformKey = uniforms.find(variableName);
        if (uniformKey != uniforms.end()){
            continue;
        }

        // Add the entry to the map
        GLuint uniID = glGetUniformLocation(shaderID, variableName);
        setUniform(variableName, uniID);
        newUniformsFound++;

        // Update iterator for the next search
        it = match.suffix().first;
    }
    std::cout << "Scan complete. Uniforms found: " << newUniformsFound << std::endl;
}

int UniformVarManager::getUniformLength() const {
    return uniformLength;
}

std::vector<std::string> UniformVarManager::getUniformList() {
    // create a vector list
    std::vector<std::string> keys;
    keys.reserve(uniformLength);

    // iterate each key and add it to the vector
    for(const auto& pair : uniforms){
        keys.push_back(pair.first);
    }

    return keys;
}

int UniformVarManager::setUniform(const std::string& key, GLuint ID) {
    auto uniformKey = uniforms.find(key);
    if (uniformKey != uniforms.end()){
        uniformKey->second = ID;
        return 0;
    }else{
        uniforms[key] = ID;
        uniformLength++;
        return 1;
    }
}

GLuint UniformVarManager::getUniform(const std::string& uniformName) {
    auto uniformKey = uniforms.find(uniformName);
    if (uniformKey != uniforms.end()){
        return uniformKey->second;
    }
    return -1;
}
