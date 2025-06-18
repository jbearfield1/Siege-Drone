#include <iostream>
#include <chrono>
#include <string>
#include "../include/SPI.h"

// #define SPI_DEVICE "/dev/spidev0.0"

int main() {
	// spi settings
	const char* SPI_DEVICE = "/dev/spidev0.0";
    const uint32_t SPEED = 4'000'000; // Hz
    const uint8_t MODE = 0;
    const uint8_t BITS = 8;
    const uint8_t DELAY = 0;
	SPI arduino(SPI_DEVICE, SPEED, MODE, BITS, DELAY);

    // variables for storing user input and the parsed float
    std::string input;
    float num;

    while (true) {
        // takes float input and stores it in num
        std::cout << "Input: ";
        std::getline(std::cin, input);
        num = std::stof(input);

        auto start = std::chrono::high_resolution_clock::now();

		// sends user input
		if (arduino.send(num) != EXIT_SUCCESS) {
			std:: cout << "Unable to send " << num << std::endl;
		}

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Sent: " << num  << std::endl;
        std::cout << "Received: " << arduino.recv() << std::endl;
        std::cout << "Completed in " << duration.count() << " us" << std::endl;
    }
}
