#include "model.h"

#include <vector>

#include "core/log/log.h"
#include "core/renderer/buffer.h"
#include "core/renderer/vertex_array.h"
#include "core/renderer/vertex_format/vertex_pnt.h"

namespace genesis {
void Model::Draw(Shader& shader) const {
  for (auto& mesh : meshes_) {
    mesh.Draw(shader);
  }
}

void Model::DrawInstanced(Shader& shader, unsigned int count) const {
  for (auto& mesh : meshes_) mesh.DrawInstanced(shader, count);
}

void Model::LoadModel(const std::filesystem::path& path) {
  Assimp::Importer importer;
  const aiScene* scene =
      importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    CORE_LOG_ERROR("Failed to load object by assimp: {0}", importer.GetErrorString());
    return;
  }
  directory_ = path.parent_path();
  ProcessNode(scene->mRootNode, scene);
  CORE_LOG_TRACE("Success to load object by assimp: {0}", path.string());
}

void Model::ProcessNode(const aiNode* node, const aiScene* scene) {
  for (int i = 0; i < node->mNumMeshes; i++) {
    aiMesh* current_mesh = scene->mMeshes[node->mMeshes[i]];
    meshes_.push_back(ProcessMesh(current_mesh, scene));
  }
  for (int i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene);
  }
}

Mesh Model::ProcessMesh(const aiMesh* mesh, const aiScene* scene) {
  std::vector<VertexPNT> vertices;
  vertices.reserve(mesh->mNumVertices);
  for (size_t i = 0; i < mesh->mNumVertices; i++) {
    VertexPNT vertex;

    vertex.position.x = mesh->mVertices[i].x;
    vertex.position.y = mesh->mVertices[i].y;
    vertex.position.z = mesh->mVertices[i].z;

    if (mesh->HasNormals()) {
      vertex.normal.x = mesh->mNormals[i].x;
      vertex.normal.y = mesh->mNormals[i].y;
      vertex.normal.z = mesh->mNormals[i].z;
    }

    if (mesh->mTextureCoords[0] != nullptr) {
      vertex.tex_coord.x = mesh->mTextureCoords[0][i].x;
      vertex.tex_coord.y = mesh->mTextureCoords[0][i].y;
    } else {
      vertex.tex_coord = glm::vec2(0.0f, 0.0f);
    }
    vertices.push_back(vertex);
  }

  auto vbo = VertexBuffer::Create(vertices.data(), sizeof(VertexPNT) * vertices.size());
  auto vao = VertexArray::Create({MathDataType::kFloat3, MathDataType::kFloat3, MathDataType::kFloat2});
  vao->AddVertexBuffer(*vbo);

  std::vector<unsigned int> indicies;
  for (size_t i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (size_t j = 0; j < face.mNumIndices; j++) {
      indicies.push_back(face.mIndices[j]);
    }
  }
  auto ebo = IndexBuffer::Create(indicies.data(), sizeof(unsigned int) * indicies.size());
  vao->SetIndexBuffer(*ebo);

  std::vector<std::shared_ptr<Texture2D>> textures;
  if (mesh->mMaterialIndex >= 0) {
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    LoadMaterialTextures(textures, material, aiTextureType_DIFFUSE, TextureType::Diffuse);
    LoadMaterialTextures(textures, material, aiTextureType_SPECULAR, TextureType::Specular);
  }
  return Mesh(std::move(vbo), std::move(vao), std::move(ebo), std::move(textures));
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