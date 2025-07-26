#include<iostream>
#include "networking/base.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
int main() {
    try {
        // 1. Tạo IO context
        boost::asio::io_context io_context;

        // 2. Giải quyết địa chỉ IP và cổng thành danh sách endpoint
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "1337");

        // 3. Tạo socket TCP
        tcp::socket socket(io_context);

        // 4. Kết nối socket tới server
        boost::asio::connect(socket, endpoints);

        // 5. Nhận và in dữ liệu từ server
        while (true) {
            std::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof) {
                // Kết nối bị ngắt một cách bình thường
                break;
            } else if (error) {
                // Một lỗi khác xảy ra
                throw boost::system::system_error(error);
            }

            // In dữ liệu ra console
            std::cout.write(buf.data(), len);
        }
    } catch (std::exception& e) {
        // In lỗi nếu có
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}