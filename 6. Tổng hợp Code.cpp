#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <ctime>
#include <windows.h>
using namespace std;

#define C_VIEN    11
#define C_TIEU_DE 14
#define C_TEXT    15
#define C_CHON    10
#define C_LOI     12
#define W_BIENSO   12
#define W_HANG     15 
#define W_NAMSX    8
#define W_LOAI     10
#define W_THONGSO  33
#define W_PHI      18
#define W_FRAME    80
#define M_W_IN     50
#define M_W_FRAME  52

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void inHieuUng(string text, int color, int delay = 5) {
    setColor(color);       
    for (int i = 0; i < text.length(); i++) {      
        cout << text[i];               
        Sleep(delay);        
    }
}
void inTieuDeMenu(string title, int color) {
    setColor(C_VIEN); cout << "  " << char(186) << " ";
    setColor(color);
    int padLeft = (M_W_IN - (int)title.length()) / 2;
    int padRight = M_W_IN - (int)title.length() - padLeft;
    cout << string(padLeft, ' ') << title << string(padRight, ' ');   
    setColor(C_VIEN); cout << " " << char(186) << "\n";          
}
void inDongMenu(string stt, string text, int sttColor = C_TIEU_DE) {
    setColor(C_VIEN); cout << "  " << char(186) << " "; 
    setColor(sttColor); 
    string prefix = stt + ". ";
    cout << left << setw(4) << prefix;
    setColor(C_TEXT);   
    cout << left << setw(46) << text;  
    setColor(C_VIEN); cout << " " << char(186) << "\n";     
}
string DinhDangTien(double tien) {
    long long giaTri = (long long)tien;
    stringstream ss;
    ss << giaTri;
    string s = ss.str();
    int n = s.length();
    for (int i = n - 3; i > 0; i -= 3) {
        s.insert(i, ".");
    }
    return s;
}
string toLower(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
    return str;
}

class PhuongTien {
protected:
    string bienSo;
    string hangSanXuat;  
    int namSanXuat; 
    double giaGoc;
public:
    PhuongTien() {
        bienSo = "";
        hangSanXuat = "";
        namSanXuat = 1900;
    }
    PhuongTien(string bs, string hsx, int nsx) {
        bienSo = bs;
        hangSanXuat = hsx;
        namSanXuat = nsx;
    }
    PhuongTien(const PhuongTien& p) {
        bienSo = p.bienSo;
        hangSanXuat = p.hangSanXuat;
        namSanXuat = p.namSanXuat;
    }
    virtual ~PhuongTien() {}
    string getBienSo() const { return bienSo; }
    string getHangSanXuat() const { return hangSanXuat; }
    int getNamSanXuat() const { return namSanXuat; }
    void setBienSo(string bs) { bienSo = bs; }
    void setHangSanXuat(string hsx) { hangSanXuat = hsx; }
    void setNamSanXuat(int nsx) { namSanXuat = nsx; }
    virtual string GetLoaiPhuongTien() const=0;
    virtual string GetThongSo() const=0;
    double TinhPhiBaoTri(double quangDuong, double phiCoBan, double litTieuThu, double donGia) const {
        if (quangDuong <= 0) return phiCoBan;
        return phiCoBan + (quangDuong / 100.0) * litTieuThu * donGia;
    }
    virtual double TinhPhiBaoTri(double quangDuong = 0) const=0;
    virtual void Nhap(istream& in) {
        setColor(C_VIEN); cout << "  " << char(254) << " Nhap Bien so: ";
        setColor(C_TEXT); getline(in, bienSo);
        setColor(C_VIEN); cout << "  " << char(254) << " Nhap Hang san xuat: ";
        setColor(C_TEXT); getline(in, hangSanXuat);
        time_t now = time(0);
        tm* ltm = localtime(&now);
        int namHienTai = 1900 + ltm->tm_year;
        setColor(C_VIEN);
        cout << "  " << char(254) << " Nhap Nam san xuat: ";
        setColor(C_TEXT);
        while (!(in >> namSanXuat) ||
            namSanXuat < 1900 || namSanXuat > namHienTai) {
            in.clear();
            in.ignore(32767, '\n');
            setColor(C_LOI); cout << "  " << char(254) << " [LOI] Nam san xuat phai tu 1900 den " << namHienTai << "!\n";
            setColor(C_VIEN); cout << "  " << char(254) << " Nhap lai Nam san xuat: ";
            setColor(C_TEXT);
        }
        in.ignore(32767, '\n');
    }
    virtual void HienThiThongTin(ostream& out) const {
        out << left
            << setw(W_BIENSO) << bienSo
            << setw(W_HANG) << hangSanXuat
            << setw(W_NAMSX) << namSanXuat
            << setw(W_LOAI) << GetLoaiPhuongTien()
            << setw(W_THONGSO) << GetThongSo();
    }
    friend istream& operator >> (istream& in, PhuongTien& p) {
        p.Nhap(in);
        return in;
    }
    friend ostream& operator << (ostream& out, const PhuongTien& p) {
        p.HienThiThongTin(out);
        return out;
    }
};

class XeOto : public PhuongTien {
private:
    int soChoNgoi;
    string kieuDang;
public:
    XeOto() : PhuongTien() {
        soChoNgoi = 4;
        kieuDang = "";
    }
    XeOto(string bs, string hsx, int nsx, int soCho, string kd) : PhuongTien(bs, hsx, nsx) {
        soChoNgoi = soCho;
        kieuDang = kd;
    }
    XeOto(const XeOto& p) : PhuongTien(p) {
        soChoNgoi = p.soChoNgoi;
        kieuDang = p.kieuDang;
    }
    ~XeOto() override {}
    int getSoChoNgoi() const { return soChoNgoi; }
    string getKieuDang() const { return kieuDang; }
    void setSoChoNgoi(int soCho) { soChoNgoi = soCho; }
    void setKieuDang(string kd) { kieuDang = kd; }
    string GetLoaiPhuongTien() const override {
        return "Xe oto";
    }
    string GetThongSo() const override {
        stringstream ss;
        ss << soChoNgoi << " cho" << " - " << kieuDang;
        return ss.str();
    }
    double TinhPhiBaoTri(double quangDuong = 0) const override {
        double phiCoBan = 1500000;
        if (soChoNgoi <= 5) phiCoBan += 500000;
        else if (soChoNgoi <= 9) phiCoBan += 1000000;
        else phiCoBan += 2000000;
        double litTieuThu = 8.0;
        string kd = toLower(kieuDang);
        if (soChoNgoi > 7 || kd.find("suv") != string::npos) litTieuThu = 12.0;
        else if (soChoNgoi > 5) litTieuThu = 10.0;
        return PhuongTien::TinhPhiBaoTri(quangDuong, phiCoBan, litTieuThu, 22000);
    }
    void Nhap(istream& in) override {
        PhuongTien::Nhap(in);
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
        setColor(C_VIEN);
        cout << "  " << char(254) << " Nhap Kieu dang (Sedan, SUV, Hatchback...): ";
        setColor(C_TEXT);
        getline(in, kieuDang);
    }
    void HienThiThongTin(ostream& out) const {
        PhuongTien::HienThiThongTin(out);
    }
    friend istream& operator>>(istream& in, XeOto& p) {
        p.Nhap(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, const XeOto& p) {
        p.HienThiThongTin(out);
        return out;
    }
};

class XeMay : public PhuongTien {
private:
    double congSuat;
    string heTruyenDong;
public:
    XeMay():PhuongTien(){
        congSuat = 0;
        heTruyenDong = "Xe so";
    }
    XeMay(string bs,string hsx, int nsx, double cs, string htd):PhuongTien(bs, hsx, nsx){
        congSuat = (cs>0) ? cs:0;
        heTruyenDong = htd;
    }
    XeMay(const XeMay &p):PhuongTien(p){
        congSuat = p.congSuat;
        heTruyenDong = p.heTruyenDong;
    }
    ~XeMay() override{}
    double getCongSuat() const { return congSuat; }
    string getHeTruyenDong() const { return heTruyenDong; }
    void setCongSuat (double cs) { if(cs >= 0) congSuat = cs; }
    void setHeTruyenDong (string htd) { heTruyenDong = htd; }
    string GetLoaiPhuongTien() const override { return "Xe may"; }
    string GetThongSo() const override {
        stringstream ss;
        ss << fixed << setprecision(0) << congSuat << " - " << heTruyenDong;
        return ss.str();
    }
    double TinhPhiBaoTri(double quangDuong = 0) const override {
        double phiCoBan = 150000;
        if (congSuat > 150) phiCoBan += 200000;
        double litTieuThu = 1.8;
        if (congSuat > 150) litTieuThu = 3.5;
        else if (congSuat >= 125) litTieuThu = 2.2;
        string htd = toLower(heTruyenDong);
        if (htd.find("xe ga") != string::npos || htd.find("tay ga") != string::npos) {
            litTieuThu += 0.5;
        }
        return PhuongTien::TinhPhiBaoTri(quangDuong, phiCoBan, litTieuThu, 22000);
    }
    void Nhap(istream& in) override {
        PhuongTien::Nhap(in);
        setColor(C_VIEN); cout << "  " << char(254) << " Nhap cong suat: ";
        setColor(C_TEXT);
        in >> congSuat;
        if (in.fail() || congSuat < 0) {
            in.clear();
            congSuat = 0;
        }
        in.ignore(32767,'\n');
        setColor(C_VIEN); cout << "  " << char(254) << " Nhap he truyen dong: ";
        setColor(C_TEXT);
        getline(in,heTruyenDong);
    }
    void HienThiThongTin(ostream& out) const {
        PhuongTien::HienThiThongTin(out);
    }
    friend istream& operator>>(istream& in, XeMay &p) {
        p.Nhap(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, const XeMay &p) {
        p.HienThiThongTin(out);
        return out;
    }
};

class XeTai : public PhuongTien {
private:
    double taiTrong;
    int soTrucBanhXe;
    string loaiThungXe;
public:
    XeTai() : PhuongTien() {
        taiTrong = 0;
        soTrucBanhXe = 0;
        loaiThungXe = "";
    }
    XeTai(string bs, string hsx, int nsx, double tt, int soTruc, string loaiThung) : PhuongTien(bs, hsx, nsx) {
        taiTrong = tt;
        soTrucBanhXe = soTruc;
        loaiThungXe = loaiThung;
    }
    XeTai(const XeTai& p) : PhuongTien(p) {
        taiTrong = p.taiTrong;
        soTrucBanhXe = p.soTrucBanhXe;
        loaiThungXe = p.loaiThungXe;
    }
    ~XeTai() override {}
    double getTaiTrong() const { return taiTrong; }
    int getSoTrucBanhXe() const { return soTrucBanhXe; }
    string getLoaiThungXe() const { return loaiThungXe; }
    void setTaiTrong(double tt) { taiTrong = tt; }
    void setSoTrucBanhXe(int soTruc) { soTrucBanhXe = soTruc; }
    void setLoaiThungXe(string loaiThung) { loaiThungXe = loaiThung; }
    string GetLoaiPhuongTien() const override {
        return "Xe tai";
    }
    string GetThongSo() const override {
        stringstream ss;
        ss << taiTrong << " tan" << " - " << loaiThungXe << " - " << soTrucBanhXe << " truc";
        return ss.str();
    }
    double TinhPhiBaoTri(double quangDuong = 0) const override {
        double phiCoBan = 1000000 + taiTrong * 200000;
        double litTieuThu = 12.0; 
        if (taiTrong > 5) litTieuThu += 10.0;
        else if (taiTrong > 2) litTieuThu += 5.0;
        if (soTrucBanhXe >= 4) litTieuThu += 4.0;
        string loai = toLower(loaiThungXe);
        if (loai.find("dong lanh") != string::npos) litTieuThu += 3.0;
        return PhuongTien::TinhPhiBaoTri(quangDuong, phiCoBan, litTieuThu, 20000);
    }
    void Nhap(istream& in) override {
        PhuongTien::Nhap(in);
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
        setColor(C_VIEN); cout << "  " << char(254) << " Nhap Loai thung xe: ";
        setColor(C_TEXT);
        getline(in, loaiThungXe);
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
    void HienThiThongTin(ostream& out) const {
        PhuongTien::HienThiThongTin(out);
    }
    friend istream& operator>>(istream& in, XeTai& p) {
        p.Nhap(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, const XeTai& p) {
        p.HienThiThongTin(out);
        return out;
    }
};

class QuanLyPhuongTien {
private:
    vector<PhuongTien*> ds;
public:
    ~QuanLyPhuongTien() {
        for (int i = 0; i < ds.size(); i++) {
            delete ds[i];
        }
        ds.clear();
    }
    void ThemPhuongTien(PhuongTien* pt) {
        if (pt != NULL) {
            ds.push_back(pt);
        }
    }
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
    void TinhTongPhiBaoTri() const {
        system("cls");
        int frameW = 52; 
        double quangDuong = 0;
        setColor(C_TIEU_DE);
        cout << "\n  *********** DU TOAN CHI PHI (BAO TRI + NHIEN LIEU) **************\n";
        cout << endl;
        inHieuUng("  >> Nhap so Km du kien di chuyen (Nhap 0 neu chi tinh phi bao tri): ", C_TIEU_DE, 0);
        setColor(C_TEXT);
        cin >> quangDuong;
        if(cin.fail() || quangDuong < 0) { cin.clear(); cin.ignore(32767, '\n'); quangDuong = 0; }
        else cin.ignore(32767, '\n');
        setColor(C_VIEN); cout << "\n  " << char(201) << string(frameW, char(205)) << char(187) << "\n";
        setColor(C_VIEN); cout << "  " << char(186) << " ";
		setColor(C_CHON); cout << left << setw(14) << "Bien so" << setw(14) << "Loai xe" << right << setw(22) << "Thanh tien (VND)";
		setColor(C_VIEN); cout << " " << char(186);
		cout <<"\n  "<<char(204) << string(frameW, char(205)) << char(185) << "\n";
    	double tongPhi = 0;
        for (int i = 0; i < ds.size(); i++) {
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
            InTieuDeBang();
            for (int i = 0; i < ds.size(); i++) {
                setColor(C_VIEN); cout << "  " << char(186) << " ";
                setColor(C_TEXT); cout << *ds[i];
                setColor(C_VIEN); cout << " " << char(186) << "\n";
            }
            setColor(C_VIEN);
            cout << "  " << char(200) << string(W_FRAME, char(205)) << char(188) << "\n\n";
            setColor(C_TEXT);
            cout << "  >> Nhap bien so xe can xem chi tiet (Hoac nhap '0' de thoat): ";
            getline(cin, bs);
            if (bs == "0") break;
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
            setColor(C_VIEN); cout << "\n  ";
            system("pause");
        } while (true);
    }
};

int main() {
    SetConsoleOutputCP(437); 
    QuanLyPhuongTien* ql = new QuanLyPhuongTien();
    int luaChon;
    do {
        system("cls");
        setColor(C_VIEN);
        cout << "\n  " << char(201) << string(M_W_FRAME, char(205)) << char(187) << "\n";
        inTieuDeMenu("QUAN LY PHUONG TIEN GIAO THONG", C_TIEU_DE);
        inTieuDeMenu("Nhiem vu he thong Me Thuong Me Do TUD", C_VIEN);
        setColor(C_VIEN); cout << "  " << char(204) << string(M_W_FRAME, char(205)) << char(185) << "\n";
        inDongMenu("1", "Them phuong tien (Oto, Xe may, Xe tai)", C_TIEU_DE);
        inDongMenu("2", "Hien thi danh sach & Tra cuu chi tiet", C_CHON);
        inDongMenu("3", "Du toan chi phi (Bao tri + Nhien lieu)", C_TIEU_DE);
        inDongMenu("4", "Them du lieu mau (Test nhanh)", C_TIEU_DE); 
        inDongMenu("0", "Thoat chuong trinh", C_LOI);
        setColor(C_VIEN); cout << "  " << char(200) << string(M_W_FRAME, char(205)) << char(188) << "\n\n";
        inHieuUng("  >> Nhap lua chon cua ban: ", C_TIEU_DE, 0);
        setColor(C_TEXT); cin >> luaChon;
        if (cin.fail()) { 
            cin.clear();
            cin.ignore(32767, '\n');
            luaChon = -1;
        } else { 
            cin.ignore(32767, '\n'); 
        }
        switch (luaChon) {
            case 1: {
                int loaiXe;
                do {
                    system("cls");
                    cout << "\n";
                    setColor(C_VIEN); cout << "  " << char(201) << string(M_W_FRAME, char(205)) << char(187) << "\n";
                    inTieuDeMenu("CHON LOAI PHUONG TIEN CAN THEM", C_TIEU_DE);
                    setColor(C_VIEN); cout << "  " << char(204) << string(M_W_FRAME, char(205)) << char(185) << "\n";
                    inDongMenu("1", "Them Xe Oto", C_TIEU_DE);
                    inDongMenu("2", "Them Xe May", C_TIEU_DE);
                    inDongMenu("3", "Them Xe Tai", C_TIEU_DE);
                    inDongMenu("0", "Quay lai Menu chinh", C_LOI);
                    setColor(C_VIEN); cout << "  " << char(200) << string(M_W_FRAME, char(205)) << char(188) << "\n\n";
                    inHieuUng("  >> Nhap loai xe muon them: ", C_TIEU_DE, 0);
                    setColor(C_TEXT);
                    cin >> loaiXe;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(32767, '\n');
                        loaiXe = -1;
                    } else {
                        cin.ignore(32767, '\n');
                    }
                    if (loaiXe == 0) {
                        inHieuUng("\n  => Da quay lai Menu chinh!\n", C_CHON);
                        break;
                    }
                    PhuongTien* pt = NULL; 
                    switch (loaiXe) {
                        case 1:
                            cout << "\n"; inHieuUng("  --- NHAP THONG TIN XE OTO ---\n", C_TIEU_DE);
                            pt = new XeOto();
                            break;
                        case 2:
                            cout << "\n"; inHieuUng("  --- NHAP THONG TIN XE MAY ---\n", C_TIEU_DE);
                            pt = new XeMay();
                            break;
                        case 3:
                            cout << "\n"; inHieuUng("  --- NHAP THONG TIN XE TAI ---\n", C_TIEU_DE);
                            pt = new XeTai();
                            break;
                        default:
                            inHieuUng("\n  [LOI] Loai xe khong hop le!\n", C_LOI);
                            break;
                    }
                    if (pt != NULL) {
                        cin >> *pt; 
                        ql->ThemPhuongTien(pt);
                        inHieuUng("\n  => Da them phuong tien thanh cong!\n", C_CHON);
                        ql->InTieuDeBang();
                        setColor(C_VIEN); cout << "  " << char(186) << " ";
                        setColor(C_TEXT); cout << *pt; 
                        setColor(C_VIEN); cout << " " << char(186) << "\n";
                        cout << "  " << char(200) << string(W_FRAME, char(205)) << char(188) << "\n";
                        setColor(C_TEXT);
                    }
                    setColor(C_VIEN); cout << "\n  ";
                    system("pause");
                } while (true);
                break;
            }
            case 2: 
                system("cls");
                ql->HienThiVaTraCuu();
                break;
            case 3: 
                system("cls");
                ql->TinhTongPhiBaoTri();
                break;
            case 4: {
                ql->ThemPhuongTien(new XeOto("51F-123.45", "Toyota", 2020, 5, "Sedan"));
                ql->ThemPhuongTien(new XeMay("59A-999.99", "Honda", 2022, 150, "Xe con tay"));
                ql->ThemPhuongTien(new XeTai("60C-567.89", "Isuzu", 2018, 8.5, 3, "Dong lanh"));
                inHieuUng("\n  => Da nap du lieu mau (1 Xe Oto, 1 Xe May, 1 Xe Tai) de test nhanh chuc nang!\n", C_CHON);
                break;
            }
            case 0:
                cout << "\n";
                inHieuUng("  DANG THOAT CHUONG TRINH", C_LOI, 10);
                inHieuUng("...", C_LOI, 100);
                inHieuUng("\n  TAM BIET!\n\n", C_CHON, 10);
                break;
            default:
                inHieuUng("\n  [LOI] Lua chon khong hop le! Vui long nhap lai.\n", C_LOI);
                break;
        }
        if (luaChon != 0) {
            setColor(C_VIEN); cout << "\n  ";
            system("pause");
        }
    } while (luaChon != 0);
    delete ql;
    return 0;
}
