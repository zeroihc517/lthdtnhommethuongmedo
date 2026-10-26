class XeMay : public PhuongTien {
private:
    double congSuat;              // Công suất 
    string heTruyenDong;          // Xe số, xe ga, xe côn tay
public:
    // Hàm khởi tạo mặc định
    XeMay():PhuongTien(){
        congSuat = 0;
        heTruyenDong = "Xe so";
    }
    // Hàm khởi tạo có tham số
    XeMay(string bs,string hsx, int nsx, double gia, double cs, string htd):PhuongTien(bs, hsx, nsx, gia){
        congSuat = (cs>0) ? cs:0;
        heTruyenDong = htd;
    }
    // Hàm khởi tạo sao chép
    XeMay(const XeMay &p):PhuongTien(p){
        congSuat = p.congSuat;
        heTruyenDong = p.heTruyenDong;
    }
    // Hàm hủy
    ~XeMay() override{}
    // Getter
    double getCongSuat() const { return congSuat; }
    string getHeTruyenDong() const { return heTruyenDong; }
    // Setter
    void setCongSuat (double cs) { if(cs >= 0) congSuat = cs; }
    void setHeTruyenDong (string htd) { heTruyenDong = htd; }
    // Lấy loại phương tiện (Đa hình)
    string GetLoaiPhuongTien() const override { return "Xe may"; }
    // Lấy thông số riêng của xe máy (Đa hình)
    string GetThongSo() const override {
        stringstream ss;
        ss << fixed << setprecision(0) << congSuat << " - " << heTruyenDong;
        return ss.str();
    }
    // Đa hình: Tính tổng chi phí (Bao gồm phí bảo trì + Tiền xăng)
    double TinhPhiBaoTri(double quangDuong = 0) const override {
        double phiCoBan = 150000;
        if (congSuat > 150) phiCoBan += 200000;
        if (quangDuong <= 0) return phiCoBan;
        double litTieuThuMoi100Km = 1.8;
        if (congSuat > 150) litTieuThuMoi100Km = 3.5;
        else if (congSuat >= 125) litTieuThuMoi100Km = 2.2;
        string htd = toLower(heTruyenDong);
        if (htd.find("xe ga") != string::npos || htd.find("tay ga") != string::npos) {
            litTieuThuMoi100Km += 0.5;
        }
        double tienXang = (quangDuong / 100.0) * litTieuThuMoi100Km * 22000;
        return phiCoBan + tienXang;
    }
    // Hàm nhập thông tin xe máy
    void Nhap(istream& in) override {
        PhuongTien::Nhap(in);        // Gọi hàm nhập của lớp PhuongTien
        // Nhập công suất
        setColor(C_VIEN); cout << "  " << char(254) << " Nhap cong suat: ";
        setColor(C_TEXT);
        in >> congSuat;
        if (in.fail() || congSuat < 0) {
            in.clear();
            congSuat = 0;
        }
        in.ignore(32767,'\n');
        // Nhập hệ truyền động
        setColor(C_VIEN); cout << "  " << char(254) << " Nhap he truyen dong: ";
        setColor(C_TEXT);
        getline(in,heTruyenDong);
    }
    // Hàm hiển thị thông tin
    void HienThiThongTin(ostream& out) const {
        PhuongTien::HienThiThongTin(out);
    }
    // Quá tải nhập
    friend istream& operator>>(istream& in, XeMay &p) {
        p.Nhap(in);
        return in;
    }
    // Quá tải xuất
    friend ostream& operator<<(ostream& out, const XeMay &p) {
        p.HienThiThongTin(out);
        return out;
    }
};
