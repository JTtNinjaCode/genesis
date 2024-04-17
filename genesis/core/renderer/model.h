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
class Model : public Component {
 public:
  Model() = default;
  Model(const std::filesystem::path& path) { LoadModel(path.string()); }
  void LoadModel(const std::filesystem::path& path);

  void Draw(Shader& shader);
  void DrawInstanced(Shader& shader, unsigned int count);

 private:
  void ProcessNode(const aiNode* node, const aiScene* scene);
  Mesh ProcessMesh(const aiMesh* mesh, const aiScene* scene);
  void LoadMaterialTextures(std::vector<std::shared_ptr<Texture2D>>& textures, aiMaterial* mat, aiTextureType type,
                            TextureType textureType);
  std::vector<Mesh> meshes_;
  std::filesystem::path directory_;
};

}  // namespace genesis