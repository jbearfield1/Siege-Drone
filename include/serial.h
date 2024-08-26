#include <boost/asio.hpp>

class Serial {
public:
    /**
     * @param port a string representation of the serial port the serial device is connected through
     * @param baud_rate the desired rate (in bits/second) to send data over serial -- must match connected serial device
     * @brief opens serial communication through passed serial port and sets the baud rate
     */
    Serial(std::string port, unsigned int baud_rate);

    /**
     * @param data the float variable that contains the number to be sent over serial
     * @brief sends the passed float over the set serial port
     */
    void write(const float& data);

    /**
     * @param msg the string containing the message to be sent over serial
     * @brief sends the passed string over the set serial port
     */
    void write_string(std::string msg);

    /**
     * @returns a string representation of the data sent over serial to this device
     * @brief reads from serial until it encounters a newline character and then returns the
     *        read string
     */
    std::string read_line();
private:
    // member variable for the io context used for the serial port
    boost::asio::io_context io;
    // member variable for the serial port being communicated thtough
    boost::asio::serial_port serial;
};