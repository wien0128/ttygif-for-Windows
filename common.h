#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <Windows.h>
#include <iostream>

namespace ttygif 
{
	constexpr int DEFAULY_FRAME_DELAY = 100;
	constexpr int DEFAULT_BUFFER_SIZE = 8192;
	constexpr int MAX_WIDTH = 1920;
	constexpr int MAX_HEIGHT = 1080;

	enum class RecordingState
	{
		IDLE,
		RECORDING,
		_ERROR
	};

	enum class ErrorCode
	{
		SUCCESS = 0,
		CONSOLE_ERROR,
		MEMORY_ERROR,
		FILE_ERROR
	};

	namespace utils
	{
		std::string getErrorMessage(ErrorCode errorCode);
		std::string getCurrentTimestamp();
	}
}