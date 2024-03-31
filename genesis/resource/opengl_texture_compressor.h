#pragma once
namespace genesis{
struct TextureFormat {
  unsigned int channels;
  unsigned int width;
  unsigned int height;
  unsigned char* data;
};


class OpenglTextureCompressor {};

}