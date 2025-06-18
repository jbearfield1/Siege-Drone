#include <cstdint>

// class used to abstract SPI communication, temporarily only works with our use case of transferring floats
class SPI {
public:
	/**
	 * @param device the filename of the SPI device to be connected to
	 * @param speed the speed in Hz at which data is to be read
	 * @param mode designated SPI mode between 0 and 3 (inclusive) -- sets clock polarity and phase
	 * @param bits the number of bits in a packet (defaulted to 8)
	 * @param delay the delay in microseconds (defaulted to 0)
	 * @brief opens up a file descriptor to begin writing to specified SPI peripheral and sets the desired settings
	 */
	SPI(const char* device, uint32_t speed, uint8_t mode = 0, uint8_t bits = 8, uint8_t delay = 0);

	/**
	 * @param num the float to be sent over SPI
	 * @brief sends the float over SPI to the peripheral device
	 * @returns the exit code of the funcion
	 */
	int send(float num);

	/**
	 * @brief reads the last data returned from the SPI peripheral device
	 * @returns the float sitting in the rx buffer
	 */
	float recv();

private:
	// union used to convert between a float and an array of bytes
	union converter {
		uint8_t array[sizeof(float)];
		float num;
	};

	// file descriptor associated with spi connection
	int fd;

	// SPI settings that need to be saved for sending
	uint32_t speed;
	uint8_t bits;
	uint8_t delay;

	converter tx;
	converter rx;
};
