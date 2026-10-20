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
        ss << taiTrong << " tan" << " - " << loaiThungXe
           << " - " << soTrucBanhXe << " truc";
        return ss.str();
    }
    // Đa hình lấy từ hàm TinhPhiBaoTri() của lớp cha 
    double TinhPhiBaoTri() const override {
        return 1000000 + taiTrong * 200000;
    }
    double TinhCuocVanChuyen(double quangDuong, int namHienTai) const {
        if (quangDuong <= 0) return 0;
        int tuoiXe = namHienTai - getNamSanXuat();
        if (tuoiXe < 0) {
            cout << "[LOI] Nam san xuat khong the lon hon nam hien tai!\n";
            return 0;
        }
        // Đơn giá cơ bản: 5000 VND/km (chi phí lăn bánh gốc)
        double donGiaMoiKm = 5000; 
        // 1. Gộp phụ phí theo tải trọng (Chi phí vận hành + Cước vận chuyển)
        if (taiTrong > 5) {
            donGiaMoiKm += 15000; // 3000 (vận hành) + 12000 (cước)
        } else if (taiTrong > 2) {
            donGiaMoiKm += 9500;  // 1500 (vận hành) + 8000 (cước)
        } else {
            donGiaMoiKm += 5000;  // 0 (vận hành) + 5000 (cước)
        }
        // 2. Phụ phí cấu hình xe (số trục bánh xe)
        if (soTrucBanhXe >= 4) {
            donGiaMoiKm += 2000;
        } else if (soTrucBanhXe == 3) {
            donGiaMoiKm += 1000;
        }
        // 3. Phụ phí rủi ro/hao mòn xe cũ (tuổi xe > 10 năm)
        if (tuoiXe > 10) donGiaMoiKm += 1000;
        // 4. Phụ phí xe chuyên dụng (thùng đông lạnh)
        if (toLower(loaiThungXe) == "dong lanh") donGiaMoiKm += 3000;
        // Trả về tổng cước dựa trên quãng đường nhân với tổng đơn giá 1 km
        return quangDuong * donGiaMoiKm;
    }
     // HÀM PHÂN LOẠI THÙNG XE, ĐỂ ĐƯA RA CÁC OPTION CHO KHÁCH HÀNG LỰA CHỌN
    string PhanLoaiThungXe() const {
        string loai =  toLower(loaiThungXe);
        if (loai == "dong lanh") { return "Thung dong lanh"; }
        if (loai == "thung kin") { return "Thung kin"; }
        if (loai == "thung bat") { return "Thung bat"; }
        if (loai == "xe ben") { return "Xe ben"; }
        return "Khong xac dinh";
    }
    bool KiemTraXeCoNenThayThe(int namHienTai) const {
        int tuoiXe = namHienTai - getNamSanXuat();
        if (tuoiXe < 0) {
            cout << "[LOI] Nam san xuat khong the lon hon nam hien tai!\n";
            return false;
        }
        double giaTriHienTai = TinhGiaTriHienTai(namHienTai);
        // Bóc tách tính chi phí vận hành (hao mòn, xăng xe, bảo dưỡng...) 
        // không bao gồm phí vận chuyển để đánh giá đúng tình trạng xuống cấp của xe
        double chiPhiVanHanh1Km = 5000; 
        if (taiTrong > 5) chiPhiVanHanh1Km += 3000;
        else if (taiTrong > 2) chiPhiVanHanh1Km += 1500;
        if (soTrucBanhXe >= 4) chiPhiVanHanh1Km += 2000;
        else if (soTrucBanhXe == 3) chiPhiVanHanh1Km += 1000;
        if (tuoiXe > 10) chiPhiVanHanh1Km += 1000;
        // Xe trên 15 năm, giá trị giảm dưới 30% và chi phí vận hành gốc >= 8000đ/km
        if (tuoiXe > 15 && giaTriHienTai < (getGiaGoc() * 0.3) && chiPhiVanHanh1Km >= 8000) {
            return true;
        }
        return false;
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
            setColor(C_VIEN); cout << "  " << char(254) << " [LOI] Tai trong khong hop le!\n";
            cout << "  " << char(254) << " Nhap lai Tai trong (tan): ";
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
            setColor(C_VIEN); cout << "  " << char(254) << " [LOI] So truc khong hop le!\n";
            cout << "  " << char(254) << " Nhap lai So truc banh xe: ";
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
