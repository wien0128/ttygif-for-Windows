#include <iostream>
#include "terminal_recorder.h"
#include "gif_converter.h"


int main()
{
	ttygif::TerminalRecorder recorder;
	ttygif::GifConverter converter;

    while (true) {
        std::string command;
        std::cout << "Enter command (start/stop/save/exit): ";
        std::cin >> command;

        if (command == "start") {
            if (recorder.startRecording()) {
                std::cout << "Recording started." << std::endl;
            }
            else {
                std::cerr << "Failed to start recording: "
                    << ttygif::utils::getErrorMessage(recorder.getLastError()) << std::endl;
            }
        }
        else if (command == "stop") {
            if (recorder.stopRecording()) {
                std::cout << "Recording stopped." << std::endl;
            }
            else {
                std::cerr << "Failed to stop recording." << std::endl;
            }
        }
        else if (command == "save") {
            std::string filename;
            int delayMs;

            std::cout << "Enter filename: ";
            std::cin >> filename;
            std::cout << "Enter frame delay in milliseconds: ";
            std::cin >> delayMs;

            if (converter.saveToGif(filename, recorder.getFrames(), delayMs)) {
                std::cout << "GIF saved as " << filename << "." << std::endl;
            }
            else {
                std::cerr << "Failed to save GIF." << std::endl;
            }
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cerr << "Unknown command." << std::endl;
        }
    }

	return 0;
}