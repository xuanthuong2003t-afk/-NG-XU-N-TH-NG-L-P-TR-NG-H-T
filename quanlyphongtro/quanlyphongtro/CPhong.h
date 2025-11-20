#pragma once
#ifndef CPHONG_H
#define CPHONG_H

#include <string>
#include <iostream>
#include <vector> // <--- THÊM DÒNG NÀY

class CPhong {
private:
    std::string MaPhong;
    std::string LoaiPhong;
    float GiaPhong;
    bool TrangThai; // true: Đã thuê, false: Trống
public:
    // Constructor
    CPhong(std::string ma = "", std::string loai = "", float gia = 0.0, bool trangThai = false);

    // Getters & Setters
    std::string getMaPhong() const;
    float getGiaPhong() const;
    bool getTrangThai() const;
    void setTrangThai(bool tt);

    // Nghiệp vụ
    void Nhap();
    void Sua();
    void Xuat() const;
    bool KiemTraDangThue() const;
    void ThuePhong();
    void TraPhong();

    // File I/O
    std::string GhiDuLieu() const;
    // Dòng 35 (đã chính xác)
    void DocDuLieu(const std::vector<std::string>& data);
};

#endif // CPHONG_H