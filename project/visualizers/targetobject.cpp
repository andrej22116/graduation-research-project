#include "TargetObject.hpp"

#include <QString>

#include <stdexcept>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <QDebug>

void TargetObject::loadMesh(const QString& path)
{
    // Auto remove sources in destructor
    Assimp::Importer importer{};

    auto scene = importer.ReadFile( path.toLocal8Bit().data()
                                  , aiProcess_Triangulate
                                  | aiProcess_FlipUVs
                                  | aiProcess_CalcTangentSpace
                                  | aiProcess_GenNormals
                                  | aiProcess_ImproveCacheLocality
                                  | aiProcess_FixInfacingNormals
                                  | aiProcess_FindInvalidData
                                  | aiProcess_GenUVCoords
                                  | aiProcess_OptimizeMeshes
                                    );

    if ( !scene
         || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
         || !scene->mRootNode ) {
        throw std::runtime_error(importer.GetErrorString());
    }

    auto mesh = scene->mMeshes[0];

    vertices.reserve(mesh->mNumVertices);

    for ( uint i = 0; i < mesh->mNumVertices; ++i ) {

        vertices.emplace_back();
        auto& vertex = vertices.back();

        vertex.position = mesh->mVertices[i];

        vertex.normal = mesh->HasNormals() ? mesh->mNormals[i]
                                           : aiVector3D{0, 0, 0};

        vertex.texCoords = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i]
                                                     : aiVector3D{0, 0, 0};

        if ( mesh->HasTangentsAndBitangents() ) {
            vertex.tangent = mesh->mTangents[i];
            vertex.bitangent = mesh->mBitangents[i];
        }
        else {
            vertex.tangent = aiVector3D{0, 0, 0};
            vertex.bitangent = aiVector3D{0, 0, 0};
        }
    }

    // Triangulated faces...
    indices.reserve(mesh->mNumFaces * 3);

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        auto face = mesh->mFaces[i];
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }
}

void TargetObject::clear()
{
    vertices = std::vector<Vertex>{};
    indices = std::vector<unsigned int>{};
}

bool TargetObject::loaded()
{
    return !vertices.empty() && !indices.empty();
}

TargetObject::operator bool()
{
    return !vertices.empty() && !indices.empty();
}
