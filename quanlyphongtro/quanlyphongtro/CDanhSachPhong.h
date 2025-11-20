#pragma once
#ifndef CDANHSACHPHONG_H
#define CDANHSACHPHONG_H

#include "CPhong.h"
#include <vector>

// Định nghĩa cấu trúc Node cho danh sách liên kết
struct NodePhong {
    CPhong* data;
    NodePhong* next;
};

class CDanhSachPhong {
private:
    NodePhong* head;
    NodePhong* tail;
    const std::string TEN_FILE = "phong.txt";

public:
    CDanhSachPhong();
    ~CDanhSachPhong();

    void Clear(); // Xóa tất cả các node để tránh rò rỉ bộ nhớ
    void Them(CPhong* p);
    bool Xoa(const std::string& ma);
    bool Sua(const std::string& ma);
    CPhong* TimKiem(const std::string& ma);
    void XuatDanhSach() const;
    float TinhTongThu() const;

    // File I/O
    void LuuFile() const;
    void DocFile();
};

#endif // CDANHSACHPHONG_H#pragma once
