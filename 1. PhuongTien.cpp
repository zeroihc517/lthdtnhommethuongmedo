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
public:
    // Hàm khởi tạo mặc định
    PhuongTien() {
        bienSo = "";
        hangSanXuat = "";
        namSanXuat = 1900;
        giaGoc = 0;
    }
    // Hàm khởi tạo có tham số
    PhuongTien(string bs, string hsx, int nsx, double gia) {
        bienSo = bs;
        hangSanXuat = hsx;
        namSanXuat = nsx;
        giaGoc = gia;
    }
    // Hàm khởi tạo sao chép
    PhuongTien(const PhuongTien& p) {
        bienSo = p.bienSo;
        hangSanXuat = p.hangSanXuat;
        namSanXuat = p.namSanXuat;
        giaGoc = p.giaGoc;
    }
    // Hàm hủy
    virtual ~PhuongTien() {}
    // Hàm chuyển toàn bộ ký tự chữ cái in hoa trong chuỗi thành chữ thường
    static string toLower(string str) {                    
        for (size_t i = 0; i < str.length(); i++) {        // Duyệt lần lượt từng ký tự trong chuỗi str
            if (str[i] >= 'A' && str[i] <= 'Z') {         // Kiểm tra ký tự hiện tại có nằm trong khoảng từ 'A' đến 'Z' hay không
                str[i] = str[i] + 32;                     // Chuyển chữ in hoa thành chữ thường bằng cách cộng thêm 32 vào mã ASCII
            }
        }
        return str;                                      // Trả về chuỗi sau khi đã chuyển các chữ cái in hoa thành chữ thường
    }
    // Hàm get
    string getBienSo() const { return bienSo; }
    string getHangSanXuat() const { return hangSanXuat; }
    int getNamSanXuat() const { return namSanXuat; }
    double getGiaGoc() const { return giaGoc; }
    // Hàm set
    void setBienSo(string bs) { bienSo = bs; }
    void setHangSanXuat(string hsx) { hangSanXuat = hsx; }
    void setNamSanXuat(int nsx) { namSanXuat = nsx; }
    void setGiaGoc(double gia) { giaGoc = gia; }
    // Phương thức thuần ảo
    virtual string GetLoaiPhuongTien() const=0;     // Trả về loại phương tiện, ví dụ: Xe máy, Ô tô... 
    virtual string GetThongSo() const=0;            // Trả về thông số riêng của phương tiện, ví dụ: Số chỗ ngồi, dung tích xi lanh...
    virtual double TinhPhiBaoTri() const=0;         // Tính phí bảo trì của phương tiện
    // Tính giá trị hiện tại
    double TinhGiaTriHienTai(int namHienTai=2026) const {
        int soNam = namHienTai - namSanXuat;
        if (soNam < 0) { soNam = 0; }
        return giaGoc*pow(0.9, soNam);
    }
    // Nhập thông tin
    virtual void Nhap(istream& in) {
        setColor(C_VIEN); cout << "  " << char(204) << char(205) << " Nhap Bien so: ";
        setColor(C_TEXT); getline(in, bienSo);
        
        setColor(C_VIEN); cout << "  " << char(204) << char(205) << " Nhap Hang san xuat: ";
        setColor(C_TEXT); getline(in, hangSanXuat);
        
        // --- ĐÃ ĐƯA LOGIC KIỂM TRA NĂM VÀO ĐÂY ---
        time_t now = time(0);
        tm* ltm = localtime(&now);
        int namHienTai = 1900 + ltm->tm_year;

        setColor(C_VIEN); cout << "  " << char(204) << char(205) << " Nhap Nam san xuat: ";
        setColor(C_TEXT); 
        // Vòng lặp gom chung bắt lỗi nhập chữ (fail) và lỗi logic (sai khoảng năm)
        while (!(in >> namSanXuat) || namSanXuat < 1900 || namSanXuat > namHienTai) {
            in.clear(); // Xóa cờ lỗi
            in.ignore(32767, '\n'); // Bỏ qua ký tự thừa
            setColor(C_VIEN);
            cout << "  " << char(204) << char(205) << " [LOI] Nam san xuat phai tu 1900 den " << namHienTai << "!\n";
            cout << "  " << char(204) << char(205) << " Nhap lai Nam san xuat: ";
            setColor(C_TEXT);
        }
        in.ignore(32767, '\n');

        setColor(C_VIEN); cout << "  " << char(204) << char(205) << " Nhap Gia goc (VND): ";
        setColor(C_TEXT); 
        while (!(in >> giaGoc) || giaGoc < 0) { // Sẵn tiện bắt lỗi giá gốc âm
            in.clear();
            in.ignore(32767, '\n');
            setColor(C_VIEN); cout << "  " << char(204) << char(205) << " [LOI] Gia goc khong hop le!\n";
            cout << "  " << char(204) << char(205) << " Nhap lai Gia goc (VND): ";
            setColor(C_TEXT);
        }
        in.ignore(32767, '\n');
    }
    // Hiển thị thông tin
    virtual void HienThiThongTin(ostream& out) const {
        out << left
            << setw(W_BIENSO) << bienSo                                     // In biển số theo độ rộng W_BIENSO
            << setw(W_HANG) << hangSanXuat                                  // In hãng sản suất
            << setw(W_NAMSX) << namSanXuat                                  // In năm sản xuất
            << setw(W_LOAI) << GetLoaiPhuongTien()                          // Gọi hàm ảo để lấy loại phương tiện
            << setw(W_THONGSO) << GetThongSo();                             // Gọi hàm ảo để lấy thông số riêng
        stringstream ssPhi;                                                 // Tạo lượng chuỗi để định dạng phí bảo trì
        ssPhi << fixed << setprecision(0) << TinhPhiBaoTri() << " VND";     
        out << right << setw(W_PHI) << ssPhi.str();                          // Căn lề phải và in phí bảo trì theo độ rộng cột
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
