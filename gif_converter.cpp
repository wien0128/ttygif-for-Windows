#include "gif_converter.h"

namespace ttygif
{
	bool GifConverter::saveToGif(const std::string& filename,
		const std::vector<FrameData>& frames,
		int frameDelayMs)
	{
		if (frames.empty())
		{
			lastError = ErrorCode::FILE_ERROR;
			return false;
		}

		GifWriter gifWriter;
		const int width = frames[0].width;
		const int height = frames[0].height;

		// Initialize GIF writer
		if (!GifBegin(&gifWriter, filename.c_str(), width, height, frameDelayMs / 10))
		{
			lastError = ErrorCode::FILE_ERROR;
			return false;
		}

		// Convert and write each frame
		for (const auto& frame : frames)
		{
			std::vector<uint8_t> imageData(width * height * 4);	// RGBA format

			convertFrameToRGBA(frame, imageData);

			if (!GifWriteFrame(&gifWriter, imageData.data(), width, height, frameDelayMs / 10))
			{
				GifEnd(&gifWriter);
				lastError = ErrorCode::FILE_ERROR;
				return false;
			}
		}

		GifEnd(&gifWriter);
		return true;
	}

	void GifConverter::convertFrameToRGBA(const FrameData& frame,
		std::vector<uint8_t>& imageData)
	{
		const SHORT width = frame.width;
		const SHORT height = frame.height;

		for (SHORT y = 0; y < height; ++y)
		{
			for (SHORT x = 0; x < width; ++x)
			{
				const int index = y * width + x;
				const CHAR_INFO& charInfo = frame.buffer[index];

				uint8_t r = (charInfo.Attributes & 0xF) * 16;
				uint8_t g = ((charInfo.Attributes >> 4) & 0xF) * 16;
				uint8_t b = ((charInfo.Attributes >> 8) & 0xF) * 16;

				imageData[index * 4 + 0] = r; // Red
				imageData[index * 4 + 1] = g; // Green
				imageData[index * 4 + 2] = b; // Blue
				imageData[index * 4 + 3] = 255; // Alpha (opaque)
			}
		}
	}
}
