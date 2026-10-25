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
             << right << setw(W_PHI) << "Phi Bao Tri" << "  ";
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
        int innerW = 50; 
        int frameW = 52; 
         setColor(C_VIEN);
        cout << "\n  " << char(201) << string(frameW, char(205)) << char(187) << "\n";
        inTieuDeMenu("THONG KE TONG PHI BAO TRI", C_TIEU_DE);
        setColor(C_VIEN);
       cout << "  " << char(204) << string(frameW, char(205)) << char(185) << "\n";
    cout << "  " << char(186) << " ";
    setColor(C_CHON);
    cout << left << setw(14) << "Bien so" << setw(14) << "Loai xe" << right << setw(22) << "Thanh tien (VND)";
    setColor(C_VIEN); 
    cout << " " << char(186);
    cout <<"\n  "<<char(204) << string(frameW, char(205)) << char(185) << "\n";
      double tongPhi = 0;
        for (size_t i = 0; i < ds.size(); i++) {
            tongPhi += ds[i]->TinhPhiBaoTri(); // Tính da hình
            cout << "  " << char(186) << " ";
      setColor(C_TEXT);
      cout << left << setw(14) << ds[i]->getBienSo() << setw(14) << ds[i]->GetLoaiPhuongTien() << right << setw(22) << DinhDangTien(ds[i]->TinhPhiBaoTri());

    setColor(C_VIEN);

    cout << " " << char(186) << "\n";
        }
        setColor(C_VIEN);
        cout <<"  "<<char(204) << string(frameW, char(205)) << char(185) << "\n";
        cout << "  " << char(186);
        setColor(C_TEXT);
    cout << left << setw(28)
  << " + Tong so luong phuong tien: " 
    << right << setw(21) << ds.size()<<" ";

    setColor(C_VIEN);
    cout << char(186) << "\n";

    // Tong phi bao tri
      cout << "  " << char(186) << " ";

    setColor(C_TEXT);
    string tongTien = DinhDangTien(tongPhi) + " VND";
    cout << left 
    << setw(28) << "+ Tong phi bao tri phai thu:"
       << right << setw(22) << tongTien;
      setColor(C_VIEN);
      cout << " " << char(186) << "\n";
  cout << "  " << char(200) << string(frameW, char(205)) << char(188) << "\n";

    setColor(C_TEXT);
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
            if (toLower(ds[i]->getBienSo()) == toLower(bs)) {
                found = true;
                cout << "\n  --- THONG TIN CHI TIET --- \n";
                cout << "  Loai xe: " << ds[i]->GetLoaiPhuongTien() << "\n";
                cout << "  Bien so: " << ds[i]->getBienSo() << "\n";
                cout << "  Gia tri hien tai (nam 2026): " << DinhDangTien(ds[i]->TinhGiaTriHienTai(2026)) << " VND\n";
                // Sử dụng dynamic_cast để gọi các hàm riêng của từng lớp con (thể hiện tính chuyên sâu)
                if (XeOto* oto = dynamic_cast<XeOto*>(ds[i])) {
                    cout << "  Phan khuc: " << oto->PhanLoaiPhanKhuc() << "\n";
                    cout << "  Can dang kiem: " << (oto->KiemTraCanDangKiem(2026) ? "Can di dang kiem gap!" : "Con han dang kiem.") << "\n";
                }
                else if (XeMay* xemay = dynamic_cast<XeMay*>(ds[i])) {
                    cout << "  Yeu cau bang lai: " << xemay->YeuCauBangLai() << "\n";
                    cout << "  Tinh trang nhot: ";
                    xemay->KiemTraThayNhot();
                }
                else if (XeTai* xetai = dynamic_cast<XeTai*>(ds[i])) {
                    cout << "  Phan loai thung: " << xetai->PhanLoaiThungXe() << "\n";
                    cout << "  Can xem xet thay the xe: " << (xetai->KiemTraXeCoNenThayThe(2026) ? "Nen dau tu xe moi!" : "Xe van con tot.") << "\n";
                }
                break;
            }
        }
        if (!found) {
            inHieuUng("\n  [LOI] Khong tìm thay bien so xe phu hop trong he thong!\n", C_LOI);
        }
    }
};
