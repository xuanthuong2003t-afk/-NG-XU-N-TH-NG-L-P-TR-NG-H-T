#include "CDanhSachPhong.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

// Hàm tiện ích nội bộ để tách chuỗi
vector<string> tachChuoiPhong(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

CDanhSachPhong::CDanhSachPhong() : head(nullptr), tail(nullptr) {}

CDanhSachPhong::~CDanhSachPhong() {
    Clear();
}

void CDanhSachPhong::Clear() {
    NodePhong* current = head;
    while (current != nullptr) {
        NodePhong* next = current->next;
        delete current->data; // Xóa đối tượng CPhong
        delete current;       // Xóa node
        current = next;
    }
    head = tail = nullptr;
}

void CDanhSachPhong::Them(CPhong* p) {
    NodePhong* newNode = new NodePhong{ p, nullptr };
    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

bool CDanhSachPhong::Xoa(const std::string& ma) {
    NodePhong* current = head;
    NodePhong* prev = nullptr;

    while (current != nullptr && current->data->getMaPhong() != ma) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return false; // Không tìm thấy

    if (prev == nullptr) { // Xóa node đầu
        head = current->next;
    }
    else {
        prev->next = current->next;
    }

    if (current == tail) { // Cập nhật tail nếu xóa node cuối
        tail = prev;
    }

    delete current->data; // Quan trọng: Hủy đối tượng CPhong
    delete current;       // Quan trọng: Hủy node
    return true;
}

bool CDanhSachPhong::Sua(const std::string& ma) {
    CPhong* p = TimKiem(ma);
    if (p) {
        cout << "\n--- Nhap Thong Tin Cap Nhat cho Phong " << ma << " ---" << endl;
        p->Sua();
        return true;
    }
    return false;
}

CPhong* CDanhSachPhong::TimKiem(const std::string& ma) {
    NodePhong* current = head;
    while (current != nullptr) {
        if (current->data->getMaPhong() == ma) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr; // Không tìm thấy
}

void CDanhSachPhong::XuatDanhSach() const {
    if (head == nullptr) {
        cout << "=> Danh sach phong hien dang TRONG." << endl;
        return;
    }
    cout << "\n--- DANH SACH PHONG TRO ---\n";
    cout << "+----------+---------------+---------------+----------+" << endl;
    cout << "| Ma Phong | Loai Phong    | Gia Phong(VND)| Trang Thai |" << endl;
    cout << "+----------+---------------+---------------+----------+" << endl;

    NodePhong* current = head;
    int count = 0;
    while (current != nullptr) {
        current->data->Xuat();
        current = current->next;
        count++;
    }

    cout << "+----------+---------------+---------------+----------+" << endl;
    cout << "TONG SO PHONG: " << count << endl;
}

float CDanhSachPhong::TinhTongThu() const {
    float tongThu = 0;
    NodePhong* current = head;
    while (current != nullptr) {
        if (current->data->KiemTraDangThue()) {
            tongThu += current->data->getGiaPhong();
        }
        current = current->next;
    }
    return tongThu;
}

void CDanhSachPhong::LuuFile() const {
    ofstream outFile(TEN_FILE);
    if (!outFile.is_open()) {
        cerr << "LOI: Khong mo duoc file " << TEN_FILE << " de ghi!" << endl;
        return;
    }

    NodePhong* current = head;
    while (current != nullptr) {
        outFile << current->data->GhiDuLieu() << endl;
        current = current->next;
    }
    outFile.close();
}

void CDanhSachPhong::DocFile() {
    ifstream inFile(TEN_FILE);
    if (!inFile.is_open()) {
        // cout << "Khong tim thay file " << TEN_FILE << ", bat dau voi danh sach rong." << endl;
        return;
    }

    Clear(); // Xóa dữ liệu cũ trước khi đọc
    string line;
    while (getline(inFile, line)) {
        vector<string> data = tachChuoiPhong(line, ',');
        if (data.size() >= 4) {
            CPhong* p = new CPhong(); // Tạo đối tượng CPhong mới
            p->DocDuLieu(data);
            Them(p); // Thêm vào danh sách liên kết
        }
    }
    inFile.close();
}