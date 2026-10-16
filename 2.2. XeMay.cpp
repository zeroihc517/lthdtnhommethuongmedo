class XeMay:public PhuongTien{
private:
    double congSuat;          // Công suất (đơn vị: cc)
    string heTruyenDong;      // Xe số, xe ga, xe côn tay
    double soKmDaDi;          // Số km xe đã đi
public:
    // Hàm khởi tạo mặc định
    XeMay():PhuongTien(){
        congSuat=0;
        heTruyenDong="Xe so";
        soKmDaDi=0;   
    }
    // Hàm khởi tạo có tham số
    XeMay(string bs,string hsx, int nsx, double gia, int thanghh, int namhh, double cs, string htd, double skm):PhuongTien(bs, hsx, nsx, gia, thanghh, namhh){
        congSuat=cs;
        heTruyenDong=htd;
        sKmDaDi=skm;
    }
    // Hàm khởi tạo sao chép
    XeMay(const XeMay &p):PhuongTien(p){
        congSuat=p.congSuat;
        hetuyenDong=p.heTruyenDong;
        soKmDaDi=p.soKmDaDi;
    }
    // Hàm hủy
    ~XeMay() override{}
    // Getter
    double getCongSuat() const{return congSuat;}
    string getHeTruyenDong() const {return heTruyenDong;}
    double getSoKmDaDi() const {return soKmDaDi;}
    // Setter
    void setCongSuat(double cs){congSuat=cs;}
    void setHeTruyenDong(string htd){heTruyenDong=htd;}
    void setSoKmDaDi(double skm){soKmDaDi=skm;}
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
        if(congSuat<=175) return "Bang A1";
        return "Bang A2";
    }
    //
    void 


};   
