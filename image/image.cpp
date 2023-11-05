#include "image.h"

#include "../exception/exception.h"

#include <cassert>

namespace bmp {

Pixel::Pixel(int blue, int green, int red) {
    b = std::clamp(blue, kMinColorValue, kMaxColorValue);
    g = std::clamp(green, kMinColorValue, kMaxColorValue);
    r = std::clamp(red, kMinColorValue, kMaxColorValue);
}

Image::Image(std::string_view input_file) {
    std::ifstream in(input_file.data(), std::ios::in | std::ios::binary);
    if (!in.is_open()) {
        throw my_exception::ImageException("can not open file");
    }

    ReadHeaders(in, input_file);
    ReadImage(in, input_file);

    in.close();
}

void Image::Save(std::string_view output_file) {
    std::ofstream out(output_file.data(), std::ios::out | std::ios::binary);
    if (!out.is_open()) {
        throw std::exception();
    }

    WriteHeaders(out, output_file);
    WriteImage(out);

    out.close();
}

size_t Image::GetHeight() const {
    return static_cast<size_t>(info_.height);
}

size_t Image::GetWidth() const {
    return static_cast<size_t>(info_.width);
}

PixelMatrix Image::GetPixels() const {
    return image_;
}

const Pixel& Image::GetPixel(size_t height, size_t width) const {
    assert(height >= 0 && height < GetHeight());
    assert(width >= 0 && width < GetWidth());

    return image_[height][width];
}

void Image::SetPixel(const Pixel& new_pixel, size_t height, size_t width) {
    assert(height >= 0 && height < GetHeight());
    assert(width >= 0 && width < GetWidth());

    image_[height][width] = new_pixel;
}

void Image::Resize(size_t new_height, size_t new_width) {
    size_t curr_height = GetHeight();
    size_t curr_width = GetWidth();

    if (curr_height > new_height) {
        image_.resize(new_height);
        info_.height = static_cast<uint32_t>(new_height);
    }

    if (curr_width > new_width) {
        for (auto& row : image_) {
            row.resize(new_width);
        }

        info_.width = static_cast<uint32_t>(new_width);
    }
}

void Image::ReadHeaders(std::ifstream& in, std::string_view input_file) {
    in.read(reinterpret_cast<char*>(&header_signature_), kBmpSignatureByteSize);
    if (header_signature_[0] != kBmpFirstSignature || header_signature_[1] != kBmpSecondSignature) {
        throw my_exception::ImageException("invalid image format");
    }

    in.read(reinterpret_cast<char*>(&header_), kBmpHeaderNoSignatureByteSize);

    in.read(reinterpret_cast<char*>(&info_), kBmpInfoByteSize);
    if (info_.bits_per_pixel != kBitsPerPixel) {
        throw my_exception::ImageException("required 24 bits per pixel");
    }

    if (info_.compression != kNotCompressionFlag) {
        throw my_exception::ImageException("image should not be compressed");
    }
}

void Image::ReadImage(std::ifstream& in, std::string_view input_file) {
    in.seekg(header_.offset);

    uint32_t padding = CalcPadding();
    PixelMatrix pixels(info_.height, std::vector<Pixel>(info_.width));
    for (auto& row : pixels) {
        for (auto& pixel : row) {
            in.read(reinterpret_cast<char*>(&pixel), sizeof(Pixel));
        }

        in.seekg(padding, std::ios::cur);
    }

    std::reverse(pixels.begin(), pixels.end());

    image_ = std::move(pixels);
}

void Image::WriteHeaders(std::ofstream& out, std::string_view output_file) {
    out.write(reinterpret_cast<char*>(&header_signature_), kBmpSignatureByteSize);

    header_.offset = kBmpSignatureByteSize + kBmpHeaderNoSignatureByteSize + kBmpInfoByteSize;
    header_.file_size = header_.offset + GetHeight() * (GetWidth() * kColorCount + CalcPadding());
    out.write(reinterpret_cast<char*>(&header_), kBmpHeaderNoSignatureByteSize);

    out.write(reinterpret_cast<char*>(&info_), kBmpInfoByteSize);
}

void Image::WriteImage(std::ofstream& out) {
    std::reverse(image_.begin(), image_.end());

    uint32_t padding = CalcPadding();
    uint8_t padding_value = 0;
    for (const auto& row : image_) {
        for (const auto& pixel : row) {
            out.write(reinterpret_cast<const char*>(&pixel), sizeof(Pixel));
        }

        out.write(reinterpret_cast<char*>(&padding_value), padding);
    }
}

uint32_t Image::CalcPadding() const {
    size_t width_in_bytes = GetWidth() * kColorCount;
    size_t padding = (kPadding - width_in_bytes % kPadding) % kPadding;

    return static_cast<uint32_t>(padding);
}

} // bmp namespace
