class QuanLyPhuongTien {
private:
    vector<PhuongTien*> ds;
public:
    // Destructor giai phong bo nho tranh Memory Leak
    ~QuanLyPhuongTien() {
        for (int i = 0; i < ds.size(); i++) {
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
             << setw(W_THONGSO) << "Thong So Rieng";
        setColor(C_VIEN); cout << "  " << char(186) << "\n";
        cout << "  " << char(204) << string(W_FRAME, char(205)) << char(185) << "\n";
    }
    // Tinh tong phi bao tri
    void TinhTongPhiBaoTri() const {
        system("cls");
        int frameW = 52; 
        // Xin người dùng nhập quãng đường để dự toán chi phí nhiên liệu
        double quangDuong = 0;
        cout << "\n";
        setColor(C_VIEN); cout << "  " << char(201) << string(frameW, char(205)) << char(187) << "\n";
        inTieuDeMenu("DU TOAN CHI PHI (BAO TRI + NHIEN LIEU)", C_TIEU_DE);
        setColor(C_VIEN); cout << "  " << char(200) << string(frameW, char(205)) << char(188) << "\n\n";
        inHieuUng("  >> Nhap so Km du kien di chuyen (Nhap 0 neu chi tinh phi bao tri): ", C_TIEU_DE, 0);
        setColor(C_TEXT);
        cin >> quangDuong;
        if(cin.fail() || quangDuong < 0) { cin.clear(); cin.ignore(32767, '\n'); quangDuong = 0; }
        else cin.ignore(32767, '\n');
        // Vẽ bảng thống kê
        setColor(C_VIEN); cout << "\n  " << char(201) << string(frameW, char(205)) << char(187) << "\n";
        setColor(C_VIEN); cout << "  " << char(186) << " ";
		setColor(C_CHON); cout << left << setw(14) << "Bien so" << setw(14) << "Loai xe" << right << setw(22) << "Thanh tien (VND)";
		setColor(C_VIEN); cout << " " << char(186);
		cout <<"\n  "<<char(204) << string(frameW, char(205)) << char(185) << "\n";
    	double tongPhi = 0;
        for (int i = 0; i < ds.size(); i++) {
            // TÍNH ĐA HÌNH Ở ĐÂY: Hàm sẽ tự quyết định gọi công thức của XeOto, XeMay hay XeTai
            double chiPhiXe = ds[i]->TinhPhiBaoTri(quangDuong); 
            tongPhi += chiPhiXe;  
            cout << "  " << char(186) << " ";
			setColor(C_TEXT);
			cout << left << setw(14) << ds[i]->getBienSo() << setw(14) << ds[i]->GetLoaiPhuongTien() << right << setw(22) << DinhDangTien(chiPhiXe);
            setColor(C_VIEN); cout << " " << char(186) << "\n";
        }
        setColor(C_VIEN); cout <<"  "<<char(204) << string(frameW, char(205)) << char(185) << "\n";
        cout << "  " << char(186); setColor(C_TEXT);
        cout << left << setw(28) << " + Tong so luong phuong tien: " << right << setw(21) << ds.size()<<" ";
        setColor(C_VIEN); cout << char(186) << "\n";
	    cout << "  " << char(186) << " ";    
		setColor(C_TEXT);
		cout << left << setw(28) << "+ Tong chi phi du toan:" << right << setw(22) << (DinhDangTien(tongPhi) + " VND");
    	setColor(C_VIEN); cout << " " << char(186) << "\n";
 	    cout << "  " << char(200) << string(frameW, char(205)) << char(188) << "\n";
        setColor(C_TEXT);
    }
    void inBangTuVan(string thuocTinh, string giaTri,int m ,int n) const {
        setColor(C_VIEN); cout << "  " << char(186) << " ";
        setColor(C_TIEU_DE); cout << left << setw(m) << thuocTinh;
        setColor(C_VIEN); cout << char(186) << " ";
        setColor(C_TEXT); cout << left << setw(n) << giaTri;
        setColor(C_VIEN); cout << char(186) << "\n";
    }
    // Hàm GỘP mới: Vừa hiển thị danh sách, vừa tra cứu chi tiết
    void HienThiVaTraCuu() const {
        if (ds.empty()) {
            system("cls");
            inHieuUng("\n  [THONG BAO] Danh sach phuong tien dang trong!\n", C_LOI);
            return;
        }
        string bs;
        do {
            system("cls");
            setColor(C_TIEU_DE);
            cout << "\n" << string(15, ' ') << "------------ DANH SACH TONG HOP & TRA CUU XE ------------\n\n";
            // 1. IN DANH SÁCH TỔNG HỢP
            InTieuDeBang();
            for (int i = 0; i < ds.size(); i++) {
                setColor(C_VIEN); cout << "  " << char(186) << " ";
                setColor(C_TEXT); cout << *ds[i];
                setColor(C_VIEN); cout << " " << char(186) << "\n";
            }
            setColor(C_VIEN);
            cout << "  " << char(200) << string(W_FRAME, char(205)) << char(188) << "\n\n";
            // 2. HỎI NGƯỜI DÙNG CÓ MUỐN TRA CỨU KHÔNG
            setColor(C_TEXT);
            cout << "  >> Nhap bien so xe can xem chi tiet (Hoac nhap '0' de thoat): ";
            getline(cin, bs);
            if (bs == "0") break; // Thoát vòng lặp về Menu chính
            // 3. IN BẢNG TƯ VẤN CHI TIẾT CHO XE ĐƯỢC CHỌN
            bool found = false;
            int W_LEFT = 28, W_RIGHT = 45;
            for (int i = 0; i < ds.size(); i++) {
                if (ds[i]->getBienSo() == bs) {
                    found = true;        
                    cout << "\n";
                    setColor(C_VIEN);
                    cout << "  " << char(201) << string(W_LEFT + 2, char(205)) << char(203) << string(W_RIGHT + 2, char(205)) << char(187) << "\n";            
                    cout << "  " << char(186) << " ";
                    setColor(C_CHON); cout << left << setw(W_LEFT) << "THUOC TINH";
                    setColor(C_VIEN); cout << " " << char(186) << " ";
                    setColor(C_CHON); cout << left << setw(W_RIGHT) << "GIA TRI CHI TIET";
                    setColor(C_VIEN); cout << " " << char(186) << "\n";          
                    cout << "  " << char(204) << string(W_LEFT + 2, char(205)) << char(206) << string(W_RIGHT + 2, char(205)) << char(185) << "\n";    
                    inBangTuVan("Loai xe", ds[i]->GetLoaiPhuongTien(), W_LEFT+1, W_RIGHT+1);
                    inBangTuVan("Bien so", ds[i]->getBienSo(), W_LEFT+1, W_RIGHT+1);
                    inBangTuVan("Hang san xuat", ds[i]->getHangSanXuat(), W_LEFT+1, W_RIGHT+1);           
                    stringstream ss; ss << ds[i]->getNamSanXuat();
                    inBangTuVan("Nam san xuat", ss.str(), W_LEFT+1, W_RIGHT+1);          
                    inBangTuVan("Gia tri hien tai (nam 2026)", DinhDangTien(ds[i]->TinhGiaTriHienTai(2026)) + " VND", W_LEFT+1, W_RIGHT+1);         
                    setColor(C_VIEN);
                    cout << "  " << char(204) << string(W_LEFT + 2, char(205)) << char(206) << string(W_RIGHT + 2, char(205)) << char(185) << "\n";
                    if (XeOto* oto = dynamic_cast<XeOto*>(ds[i])) {
                        stringstream ssChoNgoi; ssChoNgoi << oto->getSoChoNgoi() << " cho";
                        inBangTuVan("So cho ngoi", ssChoNgoi.str(), W_LEFT+1, W_RIGHT+1);
                        inBangTuVan("Kieu dang", oto->getKieuDang(), W_LEFT+1, W_RIGHT+1);
                    }
                    else if (XeMay* xemay = dynamic_cast<XeMay*>(ds[i])) {
                        stringstream ssCS; ssCS << xemay->getCongSuat() << " cc";
                        inBangTuVan("Cong suat", ssCS.str(), W_LEFT+1, W_RIGHT+1);
                        inBangTuVan("He truyen dong", xemay->getHeTruyenDong(), W_LEFT+1, W_RIGHT+1);
                    }
                    else if (XeTai* xetai = dynamic_cast<XeTai*>(ds[i])) {
                        stringstream ssTT; ssTT << xetai->getTaiTrong() << " tan";
                        inBangTuVan("Tai trong", ssTT.str(), W_LEFT+1, W_RIGHT+1);
                        stringstream ssTruc; ssTruc << xetai->getSoTrucBanhXe() << " truc";
                        inBangTuVan("So truc banh xe", ssTruc.str(), W_LEFT+1, W_RIGHT+1);
                        inBangTuVan("Loai thung xe", xetai->getLoaiThungXe(), W_LEFT+1, W_RIGHT+1);
                    }
                    setColor(C_VIEN);
                    cout << "  " << char(200) << string(W_LEFT + 2, char(205)) << char(202) << string(W_RIGHT + 2, char(205)) << char(188) << "\n";
                    break;
                }
            }    
            if (!found) {
                inHieuUng("\n  [LOI] Khong tim thay bien so xe phu hop trong he thong!\n", C_LOI);
            }
            // Dừng màn hình trước khi vòng lặp tải lại danh sách
            setColor(C_VIEN); cout << "\n  ";
            system("pause");
        } while (true);
    }
};
