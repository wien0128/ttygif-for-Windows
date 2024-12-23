#include "GifCreator.h"
#include <iostream>

// 생성자: 초기화
GifCreator::GifCreator(int width, int height, int quality, int delay, bool useGlobalColorMap)
    : width(width), height(height), quality(quality), delay(delay), useGlobalColorMap(useGlobalColorMap) {
}

// 소멸자: 리소스 정리 (필요 시)
GifCreator::~GifCreator() {
    close(); // 열린 GIF 파일이 있으면 닫음
}

// GIF 파일 열기
bool GifCreator::open(const std::string& filename) {
    int preAllocSize = useGlobalColorMap ? width * height * 3 * 3 : width * height * 3;
    if (!gifEncoder.open(filename.c_str(), width, height, quality, useGlobalColorMap, 0 /* loop */, preAllocSize)) {
        std::cerr << "Failed to open GIF file: " << filename << std::endl;
        return false;
    }
    return true;
}

// 프레임 추가
bool GifCreator::addFrame(const std::vector<uint32_t>& frameData) {
    if (frameData.size() != static_cast<size_t>(width * height)) {
        std::cerr << "Frame size does not match GIF dimensions." << std::endl;
        return false;
    }

    if (!gifEncoder.push(GifEncoder::PIXEL_FORMAT_RGBA, reinterpret_cast<const uint8_t*>(frameData.data()), width, height, delay)) {
        std::cerr << "Failed to add frame to GIF." << std::endl;
        return false;
    }
    return true;
}

// GIF 파일 닫기
bool GifCreator::close() {
    if (!gifEncoder.close()) {
        std::cerr << "Failed to close GIF file." << std::endl;
        return false;
    }
    return true;
}
