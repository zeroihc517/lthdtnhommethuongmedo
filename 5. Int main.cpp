int main() {
    SetConsoleOutputCP(437); 
    QuanLyPhuongTien ql;
    int luaChon;
    do {
        system("cls");
        setColor(C_VIEN);
        cout << "\n  " << char(201) << string(M_W_FRAME, char(205)) << char(187) << "\n";
        inTieuDeMenu("QUAN LY PHUONG TIEN GIAO THONG", C_TIEU_DE);
        inTieuDeMenu("Me thuong me do", C_VIEN);
        setColor(C_VIEN); cout << "  " << char(204) << string(M_W_FRAME, char(205)) << char(185) << "\n";
        inDongMenu("1", "Them Xe Oto", C_TIEU_DE);
        inDongMenu("2", "Them Xe May", C_TIEU_DE);
        inDongMenu("3", "Them Xe Tai", C_TIEU_DE);
        inDongMenu("4", "Hien thi danh sach phuong tien", C_TIEU_DE);
        inDongMenu("5", "Tinh tong phi bao tri", C_TIEU_DE);
        inDongMenu("6", "Kiem tra cac tinh nang sang tao", C_CHON);
        inDongMenu("0", "Thoat chuong trinh", C_LOI);
        setColor(C_VIEN); cout << "  " << char(200) << string(M_W_FRAME, char(205)) << char(188) << "\n\n";
        inHieuUng("  >> Nhap lua chon cua ban: ", C_TIEU_DE, 0);
        setColor(C_TEXT); cin >> luaChon;
        if (cin.fail()) { 
            cin.clear(); 
            luaChon = -1; 
        }
        cin.ignore(32767, '\n');
        switch (luaChon) {
            case 1: {
                cout << "\n"; inHieuUng("  --- NHAP THONG TIN XE OTO ---\n", C_TIEU_DE);
                PhuongTien* oto = new XeOto();
                cin >> *oto;
                ql.ThemPhuongTien(oto);
                inHieuUng("\n  => Da them xe oto thanh cong!\n", C_CHON);
                break;
            }
            case 2: {
                cout << "\n"; inHieuUng("  --- NHAP THONG TIN XE MAY ---\n", C_TIEU_DE);
                PhuongTien* xm = new XeMay();
                cin >> *xm;
                ql.ThemPhuongTien(xm);
                inHieuUng("\n  => Da them xe may thanh cong!\n", C_CHON);
                break;
            }
            case 3: {
                cout << "\n"; inHieuUng("  --- NHAP THONG TIN XE TAI ---\n", C_TIEU_DE);
                PhuongTien* xt = new XeTai();
                cin >> *xt;
                ql.ThemPhuongTien(xt);
                inHieuUng("\n  => Da them xe tai thanh cong!\n", C_CHON);
                break;
            }
            case 4: ql.HienThiDanhSach(); break;
            case 5: ql.TinhTongPhiBaoTri(); break;
            case 6: ql.KiemTraTinhNangMoRong(); break;
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
