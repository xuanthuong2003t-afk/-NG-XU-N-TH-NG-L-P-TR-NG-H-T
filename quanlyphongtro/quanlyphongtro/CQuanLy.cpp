#include "CQuanLy.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <conio.h> // cho _getch()
#include <cstdlib> // cho system("cls")

using namespace std;

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// --- HÀM TRỢ GIÚP NHẬP LIỆU ---
int GetMenuChoice(int min, int max) {
    int choice;
    while (true) {
        cout << "Nhap lua chon cua ban (" << min << "-" << max << "): ";
        if (cin >> choice) {
            if (choice >= min && choice <= max) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa buffer
                return choice;
            }
            else {
                cout << "=> Lua chon khong hop le. Vui long nhap trong khoang " << min << " den " << max << "." << endl;
            }
        }
        else {
            cout << "=> Loi: Vui long nhap mot so." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void PauseScreen() {
    cout << "\nNhan phim bat ky de tiep tuc...";
    _getch();
}

// --- IMPLEMENTATION CQUANLY ---

CQuanLy::CQuanLy() {
    // Constructor
}

CQuanLy::~CQuanLy() {
    // Destructor tự động gọi hàm hủy của dsPhong và dsNguoiThue
    // đã được định nghĩa để xóa các con trỏ (RAII)
}

void CQuanLy::LuuDanhSach() const {
    dsPhong.LuuFile();
    dsNguoiThue.LuuFile();
}

void CQuanLy::DocDanhSach() {
    dsPhong.DocFile();
    dsNguoiThue.DocFile();
}

// --- NGHIỆP VỤ PHÒNG ---

void CQuanLy::ThemPhong() {
    cout << "\n--- THEM PHONG MOI ---" << endl;
    string maPhong;
    cout << "  - Nhap Ma Phong: ";
    cin >> maPhong;

    if (dsPhong.TimKiem(maPhong)) {
        cout << "=> LOI: Ma Phong '" << maPhong << "' da ton tai." << endl;
        return;
    }

    CPhong* p = new CPhong(); // Tạo đối tượng mới
    p->Nhap(); // Nhập thông tin còn lại
    p->setTrangThai(false); // Đảm bảo trạng thái là trống

    // Cần set MaPhong cho đối tượng p
    // (Thiết kế CPhong::Nhap() không bao gồm MaPhong, nên ta phải làm thủ công)
    // Tốt hơn là sửa CPhong::Nhap và CPhong::CPhong
    // Tạm thời chấp nhận thiết kế này:
    delete p; // Hủy đối tượng vừa tạo
    p = new CPhong(maPhong, "", 0.0, false); // Tạo lại với mã
    p->Nhap(); // Nhập lại thông tin (hơi bất tiện)

    dsPhong.Them(p);
    cout << "=> Them phong '" << maPhong << "' thanh cong!" << endl;
    LuuDanhSach();
}

void CQuanLy::XoaPhong() {
    cout << "\n--- XOA PHONG ---" << endl;
    string maPhong;
    cout << "  - Nhap Ma Phong can xoa: ";
    cin >> maPhong;

    CPhong* p = dsPhong.TimKiem(maPhong);
    if (!p) {
        cout << "=> LOI: Khong tim thay phong '" << maPhong << "'." << endl;
        return;
    }

    if (p->KiemTraDangThue()) {
        cout << "=> LOI: Phong '" << maPhong << "' dang co nguoi thue. Khong a xoa." << endl;
        return;
    }

    if (dsPhong.Xoa(maPhong)) {
        cout << "=> Xoa phong '" << maPhong << "' thanh cong!" << endl;
        LuuDanhSach();
    }
    else {
        cout << "=> Xoa that bai." << endl;
    }
}

void CQuanLy::SuaPhong() {
    cout << "\n--- SUA THONG TIN PHONG ---" << endl;
    string maPhong;
    cout << "  - Nhap Ma Phong can sua: ";
    cin >> maPhong;

    if (dsPhong.Sua(maPhong)) {
        LuuDanhSach();
    }
    else {
        cout << "=> LOI: Khong tim thay phong '" << maPhong << "'." << endl;
    }
}

void CQuanLy::TimPhong() {
    cout << "\n--- TIM KIEM PHONG ---" << endl;
    string maPhong;
    cout << "  - Nhap Ma Phong can tim: ";
    cin >> maPhong;

    CPhong* p = dsPhong.TimKiem(maPhong);
    if (p) {
        cout << "=> Tim thay thong tin phong:" << endl;
        cout << "+----------+---------------+---------------+----------+" << endl;
        p->Xuat();
        cout << "+----------+---------------+---------------+----------+" << endl;
    }
    else {
        cout << "=> Khong tim thay phong '" << maPhong << "'." << endl;
    }
}

void CQuanLy::HienThiDanhSachPhong() {
    dsPhong.XuatDanhSach();
}

// --- NGHIỆP VỤ NGƯỜI THUÊ ---

void CQuanLy::ThemNguoiThue() {
    cout << "\n--- THEM NGUOI THUE (Khong kem thue phong) ---" << endl;
    cout << "=> LUU Y: Chuc nang nay chi them nguoi thue vao he thong." << endl;
    cout << "=> De thue phong, vui long su dung chuc nang 'Thue Phong'." << endl;

    string maNT;
    cout << "  - Nhap Ma Nguoi Thue: ";
    cin >> maNT;

    if (dsNguoiThue.TimKiem(maNT)) {
        cout << "=> LOI: Ma Nguoi Thue '" << maNT << "' da ton tai." << endl;
        return;
    }

    // Tạo đối tượng mới và nhập
    CNguoiThue* n = new CNguoiThue();
    // Mã phòng = "NULL" vì chưa thuê
    n->Nhap("CHUA THUE", maNT);

    dsNguoiThue.Them(n);
    cout << "=> Them nguoi thue '" << maNT << "' thanh cong!" << endl;
    LuuDanhSach();
}

void CQuanLy::XoaNguoiThue() {
    cout << "\n--- XOA NGUOI THUE ---" << endl;
    string maNT;
    cout << "  - Nhap Ma Nguoi Thue can xoa: ";
    cin >> maNT;

    CNguoiThue* n = dsNguoiThue.TimKiem(maNT);
    if (!n) {
        cout << "=> LOI: Khong tim thay nguoi thue '" << maNT << "'." << endl;
        return;
    }

    if (n->getMaPhong() != "CHUA THUE") {
        cout << "=> LOI: Nguoi thue '" << maNT << "' dang thue phong '" << n->getMaPhong() << "'." << endl;
        cout << "=> Vui long 'Tra Phong' truoc khi xoa." << endl;
        return;
    }

    if (dsNguoiThue.Xoa(maNT)) {
        cout << "=> Xoa nguoi thue '" << maNT << "' thanh cong!" << endl;
        LuuDanhSach();
    }
    else {
        cout << "=> Xoa that bai." << endl;
    }
}

void CQuanLy::SuaNguoiThue() {
    cout << "\n--- SUA THONG TIN NGUOI THUE ---" << endl;
    string maNT;
    cout << "  - Nhap Ma Nguoi Thue can sua: ";
    cin >> maNT;

    if (dsNguoiThue.Sua(maNT)) {
        LuuDanhSach();
    }
    else {
        cout << "=> LOI: Khong tim thay nguoi thue '" << maNT << "'." << endl;
    }
}

void CQuanLy::TimNguoiThue() {
    cout << "\n--- TIM KIEM NGUOI THUE ---" << endl;
    string maNT;
    cout << "  - Nhap Ma Nguoi Thue can tim: ";
    cin >> maNT;

    CNguoiThue* n = dsNguoiThue.TimKiem(maNT);
    if (n) {
        cout << "=> Tim thay thong tin nguoi thue:" << endl;
        cout << "+------------+--------------------+----------+---------------+------------+" << endl;
        n->Xuat();
        cout << "+------------+--------------------+----------+---------------+------------+" << endl;
    }
    else {
        cout << "=> Khong tim thay nguoi thue '" << maNT << "'." << endl;
    }
}

void CQuanLy::HienThiDanhSachNguoiThue() {
    dsNguoiThue.XuatDanhSach();
}

// --- NGHIỆP VỤ THUÊ/TRẢ ---

void CQuanLy::ThuePhong() {
    cout << "\n--- THUE PHONG ---" << endl;

    // Bước 1: Chọn phòng
    string maPhong;
    cout << "  - Nhap Ma Phong muon thue: ";
    cin >> maPhong;

    CPhong* p = dsPhong.TimKiem(maPhong);
    if (!p) {
        cout << "=> LOI: Khong tim thay phong '" << maPhong << "'." << endl;
        return;
    }
    if (p->KiemTraDangThue()) {
        cout << "=> LOI: Phong '" << maPhong << "' da co nguoi thue." << endl;
        return;
    }

    // Bước 2: Nhập thông tin người thuê
    string maNT;
    cout << "  - Nhap Ma Nguoi Thue: ";
    cin >> maNT;

    if (dsNguoiThue.TimKiem(maNT)) {
        cout << "=> LOI: Ma Nguoi Thue '" << maNT << "' da ton tai." << endl;
        cout << "=> Neu nguoi thue da co, he thong se tu dong cap nhat." << endl;
        // Tạm thời: Yêu cầu mã khác
        return;
    }

    // (Logic phức tạp: nếu người thuê đã có -> chỉ cập nhật MaPhong)
    // (Logic đơn giản: tạo người thuê mới)

    CNguoiThue* n = new CNguoiThue();
    n->Nhap(maPhong, maNT); // Nhập thông tin

    // Bước 3: Cập nhật
    dsNguoiThue.Them(n);
    p->ThuePhong();

    cout << "=> Thue phong '" << maPhong << "' cho nguoi thue '" << maNT << "' thanh cong!" << endl;
    LuuDanhSach();
}

void CQuanLy::TraPhong() {
    cout << "\n--- TRA PHONG ---" << endl;

    // Bước 1: Chọn phòng
    string maPhong;
    cout << "  - Nhap Ma Phong muon tra: ";
    cin >> maPhong;

    CPhong* p = dsPhong.TimKiem(maPhong);
    if (!p) {
        cout << "=> LOI: Khong tim thay phong '" << maPhong << "'." << endl;
        return;
    }
    if (!p->KiemTraDangThue()) {
        cout << "=> LOI: Phong '" << maPhong << "' dang trong. Khong can tra." << endl;
        return;
    }

    // Bước 2: Tìm người thuê
    CNguoiThue* n = dsNguoiThue.TimKiemTheoMaPhong(maPhong);
    if (!n) {
        cout << "=> LOI DU LIEU: Phong dang thue nhung khong tim thay nguoi thue!" << endl;
        // Vẫn cho trả phòng
        p->TraPhong();
        LuuDanhSach();
        cout << "=> Da cap nhat trang thai phong thanh TRONG." << endl;
        return;
    }

    // Bước 3: Tính tiền và xác nhận
    cout << "\n--- THONG TIN TRA PHONG ---" << endl;
    cout << "  - Nguoi thue: " << n->getMaNguoiThue() << endl;
    cout << "  - Ma phong: " << n->getMaPhong() << endl;
    cout << "  - So thang thue: " << n->getSoThangThue() << endl;
    cout << "  - Gia phong (1 thang): " << fixed << setprecision(0) << p->getGiaPhong() << " VND" << endl;
    float tongTien = n->TinhTienPhong(p->getGiaPhong());
    cout << "  --------------------------------" << endl;
    cout << "  - TONG TIEN THANH TOAN: " << tongTien << " VND" << endl;
    cout << "\n=> Tra phong thanh cong!" << endl;

    // Bước 4: Cập nhật hệ thống
    p->TraPhong(); // Cập nhật phòng
    dsNguoiThue.XoaTheoMaPhong(maPhong); // Xóa người thuê khỏi danh sách

    LuuDanhSach();
}

void CQuanLy::ThongKeTongThu() {
    cout << "\n--- THONG KE DOANH THU (DU KIEN HANG THANG) ---" << endl;
    float tongThu = dsPhong.TinhTongThu();
    cout << "=> Tong doanh thu du kien tu cac phong dang thue: " << fixed << setprecision(0) << tongThu << " VND" << endl;
}

// --- CÁC MENU ---

void CQuanLy::MenuChinh() {
    int choice;
    do {
        system(CLEAR_SCREEN);
        cout << "==========================================" << endl;
        cout << "        QUAN LY NHA TRO (LINKED LIST)     " << endl;
        cout << "==========================================" << endl;
        cout << "1. Quan Ly Phong" << endl;
        cout << "2. Quan Ly Nguoi Thue" << endl;
        cout << "3. Thue / Tra Phong" << endl;
        cout << "4. Thong Ke Doanh Thu" << endl;
        cout << "0. Thoat (Tu dong luu)" << endl;
        cout << "------------------------------------------" << endl;
        choice = GetMenuChoice(0, 4);

        switch (choice) {
        case 1: MenuQuanLyPhong(); break;
        case 2: MenuQuanLyNguoiThue(); break;
        case 3: MenuThueTraPhong(); break;
        case 4:
            ThongKeTongThu();
            PauseScreen();
            break;
        case 0:
            cout << "\nDang luu du lieu truoc khi thoat..." << endl;
            LuuDanhSach();
            cout << "Tam biet!" << endl;
            break;
        }
    } while (choice != 0);
}

void CQuanLy::MenuQuanLyPhong() {
    int choice;
    do {
        system(CLEAR_SCREEN);
        cout << "--- QUAN LY PHONG ---" << endl;
        cout << "1. Them Phong" << endl;
        cout << "2. Xoa Phong" << endl;
        cout << "3. Sua Phong" << endl;
        cout << "4. Tim Kiem Phong" << endl;
        cout << "5. Hien Thi Tat Ca Phong" << endl;
        cout << "0. Quay lai Menu Chinh" << endl;
        cout << "---------------------" << endl;
        choice = GetMenuChoice(0, 5);

        switch (choice) {
        case 1: ThemPhong(); break;
        case 2: XoaPhong(); break;
        case 3: SuaPhong(); break;
        case 4: TimPhong(); break;
        case 5: HienThiDanhSachPhong(); break;
        case 0: return;
        }
        if (choice != 0) PauseScreen();
    } while (true);
}

void CQuanLy::MenuQuanLyNguoiThue() {
    int choice;
    do {
        system(CLEAR_SCREEN);
        cout << "--- QUAN LY NGUOI THUE ---" << endl;
        cout << "1. Them Nguoi Thue (Chua thue phong)" << endl;
        cout << "2. Xoa Nguoi Thue (Phai tra phong truoc)" << endl;
        cout << "3. Sua Nguoi Thue" << endl;
        cout << "4. Tim Kiem Nguoi Thue" << endl;
        cout << "5. Hien Thi Tat Ca Nguoi Thue" << endl;
        cout << "0. Quay lai Menu Chinh" << endl;
        cout << "--------------------------" << endl;
        choice = GetMenuChoice(0, 5);

        switch (choice) {
        case 1: ThemNguoiThue(); break;
        case 2: XoaNguoiThue(); break;
        case 3: SuaNguoiThue(); break;
        case 4: TimNguoiThue(); break;
        case 5: HienThiDanhSachNguoiThue(); break;
        case 0: return;
        }
        if (choice != 0) PauseScreen();
    } while (true);
}

void CQuanLy::MenuThueTraPhong() {
    int choice;
    do {
        system(CLEAR_SCREEN);
        cout << "--- THUE / TRA PHONG ---" << endl;
        cout << "1. Thue Phong" << endl;
        cout << "2. Tra Phong" << endl;
        cout << "0. Quay lai Menu Chinh" << endl;
        cout << "------------------------" << endl;
        choice = GetMenuChoice(0, 2);

        switch (choice) {
        case 1: ThuePhong(); break;
        case 2: TraPhong(); break;
        case 0: return;
        }
        if (choice != 0) PauseScreen();
    } while (true);
}