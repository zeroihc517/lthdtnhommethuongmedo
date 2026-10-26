class QuanLyPhuongTien {
private:
    vector<PhuongTien*> ds;
public:
    // Destructor giai phong bo nho tranh Memory Leak
    ~QuanLyPhuongTien() {
        for (size_t i = 0; i < ds.size(); i++) {
            delete ds[i];
        }
        ds.clear();
    }
    // Them phuong tien nhan con tro 
    void ThemPhuongTien(PhuongTien* pt) {
        if (pt != NULL) {
            ds.push_back(pt);
        }
    }
    // In khung tieu de bang 
    void InTieuDeBang() const {
        setColor(C_VIEN);
        cout << "  " << char(201) << string(W_FRAME, char(205)) << char(187) << "\n";
        cout << "  " << char(186) << left;
        setColor(C_CHON);
             cout << setw(W_BIENSO) << " Bien So"
             << setw(W_HANG) << "Hang SX"
             << setw(W_NAMSX) << "Nam SX"
             << setw(W_LOAI) << "Loai Xe"
             << setw(W_THONGSO) << "Thong So Rieng"
             << right << setw(W_PHI) << "Phi Bao Tri" << "  ";
        setColor(C_VIEN); cout << char(186) << "\n";
        cout << "  " << char(204) << string(W_FRAME, char(205)) << char(185) << "\n";
    }
    // Hien thi toan bo danh sach 
    void HienThiDanhSach() const {
        system("cls");
        int frameW=120;
        if (ds.empty()) {
            inHieuUng("\n  [THONG BAO] Danh sach phuong tien dang trong!\n", C_LOI);
            return;
        }
        setColor(C_TIEU_DE);
		cout << "\n" << string(2 + (frameW + 2 - 55) / 2, ' ') << "------------ DANH SACH XE------------\n\n";
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
    // Tinh tong phi bao tri
    void TinhTongPhiBaoTri() const {
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
			cout << left << setw(14) << ds[i]->getBienSo() << setw(14) 
				<< ds[i]->GetLoaiPhuongTien() << right << setw(22) << DinhDangTien(ds[i]->TinhPhiBaoTri());
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
    void inBangTuVan(string thuocTinh, string giaTri,int m ,int n) const {
    setColor(C_VIEN);
    cout << "  " << char(186) << " ";
    setColor(C_TIEU_DE);
    cout << left << setw(m) << thuocTinh;
    setColor(C_VIEN);
    cout << char(186) << " ";
    setColor(C_TEXT);
    cout << left << setw(n) << giaTri;
    setColor(C_VIEN);
    cout << char(186) << "\n";
}
void TuVanXe() const {
         setColor(C_VIEN);
             int innerW = 50; 
        int frameW = 52; cout<<"\n";
        setColor(C_TIEU_DE); 
		cout << "\n" << string(2 + (frameW + 2 - 55) / 2, ' ') << "------------ TRA CUU CHI TIET & TU VAN XE ------------\n\n";
        if (ds.empty()) {
            inHieuUng("\n  [THONG BAO] Danh sach trong, chua co xe de tra cuu!\n", C_LOI);
            return;}
            setColor(C_TEXT);
			cout<< "  "<<"Nhap bien so xe can tra cuu tinh nang rieng: ";
		string bs;
		setColor(C_TEXT);
		getline(cin, bs);     		
        bool found = false;
        // Dinh dang do rong 2 cot cua bang chi tiet
        int W_LEFT = 28;
        int W_RIGHT = 45;
        for (size_t i = 0; i < ds.size(); i++) {
            if (ds[i]->getBienSo()== bs) {
                found = true;        
                // --- VE KHUNG TREN CUNG CUA BANG ---
                setColor(C_VIEN);
                cout << "  " << char(201) << string(W_LEFT + 2, char(205)) << char(203) << string(W_RIGHT + 2, char(205)) << char(187) << "\n";            
                // --- TIEU DE COT ---
                cout << "  " << char(186) << " ";
                setColor(C_CHON); cout << left << setw(W_LEFT) << "THUOC TINH";
                setColor(C_VIEN); cout << " " << char(186) << " ";
                setColor(C_CHON); cout << left << setw(W_RIGHT) << "GIA TRI CHI TIET";
                setColor(C_VIEN); cout << " " << char(186) << "\n";          
                // --- DUONG NGAN CACH TIEU DE ---
                cout << "  " << char(204) << string(W_LEFT + 2, char(205)) << char(206) << string(W_RIGHT + 2, char(205)) << char(185) << "\n";    
                // --- IN THONG TIN CHUNG ---
                inBangTuVan("Loai xe", ds[i]->GetLoaiPhuongTien(), W_LEFT+1, W_RIGHT+1);
                inBangTuVan("Bien so", ds[i]->getBienSo(),W_LEFT+1, W_RIGHT+1);
                inBangTuVan("Hang san xuat", ds[i]->getHangSanXuat(),W_LEFT+1, W_RIGHT+1);           
                // Chuyen doi kieu so sang string de hien thi
                stringstream ss; ss << ds[i]->getNamSanXuat();
                inBangTuVan("Nam san xuat", ss.str(), W_LEFT+1, W_RIGHT+1);          
                string giaTriStr = DinhDangTien(ds[i]->TinhGiaTriHienTai(2026)) + " VND";
                inBangTuVan("Gia tri hien tai (nam 2026)", giaTriStr, W_LEFT+1, W_RIGHT+1);         
                // --- DUONG NGAN CACH CHUYEN SAU ---
                setColor(C_VIEN);
                cout << "  " << char(204) << string(W_LEFT + 2, char(205)) << char(206) << string(W_RIGHT + 2, char(205)) << char(185) << "\n";
                // --- IN THONG TIN CHUYEN SAU (TU VAN XE) ---
                if (XeOto* oto = dynamic_cast<XeOto*>(ds[i])) {
                    inBangTuVan("Phan khuc", oto->PhanLoaiPhanKhuc(), W_LEFT+1, W_RIGHT+1);
                    inBangTuVan("Can dang kiem", (oto->KiemTraCanDangKiem(2026) ? "Can di dang kiem gap!" : "Con han dang kiem."), W_LEFT+1, W_RIGHT+1);
                }
                else if (XeMay* xemay = dynamic_cast<XeMay*>(ds[i])) {
                    inBangTuVan("Yeu cau bang lai", xemay->YeuCauBangLai(), W_LEFT+1, W_RIGHT+1);          
                    double kmDaDiLanTruoc = xemay->getSoKmDaDi() - xemay->getSoKmThayNhotGanNhat();
                    string htd = xemay->getHeTruyenDong();
                    string tinhTrangNhot = "Nhot con tot";                 
                    if (htd == "xe ga") {
                        if (kmDaDiLanTruoc >= 4500) tinhTrangNhot = "Nen thay nhot (Da di >= 4500km)";
                    } else {
                        if (kmDaDiLanTruoc >= 1500) tinhTrangNhot = "Nen thay nhot (Da di >= 1500km)";
                    }
                    inBangTuVan("Tinh trang nhot", tinhTrangNhot, W_LEFT+1, W_RIGHT+1);
                }
                else if (XeTai* xetai = dynamic_cast<XeTai*>(ds[i])) {
                    inBangTuVan("Phan loai thung", xetai->PhanLoaiThungXe(), W_LEFT+1, W_RIGHT+1);
                    inBangTuVan("Kiem tra thay the", (xetai->KiemTraXeCoNenThayThe(2026) ? "Nen dau tu xe moi!" : "Xe van con tot."), W_LEFT+1, W_RIGHT+1);
                }          
                // --- VE KHUNG DUOI CUNG ---
                setColor(C_VIEN);
                cout << "  " << char(200) << string(W_LEFT + 2, char(205)) << char(202) << string(W_RIGHT + 2, char(205)) << char(188) << "\n";
                break;
            }
        }    
        if (!found) {
            inHieuUng("\n  [LOI] Khong tim thay bien so xe phu hop trong he thong!\n", C_LOI);
        }
    }
};
