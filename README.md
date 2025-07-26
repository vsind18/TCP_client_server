# 💬 TCP Chat Client-Server (C++ & Boost.Asio)

## 📌 Giới thiệu

Đây là một dự án C++ sử dụng thư viện Boost.Asio để xây dựng một hệ thống **chat client-server** hoạt động trên giao thức TCP.

- Hỗ trợ **nhiều client kết nối đồng thời**.
- Mỗi client được định danh bằng một **nickname** khi kết nối.
- Client có thể gửi tin nhắn đến **tất cả các client khác** thông qua **server**.
- Server chỉ đóng vai trò là **trung gian chuyển tiếp** tin nhắn.

---

## ⚙️ Cách hoạt động

### 1. Server
- Mở cổng TCP (`1337` mặc định) và chấp nhận nhiều kết nối client.
- Mỗi client được xử lý trên một **thread riêng biệt**.
- Lưu nickname và socket của từng client.
- Khi nhận được tin nhắn từ một client, server sẽ:
  - Gửi lại tin nhắn đó cho **tất cả các client khác** (broadcast).
  - Gắn tên người gửi vào tin nhắn (`[nickname]: message`).
- ❌ Server **không gửi tin nhắn chủ động** (không có input từ người quản trị).

### 2. Client
- Kết nối đến địa chỉ server (localhost hoặc IP).
- Gửi nickname ngay sau khi kết nối.
- Chạy 2 luồng:
  - Một luồng để nhập tin nhắn từ người dùng.
  - Một luồng để nhận và in tin nhắn từ server.

---

---

## 🔁 Workflow phát triển

### Giai đoạn 1: Simple TCP Client & Server

- Tạo server lắng nghe trên cổng và chấp nhận 1 kết nối.
- Tạo client kết nối đến server.
- Gửi và nhận chuỗi văn bản đơn giản (1-1).

### Giai đoạn 2: Nâng cấp thành Chat App

- Từ server đơn: xử lý nhiều client bằng `std::thread`.
- Lưu socket + nickname.
- Khi 1 client gửi tin nhắn:
  - Server nhận.
  - Server chuyển tiếp tới các client khác.
- Client vừa gửi vừa nhận qua 2 luồng riêng biệt.

---

## 🚀 Cách sử dụng

### Build

> Yêu cầu: Boost.Asio, CMake , C++

```bash
cd TCP_client_server/build
make 
./server/server.exe
./client/client.exe
