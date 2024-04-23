//
// Created by janha on 23/04/2024.
//

#include "SplineGenerator3D.h"



glm::vec3 SplineGenerator3D::CalculateBezierPoint(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    glm::vec3 p = uuu * p0;
    p += 3 * uu * t * p1;
    p += 3 * u * tt * p2;
    p += ttt * p3;

    return p;
}

void SplineGenerator3D::computeBezierCurvePointsAndNormals(int resolution) {
    glm::vec3 temp, temp1;

    for (int i = 0; i <= resolution; i++) {
        float t = i / (float)resolution;

        // calculate point on curve
        glm::vec3 pointOnCurve = CalculateBezierPoint(t, pointA, pointB, pointC, pointD);
        temp.x = pointOnCurve.x; temp.y = pointOnCurve.y; temp.z = pointOnCurve.z;
        points.push_back(temp);

        // calculate normals
        normals.push_back(Normal(pointA, pointB, pointC, pointD, t));
    }
    temp1.x += 1;
}

SplineGenerator3D::SplineGenerator3D(const glm::vec3 &pointA, const glm::vec3 &pointB, const glm::vec3 &pointC,
                                     const glm::vec3 &pointD) : pointA(pointA), pointB(pointB), pointC(pointC),
                                                          pointD(pointD) {}

glm::vec3 SplineGenerator3D::Tangent(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t) {
    return 3.0f * (1.0f - t) * (1.0f - t) * (p1 - p0) + 6.0f * (1.0f - t) * t * (p2 - p1) + 3.0f * t * t * (p3 - p2);
}

glm::vec3 SplineGenerator3D::Normal(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t) {
    glm::vec3 t1 = Tangent(p0, p1, p2, p3, t);
    tangents.push_back(t1);
    glm::vec3 t2 = Tangent(p0, p1, p2, p3, t + 0.01f); // Small offset for numerical stability

    glm::vec3 b = glm::normalize(glm::cross(t2, t1));
    return glm::normalize(glm::cross(t1, b));
}

void SplineGenerator3D::generateMesh(float width) {
    unsigned int index = 0; // the current index for the new vertices

    for(int i = 0; i < points.size(); i++){
        glm::vec3 point = points.at(i);
        glm::vec3 tangent = tangents.at(i);
        glm::vec3 normal = normals.at(i);

        glm::vec3 side = glm::cross(tangent, normal);
        side = glm::normalize(side) * width; // The side direction, of length width

        glm::vec3 vertex1 = point + side;
        glm::vec3 vertex2 = point - side;

        vertexes.push_back(Vertex{vertex1, normal, glm::vec3{0,0,0},tangent, glm::vec3{0,0,0}});
        vertexes.push_back(Vertex{vertex2, normal, glm::vec3{0,0,0},tangent, glm::vec3{0,0,0}});


        vertices.push_back(vertex1);
        vertices.push_back(vertex2);

        if (i >= 1) { // If it's not the first point
            // Triangle 1
            indices.push_back(index-2);
            indices.push_back(index-1);
            indices.push_back(index);

            // Triangle 2
            indices.push_back(index-1);
            indices.push_back(index+1);
            indices.push_back(index);


        }
        index += 2; // increment the index
    }

    mesh = new Mesh(vertexes, indices, {});
}

void SplineGenerator3D::generateBezierCurve(int resolution ,float width) {
    computeBezierCurvePointsAndNormals(resolution);
    generateMesh(width);
}

void SplineGenerator3D::draw(Shader shader) {
    mesh->Draw(shader);
}

Mesh *SplineGenerator3D::getMesh() {
    return mesh;
}
