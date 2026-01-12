#include "Menu.h"
#include <iostream>
#include <locale>

int main() {
    // Set locale for Vietnamese characters (if supported)
    try {
        std::locale::global(std::locale(""));
    } catch (...) {
        // Ignore if locale setting fails
    }
    
    std::cout << "╔══════════════════════════════════════════════════╗\n";
    std::cout << "║   CHÀO MỪNG ĐẾN VỚI HỆ THỐNG NGÂN HÀNG           ║\n";
    std::cout << "║   BANKING ACCOUNT MANAGEMENT SYSTEM              ║\n";
    std::cout << "╚══════════════════════════════════════════════════╝\n";
    std::cout << "\nĐang khởi động hệ thống...\n";
    
    Menu menu;
    menu.run();
    
    return 0;
}
