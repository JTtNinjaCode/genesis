#include "model.h"

#include <iostream>
#include <vector>

#include "core/log/log.h"
#include "core/renderer/buffer.h"
#include "core/renderer/vertex_array.h"
#include "core/renderer/vertex_format/vertex_pnt.h"
namespace genesis {

void Model::LoadModel(const std::filesystem::path& path, const VerticesLayout layout) {
  Assimp::Importer importer;
  const aiScene* scene =
      importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    CORE_LOG_ERROR("Failed to load object by assimp: {0}", importer.GetErrorString());
    return;
  }
  directory_ = path.parent_path();
  ProcessNode(scene->mRootNode, scene, layout);
  CORE_LOG_TRACE("Success to load object by assimp: {0}", path.string());
}

const std::vector<Mesh>& Model::GetMeshes() const { return meshes_; }

void Model::ProcessNode(const aiNode* node, const aiScene* scene, const VerticesLayout layout) {
  for (int i = 0; i < node->mNumMeshes; i++) {
    aiMesh* current_mesh = scene->mMeshes[node->mMeshes[i]];
    meshes_.push_back(ProcessMesh(current_mesh, scene, layout));
  }
  for (int i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene, layout);
  }
}

Mesh Model::ProcessMesh(const aiMesh* mesh, const aiScene* scene, const VerticesLayout layout) {
  std::shared_ptr<VertexBuffer> vbo;
  std::shared_ptr<VertexArray> vao;

  // set vao and vbo
  if (layout == PNT) {
    std::vector<VertexPNT> vertices;
    vertices.reserve(mesh->mNumVertices);
    for (size_t i = 0; i < mesh->mNumVertices; i++) {
      VertexPNT vertex;
      vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
      if (mesh->HasNormals()) {
        vertex.normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
      }
      if (mesh->HasTextureCoords(0)) {
        vertex.tex_coord.x = mesh->mTextureCoords[0][i].x;
        vertex.tex_coord.y = mesh->mTextureCoords[0][i].y;
      } else {
        vertex.tex_coord = glm::vec2(0.0f, 0.0f);
      }
      vertices.push_back(vertex);
    }
    vbo = VertexBuffer::Create(vertices.data(), sizeof(VertexPNT) * vertices.size());
    vao = VertexArray::Create(VertexPNT::GetLayout());
  } else if (layout == PC) {
    std::vector<VertexPC> vertices;
    vertices.reserve(mesh->mNumVertices);
    for (size_t i = 0; i < mesh->mNumVertices; i++) {
      VertexPC vertex;
      vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
      unsigned int materialIndex = mesh->mMaterialIndex;
      aiMaterial* material = scene->mMaterials[materialIndex];
      aiColor3D color(0.f, 0.f, 0.f);
      if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color)) {
        vertex.colors = {color.r, color.g, color.b, 1.0f};
      }
      vertices.push_back(vertex);
    }
    vbo = VertexBuffer::Create(vertices.data(), sizeof(VertexPC) * vertices.size());
    vao = VertexArray::Create(VertexPC::GetLayout());
  }

    vao->SetVertexBuffer(vbo);

  std::vector<unsigned int> indicies;
  for (size_t i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (size_t j = 0; j < face.mNumIndices; j++) {
      indicies.push_back(face.mIndices[j]);
    }
  }
  auto ebo = IndexBuffer::Create(indicies.data(), sizeof(unsigned int) * indicies.size());
  vao->SetIndexBuffer(ebo);

  std::vector<std::shared_ptr<Texture2D>> textures;
  if (mesh->mMaterialIndex >= 0) {
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    LoadMaterialTextures(textures, material, aiTextureType_DIFFUSE, TextureType::kDiffuse);
    LoadMaterialTextures(textures, material, aiTextureType_SPECULAR, TextureType::kSpecular);
  }
  return Mesh(std::move(vao), std::move(textures));
}

void Model::LoadMaterialTextures(std::vector<std::shared_ptr<Texture2D>>& textures, aiMaterial* mat, aiTextureType type,
                                 TextureType texture_type) {
  for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);
    textures.push_back(Texture2D::Create(directory_ / std::string(str.C_Str()), texture_type));
  }
}

}  // namespace genesis