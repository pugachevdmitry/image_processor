project(image-processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    image_processor
    image_processor.cpp
        Color.cpp
        PixelArray.cpp
        Image.cpp
        FilterInterface.cpp
        filters/Crop.cpp
        FilterController.cpp
        filters/Negative.cpp
        filters/Grayscale.cpp
        filters/Sharpening.cpp
        MatrixFilter.cpp
        filters/Edge.cpp
        filters/GaussianBlur.cpp
        DPixelArray.cpp
        filters/FishEye.cpp
)




