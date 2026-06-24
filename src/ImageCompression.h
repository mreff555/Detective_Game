#ifndef IMAGE_COMPRESSION_H
#define IMAGE_COMPRESSION_H

#include <raylib.h>
#include <string>
#include <vector>

namespace highline_ridge
{

std::string resolveAssetPath(const std::string& assetRoot, const std::string& path);

std::vector<std::string> buildAssetSearchPaths(
    const std::string& assetRoot,
    const std::string& relativePath);

std::string compressedAssetPath(const std::string& path);

bool decompressXzFile(const std::string& path, std::vector<unsigned char>& outBytes);

bool compressBytesToXzFile(
    const unsigned char* input,
    size_t inputSize,
    const std::string& outputPath);

bool writeBinaryFile(const std::string& path, const unsigned char* data, size_t size);

bool ensureParentDirectoryExists(const std::string& filePath);

bool loadAssetBytesFromFile(const std::string& path, std::vector<unsigned char>& outBytes);

bool loadImageFromAssetFile(const std::string& path, Image& outImage);

bool loadTextureFromAssetFile(const std::string& path, Texture2D& outTexture);

}

#endif /* IMAGE_COMPRESSION_H */