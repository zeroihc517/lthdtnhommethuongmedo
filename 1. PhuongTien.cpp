#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <ctime>
#include <windows.h>
using namespace std;
class PhuongTien {
protected:
    string bienSo;                      // Biển số của phương tiện
    string hangSanXuat;                 // Tên hàng sản xuất
    int namSanXuat;                     // Năm sản xuất
    double giaGoc;                      // Giá gốc của phương tiện
    int thangHetHanBaoHiem;             // Tháng hết hạn bảo hiểm
    int namHetHanBaoHiem;               // Năm hết hạn bảo hiểm
public:
    // Hàm khởi tạo mặc định
    PhuongTien() {
        bienSo = "";
        hangSanXuat = "";
        namSanXuat = 1900;
        giaGoc = 0;
        thangHetHanBaoHiem = 1;
        namHetHanBaoHiem = 2025;
    }
    // Hàm khởi tạo có tham số
    PhuongTien(string bs, string hsx, int nsx, double gia, int thanghh, int namhh) {
        bienSo = bs;
        hangSanXuat = hsx;
        namSanXuat = nsx;
        giaGoc = gia;
        thangHetHanBaoHiem = thanghh;
        namHetHanBaoHiem = namhh;
    }
    // Hàm khởi tạo sao chép
    PhuongTien(const PhuongTien& p) {
        bienSo = p.bienSo;
        hangSanXuat = p.hangSanXuat;
        namSanXuat = p.namSanXuat;
        giaGoc = p.giaGoc;
        thangHetHanBaoHiem = p.thangHetHanBaoHiem;
        namHetHanBaoHiem = p.namHetHanBaoHiem;
    }
    // Hàm hủy
    virtual ~PhuongTien() {}
    // Hàm get
    string getBienSo() const { return bienSo; }
    string getHangSanXuat() const { return hangSanXuat; }
    int getNamSanXuat() const { return namSanXuat; }
    double getGiaGoc() const { return giaGoc; }
    int getThangHetHanBaoHiem() const { return thangHetHanBaoHiem; }
    int getNamHetHanBaoHiem() const { return namHetHanBaoHiem; }
    // Hàm set
    void setBienSo(string bs) { bienSo=bs; }
    void setHangSanXuat(string hsx) { hangSanXuat=hsx; }
    void setNamSanXuat(int nsx) { namSanXuat=nsx; }
    void setGiaGoc(double gia) { giaGoc=gia; }
    void setThangHetHanBaoHiem(int thanghh) { thangHetHanBaoHiem=thanghh; }
    void setNamHetHanBaoHiem(int namhh) { namHetHanBaoHiem=namhh; }
    // Phương thức thuần ảo
    virtual string GetLoaiPhuongTien() const=0;     // Trả về loại phương tiện, ví dụ: Xe máy, Ô tô... 
    virtual string GetThongSo() const=0;            // Trả về thông số riêng của phương tiện, ví dụ: Số chỗ ngồi, dung tích xi lanh...
    virtual double TinhPhiBaoTri() const=0;         // Tính phí bảo trì của phương tiện
    // Kiểm tra niên hạn
    void KiemTraNienHan(int namHienTai=2026) const {
        if (namHienTai-namSanXuat>20) {
            inHieuUng("  [CANH BAO] Xe da qua 20 nam su dung, da qua nien han!!\n", C_LOI);
        }
    }
    // Lấy mã vùng
    string LayMaVung() const {
        if (bienSo.length()>=2) { 
            return bienSo.substr(0, 2);             // Lấy 2 kí tự bắt đầu từ vị trí 0
        }
        return "Unknown";                           // Nếu biển số có ít hơn 2 kí tự
    }
    // Tính giá trị hiện tại
    double TinhGiaTriHienTai(int namHienTai=2026) const {
        int soNam=namHienTai-namSanXuat;
        if (soNam<0) { soNam=0; }
        return giaGoc*pow(0.9, soNam);
    }
    // Kiểm tra bảo hiểm đã hết hạn hay chưa?
    void KiemTraBaoHiem(int thangHienTai, int namHienTai) const {
        if (namHienTai>namHetHanBaoHiem || (namHienTai==namHetHanBaoHiem && thangHienTai>thangHetHanBaoHiem)) {
            inHieuUng("  [CANH BAO] Xe da het han bao hiem dan su! Muc phat du kien: 400.000 - 600.000 VND.\n", C_LOI);
        }
    }
    // Nhập thông tin
    virtual void Nhap(istream& in) {
        setColor(C_VIEN); cout << "  " << char(204) << char(205) << " Nhap Bien so: ";
        setColor(C_TEXT); getline(in, bienSo);
        setColor(C_VIEN); cout << "  " << char(204) << char(205) << " Nhap Hang san xuat: ";
        setColor(C_TEXT); getline(in, hangSanXuat);
        setColor(C_VIEN); cout << "  " << char(204) << char(205) << " Nhap Nam san xuat: ";
        setColor(C_TEXT); in>>namSanXuat;
        if (in.fail()) { in.clear(); }                                  // Nếu lượng nhập bị lỗi thì xóa có lỗi
        in.ignore(32767, '\n');
        setColor(C_VIEN); cout << "  " << char(204) << char(205) << " Nhap Gia goc (VND): ";
        setColor(C_TEXT); in >> giaGoc;
        if (in.fail()) { in.clear(); }                                  // Xử lý có lỗi (nếu có)
        in.ignore(32767, '\n');
    }
    // Hiển thị thông tin
    virtual void HienThiThongTin(ostream& out) const {
        out << left
            << setw(W_BIENSO) << bienSo                                 // In biển số theo độ rộng W_BIENSO
            << setw(W_HANG) << hangSanXuat                              // In hãng sản suất
            << setw(W_NAMSX) << namSanXuat                              // In năm sản xuất
            << setw(W_LOAI) << GetLoaiPhuongTien()                      // Gọi hàm ảo để lấy loại phương tiện
            << setw(W_THONGSO) << GetThongSo();                         // Gọi hàm ảo để lấy thông số riêng
        stringstream ssPhi;                                         // Tạo lượng chuỗi để định dạng phí bảo trì
        ssPhi << fixed << setprecision(0) << TinhPhiBaoTri() << " VND";     
        out << right << setw(W_PHI) << ssPhi.str();                       // Căn lề phải và in phí bảo trì theo độ rộng cột
    }
    // Toán tử nhập
    friend istream& operator >> (istream& in, PhuongTien& p) {
        p.Nhap(in);
        return in;
    }
    // Toán tử xuất
    friend ostream& operator << (ostream& out, const PhuongTien& p) {
        p.HienThiThongTin(out);
        return out;
    }
};
