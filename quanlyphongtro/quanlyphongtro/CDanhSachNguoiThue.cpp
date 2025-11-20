#include "CDanhSachNguoiThue.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

// Hàm tiện ích nội bộ
vector<string> tachChuoiNguoi(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

CDanhSachNguoiThue::CDanhSachNguoiThue() : head(nullptr), tail(nullptr) {}

CDanhSachNguoiThue::~CDanhSachNguoiThue() {
    Clear();
}

void CDanhSachNguoiThue::Clear() {
    NodeNguoi* current = head;
    while (current != nullptr) {
        NodeNguoi* next = current->next;
        delete current->data; // Xóa đối tượng CNguoiThue
        delete current;       // Xóa node
        current = next;
    }
    head = tail = nullptr;
}

void CDanhSachNguoiThue::Them(CNguoiThue* n) {
    NodeNguoi* newNode = new NodeNguoi{ n, nullptr };
    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Xóa dựa trên Mã Người Thuê
bool CDanhSachNguoiThue::Xoa(const std::string& maNT) {
    NodeNguoi* current = head;
    NodeNguoi* prev = nullptr;

    while (current != nullptr && current->data->getMaNguoiThue() != maNT) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return false; // Không tìm thấy

    if (prev == nullptr) head = current->next;
    else prev->next = current->next;

    if (current == tail) tail = prev;

    delete current->data;
    delete current;
    return true;
}

// Xóa dựa trên Mã Phòng
bool CDanhSachNguoiThue::XoaTheoMaPhong(const std::string& maP) {
    NodeNguoi* current = head;
    NodeNguoi* prev = nullptr;

    while (current != nullptr && current->data->getMaPhong() != maP) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return false; // Không tìm thấy

    if (prev == nullptr) head = current->next;
    else prev->next = current->next;

    if (current == tail) tail = prev;

    delete current->data;
    delete current;
    return true;
}

bool CDanhSachNguoiThue::Sua(const std::string& maNT) {
    CNguoiThue* n = TimKiem(maNT);
    if (n) {
        cout << "\n--- Nhap Thong Tin Cap Nhat cho Nguoi Thue " << maNT << " ---" << endl;
        n->Sua();
        return true;
    }
    return false;
}

CNguoiThue* CDanhSachNguoiThue::TimKiem(const std::string& maNT) {
    NodeNguoi* current = head;
    while (current != nullptr) {
        if (current->data->getMaNguoiThue() == maNT) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

CNguoiThue* CDanhSachNguoiThue::TimKiemTheoMaPhong(const std::string& maP) {
    NodeNguoi* current = head;
    while (current != nullptr) {
        if (current->data->getMaPhong() == maP) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

void CDanhSachNguoiThue::XuatDanhSach() const {
    if (head == nullptr) {
        cout << "=> Danh sach nguoi thue hien dang TRONG." << endl;
        return;
    }
    cout << "\n--- DANH SACH NGUOI THUE ---\n";
    cout << "+------------+--------------------+----------+---------------+------------+" << endl;
    cout << "| Ma NT      | Ten                | Ma Phong | Ngay Thue     | So Thang   |" << endl;
    cout << "+------------+--------------------+----------+---------------+------------+" << endl;

    NodeNguoi* current = head;
    int count = 0;
    while (current != nullptr) {
        current->data->Xuat();
        current = current->next;
        count++;
    }

    cout << "+------------+--------------------+----------+---------------+------------+" << endl;
    cout << "TONG SO NGUOI THUE: " << count << endl;
}

void CDanhSachNguoiThue::LuuFile() const {
    ofstream outFile(TEN_FILE);
    if (!outFile.is_open()) {
        cerr << "LOI: Khong mo duoc file " << TEN_FILE << " de ghi!" << endl;
        return;
    }

    NodeNguoi* current = head;
    while (current != nullptr) {
        outFile << current->data->GhiDuLieu() << endl;
        current = current->next;
    }
    outFile.close();
}

void CDanhSachNguoiThue::DocFile() {
    ifstream inFile(TEN_FILE);
    if (!inFile.is_open()) {
        // cout << "Khong tim thay file " << TEN_FILE << ", bat dau voi danh sach rong." << endl;
        return;
    }

    Clear(); // Xóa dữ liệu cũ
    string line;
    while (getline(inFile, line)) {
        vector<string> data = tachChuoiNguoi(line, ',');
        if (data.size() >= 7) {
            CNguoiThue* n = new CNguoiThue(); // Tạo đối tượng mới
            n->DocDuLieu(data);
            Them(n); // Thêm vào danh sách liên kết
        }
    }
    inFile.close();
}