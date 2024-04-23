//
// Created by janha on 23/04/2024.
//

#ifndef MEP_SPLINEGENERATOR3D_H
#define MEP_SPLINEGENERATOR3D_H

#include "../Game/Graphics/components/Model/Mesh.h"


class SplineGenerator3D {
public:
    std::vector<Vertex> vertexes = {};
    std::vector<glm::vec3> vertices = {};
    std::vector<unsigned int> indices = {};

    SplineGenerator3D(const glm::vec3 &pointA, const glm::vec3 &pointB, const glm::vec3 &pointC, const glm::vec3 &pointD);

    glm::vec3 CalculateBezierPoint(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    void computeBezierCurvePointsAndNormals(int resolution);
    void generateMesh(float width);

    void generateBezierCurve(int resolution, float width);

    void draw(Shader shader);

    Mesh * getMesh();

private:
    glm::vec3 pointA;
    glm::vec3 pointB;
    glm::vec3 pointC;
    glm::vec3 pointD;

    std::vector<glm::vec3> points;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> normals;

    glm::vec3 Tangent(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t);
    glm::vec3 Normal(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t);

    Mesh * mesh = nullptr;
};


#endif //MEP_SPLINEGENERATOR3D_H
