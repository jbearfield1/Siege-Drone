#include "../include/SPI.h"
#include <linux/spi/spi.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

SPI::SPI(const char* device, uint32_t speed, uint8_t mode, uint8_t bits, uint8_t delay) {
	// attempts to open given spi device and save file descriptor
	fd = open(device, O_RDWR);
	// returns error if unable to open
	if (fd < 0) {
		perror("Failed to open SPI device");
	}

	// sets all specified settings
	if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0 || ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0) {
		perror("Failed to set max speed");
		close(fd);
	} 
	if (ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0 || ioctl(fd, SPI_IOC_RD_MODE, &mode) < 0) {
		perror("Failed to set SPI mode");
		close(fd);
	} 
	if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0 || ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) {
		perror("Failed to set bits per word");
		close(fd);
	} 

	// saves required SPI settings
	this->speed = speed;
	this->bits = bits;
	this->delay = delay;
}

int SPI::send(float num) {
	// clears tx and rx buffers
	memset(tx.array, 0, sizeof(tx));
	memset(rx.array, 0, sizeof(rx));
	// copies num into the tx buffer
	memcpy(tx.array, &num, sizeof(num));

	// sets info for transfer
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long) tx.array,
		.rx_buf = (unsigned long) rx.array,
		.len = sizeof(float),
		.speed_hz = speed,
		.delay_usecs = delay,
		.bits_per_word = bits,
	};

	// tries to send the desired number over SPI
	if (ioctl(fd, SPI_IOC_MESSAGE(1), &tr) < 0) {
		perror("Failed to transfer SPI message");
		close(fd);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

float SPI::recv() {
	// interprets rx buffer as float and returns it
	return rx.num; 
}
