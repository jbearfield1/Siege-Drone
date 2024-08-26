#include <iostream>
#include "../include/serial.h"

#define BAUD_RATE 115200
#define PORT "/dev/ttyACM0"

int main() {
    // opens the passed serial port at the given baud rate
    Serial arduino(PORT, BAUD_RATE);

    // variables for storing user input and the parsed float
    std::string input;
    float num;

    // waits for arduino to pass a message indicating it's ready before proceeding
    while (arduino.read_line().empty());

    while (true) {
        // takes float input and stores it in num
        std::cout << "Input: ";
        std::getline(std::cin, input);
        num = std::stof(input);

        // sends the input float over serial and awaits a response
        arduino.write(num);
        std::cout << arduino.read_line() << std::endl;
    }
}