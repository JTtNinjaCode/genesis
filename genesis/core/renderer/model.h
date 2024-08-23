#pragma once
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <filesystem>
#include <string>
#include <vector>

#include "core/component/component.h"
#include "mesh.h"
namespace genesis {
enum VerticesLayout {
  PNT,   // position, normal, tex_coord(uv)
  PC,  // position, normal, tex_coord(uv), color
};
class Model {
 public:
  Model() = default;
  Model(const std::filesystem::path& path, const VerticesLayout layout) { LoadModel(path.string(), layout); }
  void LoadModel(const std::filesystem::path& path, const VerticesLayout layout);

  const std::vector<Mesh>& GetMeshes() const;

 private:
  void ProcessNode(const aiNode* node, const aiScene* scene, const VerticesLayout layout);
  Mesh ProcessMesh(const aiMesh* mesh, const aiScene* scene, const VerticesLayout layout);
  void LoadMaterialTextures(std::vector<std::shared_ptr<Texture2D>>& textures, aiMaterial* mat, aiTextureType type,
                            TextureType textureType);
  std::vector<Mesh> meshes_;
  std::filesystem::path directory_;
};

}  // namespace genesis