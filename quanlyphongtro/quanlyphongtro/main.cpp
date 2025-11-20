#include "CQuanLy.h"
#include <iostream>

using namespace std;

int main() {
    // Thiết lập locale tiếng Việt cho console (tùy chọn)
    // (Có thể cần nếu hiển thị dấu bị lỗi)

    CQuanLy heThongQuanLy;

    // 1. Đọc dữ liệu từ file khi khởi động
    cout << "Dang tai du lieu..." << endl;
    heThongQuanLy.DocDanhSach();

    // 2. Chạy menu chính
    heThongQuanLy.MenuChinh();

    return 0;
}