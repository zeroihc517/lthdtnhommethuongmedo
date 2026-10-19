class XeOto : public PhuongTien {
private:
    int soChoNgoi;        // Số chỗ ngồi của ô tô (ví dụ: 4, 7, 16, 29...)
    string kieuDang;      // Kiểu dáng (ví dụ: Sedan, SUV, Hatchback, Xe khach...)
public:
    // Hàm khởi tạo mặc định
    XeOto() : PhuongTien() {
        soChoNgoi = 4;
        kieuDang = "";
    }
    // Hàm khởi tạo có tham số
    XeOto(string bs, string hsx, int nsx, double gia, int soCho, string kd) : PhuongTien(bs, hsx, nsx, gia, 0, 0) {
        soChoNgoi = soCho;
        kieuDang = kd;
    }
    // Hàm khởi tạo sao chép
    XeOto(const XeOto& p) : PhuongTien(p) {
        soChoNgoi = p.soChoNgoi;
        kieuDang = p.kieuDang;
    }
    // Hàm hủy
    ~XeOto() override {}
    // Hàm get
    int getSoChoNgoi() const { return soChoNgoi; }
    string getKieuDang() const { return kieuDang; }
    // Hàm set
    void setSoChoNgoi(int soCho) { soChoNgoi = soCho; }
    void setKieuDang(string kd) { kieuDang = kd; }
    // Đa hình: Trả về loại phương tiện
    string GetLoaiPhuongTien() const override {
        return "Xe oto";
    }
    // Đa hình: Trả về thông số riêng (hiển thị đẹp trên bảng)
    string GetThongSo() const override {
        stringstream ss;
        ss << soChoNgoi << " cho" << " - " << kieuDang;
        return ss.str();
    }
    // Đa hình: Tính phí bảo trì (Ô tô tính theo số chỗ ngồi và giá trị xe)
    double TinhPhiBaoTri() const override {
        double phiCoBan = 1500000; // Phí cơ bản cho ô tô
        if (soChoNgoi <= 5) {
            phiCoBan += 500000;
        } else if (soChoNgoi <= 9) {
            phiCoBan += 1000000;
        } else {
            phiCoBan += 2000000; // Xe khách lớn phí cao hơn
        }
        return phiCoBan;
    }
    // SÁNG TẠO 1: Phân loại phân khúc xe dựa trên số chỗ và kiểu dáng để tư vấn khách hàng
    string PhanLoaiPhanKhuc() const {
        string kd = toLower(kieuDang);
        if (soChoNgoi <= 5 && (kd.find("sedan") != string::npos || kd.find("hatchback") != string::npos)) {
            return "Oto con gia dinh (Nho gon)";
        }
        if (soChoNgoi <= 7 && kd.find("suv") != string::npos) {
            return "Oto 7 cho gam cao (SUV)";
        }
        if (soChoNgoi > 9) {
            return "Xe kinh doanh / Xe khach";
        }
        return "Oto du lịch thong thuong";
    }
    // SÁNG TẠO 2: Tính lượng nhiên liệu tiêu thụ và tiền xăng cho chuyến đi (đơn vị: VND)
    double TinhTienXangChuyenDi(double quangDuong, double giaXangCho1Lit = 22000) const {
        if (quangDuong < 0) return 0;
        double litTieuThuMoi100Km = 8.0; // Mặc định xe 4-5 chỗ tiêu thụ ~8L/100km
        // Xe nhiều chỗ hoặc dáng SUV thì tốn xăng hơn
        if (soChoNgoi > 7 || toLower(kieuDang).find("suv") != string::npos) {
            litTieuThuMoi100Km = 12.0; 
        } else if (soChoNgoi > 5) {
            litTieuThuMoi100Km = 10.0;
        }
        double tongSoLit = (quangDuong / 100.0) * litTieuThuMoi100Km;
        return tongSoLit * giaXangCho1Lit;
    }
    // SÁNG TẠO 3: Kiểm tra thời hạn đăng kiểm xe (theo quy định tại VN dựa trên tuổi xe và số chỗ)
    // Trả về số năm còn lại hoặc cảnh báo cần đi đăng kiểm
    bool KiemTraCanDangKiem(int namHienTai) const {
        int tuoiXe = namHienTai - getNamSanXuat();
        // Ô tô chở người các loại đến 9 chỗ không kinh doanh vận tải: 
        // Dưới 7 năm: đăng kiểm 2 năm/lần; Trên 7 năm: 1 năm/lần; Trên 12 năm: 6 tháng/lần.
        if (tuoiXe > 12) {
            return true; // Cần đăng kiểm gấp / kiểm tra thường xuyên
        }
        return false;
    }
    // Hàm Nhập thông tin
    void Nhap(istream& in) {
        // Gọi hàm nhập của lớp cơ sở PhuongTien
        PhuongTien::Nhap(in);
        // Kiểm tra năm sản xuất hợp lệ (dùng lại logic chuẩn của bạn)
        time_t now = time(0);
        tm* ltm = localtime(&now);
        int namHienTai = 1900 + ltm->tm_year;
        while (namSanXuat < 1900 || namSanXuat > namHienTai) {
            setColor(C_VIEN);
            cout << "  " << char(204) << char(205) << " [LOI] Nam san xuat phai tu 1900 den " << namHienTai << "!\n";
            cout << "  " << char(204) << char(205) << " Nhap lai Nam san xuat: ";
            setColor(C_TEXT);
            in >> namSanXuat;
            if (in.fail()) {
                in.clear();
                in.ignore(32767, '\n');
                continue;
            }
            in.ignore(32767, '\n');
        }
        // Nhập số chỗ ngồi
        setColor(C_VIEN);
        cout << "  " << char(204) << char(205) << " Nhap So cho ngoi: ";
        setColor(C_TEXT);
        in >> soChoNgoi;
        if (in.fail()) {
            in.clear();
        }
        in.ignore(32767, '\n');
        // Nhập kiểu dáng xe
        setColor(C_VIEN);
        cout << "  " << char(204) << char(205) << " Nhap Kieu dang (Sedan, SUV, Hatchback...): ";
        setColor(C_TEXT);
        getline(in, kieuDang);
    }
    // Hàm Hiển thị thông tin
    void HienThiThongTin(ostream& out) const {
        // Tự động kế thừa hiển thị chuẩn của PhuongTien và gọi đa hình GetThongSo()
        PhuongTien::HienThiThongTin(out);
    }
    // Toán tử nhập
    friend istream& operator>>(istream& in, XeOto& p) {
        p.Nhap(in);
        return in;
    }
    // Toán tử xuất
    friend ostream& operator<<(ostream& out, const XeOto& p) {
        p.HienThiThongTin(out);
        return out;
    }
};
