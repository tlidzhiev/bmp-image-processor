cmake_minimum_required(VERSION 3.26)
project(bmp_image_processor)

set(CMAKE_CXX_STANDARD 23)

add_executable(bmp_image_processor
        main.cpp
        command-parser/parser.cpp
        filters/blur.cpp
        filters/convolution_kernel.cpp
        filters/crop.cpp
        filters/edge_detection.cpp
        filters/filters_applying.cpp
        filters/grayscale.cpp
        filters/negative.cpp
        filters/sharpening.cpp
        image/image.cpp
        exception/exception.cpp
)
