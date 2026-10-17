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
    XeTai(string bs, string hsx, int nsx, double gia, double tt, int soTruc, string loaiThung) : PhuongTien(bs, hsx, nsx, gia, 0, 0) {
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
   // hàm chi phí lăn bánh (như là tiền xăng, tiền bảo dưỡng, tiền hư hao xe cũ, tiền trục trặc máy móc,... )
    double TinhChiPhiLanBanh(double quangDuong, int namHienTai) const {
        // Quãng đường không hợp lệ
        if (quangDuong < 0) { return 0; }
        if (getNamSanXuat() > namHienTai) {
            cout << "[LOI] Nam san xuat khong the lon hon nam hien tai!\n";
        }
        // Chi phi co ban: 5000 VND/km
        double chiPhiMoiKm = 5000;
        // Tải trọng càng lớn -> chi phí vận hành càng cao
        if (taiTrong > 5) {
            chiPhiMoiKm += 3000;
        } else if (taiTrong > 2) {
            chiPhiMoiKm += 1500;
        }
        // Số trục càng nhiều -> chi phí vận hành càng cao
        if (soTrucBanhXe >= 4) {
            chiPhiMoiKm += 2000;
        } else if (soTrucBanhXe == 3) {
            chiPhiMoiKm += 1000;
        }
        // Xe sử dụng trên 10 năm -> chi phí vận hành tăng
        int tuoiXe = namHienTai - getNamSanXuat();
        if (tuoiXe > 10) {
            chiPhiMoiKm += 1000;
        }
        // Tổng chi phí lăn bánh
        return quangDuong * chiPhiMoiKm;
    }
    // Hàm tính cước vận chuyển (đây là tiền mà khách phải trả khi muốn đặt xe)  = hàm chi phí lăn bánh + hàm phí vận chuyển 
    double TinhCuocVanChuyen(double quangDuong, int namHienTai) const {
        if (quangDuong < 0) return 0;
        double chiPhiLanBanh = TinhChiPhiLanBanh(quangDuong, namHienTai);
        double phiVanChuyen = 0; // mặc định hàm phí vận chuyển = 0 trước
        // Tính phí dựa trên tải trọng
        if (taiTrong <= 2) {
            phiVanChuyen = quangDuong * 5000; // tải trọng <= 2 thì tiền = quãng đường * 5000đ
        } else if (taiTrong <= 5) {
            phiVanChuyen = quangDuong * 8000; // tải trọng <= 5 thì tiền = quãng đường * 8000đ
        } else {
            phiVanChuyen = quangDuong * 12000; // tải trọng > 5 thì tiền = quãng đường * 12000đ
        }
        // Thùng đông lạnh tốn chi phí cao hơn ( vi xe đông lạnh cần máy móc hơn để bảo quản đồ đông lạnh ) 
        string loai = toLower(loaiThungXe);
        if (loai == "dong lanh") {
           phiVanChuyen += quangDuong * 3000;
        }
        return chiPhiLanBanh + phiVanChuyen;    // ta có hàm cước vận chuyển 
    }
    // ĐÁNH GIẢ KHẢ NĂNG VẬN CHUYỂN DỰA TRÊN TẢI TRỌNG , ĐỂ KHÁCH HÀNG CHỌN
    string DanhGiaKhaNangVanChuyen() const { // đánh giá xem vận chuyển hàng nặng hay nhẹ
        if (taiTrong <= 2) {
            return "Van chuyen hang nhe";
        }
        if (taiTrong <= 5) {
            return "Van chuyen hang trung binh";
        }
        return "Van chuyen hang nang";
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
    // HÀM KIỂM TRA XE CÓ ĐẢM BẢO CHẤT LƯỢNG/LỢI NHUẬN HAY KO , DỰA TRÊN TUỔI XE,CHI PHÍ LĂN BÁNH, 
    // NẾU XE QUÁ CŨ , TỐN NHIỀU TIỀN MÀ LỜI THẤP THÌ KO ĐỦ TIÊU CHUẨN
    bool KiemTraXeCoNenThayThe(int namHienTai) const {
        if (getNamSanXuat() > namHienTai) {
            cout << "[LOI] Nam san xuat khong the lon hon nam hien tai!\n";
            return false;
        }
        int tuoiXe = namHienTai - getNamSanXuat();
        double giaTriHienTai = TinhGiaTriHienTai(namHienTai);
        double chiPhiLanBanh = TinhChiPhiLanBanh(100, namHienTai);
        if (tuoiXe > 15 && giaTriHienTai < getGiaGoc() * 0.3 && chiPhiLanBanh > 1000000) {
            return true;
        }
        return false;
    }
    // HÀM KIỂM TRA CÓ ĐƯỢC VÀO PHỐ KO , XE < 1,5 tấn auto được vào , xe lớn mà chạy trong khung 6h - 9h&& 16h-20h thì gây ùn tắc giao thông rất nặng
    bool DuocPhepVaoPho(int gioHienTai) const {
        if (gioHienTai < 0 || gioHienTai > 23) {
            cout << "[LOI] Gio hien tai phai tu 0 den 23!\n";
            return false;
        }
        if (taiTrong <= 1.5) { return true; }
        if (gioHienTai >= 6 && gioHienTai < 9) { return false; }
        if (gioHienTai >= 16 && gioHienTai < 20) { return false; }
        return true;
    }
    // Hàm nhập
    void Nhap(istream& in) {
        // Goi ham Nhap cua lop cha
        PhuongTien::Nhap(in);
        // Nhap tai trong
        setColor(C_VIEN);
        cout << "  " << char(204) << char(205) << " Nhap Tai trong (tan): ";
        setColor(C_TEXT);
        in >> taiTrong;
        if (in.fail()) {    // Nếu nhập lỗi thì xóa màn hình
            in.clear();
        }
        in.ignore(32767, '\n');
        // Nhap loai thung
        setColor(C_VIEN);
        cout << "  " << char(204) << char(205) << " Nhap Loai thung xe: ";
        setColor(C_TEXT);
        getline(in, loaiThungXe);
        // Nhap so truc
        setColor(C_VIEN);
        cout << "  " << char(204) << char(205)
             << " Nhap So truc banh xe: ";
        setColor(C_TEXT);
        in >> soTrucBanhXe;
        if (in.fail()) {
            in.clear();// nếu nhập lỗi thì xóa màn hình
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
