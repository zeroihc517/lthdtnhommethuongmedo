// ==================== LỚP QUẢN LÝ PHƯƠNG TIỆN ====================
class QuanLyPhuongTien {
private:
    vector<PhuongTien*> ds; // Sử dụng vector chứa con trỏ để tận dụng tính đa hình

public:
    // Hàm hủy: Giải phóng bộ nhớ động để tránh rò rỉ bộ nhớ (Memory leak)
    ~QuanLyPhuongTien() {
        for (size_t i = 0; i < ds.size(); i++) {
            delete ds[i];
        }
        ds.clear();
    }

    // 1. Thêm phương tiện vào danh sách (dùng đa hình)
    void ThemPhuongTien() {
        system("cls");
        setColor(C_VIEN); cout << "  " << char(201) << string(M_W_FRAME - 4, '=') << char(187) << "\n";
        inTieuDeMenu("THEM PHUONG TIEN", C_TIEU_DE);
        setColor(C_VIEN); cout << "  " << char(204) << string(M_W_FRAME - 4, '-') << char(185) << "\n";
        
        inDongMenu("1", "Them Xe O To", C_CHON);
        inDongMenu("2", "Them Xe May", C_CHON);
        inDongMenu("3", "Them Xe Tai", C_CHON);
        inDongMenu("0", "Quay lai menu chinh", C_LOI);
        
        setColor(C_VIEN); cout << "  " << char(200) << string(M_W_FRAME - 4, '=') << char(188) << "\n";
        
        setColor(C_VIEN); cout << " Nhap lua chon cua ban: ";
        setColor(C_TEXT);
        int chon;
        if (!(cin >> chon)) {
            cin.clear();
            cin.ignore(32767, '\n');
            return;
        }
        cin.ignore(32767, '\n');

        PhuongTien* p = nullptr;
        if (chon == 1) {
            p = new XeOto();
        } else if (chon == 2) {
            p = new XeMay();
        } else if (chon == 3) {
            p = new XeTai();
        } else {
            return;
        }

        cout << "\n";
        cin >> *p; // Gọi toán tử nhập (đa hình qua hàm Nhap)
        ds.push_back(p);

        setColor(C_CHON);
        cout << "\n  " << char(254) << " Them phuong tien thanh cong!\n";
        setColor(C_TEXT);
        system("pause");
    }

    // 2. Hiển thị danh sách phương tiện dạng bảng
    void HienThiDanhSach() const {
        system("cls");
        if (ds.empty()) {
            setColor(C_LOI);
            cout << "Danh sach hien tai dang trong!\n";
            setColor(C_TEXT);
            system("pause");
            return;
        }

        setColor(C_VIEN);
        cout << left
             << setw(W_BIENSO) << "Bien So"
             << setw(W_HANG) << "Hang SX"
             << setw(W_NAMSX) << "Nam SX"
             << setw(W_LOAI) << "Loai Xe"
             << setw(W_THONGSO) << "Thong So Rieng"
             << right << setw(W_PHI) << "Phi Bao Tri" << "\n";
        cout << string(W_BIENSO + W_HANG + W_NAMSX + W_LOAI + W_THONGSO + W_PHI, '-') << "\n";
        
        setColor(C_TEXT);
        for (size_t i = 0; i < ds.size(); i++) {
            // Tận dụng tính đa hình: gọi operator<< -> HienThiThongTin -> GetThongSo, GetLoaiPhuongTien tương ứng
            cout << *ds[i] << "\n";
        }
        setColor(C_VIEN);
        cout << string(W_BIENSO + W_HANG + W_NAMSX + W_LOAI + W_THONGSO + W_PHI, '-') << "\n";
        setColor(C_TEXT);
        system("pause");
    }

    // 3. Tìm kiếm phương tiện theo biển số
    void TimKiemTheoBienSo() const {
        system("cls");
        setColor(C_TIEU_DE);
        cout << "--- TIM KIEM PHUONG TIEN THEO BIEN SO ---\n";
        setColor(C_VIEN);
        cout << "Nhap bien so can tim: ";
        setColor(C_TEXT);
        string tuKhoa;
        getline(cin, tuKhoa);

        bool timThay = false;
        cout << "\nKet qua tim kiem:\n";
        for (size_t i = 0; i < ds.size(); i++) {
            // Chuyển về chữ thường để tìm kiếm không phân biệt hoa thường
            if (PhuongTien::toLower(ds[i]->getBienSo()).find(PhuongTien::toLower(tuKhoa)) != string::npos) {
                cout << *ds[i] << "\n";
                timThay = true;
            }
        }

        if (!timThay) {
            setColor(C_LOI);
            cout << "Khong tim thay phuong tien nao phu hop!\n";
            setColor(C_TEXT);
        }
        system("pause");
    }

    // 4. Thống kê tổng phí bảo trì toàn bộ danh sách
    void ThongKePhiBaoTri() const {
        system("cls");
        setColor(C_TIEU_DE);
        cout << "--- THONG KE TONG PHI BAO TRI ---\n";
        setColor(C_TEXT);
        double tongPhi = 0;
        for (size_t i = 0; i < ds.size(); i++) {
            tongPhi += ds[i]->TinhPhiBaoTri(); // Đa hình tính phí bảo trì riêng của từng loại xe
        }
        cout << "Tong so luong phuong tien: " << ds.size() << "\n";
        cout << "Tong phi bao tri phai thu: " << DinhDangTien(tongPhi) << " VND\n";
        system("pause");
    }
};

