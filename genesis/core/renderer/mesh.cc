#include "mesh.h"

#include "core/log/log.h"
#include "core/renderer/render_command.h"
namespace genesis {

const VertexArray& Mesh::GetVAO() const { return *vao_; }

const std::vector<std::shared_ptr<Texture2D>>& Mesh::GetTextures() const { return textures_; }

}  // namespace genesis