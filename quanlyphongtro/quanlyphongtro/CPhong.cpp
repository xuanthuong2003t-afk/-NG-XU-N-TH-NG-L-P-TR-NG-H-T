#include "CPhong.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <vector>

using namespace std;

// Constructor
CPhong::CPhong(string ma, string loai, float gia, bool trangThai)
    : MaPhong(ma), LoaiPhong(loai), GiaPhong(gia), TrangThai(trangThai) {
}

// Getters & Setters
string CPhong::getMaPhong() const { return MaPhong; }
float CPhong::getGiaPhong() const { return GiaPhong; }
bool CPhong::getTrangThai() const { return TrangThai; }
void CPhong::setTrangThai(bool tt) { TrangThai = tt; }

// Nhập mới (không cho nhập MaPhong vì MaPhong là khóa chính, nên nhập riêng)
void CPhong::Nhap() {
    cout << "  - Nhap Loai Phong: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, LoaiPhong);
    cout << "  - Nhap Gia Phong (VND): ";
    while (!(cin >> GiaPhong)) {
        cout << "  - Loi: Vui long nhap so: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    TrangThai = false; // Mới thêm luôn là trống
}

// Sửa (không cho sửa MaPhong)
void CPhong::Sua() {
    cout << "  - Nhap Loai Phong moi (ENTER de bo qua): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string loaiMoi;
    getline(cin, loaiMoi);
    if (!loaiMoi.empty()) {
        LoaiPhong = loaiMoi;
    }

    cout << "  - Nhap Gia Phong moi (nhap -1 de bo qua): ";
    float giaMoi;
    while (!(cin >> giaMoi)) {
        cout << "  - Loi: Vui long nhap so: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (giaMoi != -1) {
        GiaPhong = giaMoi;
    }
    cout << "=> Cap nhat thong tin phong thanh cong!" << endl;
}


void CPhong::Xuat() const {
    cout << "| " << setw(10) << left << MaPhong
        << "| " << setw(15) << left << LoaiPhong
        << "| " << setw(15) << right << fixed << setprecision(0) << GiaPhong
        << "| " << setw(10) << left << (TrangThai ? "DANG THUE" : "TRONG") << " |" << endl;
}

bool CPhong::KiemTraDangThue() const { return TrangThai; }
void CPhong::ThuePhong() { TrangThai = true; }
void CPhong::TraPhong() { TrangThai = false; }

// File I/O
string CPhong::GhiDuLieu() const {
    return MaPhong + "," + LoaiPhong + "," + to_string(GiaPhong) + "," + (TrangThai ? "1" : "0");
}

void CPhong::DocDuLieu(const vector<string>& data) {
    if (data.size() >= 4) {
        MaPhong = data[0];
        LoaiPhong = data[1];
        try {
            GiaPhong = stof(data[2]);
            TrangThai = (data[3] == "1");
        }
        catch (const std::exception&) {
            GiaPhong = 0.0;
            TrangThai = false;
        }
    }
}