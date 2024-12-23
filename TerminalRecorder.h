#ifndef TERMINAL_RECORDER_H
#define TERMINAL_RECORDER_H

#include <windows.h>
#include <vector>
#include <string>
#include <mutex>

// TerminalRecorder 클래스 정의
class TerminalRecorder {
private:
    // 내부 데이터 구조: 프레임을 저장하는 구조체
    struct Frame {
        std::vector<std::string> textLines;  // 프레임의 텍스트 데이터
        std::vector<WORD> attributes;       // 텍스트 속성 (색상 등)
    };

    HANDLE hConsole;                        // 콘솔 핸들
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;  // 콘솔 화면 버퍼 정보
    bool isRecording;                         // 녹화 상태 플래그
    std::mutex mutex;                       // 스레드 안전성을 위한 뮤텍스
    std::vector<Frame> recordedFrames;      // 녹화된 프레임 저장

    // 현재 콘솔 화면을 캡처하는 내부 메서드
    void captureFrame();

public:
    TerminalRecorder();                     // 생성자
    ~TerminalRecorder() = default;          // 소멸자

    void startRecording();                  // 녹화 시작
    void stopRecording();                   // 녹화 중지

    const std::vector<Frame>& getRecordedFrames() const;  // 녹화된 프레임 반환
    void clearRecordedFrames();            // 녹화된 프레임 초기화
};

#endif // TERMINAL_RECORDER_HPP
