#ifndef GIF_CREATOR_H
#define GIF_CREATOR_H

#include <string>
#include <vector>
#include <cstdint>
#include "GifEncoder.h" // GifEncoder 라이브러리 헤더 포함

class GifCreator {
private:
    int width;                      // GIF의 가로 크기
    int height;                     // GIF의 세로 크기
    int quality;                    // GIF 품질 (1~100, 높을수록 품질 좋음)
    int delay;                      // 각 프레임의 지연 시간 (ms 단위)
    bool useGlobalColorMap;         // 글로벌 컬러 맵 사용 여부
    GifEncoder gifEncoder;          // GifEncoder 객체

public:
    GifCreator(int width, int height, int quality = 10, int delay = 100, bool useGlobalColorMap = true);
    ~GifCreator();

    bool open(const std::string& filename);  // GIF 파일 열기
    bool addFrame(const std::vector<uint32_t>& frameData); // 프레임 추가
    bool close();                            // GIF 파일 닫기
};

#endif // GIF_CREATOR_HPP
