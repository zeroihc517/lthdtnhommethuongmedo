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
    XeTai(string bs, string hsx, int nsx, double gia, int thanghh, int namhh,  double tt, int soTruc, string loaiThung) : PhuongTien(bs, hsx, nsx, gia, thanghh, namhh) {
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
   // hàm chi phí lăn bánh ( như là tiền xăng, tiền bảo dưỡng, tiền hư hao xe cũ, tiền trục trặc máy móc, ...  )
    double TinhChiPhiLanBanh(double quangDuong) const {
        if (quangDuong < 0) { return 0; }
        double chiPhiMoiKm = 5000; // mặc định chi phí lăn bánh = 5000d/1km . ( giống như đi 1km là tốn 5000đ tiền xăng )
        if (taiTrong > 5) { // nếu tải trọng càng lớn thì chi phí càng cao ( vì xe càng lớn, càng nặng , thì năng lượng cần tiêu thụ sẽ phát sinh lớn hơn, cần công suất lớn hơn , tốn tiền xăng hơn )
            chiPhiMoiKm += 3000;  // nếu tải trọng lớn hơn 5 thì + thêm 3000d vào chiphi/1km
        }
        else if (taiTrong > 2) {  // nếu tải trọng lớn hơn 2 thì + thêm 1500d vào chiphi/1km
            chiPhiMoiKm += 1500;
        }
        // Xe nhiều trục -> chi phí vận hành cao hơn (xe càng kéo theo nhiều trục , xe tải cần nhiều năng lượng hơn để tăng sức kéo , cộng thêm năng lượng hao phí thì chi phí lăn bánh sẽ tăng) 
        if (soTrucBanhXe >= 4) {  // nếu xe tải có nhiều hơn 4 trục thì + thêm 2000d vào chiphi/1km
            chiPhiMoiKm += 2000;
        }
        else if (soTrucBanhXe == 3) { // nếu xe tải có 3 trục thì + thêm 1000d vào chiphi/1km
            chiPhiMoiKm += 1000;
        }
        // Xe quá cũ -> chi phí vận hành tăng (xe đời cũ , máy móc đời cũ sẽ dễ dàng hư hơn , tốn nhiều nhiên liệu hơn để chạy)
        int tuoiXe = 2026 - getNamSanXuat(); // tuổi xe = 2026 - năm sản xuất 
        if (tuoiXe > 10) {
            chiPhiMoiKm += 1000; // xe sài hơn 10 năm rồi thì máy cũ nên vận hành tốn tiền hơn nên +1000d/1km;
        }
        return quangDuong * chiPhiMoiKm; // tổng giá tiền phải tốn cũng mỗi chuyến đi
    }
    // Hàm tính cước vận chuyển (đây là tiền mà khách phải trả khi muốn đặt xe)  = hàm chi phí lăn bánh + hàm phí vận chuyển 
    double TinhCuocVanChuyen(double quangDuong) const {     // Giá tiền 1 cuốc xe tai khách phải trả 
        if (quangDuong < 0) { return 0; }
        // Tạo hàm chi phí lăn bánh trước 
        double chiPhiLanBanh = TinhChiPhiLanBanh(quangDuong);
        double phiVanChuyen = 0; // mặc định hàm phí vận chuyển = 0 trước
        // Tính phí dựa trên tải trọng
        if (taiTrong <= 2) {
            phiVanChuyen = quangDuong * 5000; // tải trọng <= 2 thì tiền = quãng đường * 5000đ
        }
        else if (taiTrong <= 5) {
            phiVanChuyen = quangDuong * 8000; // tải trọng <= 5 thì tiền = quãng đường * 8000đ
        }
        else {
            phiVanChuyen = quangDuong * 12000; // tải trọng > 5 thì tiền = quãng đường * 12000đ
        }
        // Thùng đông lạnh tốn chi phí cao hơn ( vi xe đông lạnh cần máy móc hơn để bảo quản đồ đông lạnh ) 
        if (loaiThungXe == "Dong lanh" || loaiThungXe == "dong lanh") {
            phiVanChuyen += quangDuong * 3000;    // tiền = quãng đường * 3000đ nữa
        }
        return chiPhiLanBanh + phiVanChuyen;// ta có hàm cước vận chuyển 
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
    string PhanLoaiThungXe() const { // hàm phân loại thùng xe
        if (loaiThungXe == "Dong lanh" || loaiThungXe == "dong lanh") {
            return "Thung dong lanh";   // thùng mà có hệ thống giữ nhiệt đông lạnh
        }
        if (loaiThungXe == "Thung kin" || loaiThungXe == "thung kin") {
            return "Thung kin"; // thùng mà có nóc 
        }
        if (loaiThungXe == "Thung bat" || loaiThungXe == "thung bat") {
            return "Thung bat"; // thùng được che bằng miếng bạt
        }
        if (loaiThungXe == "Xe ben" || loaiThungXe == "xe ben") {
            return "Xe ben"; // xe có thể nâng lên nâng xuống 
        }
        return "Khong xac dinh";
    }
    // HÀM KIỂM TRA XE CÓ ĐẢM BẢO CHẤT LƯỢNG/LỢI NHUẬN HAY KO , DỰA TRÊN TUỔI XE,CHI PHÍ LĂN BÁNH, 
    // NẾU XE QUÁ CŨ , TỐN NHIỀU TIỀN MÀ LỜI THẤP THÌ KO ĐỦ TIÊU CHUẨN
    bool KiemTraXeCoNenThayThe(int namHienTai = 2026) const {
        int tuoiXe = namHienTai - getNamSanXuat(); // hàm tuổi xe 
        double giaTriHienTai = TinhGiaTriHienTai(namHienTai); 
        // Chi phi lan banh trong 100 km
        double chiPhiLanBanh = TinhChiPhiLanBanh(100);
        // Xe quá cũ + giá trị còn lại thấp
        // + chi phí lăn bánh cao
        if (tuoiXe > 15 &&
            giaTriHienTai < getGiaGoc() * 0.3 && // giá trị hiện tại < giá gốc x 30% ( nghĩa là Giá trị hiện tại của xe đã thấp hơn 30% giá gốc.)
            chiPhiLanBanh > 1000000) {
            return true; // là nên thay thế rồi
        }
        return false; // xe vẫn ổn chạy được
    }
// HÀM KIỂM TRA CÓ ĐƯỢC VÀO PHỐ KO , XE < 1,5 tấn auto được vào , xe lớn mà chạy trong khung 6h - 9h&& 16h-20h thì gây ùn tắc giao thông rất nặng
    bool DuocPhepVaoPho(int gioHienTai) const {
        // Xe <= 1.5 tan duoc phep vao
        if (taiTrong <= 1.5) {
            return true; // cho vào
        }
        // Khung gio 6h - 9h
        if (gioHienTai >= 6 && gioHienTai < 9) {
            return false; // ko cho vào
        }
        // Khung gio 16h - 20h
        if (gioHienTai >= 16 && gioHienTai < 20) {
            return false; // ko cho vào
        }
        return true;// cho vào
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
