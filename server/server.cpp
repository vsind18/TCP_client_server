#include <iostream> 
#include "networking/base.h"
// (Tự định nghĩa) Có thể chứa hàm hoặc khai báo mạng riêng
#include <boost/asio.hpp> 
// Thư viện Boost.Asio để lập trình mạng TCP/UDP

using boost::asio::ip::tcp; 
// Giúp viết ngắn gọn tcp::socket thay vì boost::asio::ip::tcp::socket

int main(int argc, char* argv[]) {
// Hàm chính của chương trình. argc, argv để nhận tham số dòng lệnh
    try {
        boost::asio::io_context io_context;
        // Bộ xử lý I/O trung tâm của Boost.Asio

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1337));
        // Mở cổng 1337 để lắng nghe kết nối TCP từ client (IPv4)

        while (true) {
            std::cout << "Accepting connections on port 1337!\n";
            // In log khi server đang chờ client

            tcp::socket socket(io_context);
            // Tạo một socket TCP để giao tiếp với client

            acceptor.accept(socket);
            // Dừng lại và chờ client kết nối. Khi client kết nối, socket gắn với kết nối đó.

            std::cout << "Client connected! Sending message!\n";
            // In log xác nhận đã kết nối client

            std::string hello_message = "Hello, beautiful client!\n";
            // Nội dung sẽ gửi cho client

            boost::system::error_code error;
            // Biến chứa mã lỗi (nếu có) khi gửi dữ liệu

            boost::asio::write(socket, boost::asio::buffer(hello_message), error);
            // Gửi dữ liệu đến client qua socket
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        // Nếu có lỗi, in thông báo lỗi ra console
    }

    return 0;
    // Kết thúc chương trình
}
