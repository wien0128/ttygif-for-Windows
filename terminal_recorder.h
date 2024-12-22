#pragma once

#include "common.h"
#include "gif.h"
#include <memory>

namespace ttygif
{
    // Structure to store a single frame of terminal data
	struct FrameData
	{
        std::vector<CHAR_INFO> buffer{};  // Terminal buffer data
        std::chrono::system_clock::time_point timestamp{};    // Frame capture time
        SHORT width{0};    // Frame width
        SHORT height{0};   // Frame height
	};

    // Class for managing Windows terminal capture
    class TerminalRecorder 
    {
    public:
        TerminalRecorder();
        ~TerminalRecorder() = default;

        // Delete copy constructor and assignment operator
        TerminalRecorder(const TerminalRecorder&) = delete;
        TerminalRecorder& operator=(const TerminalRecorder&) = delete;

        // Recording control functions
        bool startRecording() noexcept;
        bool stopRecording() noexcept;
        bool isRecording() const noexcept;

        // Frame management functions
        const std::vector<FrameData>& getFrames() const noexcept;
        void clearFrames() noexcept;

        // Status check functions
        RecordingState getState() const noexcept;
        ErrorCode getLastError() const noexcept;

    private:
        std::unique_ptr<std::remove_pointer<HANDLE>::type, decltype(&CloseHandle)> consoleHandle;
        std::vector<FrameData> frames;
        RecordingState state;
        ErrorCode lastError;

        // Capture single frame
        bool captureFrame();
    };
}