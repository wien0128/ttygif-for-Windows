#include "common.h"


namespace ttygif::utils
{
	std::string getErrorMessage(ErrorCode errorCode)
	{
		switch (errorCode)
		{
		case ttygif::ErrorCode::SUCCESS:
			return "Operation succesful.";
		case ttygif::ErrorCode::CONSOLE_ERROR:
			return "Failed to access console handle";
		case ttygif::ErrorCode::MEMORY_ERROR:
			return "Memory allocation failed.";
		case ttygif::ErrorCode::FILE_ERROR:
			return "File operation failed.";
		default:
			return "Unrecognized error occurred.";
		}
	}

	std::string getCurrentTimestamp()
	{
		auto now = std::chrono::system_clock::now();
		auto time_t_now = std::chrono::system_clock::to_time_t(now);

		std::tm localTime;
		localtime_s(&localTime, &time_t_now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

		return oss.str();
	}
}
