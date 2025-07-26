#include <iostream>
#include <thread>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void read_messages(tcp::socket& socket){
    try{
        for(;;){
            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, "\n");
            std::istream input(&buffer);
            std::string msg;
            std::getline(input, msg);
            std::cout << msg << std::endl;
        }
    } catch (...){
        std::cout << "Disconnected from server. \n";
    }
}

int main(){
    try {
        boost::asio::io_context io_context;
        
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "1337");

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::cout << "Enter your name: ";
        std::string name;
        std::getline(std::cin, name);
        boost::asio::write(socket, boost::asio::buffer("NAME: " + name + "\n"));

        std::thread reader(read_messages, std::ref(socket));

        while (true){
            std::string msg;
            // std::cout << "Chat: ";
            std::getline(std::cin, msg);
            boost::asio::write(socket, boost::asio::buffer(msg + "\n"));
        }

        reader.join();

    } catch (std::exception& e){
        std::cerr << "Client error: " << e.what() << std::endl;
    }
    return 0;
}