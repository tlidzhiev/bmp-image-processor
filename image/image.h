#pragma once

#include <vector>
#include <fstream>
#include <string>

namespace bmp {

constexpr unsigned short int kBmpSignatureByteSize = 2;
constexpr unsigned short int kBmpFirstSignature = 0x42;
constexpr unsigned short int kBmpSecondSignature = 0x4D;
constexpr unsigned short int kBmpHeaderNoSignatureByteSize = 12;

constexpr unsigned short int kBmpInfoByteSize = 40;
constexpr unsigned short int kBitsPerPixel = 24;
constexpr uint32_t kColorCount = 3;
constexpr uint32_t kNotCompressionFlag = 0;
constexpr uint32_t kPadding = 4;

constexpr int kMinColorValue = 0;
constexpr int kMaxColorValue = 255;

struct BMPHeader {
    uint32_t file_size = 0; // in bytes
    uint16_t reserved_1 = 0;
    uint16_t reserved_2 = 0;
    uint32_t offset = 0;
};

struct BMPInfo {
    uint32_t header_size = 0;
    uint32_t width = 0; // in pixels
    uint32_t height = 0; // in pixels
    unsigned short int planes = 0;
    unsigned short int bits_per_pixel = 0;
    uint32_t compression = 0;
    uint32_t image_size = 0;
    uint32_t x_pixels_per_meter = 0;
    uint32_t y_pixels_per_meter = 0;
    uint32_t colors_used_count = 0;
    uint32_t colors_important_count = 0;
};

struct Pixel {
    Pixel() = default;
    Pixel(int blue, int green, int red);

    uint8_t b = 0;
    uint8_t g = 0;
    uint8_t r = 0;
};

using PixelMatrix = std::vector<std::vector<Pixel>>;

class Image {
public:
    explicit Image(std::string_view input_file);
    void Save(std::string_view output_file);
    [[nodiscard]] size_t GetHeight() const;
    [[nodiscard]] size_t GetWidth() const;
    [[nodiscard]] PixelMatrix GetPixels() const;
    [[nodiscard]] const Pixel& GetPixel(size_t height, size_t width) const;
    void SetPixel(const Pixel& new_pixel, size_t height, size_t width);
    void Resize(size_t new_height, size_t new_width);

    ~Image() = default;
private:
    void ReadHeaders(std::ifstream& in, std::string_view input_file);
    void ReadImage(std::ifstream& in, std::string_view input_file);
    void WriteHeaders(std::ofstream& out, std::string_view output_file);
    void WriteImage(std::ofstream& out);
    [[nodiscard]] uint32_t CalcPadding() const;

    PixelMatrix image_;
    unsigned char header_signature_[kBmpSignatureByteSize]{};
    BMPHeader header_;
    BMPInfo info_;
};

} // bmp namespace
