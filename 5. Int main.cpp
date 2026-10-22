int main() {
    SetConsoleOutputCP(437); 
    QuanLyPhuongTien ql;
    int luaChon;
    do {
        system("cls");
        setColor(C_VIEN);
        cout << "\n  " << char(201) << string(M_W_FRAME, char(205)) << char(187) << "\n";
        inTieuDeMenu("QUAN LY PHUONG TIEN GIAO THONG", C_TIEU_DE);
        inTieuDeMenu("MTMD - Toan Ung Dung va Phan Vi Du", C_VIEN);
        setColor(C_VIEN); cout << "  " << char(204) << string(M_W_FRAME, char(205)) << char(185) << "\n";
        inDongMenu("1", "Them phuong tien (Oto, Xe may, Xe tai)", C_TIEU_DE);
        inDongMenu("2", "Hien thi danh sach phuong tien", C_TIEU_DE);
        inDongMenu("3", "Tinh tong phi bao tri", C_TIEU_DE);
        inDongMenu("4", "Tra cuu chi tiet & Tu van xe", C_CHON);
        inDongMenu("5", "Them du lieu mau (Test nhanh)", C_TIEU_DE); 
        inDongMenu("0", "Thoat chuong trinh", C_LOI);
        setColor(C_VIEN); cout << "  " << char(200) << string(M_W_FRAME, char(205)) << char(188) << "\n\n";
        
        inHieuUng("  >> Nhap lua chon cua ban: ", C_TIEU_DE, 0);
        setColor(C_TEXT); cin >> luaChon;
        
        // X? lý l?i trôi l?nh n?u ngu?i dùng nh?p sai ki?u d? li?u
        if (cin.fail()) { 
            cin.clear(); 
            cin.ignore(32767, '\n');
            luaChon = -1; 
        } else {
            cin.ignore(32767, '\n');
        }

        switch (luaChon) {
            case 1: {
                int loaiXe;
                do {
                    system("cls"); // Xóa màn hình tru?c khi hi?n menu ph?
                    
                    // Hi?n th? Menu ph? d?ng khung chia ô
                    cout << "\n";
                    setColor(C_VIEN); cout << "  " << char(201) << string(M_W_FRAME, char(205)) << char(187) << "\n";
                    inTieuDeMenu("CHON LOAI PHUONG TIEN CAN THEM", C_TIEU_DE);
                    setColor(C_VIEN); cout << "  " << char(204) << string(M_W_FRAME, char(205)) << char(185) << "\n";
                    inDongMenu("1", "Them Xe Oto", C_TIEU_DE);
                    inDongMenu("2", "Them Xe May", C_TIEU_DE);
                    inDongMenu("3", "Them Xe Tai", C_TIEU_DE);
                    inDongMenu("0", "Quay lai Menu chinh", C_LOI);
                    setColor(C_VIEN); cout << "  " << char(200) << string(M_W_FRAME, char(205)) << char(188) << "\n\n";
                    
                    inHieuUng("  >> Nhap loai xe muon them: ", C_TIEU_DE, 0);
                    setColor(C_TEXT);
                    cin >> loaiXe;
                    
                    // X? lý l?i trôi l?nh cho Menu ph?
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(32767, '\n');
                        loaiXe = -1;
                    } else {
                        cin.ignore(32767, '\n');
                    }

                    if (loaiXe == 0) {
                        inHieuUng("\n  => Da quay lai Menu chinh!\n", C_CHON);
                        break; // Thoát vòng l?p ph?, tr? v? menu chính
                    }

                    PhuongTien* pt = NULL; // Kh?i t?o m?t con tr? cha chung d? gom code

                    // X? lý kh?i t?o d?i tu?ng d?ng theo l?a ch?n
                    switch (loaiXe) {
                        case 1:
                            cout << "\n"; inHieuUng("  --- NHAP THONG TIN XE OTO ---\n", C_TIEU_DE);
                            pt = new XeOto();
                            break;
                        case 2:
                            cout << "\n"; inHieuUng("  --- NHAP THONG TIN XE MAY ---\n", C_TIEU_DE);
                            pt = new XeMay();
                            break;
                        case 3:
                            cout << "\n"; inHieuUng("  --- NHAP THONG TIN XE TAI ---\n", C_TIEU_DE);
                            pt = new XeTai();
                            break;
                        default:
                            inHieuUng("\n  [LOI] Loai xe khong hop le!\n", C_LOI);
                            break;
                    }

                    // N?u ngu?i dùng ch?n dúng lo?i xe (pt dã du?c c?p phát)
                    if (pt != NULL) {
                        cin >> *pt; // Tính da hình: t? d?ng g?i dúng hàm Nhap() c?a l?p con
                        ql.ThemPhuongTien(pt);
                        inHieuUng("\n  => Da them phuong tien thanh cong!\n", C_CHON);
                        
                        // V? b?ng và hi?n th? phuong ti?n v?a thêm
                        ql.InTieuDeBang();
                        setColor(C_VIEN); cout << "  " << char(186) << " ";
                        setColor(C_TEXT); cout << *pt; 
                        setColor(C_VIEN); cout << " " << char(186) << "\n";
                        cout << "  " << char(200) << string(W_FRAME, char(205)) << char(188) << "\n";
                        setColor(C_TEXT);
                    }
                    
                    // D?ng màn hình d? d?c k?t qu? tru?c khi l?p l?i menu ph?
                    setColor(C_VIEN); cout << "\n  ";
                    system("pause");

                } while (true); // Ch?y liên t?c cho d?n khi ngu?i dùng nh?p 0 (g?p l?nh break)
                
                break; // K?t thúc case 1 c?a menu chính
            }
            case 2: 
                ql.HienThiDanhSach(); 
                break;
            case 3: 
                ql.TinhTongPhiBaoTri(); 
                break;
            case 4: 
                ql.KiemTraTinhNangMoRong(); 
                break;
            case 5: {
                // Thêm d? li?u m?u c?ng d? test nhanh các phuong th?c riêng bi?t
                ql.ThemPhuongTien(new XeOto("51F-123.45", "Toyota", 2020, 800000000, 5, "Sedan"));
                ql.ThemPhuongTien(new XeMay("59A-999.99", "Honda", 2022, 50000000, 150, "Xe con tay", 12000, 11000));
                ql.ThemPhuongTien(new XeTai("60C-567.89", "Isuzu", 2018, 1200000000, 8.5, 3, "Dong lanh"));
                inHieuUng("\n  => Da nap du lieu mau (1 Xe Oto, 1 Xe May, 1 Xe Tai) de test nhanh chuc nang!\n", C_CHON);
                break;
            }
            case 0:
                cout << "\n";
                inHieuUng("  DANG THOAT CHUONG TRINH", C_LOI, 10);
                inHieuUng("...", C_LOI, 100);
                inHieuUng("\n  TAM BIET!\n\n", C_CHON, 10);
                break;
            default:
                inHieuUng("\n  [LOI] Lua chon khong hop le! Vui long nhap lai.\n", C_LOI);
                break;
        }
        
        if (luaChon != 0) {
            setColor(C_VIEN); cout << "\n  ";
            system("pause");
        }

    } while (luaChon != 0);
    return 0;
}
