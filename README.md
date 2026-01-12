# Hệ Thống Quản Lý Tài Khoản Ngân Hàng
# Banking Account Management System

Hệ thống quản lý tài khoản ngân hàng được xây dựng bằng C++17 với giao diện dòng lệnh (console).

## Tính năng

### Quản lý người dùng
- ✅ Đăng ký tài khoản người dùng mới
- ✅ Đăng nhập / Đăng xuất
- ✅ Đổi mật khẩu
- ✅ Xem thông tin cá nhân

### Quản lý tài khoản ngân hàng
- ✅ Tạo tài khoản mới (Tiết kiệm, Thanh toán, Tiền gửi có kỳ hạn)
- ✅ Xem danh sách tài khoản
- ✅ Xem số dư
- ✅ Đóng tài khoản

### Giao dịch
- ✅ Gửi tiền
- ✅ Rút tiền
- ✅ Chuyển khoản
- ✅ Xem lịch sử giao dịch

## Yêu cầu hệ thống

- C++17 compiler (g++ 7.0+ hoặc clang++ 5.0+)
- CMake 3.10+

## Cài đặt và chạy

### Bước 1: Clone hoặc tải mã nguồn

```bash
cd /home/manhbao/Documents/BankingAccount
```

### Bước 2: Build dự án

```bash
mkdir -p build
cd build
cmake ..
make
```

### Bước 3: Chạy chương trình

```bash
./BankingSystem
```

hoặc từ thư mục gốc:

```bash
./bin/BankingSystem
```

## Cấu trúc thư mục

```
BankingAccount/
├── CMakeLists.txt          # Cấu hình build
├── README.md               # Tài liệu hướng dẫn
├── include/                # Header files
│   ├── models/             # Data models
│   ├── services/           # Business logic
│   ├── controllers/        # UI controllers
│   ├── utils/              # Utilities
│   └── Menu.h
├── src/                    # Source files
│   ├── main.cpp
│   ├── Menu.cpp
│   ├── models/
│   ├── services/
│   ├── controllers/
│   └── utils/
├── data/                   # Data storage (text files)
│   ├── users.txt
│   ├── accounts.txt
│   └── transactions.txt
└── bin/                    # Compiled binary
```

## Loại tài khoản

| Loại | Mô tả | Lãi suất |
|------|-------|----------|
| SAVINGS | Tài khoản tiết kiệm | 0.5% /năm |
| CHECKING | Tài khoản thanh toán | 0.1% /năm |
| FIXED_DEPOSIT | Tiền gửi có kỳ hạn | 1.5% /năm |

## Lưu ý bảo mật

- Mật khẩu được hash trước khi lưu trữ
- Dữ liệu được lưu trong các file text trong thư mục `data/`
- Đây là dự án demo, không sử dụng cho production

## Tác giả

Được tạo bởi hệ thống tự động.

## Giấy phép

MIT License
