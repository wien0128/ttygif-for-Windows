#pragma once

#include "common.h"
#include "terminal_recorder.h"
#include "gif.h"
#include <string>


namespace ttygif
{
	class GifConverter
	{
	public:
		GifConverter() = default;
		~GifConverter() = default;

		GifConverter(const GifConverter&) = delete;
		GifConverter& operator=(const GifConverter&) = delete;

		bool saveToGif(const std::string& filename, 
			const std::vector<FrameData>& frames, 
			int frameDelayMs);

	private:
		ErrorCode lastError;

		void convertFrameToRGBA(const FrameData& frame, std::vector<uint8_t>& imageData);
	};
}
