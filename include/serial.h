#include <boost/asio.hpp>

class Serial {
public:
    /**
     * @brief creates an instance of the Serial class without opening any serial ports
     */
    Serial();

    /**
     * @param port a string representation of the serial port the serial device is connected through
     * @param baudRate the desired rate (in bits/second) to send data over serial -- must match connected serial device
     * @param flowControl limits the amount of data being transmitted from the serial port -- defaults to off
     * @param parity adds a parity bit used for checking that data was successfully received -- defaults to none
     * @param charSize the number of bits in each character being sent over serial -- defaults to 8
     * @param stopBits the number of stop bits at the end of each character -- defaults to one
     * @brief creates instance of Serial class and opens the passed serial port with the given parameters
     */
    Serial(std::string port, unsigned int baudRate, 
            boost::asio::serial_port_base::flow_control flowControl = boost::asio::serial_port_base::flow_control(
                boost::asio::serial_port_base::flow_control::none),
            boost::asio::serial_port_base::parity parity = boost::asio::serial_port_base::parity(
                boost::asio::serial_port_base::parity::none),
            boost::asio::serial_port_base::character_size charSize = boost::asio::serial_port_base::character_size(
                boost::asio::serial_port_base::character_size(8)),
            boost::asio::serial_port_base::stop_bits stopBits = boost::asio::serial_port_base::stop_bits(
                boost::asio::serial_port_base::stop_bits::one)
            );

    /**
     * @param port a string representation of the serial port the serial device is connected through
     * @param baudRate the desired rate (in bits/second) to send data over serial -- must match connected serial device
     * @param flowControl limits the amount of data being transmitted from the serial port -- defaults to off
     * @param parity adds a parity bit used for checking that data was successfully received -- defaults to none
     * @param charSize the number of bits in each character being sent over serial -- defaults to 8
     * @param stopBits the number of stop bits at the end of each character -- defaults to one
     * @brief opens serial communication through passed serial port with the given parameters
     */
    void open(std::string port, unsigned int baudRate, 
            boost::asio::serial_port_base::flow_control flowControl = boost::asio::serial_port_base::flow_control(
                boost::asio::serial_port_base::flow_control::none),
            boost::asio::serial_port_base::parity parity = boost::asio::serial_port_base::parity(
                boost::asio::serial_port_base::parity::none),
            boost::asio::serial_port_base::character_size charSize = boost::asio::serial_port_base::character_size(
                boost::asio::serial_port_base::character_size(8)),
            boost::asio::serial_port_base::stop_bits stopBits = boost::asio::serial_port_base::stop_bits(
                boost::asio::serial_port_base::stop_bits::one)
            );

    /**
     * @brief method used to check the current status of the serial port
     * @returns true if the serial port is open, false otherwise
     */
    bool isOpen();

    /**
     * @brief closes the serial port
     */
    void close();

    /**
     * @param data the float variable that contains the number to be sent over serial
     * @brief sends the passed float over the set serial port
     */
    void write(const float& data);

    /**
     * @param msg the string containing the message to be sent over serial
     * @brief sends the passed string over the set serial port
     */
    void writeString(std::string msg);

    /**
     * @returns a string representation of the data sent over serial to this device
     * @brief reads from serial until it encounters a newline character and then returns the
     *        read string
     */
    std::string readLine();

    /**
     * @param baudRate the desired rate (in bits/second) to send data over serial -- must match connected serial device
     * @brief sets the baud rate of the serial port
     */
    void setBaudRate(unsigned int baudRate);

    /**
     * @param flowControl limits the amount of data being transmitted from the serial port (on/off)
     * @brief turns flow control on or off for this serial port
     */
    void setFlowControl(boost::asio::serial_port_base::flow_control flowControl);

    /**
     * @param parity adds a parity bit used for checking that data was successfully received
     * @brief sets whether or not there is a parity bit in each packet sent over this serial connection
     */
    void setParity(boost::asio::serial_port_base::parity parity);

    /**
     * @param charSize the number of bits in each character being sent over serial
     * @brief adjusts the number of data bits contained in each character being sent over serial
     */
    void setCharSize(boost::asio::serial_port_base::character_size charSize);

    /**
     * @param stopBits the number of stop bits at the end of each character
     * @brief adjusts the number of stop bits at the end of each character being sent over serial
     */
    void setStopBits(boost::asio::serial_port_base::stop_bits stopBits);

private:
    // io context used for the serial port
    boost::asio::io_context io;
    // serial port being communicated thtough
    boost::asio::serial_port serial;
};