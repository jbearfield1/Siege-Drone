#include "../include/serial.h"

using namespace boost;

Serial::Serial(std::string port, unsigned int baudRate, 
            asio::serial_port_base::flow_control flowControl,
            asio::serial_port_base::parity parity,
            asio::serial_port_base::character_size charSize,
            asio::serial_port_base::stop_bits stopBits)
            : serial(io)
{
    // opens port and sets all options
    serial.open(port);
    serial.set_option(asio::serial_port_base::baud_rate(baudRate));
    serial.set_option(asio::serial_port_base::flow_control(flowControl));
    serial.set_option(asio::serial_port_base::parity(parity));
    serial.set_option(asio::serial_port_base::character_size(charSize));
    serial.set_option(asio::serial_port_base::stop_bits(stopBits));
}

void Serial::open(std::string port, unsigned int baudRate, 
            asio::serial_port_base::flow_control flowControl,
            asio::serial_port_base::parity parity,
            asio::serial_port_base::character_size charSize,
            asio::serial_port_base::stop_bits stopBits)
{
    // if port is already open, it closes it to be reopened with passed settings
    if (isOpen())
        close();

    // opens port and sets all options
    serial.open(port);
    serial.set_option(asio::serial_port_base::baud_rate(baudRate));
    serial.set_option(asio::serial_port_base::flow_control(flowControl));
    serial.set_option(asio::serial_port_base::parity(parity));
    serial.set_option(asio::serial_port_base::character_size(charSize));
    serial.set_option(asio::serial_port_base::stop_bits(stopBits));
}

bool Serial::isOpen()
{
    return serial.is_open();
}

void Serial::close()
{
    // only closes port if it's open
    if (isOpen())
        serial.close();
}

void Serial::writeString(std::string msg)
{
    asio::write(serial, asio::buffer(msg.c_str(), msg.size()));
}

void Serial::write(const float& data)
{
    asio::write(serial, asio::buffer(&data, sizeof(data)));
}

std::string Serial::readLine()
{
    asio::streambuf response;
    std::size_t length = asio::read_until(serial, response, '\n');

    asio::streambuf::const_buffers_type bufs = response.data();
    std::string result(asio::buffers_begin(bufs), asio::buffers_begin(bufs) + response.size());

    return result;
}
