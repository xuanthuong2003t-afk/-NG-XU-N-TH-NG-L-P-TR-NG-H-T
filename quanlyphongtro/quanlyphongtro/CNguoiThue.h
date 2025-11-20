#pragma once
#ifndef CNGUOITHUE_H
#define CNGUOITHUE_H

#include <string>
#include <iostream>
#include <vector>

class CNguoiThue {
private:
    std::string MaNguoiThue;
    std::string Ten;
    std::string CMND;
    std::string SoDienThoai;
    std::string MaPhong;
    std::string NgayThue;
    int SoThangThue;

public:
    // Constructor
    CNguoiThue(std::string maNT = "", std::string ten = "", std::string cmnd = "", std::string sdt = "", std::string maP = "", std::string ngay = "", int soThang = 0);

    // Getters
    std::string getMaNguoiThue() const;
    std::string getMaPhong() const;
    int getSoThangThue() const;

    // Nghiệp vụ
    void Nhap(const std::string& maPhongThue, const std::string& maNguoiThue);
    void Sua();
    void Xuat() const;
    float TinhTienPhong(float giaPhong) const;

    // File I/O
    std::string GhiDuLieu() const;
    void DocDuLieu(const std::vector<std::string>& data);
};

#endif // CNGUOITHUE_H#pragma once
