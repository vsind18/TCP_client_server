#include <iostream>
#include <string>
#include <set>
#include <map>
#include <memory>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::set<std::shared_ptr<tcp::socket>> clients;
std::map<std::shared_ptr<tcp::socket>, std::string> client_names;
std::mutex client_mutex;

void broadcast(const std::string& msg, std::shared_ptr<tcp::socket> sender){
    std::lock_guard<std::mutex> lock(client_mutex);
    for (auto& client : clients){
        if (client != sender){
            boost::asio::write(*client, boost::asio::buffer(msg + "\n"));
        }
    }
}

void handle_client(std::shared_ptr<tcp::socket> socket){
    try {
        boost::asio::streambuf buffer;
        boost::asio::read_until(*socket, buffer, "\n");
        std::istream input(&buffer);
        std::string name_line;
        std::getline(input, name_line);

        if (name_line.rfind("NAME: ", 0) != 0){
            socket->close();
            return;
        }

        std::string name = name_line.substr(6);

        {
            std::lock_guard<std::mutex> lock(client_mutex);
            clients.insert(socket);
            client_names[socket] = name;
        }

        broadcast(name + " has joined the chat!", socket);

        while (true){
            boost::asio::streambuf msg_buf;
            boost::asio::read_until(*socket, msg_buf, "\n");

            // broadcast("Type: ", socket);

            std::istream is(&msg_buf);
            std::string msg;
            std::getline(is, msg);

            if(!msg.empty()){
                broadcast("["+ name + "]: " + msg, socket);
            }
        }
    } catch (...){
        std::lock_guard<std::mutex> lock(client_mutex);
        std::string name = client_names[socket];
        clients.erase(socket);
        client_names.erase(socket);
        broadcast(name + " has left the chat", socket);
    }
}

int main(){
    try{
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1337));
        std::cout << " Chat server started on port 1337\n";

        while(true){
            auto socket = std::make_shared<tcp::socket>(io_context);
            acceptor.accept(*socket);
            std::thread(handle_client, socket).detach();
        }
    } catch (std::exception& e){
        std::cerr<< "Server error: " << e.what() << std::endl;
    }

    return 0;
}