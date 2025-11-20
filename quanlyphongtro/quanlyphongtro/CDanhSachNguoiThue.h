#pragma once
#ifndef CDANHSACHNGUOITHUE_H
#define CDANHSACHNGUOITHUE_H

#include "CNguoiThue.h"
#include <vector>

// Ð?nh ngh?a c?u trúc Node cho danh sách liên k?t
struct NodeNguoi {
    CNguoiThue* data;
    NodeNguoi* next;
};

class CDanhSachNguoiThue {
private:
    NodeNguoi* head;
    NodeNguoi* tail;
    const std::string TEN_FILE = "nguoithue.txt";

public:
    CDanhSachNguoiThue();
    ~CDanhSachNguoiThue();

    void Clear(); // Xóa t?t c? các node
    void Them(CNguoiThue* n);
    bool Xoa(const std::string& maNT); // Xóa theo M? Ngý?i Thuê
    bool XoaTheoMaPhong(const std::string& maP); // Xóa theo M? Ph?ng
    bool Sua(const std::string& maNT);
    CNguoiThue* TimKiem(const std::string& maNT); // T?m theo M? Ngý?i Thuê
    CNguoiThue* TimKiemTheoMaPhong(const std::string& maP); // T?m theo M? Ph?ng
    void XuatDanhSach() const;

    // File I/O
    void LuuFile() const;
    void DocFile();
};

#endif // CDANHSACHNGUOITHUE_H#pragma once
