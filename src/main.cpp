#include <iostream>
#include <chrono>
#include <linux/spi/spi.h>
#include <linux/spi/spidev.h>
#include "../include/serial.h"

#define SPI_DEVICE "/dev/spidev0.0"

union converter {
    uint8_t array[sizeof(float)];
    float num;
};


converter tx;
converter rx;

int main() {
    int fd = open(SPI_DEVICE, O_RDWR);
    if (fd < 0) {
        perror("Failed to open SPI device");
        return EXIT_FAILURE;
    }

    uint8_t mode = 0;
    uint8_t bits = 8;
    uint32_t speed = 4'000'000; // Hz
    uint8_t delay = 0;

    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0 || ioctl(fd, SPI_IOC_RD_MODE, &mode) < 0) {
        perror("Failed to set SPI mode");
        close(fd);
        exit(EXIT_FAILURE);
    } 
    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0 || ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) {
        perror("Failed to set bits per word");
        close(fd);
        exit(EXIT_FAILURE);
    } 
    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0 || ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0) {
        perror("Failed to set max speed");
        close(fd);
        exit(EXIT_FAILURE);
    } 

    // variables for storing user input and the parsed float
    std::string input;
    float num;

    while (true) {
        // takes float input and stores it in num
        std::cout << "Input: ";
        std::getline(std::cin, input);
        num = std::stof(input);

        auto start = std::chrono::high_resolution_clock::now();

        memset(tx.array, 0, sizeof(tx));
        memset(rx.array, 0, sizeof(rx));
        memcpy(tx.array, &num, sizeof(num));

        struct spi_ioc_transfer tr = {
            .tx_buf = (unsigned long)tx.array,
            .rx_buf = (unsigned long)rx.array,
            .len = sizeof(float),
            .speed_hz = speed,
            .delay_usecs = delay,
            .bits_per_word = bits,
        };
        
        if (ioctl(fd, SPI_IOC_MESSAGE(1), &tr) < 0) {
            perror("Failed to transfer SPI message");
            close(fd);
            return EXIT_FAILURE;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Sent: " << tx.num << std::endl;
        std::cout << "Received: " << rx.num << std::endl;
        std::cout << "Completed in " << duration.count() << " us" << std::endl;
    }
}