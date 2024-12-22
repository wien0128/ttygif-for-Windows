#include "terminal_recorder.h"

namespace ttygif
{
    // Constructor
    TerminalRecorder::TerminalRecorder()
        : state(RecordingState::IDLE)
        , lastError(ErrorCode::SUCCESS)
        , consoleHandle(GetStdHandle(STD_OUTPUT_HANDLE))
    {
        if (consoleHandle == INVALID_HANDLE_VALUE)
        {
            lastError = ErrorCode::CONSOLE_ERROR;
            state = RecordingState::_ERROR;
        }
    }

    TerminalRecorder::~TerminalRecorder() = default;

    // Start recording if not already recording and console handle is valid
    bool TerminalRecorder::startRecording()
    {
        if (state == RecordingState::RECORDING || consoleHandle == INVALID_HANDLE_VALUE)
        {
            lastError = ErrorCode::CONSOLE_ERROR;
            return false;
        }

        state = RecordingState::RECORDING;
        return captureFrame();
    }

    // Stop recording if currently recording
    bool TerminalRecorder::stopRecording()
    {
        if (state != RecordingState::RECORDING)
        {
            return false;
        }
        state = RecordingState::IDLE;
        return true;
    }

    bool TerminalRecorder::isRecording() const noexcept
    {
        return state == RecordingState::RECORDING;
    }

    const std::vector<FrameData>& TerminalRecorder::getFrames() const noexcept
    {
        return frames;
    }

    void TerminalRecorder::clearFrames() noexcept
    {
        frames.clear();
    }

    RecordingState TerminalRecorder::getState() const noexcept
    {
        return state;
    }

    ErrorCode TerminalRecorder::getLastError() const noexcept
    {
        return lastError;
    }

    // Capture current terminal frame
    bool TerminalRecorder::captureFrame()
    {
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

        // Get console buffer information
        if (!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
        {
            lastError = ErrorCode::CONSOLE_ERROR;
            return false;
        }

        // Calculate frame dimensions
        const SHORT width = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
        const SHORT height = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;

        // Initialize frame data
        FrameData frame
        {
            .timestamp = std::chrono::system_clock::now(),
            .width = width,
            .height = height
        };

        frame.buffer.resize(width * height);

        // Set up buffer parameters for capture
        const COORD bufferSize{ width, height };
        const COORD bufferCoord{ 0, 0 };
        SMALL_RECT readRegion = {
            bufferInfo.srWindow.Left,
            bufferInfo.srWindow.Top,
            bufferInfo.srWindow.Right,
            bufferInfo.srWindow.Bottom
        };

        // Read console output to frame buffer
        if (!ReadConsoleOutput(
            consoleHandle, 
            frame.buffer.data(),
            bufferSize,
            bufferCoord,
            &readRegion))
        {
            lastError = ErrorCode::CONSOLE_ERROR;
            return false;
        }

        frames.emplace_back(std::move(frame));
        return true;
    }
}