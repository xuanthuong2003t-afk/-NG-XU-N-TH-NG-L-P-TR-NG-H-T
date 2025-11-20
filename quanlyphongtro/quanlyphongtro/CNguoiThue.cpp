#include "CNguoiThue.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <limits>

using namespace std;

// Constructor
CNguoiThue::CNguoiThue(string maNT, string ten, string cmnd, string sdt, string maP, string ngay, int soThang)
    : MaNguoiThue(maNT), Ten(ten), CMND(cmnd), SoDienThoai(sdt), MaPhong(maP), NgayThue(ngay), SoThangThue(soThang) {
}

// Getters
string CNguoiThue::getMaNguoiThue() const { return MaNguoiThue; }
string CNguoiThue::getMaPhong() const { return MaPhong; }
int CNguoiThue::getSoThangThue() const { return SoThangThue; }

// Nhập (MaPhong và MaNguoiThue được cung cấp từ bên ngoài)
void CNguoiThue::Nhap(const string& maPhongThue, const string& maNguoiThue) {
    MaPhong = maPhongThue;
    MaNguoiThue = maNguoiThue;

    cout << "  - Nhap Ten: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, Ten);
    cout << "  - Nhap CMND/CCCD: ";
    getline(cin, CMND);
    cout << "  - Nhap So Dien Thoai: ";
    getline(cin, SoDienThoai);
    cout << "  - Nhap Ngay Thue (dd/mm/yyyy): ";
    getline(cin, NgayThue);
    cout << "  - Nhap So Thang Thue: ";
    while (!(cin >> SoThangThue)) {
        cout << "  - Loi: Vui long nhap so: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Sửa (Không cho sửa MaNguoiThue và MaPhong)
void CNguoiThue::Sua() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "  - Nhap Ten moi (ENTER de bo qua): ";
    string tenMoi;
    getline(cin, tenMoi);
    if (!tenMoi.empty()) Ten = tenMoi;

    cout << "  - Nhap CMND/CCCD moi (ENTER de bo qua): ";
    string cmndMoi;
    getline(cin, cmndMoi);
    if (!cmndMoi.empty()) CMND = cmndMoi;

    cout << "  - Nhap So Dien Thoai moi (ENTER de bo qua): ";
    string sdtMoi;
    getline(cin, sdtMoi);
    if (!sdtMoi.empty()) SoDienThoai = sdtMoi;

    cout << "=> Cap nhat thong tin nguoi thue thanh cong!" << endl;
}

void CNguoiThue::Xuat() const {
    cout << "| " << setw(12) << left << MaNguoiThue
        << "| " << setw(20) << left << Ten
        << "| " << setw(10) << left << MaPhong
        << "| " << setw(15) << left << NgayThue
        << "| " << setw(10) << right << SoThangThue << " |" << endl;
}

float CNguoiThue::TinhTienPhong(float giaPhong) const {
    return giaPhong * SoThangThue;
}

// File I/O
string CNguoiThue::GhiDuLieu() const {
    return MaNguoiThue + "," + Ten + "," + CMND + "," + SoDienThoai + "," + MaPhong + "," + NgayThue + "," + to_string(SoThangThue);
}

void CNguoiThue::DocDuLieu(const vector<string>& data) {
    if (data.size() >= 7) {
        MaNguoiThue = data[0];
        Ten = data[1];
        CMND = data[2];
        SoDienThoai = data[3];
        MaPhong = data[4];
        NgayThue = data[5];
        try {
            SoThangThue = stoi(data[6]);
        }
        catch (const std::exception&) {
            SoThangThue = 0;
        }
    }
}