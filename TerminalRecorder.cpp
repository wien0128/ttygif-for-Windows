#include "TerminalRecorder.h"
#include <iostream>
#include <thread>
#include <chrono>

// 생성자: 콘솔 핸들 초기화
TerminalRecorder::TerminalRecorder()
    : hConsole(GetStdHandle(STD_OUTPUT_HANDLE)), isRecording(false) {
}

// 녹화 시작
void TerminalRecorder::startRecording() {
    isRecording = true;
    std::thread([this]() {
        while (isRecording) {
            captureFrame();
            std::this_thread::sleep_for(std::chrono::milliseconds(33)); // 약 30fps
        }
        }).detach();
}

// 녹화 중지
void TerminalRecorder::stopRecording() {
    isRecording = false;
}

// 현재 콘솔 화면 캡처 (내부 메서드)
void TerminalRecorder::captureFrame() {
    std::lock_guard<std::mutex> lock(mutex);

    if (!GetConsoleScreenBufferInfo(hConsole, &bufferInfo)) {
        std::cerr << "Failed to get console buffer info." << std::endl;
        return;
    }

    int width = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
    int height = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;

    std::vector<char> textBuffer(width * height);
    DWORD charsRead;

    COORD coord = { 0, 0 };
    if (!ReadConsoleOutputCharacterA(hConsole, textBuffer.data(), textBuffer.size(), coord, &charsRead)) {
        std::cerr << "Failed to read console output." << std::endl;
        return;
    }

    Frame frame;
    for (int i = 0; i < height; ++i) {
        frame.textLines.emplace_back(textBuffer.data() + i * width, width);
    }

    recordedFrames.push_back(frame);
}

// 녹화된 프레임 반환 (읽기 전용)
const std::vector<TerminalRecorder::Frame>& TerminalRecorder::getRecordedFrames() const {
    return recordedFrames;
}

// 녹화된 프레임 데이터 초기화
void TerminalRecorder::clearRecordedFrames() {
    std::lock_guard<std::mutex> lock(mutex);
    recordedFrames.clear();
}
