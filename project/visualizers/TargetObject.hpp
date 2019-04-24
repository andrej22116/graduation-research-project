#ifndef TARGETOBJECT_HPP
#define TARGETOBJECT_HPP

#include <assimp/vector2.h>
#include <assimp/vector3.h>
#include <vector>

struct Vertex {
    aiVector3D position;
    aiVector3D normal;
    aiVector3D texCoords;
    aiVector3D tangent;
    aiVector3D bitangent;
};

class QString;

struct TargetObject
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    void loadMesh(const QString& path);

    void clear();

    bool loaded();

    operator bool();
};

#endif // TARGETOBJECT_HPP
