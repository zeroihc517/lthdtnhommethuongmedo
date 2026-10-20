int main() {
    SetConsoleOutputCP(437); 
    QuanLyPhuongTien ql;
    int luaChon;
    do {
        system("cls");
        setColor(C_VIEN);
        cout << "\n  " << char(201) << string(M_W_FRAME, char(205)) << char(187) << "\n";
        inTieuDeMenu("QUAN LY PHUONG TIEN GIAO THONG", C_TIEU_DE);
        inTieuDeMenu("MTMT - Toan Ung Dung va Phan Vi Du", C_VIEN);
        setColor(C_VIEN); cout << "  " << char(204) << string(M_W_FRAME, char(205)) << char(185) << "\n";
        inDongMenu("1", "Them Xe Oto", C_TIEU_DE);
        inDongMenu("2", "Them Xe May", C_TIEU_DE);
        inDongMenu("3", "Them Xe Tai", C_TIEU_DE);
        inDongMenu("4", "Hien thi danh sach phuong tien", C_TIEU_DE);
        inDongMenu("5", "Tinh tong phi bao tri", C_TIEU_DE);
        inDongMenu("6", "Tra cuu chi tiet & Tu van xe", C_CHON);
        inDongMenu("7", "Them du lieu mau (Test nhanh)", C_TIEU_DE); 
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
                cout << "\n"; inHieuUng("  --- NHAP THONG TIN XE OTO ---\n", C_TIEU_DE);
                PhuongTien* oto = new XeOto();
                cin >> *oto;
                ql.ThemPhuongTien(oto);
                inHieuUng("\n  => Da them xe oto thanh cong! Thong tin vua nhap:\n", C_CHON);
                ql.InTieuDeBang();
                setColor(C_VIEN); cout << "  " << char(186) << " ";
                setColor(C_TEXT); cout << *oto;
                setColor(C_VIEN); cout << " " << char(186) << "\n";
                cout << "  " << char(200) << string(W_FRAME, char(205)) << char(188) << "\n";
                break;
            }
            case 2: {
                cout << "\n"; inHieuUng("  --- NHAP THONG TIN XE MAY ---\n", C_TIEU_DE);
                PhuongTien* xm = new XeMay();
                cin >> *xm;
                ql.ThemPhuongTien(xm);
                
                inHieuUng("\n  => Da them xe may thanh cong! Thong tin vua nhap:\n", C_CHON);
                ql.InTieuDeBang();
                setColor(C_VIEN); cout << "  " << char(186) << " ";
                setColor(C_TEXT); cout << *xm;
                setColor(C_VIEN); cout << " " << char(186) << "\n";
                cout << "  " << char(200) << string(W_FRAME, char(205)) << char(188) << "\n";
                break;
            }
            case 3: {
                cout << "\n"; inHieuUng("  --- NHAP THONG TIN XE TAI ---\n", C_TIEU_DE);
                PhuongTien* xt = new XeTai();
                cin >> *xt;
                ql.ThemPhuongTien(xt);
                
                inHieuUng("\n  => Da them xe tai thanh cong! Thong tin vua nhap:\n", C_CHON);
                ql.InTieuDeBang();
                setColor(C_VIEN); cout << "  " << char(186) << " ";
                setColor(C_TEXT); cout << *xt;
                setColor(C_VIEN); cout << " " << char(186) << "\n";
                cout << "  " << char(200) << string(W_FRAME, char(205)) << char(188) << "\n";
                break;
            }
            case 4: 
                ql.HienThiDanhSach(); 
                break;
            case 5: 
                ql.TinhTongPhiBaoTri(); 
                break;
            case 6: 
                ql.KiemTraTinhNangMoRong(); 
                break;
            case 7: {
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
