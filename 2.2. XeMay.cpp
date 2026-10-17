class XeMay:public PhuongTien{
private:
    double congSuat;              // Công suất 
    string heTruyenDong;          // Xe số, xe ga, xe côn tay
    double soKmDaDi;              // Số km xe đã đi
    double soKmThayNhotGanNhat;   // Số km lần thay nhớt gần nhất
public:
    // Hàm khởi tạo mặc định
    XeMay():PhuongTien(){
        congSuat=0;
        heTruyenDong="Xe so";
        soKmDaDi=0; 
        soKmThayNhotGanNhat=0;
    }
    // Hàm khởi tạo có tham số
    XeMay(string bs,string hsx, int nsx, double gia, double cs, string htd, double skm, double skmNhot):PhuongTien(bs, hsx, nsx, gia, 0, 0){
        congSuat=(cs>0)?cs:0;
        heTruyenDong=htd;
        soKmDaDi=(skm>0)?skm:0;
        soKmThayNhotGanNhat=(skmNhot>=0)?skmNhot:0;
    }
    // Hàm khởi tạo sao chép
    XeMay(const XeMay &p):PhuongTien(p){
        congSuat=p.congSuat;
        heTruyenDong=p.heTruyenDong;
        soKmDaDi=p.soKmDaDi;
        soKmThayNhotGanNhat=p.soKmThayNhotGanNhat;
    }
    // Hàm hủy
    ~XeMay() override{}
    // Getter
    double getCongSuat() const {return congSuat;}
    string getHeTruyenDong() const {return heTruyenDong;}
    double getSoKmDaDi() const {return soKmDaDi;}
    double getSoKmThayNhotGanNhat() const {return soKmThayNhotGanNhat;}
    // Setter
    void setCongSuat(double cs){if(cs>=0) congSuat=cs;}
    void setHeTruyenDong(string htd){heTruyenDong=htd;}
    void setSoKmDaDi(double skm){if(skm>=0) soKmDaDi=skm;}
    void setSoKmThayNhotGanNhat(double skmNhot){if(skmNhot>=0) soKmThayNhotGanNhat=skmNhot;}
    // Lấy loại phương tiện (Đa hình)
    string GetLoaiPhuongTien() const override{return "Xe may";}
    // Lấy thông số riêng của xe máy (Đa hình)
    string GetThongSo() const override {
        stringstream ss;
        ss<<fixed<<setprecision(0)<<congSuat<<" cc - "<<heTruyenDong<<" - "<<fixed<<setprecision(1)<<soKmDaDi<<" km";
        return ss.str();
    }
    // Phí bảo trì riêng cho xe máy (Đa hình)
    double TinhPhiBaoTri() const override{
        double phiCoBan=150000;
        if(congSuat>150){
            return phiCoBan + 200000;
        }
        return phiCoBan;
    }
    // Loại bằng lái phù hợp dựa trên công suất
    string YeuCauBangLai() const{
        if(congSuat<=50) return "Khong can bang lai";
        if(congSuat<=125) return "Bang A1";
        return "Bang A";
    }
    // Hàm kiểm tra xe có nên thay nhớt không
    void KiemTraThayNhot() const{
        double kmDaDiLanTruoc=soKmDaDi-soKmThayNhotGanNhat;
        string htd=toLower(heTruyenDong);
        if(htd=="xe ga"){
            if(kmDaDiLanTruoc>=4500){
                cout<<"Nen thay nhot"<<endl;
            }else {
                cout<<"Nhot con tot"<<endl;
            }
        }else {
            if(kmDaDiLanTruoc>=1500){
                cout<<"Nen thay nhot"<<endl;
            }
            else{
                cout<<"Nhot con tot"<<endl;
            }
        }
    }
    // Hàm so sánh chi phí giữ xe giữa vé ngày và vé tháng
    void TienGuiXe(int soNgay) const{
        if(soNgay<=0) return;
        double veNgay=soNgay*5000;
        double veThang=120000;
        if(veNgay>veThang){
            cout<<"Ban nen mua ve thang"<<endl;
        }else if(veNgay<veThang){
            cout<<"Ban nen mua ve ngay"<<endl;
        }else{
            cout<<"Hai phuong an co chi phi bang nhau"<<endl;
        }
    }
    // Hàm nhập thông tin xe máy
    void Nhap(istream& in) override {
        PhuongTien::Nhap(in);        // Gọi hàm nhập của lớp PhuongTien
        // Nhập công suất
        setColor(C_VIEN);
        cout<<" "<<char(204)<<char(205)<<"Nhap cong suat: ";
        setColor(C_TEXT);
        in>>congSuat;
        if(in.fail()||congSuat<0){
            in.clear();
            congSuat=0;
        }
        in.ignore(32767,'\n');
        // Nhập hệ truyền động
        setColor(C_VIEN);
        cout<<" "<<char(204)<<char(205)<<"Nhap he truyen dong: ";
        setColor(C_TEXT);
        getline(in,heTruyenDong);
        // Nhập số km đã đi
        setColor(C_VIEN);
        cout<<" "<<char(204)<<char(205)<<"Nhap so km da di: ";
        setColor(C_TEXT);
        in>>soKmDaDi;
        if(in.fail()||soKmDaDi<0){
            in.clear();
            soKmDaDi=0;
        }
        in.ignore(32767,'\n');
        // Nhập số km thay nhớt gần nhất
        setColor(C_VIEN);
        cout<<" "<<char(204)<<char(205)<<"Nhap so km da thay nhot gan nhat: ";
        setColor(C_TEXT);
        in>>soKmThayNhotGanNhat;
        if(in.fail()||soKmThayNhotGanNhat<0){
            in.clear();
            soKmThayNhotGanNhat=0;
        }
        in.ignore(32767,'\n');
    }
    // Hàm hiển thị thông tin
    void HienThiThongTin(ostream& out) const override{
        PhuongTien::HienThiThongTin(out);
    }
    // Quá tải nhập
    friend istream& operator>>(istream& in, XeMay &p){
        p.Nhap(in);
        return in;
    }
    // Quá tải xuất
    friend ostream& operator<<(ostream& out, const XeMay &p){
        p.HienThiThongTin(out);
        return out;
    }
};   
