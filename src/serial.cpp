#include "../include/serial.h"

Serial::Serial(std::string port, unsigned int baud_rate) : serial(io, port) {
    serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
}

void Serial::write_string(std::string msg) {
    boost::asio::write(serial, boost::asio::buffer(msg.c_str(), msg.size()));
}

void Serial::write(const float& data) {
    boost::asio::write(serial, boost::asio::buffer(&data, sizeof(data)));
}

std::string Serial::read_line() {
    boost::asio::streambuf response;
    std::size_t length = boost::asio::read_until(serial, response, '\n');

    boost::asio::streambuf::const_buffers_type bufs = response.data();
    std::string result(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + response.size());

    return result;
}
