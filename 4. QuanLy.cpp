class QuanLyPhuongTien {
private:
    vector<PhuongTien*> ds;
public:
    // Destructor giải phóng bộ nhớ tránh Memory Leak
    ~QuanLyPhuongTien() {
        for (size_t i = 0; i < ds.size(); i++) {
            delete ds[i];
        }
        ds.clear();
    }
    // Thêm phương tiện nhận con trỏ 
    void ThemPhuongTien(PhuongTien* pt) {
        if (pt != NULL) {
            ds.push_back(pt);
        }
    }
    // In khung tiêu đề bảng 
    void InTieuDeBang() const {
        setColor(C_VIEN);
        cout << "  " << char(201) << string(W_FRAME, char(205)) << char(187) << "\n";
        cout << "  " << char(186) << left
             << setw(W_BIENSO) << "Bien So"
             << setw(W_HANG) << "Hang SX"
             << setw(W_NAMSX) << "Nam SX"
             << setw(W_LOAI) << "Loai Xe"
             << setw(W_THONGSO) << "Thong So Rieng"
             << right << setw(W_PHI) << "Phi Bao Tri" << " ";
        setColor(C_VIEN); cout << char(186) << "\n";
        cout << "  " << char(204) << string(W_FRAME, char(205)) << char(185) << "\n";
    }
    // Hiển thị toàn bộ danh sách 
    void HienThiDanhSach() const {
        system("cls");
        if (ds.empty()) {
            inHieuUng("\n  [THONG BAO] Danh sach phuong tien dang trong!\n", C_LOI);
            return;
        }
        InTieuDeBang();
        for (size_t i = 0; i < ds.size(); i++) {
            setColor(C_VIEN); cout << "  " << char(186) << " ";
            setColor(C_TEXT); cout << *ds[i];
            setColor(C_VIEN); cout << " " << char(186) << "\n";
        }
        setColor(C_VIEN);
        cout << "  " << char(200) << string(W_FRAME, char(205)) << char(188) << "\n";
        setColor(C_TEXT);
    }
    // Tính tổng phí bảo trì
    void TinhTongPhiBaoTri() const {
        system("cls");
        inTieuDeMenu("THONG KE TONG PHI BAO TRI", C_TIEU_DE);
        double tongPhi = 0;
        for (size_t i = 0; i < ds.size(); i++) {
            tongPhi += ds[i]->TinhPhiBaoTri(); // Tính đa hình
        }
        cout << "\n  + Tong so luong phuong tien: " << ds.size() << "\n";
        cout << "  + Tong phi bao tri phai thu: " << DinhDangTien(tongPhi) << " VND\n";
    }
    // Kiểm tra tính năng mở rộng / tư vấn xe 
    void KiemTraTinhNangMoRong() const {
        system("cls");
        inTieuDeMenu("TRA CUU CHI TIET & TU VAN XE", C_TIEU_DE);
        if (ds.empty()) {
            inHieuUng("\n  [THONG BAO] Danh sach trong, chua co xe de tra cuu!\n", C_LOI);
            return;
        }
        cout << "\n  Nhap bien so xe can tra cuu tinh nang rieng: ";
        string bs;
        getline(cin, bs);
        bool found = false;
        for (size_t i = 0; i < ds.size(); i++) {
            if (PhuongTien::toLower(ds[i]->getBienSo()) == PhuongTien::toLower(bs)) {
                found = true;
                cout << "\n  --- THONG TIN CHI TIET --- \n";
                cout << "  Loai xe: " << ds[i]->GetLoaiPhuongTien() << "\n";
                cout << "  Bien so: " << ds[i]->getBienSo() << "\n";
                cout << "  Gia tri hien tai (nam 2026): " << DinhDangTien(ds[i]->TinhGiaTriHienTai(2026)) << " VND\n";
                // Sử dụng dynamic_cast để gọi các hàm riêng của từng lớp con (thể hiện tính chuyên sâu)
                if (XeOto* oto = dynamic_cast<XeOto*>(ds[i])) {
                    cout << "  Phan khúc: " << oto->PhanLoaiPhanKhuc() << "\n";
                    cout << "  Can dang kiem: " << (oto->KiemTraCanDangKiem(2026) ? "Can di dang kiem gap!" : "Con han dang kiem.") << "\n";
                }
                else if (XeMay* xemay = dynamic_cast<XeMay*>(ds[i])) {
                    cout << "  Yêu cầu bằng lái: " << xemay->YeuCauBangLai() << "\n";
                    cout << "  Tình trạng nhớt: ";
                    xemay->KiemTraThayNhot();
                }
                else if (XeTai* xetai = dynamic_cast<XeTai*>(ds[i])) {
                    cout << "  Phân loại thùng: " << xetai->PhanLoaiThungXe() << "\n";
                    cout << "  Cần xem xét thay thế xe: " << (xetai->KiemTraXeCoNenThayThe(2026) ? "Nen dau tu xe moi!" : "Xe van con tot.") << "\n";
                }
                break;
            }
        }
        if (!found) {
            inHieuUng("\n  [LOI] Khong tìm thay bien so xe phu hop trong hệ thống!\n", C_LOI);
        }
    }
};
