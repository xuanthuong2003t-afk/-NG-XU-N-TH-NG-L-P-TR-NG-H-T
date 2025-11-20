#pragma once
#pragma once
#ifndef CQUANLY_H
#define CQUANLY_H

#include "CDanhSachPhong.h"
#include "CDanhSachNguoiThue.h"

// Đổi tên CQuanLyPhongTro thành CQuanLy để ngắn gọn
class CQuanLy {
private:
    CDanhSachPhong dsPhong;
    CDanhSachNguoiThue dsNguoiThue;

    // Các hàm menu con
    void MenuQuanLyPhong();
    void MenuQuanLyNguoiThue();
    void MenuThueTraPhong();

    // Các hàm nghiệp vụ
    void ThemPhong();
    void XoaPhong();
    void SuaPhong();
    void TimPhong();
    void HienThiDanhSachPhong();

    void ThemNguoiThue(); // Thêm mới (khác với ThuePhong)
    void XoaNguoiThue();
    void SuaNguoiThue();
    void TimNguoiThue();
    void HienThiDanhSachNguoiThue();

    void ThuePhong();
    void TraPhong();
    void ThongKeTongThu();

public:
    CQuanLy();
    ~CQuanLy();

    void LuuDanhSach() const;
    void DocDanhSach();
    void MenuChinh();
};

#endif // CQUANLY_H