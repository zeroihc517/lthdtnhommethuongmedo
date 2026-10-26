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
    XeOto(string bs, string hsx, int nsx, double gia, int soCho, string kd) : PhuongTien(bs, hsx, nsx, gia) {
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
    // Đa hình: Tính tổng chi phí (Bao gồm phí bảo trì cơ bản + Tiền xăng nếu có di chuyển)
    double TinhPhiBaoTri(double quangDuong = 0) const override {
        double phiCoBan = 1500000;
        if (soChoNgoi <= 5) phiCoBan += 500000;
        else if (soChoNgoi <= 9) phiCoBan += 1000000;
        else phiCoBan += 2000000;
        // Nếu không di chuyển (quangDuong = 0), chỉ trả về phí bảo trì
        if (quangDuong <= 0) return phiCoBan;
        // Nếu có di chuyển, tính thêm tiền xăng
        double litTieuThuMoi100Km = 8.0;
        string kd = toLower(kieuDang);
        if (soChoNgoi > 7 || kd.find("suv") != string::npos) litTieuThuMoi100Km = 12.0;
        else if (soChoNgoi > 5) litTieuThuMoi100Km = 10.0;
        double tienXang = (quangDuong / 100.0) * litTieuThuMoi100Km * 22000; // Giá xăng mặc định 22000
        return phiCoBan + tienXang;
    }
    // Hàm nhập thông tin
    void Nhap(istream& in) override {
        // Gọi hàm nhập của lớp cơ sở PhuongTien (đã bao gồm kiểm tra năm)
        PhuongTien::Nhap(in);
        // Nhập số chỗ ngồi
        setColor(C_VIEN);
        cout << "  " << char(254) << " Nhap So cho ngoi: ";
        setColor(C_TEXT);
        while (!(in >> soChoNgoi) || soChoNgoi <= 0) {
            in.clear();
            in.ignore(32767, '\n');
            setColor(C_LOI);  cout << "  " << char(254) << " [LOI] So cho ngoi khong hop le!\n";
            setColor(C_VIEN); cout << "  " << char(254) << " Nhap lai So cho ngoi: ";
            setColor(C_TEXT);
        }
        in.ignore(32767, '\n');
        // Nhập kiểu dáng xe
        setColor(C_VIEN);
        cout << "  " << char(254) << " Nhap Kieu dang (Sedan, SUV, Hatchback...): ";
        setColor(C_TEXT);
        getline(in, kieuDang);
    }
    // Hàm hiển thị thông tin
    void HienThiThongTin(ostream& out) const {
        // Tự động kế thừa hiển thị chuẩn của PhuongTien và gọi đa hình GetThongSo()
        PhuongTien::HienThiThongTin(out);
    }
    // Hàm quá tải nhập
    friend istream& operator>>(istream& in, XeOto& p) {
        p.Nhap(in);
        return in;
    }
    // Hàm quá tải xuất
    friend ostream& operator<<(ostream& out, const XeOto& p) {
        p.HienThiThongTin(out);
        return out;
    }
};
