class XeTai : public PhuongTien {
private:
    double taiTrong;        // đơn vị : tấn
    int soTrucBanhXe;      // số trục của xe ( vidu là xe tải có thể 2 3 trục nối tiếp nhau ) 
    string loaiThungXe;    // Loại thùng xe ( chia ra nhiều loại, như là đông lạnh , có nắp , hay chỉ phủ miếng bạt mà ko có nắp,)
public:
    // Hàm khởi tạo mặc định
    XeTai() : PhuongTien() {
        taiTrong = 0;
        soTrucBanhXe = 0;
        loaiThungXe = "";
    }
    // Hàm khởi tạo có tham số
    XeTai(string bs, string hsx, int nsx, double gia, double tt, int soTruc, string loaiThung) : PhuongTien(bs, hsx, nsx, gia) {
        taiTrong = tt;
        soTrucBanhXe = soTruc;
        loaiThungXe = loaiThung;
    }
    // Hàm khởi tạo sao chép
    XeTai(const XeTai& p) : PhuongTien(p) {
        taiTrong = p.taiTrong;
        soTrucBanhXe = p.soTrucBanhXe;
        loaiThungXe = p.loaiThungXe;
    }
    // Hàm hủy
    ~XeTai() override {}
    // Hàm get tải trọng
    double getTaiTrong() const {
        return taiTrong;
    }
    // Hàm get số trục xe
    int getSoTrucBanhXe() const {
        return soTrucBanhXe;
    }
    // Hàm get loại thùng xe
    string getLoaiThungXe() const {
        return loaiThungXe;
    }
    // Hàm set tai trong
    void setTaiTrong(double tt) {
        taiTrong = tt;
    }
    // Hàm set số trục bánh xe
    void setSoTrucBanhXe(int soTruc) {
        soTrucBanhXe = soTruc;
    }
    // Hàm set loại thùng xe
    void setLoaiThungXe(string loaiThung) {
        loaiThungXe = loaiThung;
    }
    // Đa hình lấy từ hàm GetLoaiPhuongTien() của lớp cha 
    string GetLoaiPhuongTien() const override {
        return "Xe tai";
    }
    // Đa hình lấy từ hàm GetThongSo() của lớp cha 
    string GetThongSo() const override {
        stringstream ss;
        ss << taiTrong << " tan" << " - " << loaiThungXe << " - " << soTrucBanhXe << " truc";
        return ss.str();
    }
    // Đa hình: Tính tổng chi phí (Bao gồm phí bảo trì + Tiền dầu)
    double TinhPhiBaoTri(double quangDuong = 0) const override {
        double phiCoBan = 1000000 + taiTrong * 200000;
        if (quangDuong <= 0) return phiCoBan;
        double litTieuThuMoi100Km = 12.0; 
        if (taiTrong > 5) litTieuThuMoi100Km += 10.0;
        else if (taiTrong > 2) litTieuThuMoi100Km += 5.0;
        if (soTrucBanhXe >= 4) litTieuThuMoi100Km += 4.0;
        string loai = toLower(loaiThungXe);
        if (loai.find("dong lanh") != string::npos) litTieuThuMoi100Km += 3.0;
        double tienNienLieu = (quangDuong / 100.0) * litTieuThuMoi100Km * 20000; // Giá dầu 20000
        return phiCoBan + tienNienLieu;
    }
    void Nhap(istream& in) override {
        // Gọi hàm nhập của lớp cơ sở PhuongTien (đã bao gồm kiểm tra năm)
        PhuongTien::Nhap(in);
        // Nhập tải trọng
        setColor(C_VIEN);
        cout << "  " << char(254) << " Nhap Tai trong (tan): ";
        setColor(C_TEXT);
        while (!(in >> taiTrong) || taiTrong <= 0) {
            in.clear();
            in.ignore(32767, '\n');
            setColor(C_LOI);  cout << "  " << char(254) << " [LOI] Tai trong khong hop le!\n";
            setColor(C_VIEN); cout << "  " << char(254) << " Nhap lai Tai trong (tan): ";
            setColor(C_TEXT);
        }
        in.ignore(32767, '\n');
        // Nhập loại thùng
        setColor(C_VIEN); cout << "  " << char(254) << " Nhap Loai thung xe: ";
        setColor(C_TEXT);
        getline(in, loaiThungXe);
        // Nhập số trục
        setColor(C_VIEN); cout << "  " << char(254) << " Nhap So truc banh xe: ";
        setColor(C_TEXT);
        while (!(in >> soTrucBanhXe) || soTrucBanhXe <= 0) {
            in.clear();
            in.ignore(32767, '\n');
            setColor(C_LOI);  cout << "  " << char(254) << " [LOI] So truc khong hop le!\n";
            setColor(C_VIEN); cout << "  " << char(254) << " Nhap lai So truc banh xe: ";
            setColor(C_TEXT);
        }
        in.ignore(32767, '\n');
    }
    // Hàm hiển thị thông tin
    void HienThiThongTin(ostream& out) const {
        // PhuongTien sẽ tự động gọi hàm GetThongSo()
        // của XeTai do GetThongSo() là hàm ảo.
        PhuongTien::HienThiThongTin(out);
    }
    // hàm quá tải nhập
    friend istream& operator>>(istream& in, XeTai& p) {
        p.Nhap(in);
        return in;
    }
   // hàm quá tải xuất
    friend ostream& operator<<(ostream& out, const XeTai& p) {
        p.HienThiThongTin(out);
        return out;
    }
};
