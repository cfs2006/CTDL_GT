# 📘 Smart Dictionary (C++ Hash Table & Python AI)

> **Từ điển Anh - Việt thông minh sử dụng Cấu trúc dữ liệu Bảng băm (Hash Table) kết hợp với Python để tra cứu Online thời gian thực.**

## 🌟 Giới thiệu
Dự án này là một ứng dụng từ điển lai (Hybrid), kết hợp sức mạnh quản lý dữ liệu tốc độ cao của **C++** và khả năng xử lý ngôn ngữ tự nhiên của **Python**.

Khác với các từ điển tĩnh thông thường (phải nạp sẵn dữ liệu), ứng dụng này hoạt động theo cơ chế **"Vừa tra vừa học" (Caching mechanism)**:
1.  Tìm từ trong bộ nhớ nội bộ (Hash Table).
2.  Nếu không thấy, tự động gọi **Python** để tra cứu từ Google Translate.
3.  Lưu kết quả vào bộ nhớ để lần sau truy xuất tức thì (O(1)).

## 🚀 Tính năng nổi bật
* **Cấu trúc dữ liệu:** Sử dụng **Hash Table** với phương pháp giải quyết xung đột bằng **Linked List (Chaining)**.
* **Online Integration:** Tích hợp Python script để kiểm tra từ vựng và lấy nghĩa tiếng Việt từ Internet.
* **Smart Validation:** Tự động phát hiện từ vô nghĩa hoặc sai chính tả (ví dụ: "asdfg") và cảnh báo người dùng.
* **Persistent Storage:** Tự động lưu dữ liệu ra file (`dulieu.txt`) khi thoát và nạp lại khi mở (File I/O).
* **CRUD Operations:** Hỗ trợ đầy đủ Thêm, Xem, Sửa (Rename có kiểm tra), Xóa.

## 🛠️ Công nghệ sử dụng
* **Ngôn ngữ chính:** C++ (Quản lý bộ nhớ, Cấu trúc dữ liệu, Logic chính).
* **Ngôn ngữ phụ:** Python 3.x (API Dịch thuật, Xử lý chuỗi).
* **Thư viện Python:** `deep-translator` (Google Translate API wrapper).
* **Kỹ thuật giao tiếp:** IPC (Inter-Process Communication) thông qua `pipe` (_popen).

## 📂 Cấu trúc dự án
```text
SmartDictionary/
│
├── main.cpp          # Chương trình chính (Menu, Điều hướng)
├── Dictionary.h      # Khai báo Struct Node, Hash Table và các hàm xử lý dữ liệu
├── Dictionary.cpp    # Cài đặt chi tiết các thuật toán (Add, Delete, Search...)
├── Internet.h        # Khai báo hàm giao tiếp với Python
├── Internet.cpp      # Cài đặt hàm gọi lệnh hệ thống (System Call)
├── dich_tu.py        # Script Python xử lý dịch và kiểm tra từ vựng
├── dulieu.txt        # Database lưu trữ từ vựng (Tự sinh ra)
└── README.md         # Tài liệu dự án
⚙️ Cài đặt và Chạy
1. Yêu cầu hệ thống
Trình biên dịch C++ (G++ hoặc Visual Studio).

Python (Phiên bản 3.x trở lên).

2. Cài đặt thư viện Python
Mở Terminal/CMD và chạy lệnh sau để cài thư viện dịch thuật:

Bash

pip install deep-translator
3. Biên dịch code C++
Nếu dùng VS Code (Terminal):

Bash

g++ main.cpp Dictionary.cpp Internet.cpp -o TuDien
Nếu dùng Visual Studio:

Tạo Empty Project.

Add tất cả các file .cpp và .h vào dự án.

Bấm F5 để chạy.

4. Chạy ứng dụng
Bash

.\TuDien.exe
📸 Demo Logic
Kịch bản Tra cứu:

User nhập: House

Hệ thống kiểm tra Local RAM -> Không có.

Hệ thống gọi Python -> Trả về: Căn nhà.

Hệ thống in ra màn hình và lưu House vào Hash Table.

Lần sau User nhập: House -> Hệ thống lấy từ RAM ngay lập tức.

👨‍💻 Tác giả
Võ Thanh Phương

Sinh viên: Đại học Giao thông Vận tải TP.HCM (UTH)

Chuyên ngành: Mạng máy tính & Truyền thông dữ liệu

Dự án được thực hiện nhằm mục đích học tập môn Cấu trúc dữ liệu & Giải thuật.
