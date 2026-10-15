class XeTai : public PhuongTien
{
private:
    double taiTrong;        // Don vi: tan
    int soTrucBanhXe;      // So truc cua xe
    string loaiThungXe;    // Loai thung xe

public:
    // =====================================================
    // 1. HAM KHOI TAO MAC DINH
    // =====================================================
    XeTai()
        : PhuongTien()
    {
        taiTrong = 0;
        soTrucBanhXe = 0;
        loaiThungXe = "";
    }

    // =====================================================
    // 2. HAM KHOI TAO CO THAM SO
    // =====================================================
    XeTai(string bs, string hsx, int nsx, double gia,
          int thanghh, int namhh,
          double tt, int soTruc, string loaiThung)
        : PhuongTien(bs, hsx, nsx, gia, thanghh, namhh)
    {
        taiTrong = tt;
        soTrucBanhXe = soTruc;
        loaiThungXe = loaiThung;
    }

    // =====================================================
    // 3. HAM KHOI TAO SAO CHEP
    // =====================================================
    XeTai(const XeTai& x)
        : PhuongTien(x)
    {
        taiTrong = x.taiTrong;
        soTrucBanhXe = x.soTrucBanhXe;
        loaiThungXe = x.loaiThungXe;
    }

    // =====================================================
    // 4. HAM HUY
    // =====================================================
    ~XeTai() {}
    // =====================================================
    // 5. GETTER
    // =====================================================
    double getTaiTrong() const
    {
        return taiTrong;
    }

    int getSoTrucBanhXe() const
    {
        return soTrucBanhXe;
    }

    string getLoaiThungXe() const
    {
        return loaiThungXe;
    }

    // =====================================================
    // 6. SETTER
    // =====================================================
    void setTaiTrong(double tt)
    {
        taiTrong = tt;
    }

    void setSoTrucBanhXe(int soTruc)
    {
        soTrucBanhXe = soTruc;
    }

    void setLoaiThungXe(string loaiThung)
    {
        loaiThungXe = loaiThung;
    }

    // =====================================================
    // 7. DA HINH - LOAI PHUONG TIEN
    // =====================================================
    string GetLoaiPhuongTien() const 
    {
        return "Xe tai";
    }

    // =====================================================
    // 8. DA HINH - THONG SO
    // =====================================================
    // Dua tat ca thong tin dac trung cua XeTai vao day
    // de PhuongTien::HienThiThongTin() co the hien thi.
    string GetThongSo() const 
    {
        stringstream ss;

        ss << taiTrong << " tan"
           << " - " << loaiThungXe
           << " - " << soTrucBanhXe << " truc";

        return ss.str();
    }

    // =====================================================
    // 9. DA HINH - TINH PHI BAO TRI
    // =====================================================
    // Phi co ban: 1.000.000
    // + tai trong * 200.000
    double TinhPhiBaoTri() const  
    {
        return 1000000 + taiTrong * 200000;
    }

    // =====================================================
    // 10. HAM SANG TAO
    // TINH CHI PHI LAN BANH
    // =====================================================
    double TinhChiPhiLanBanh(double quangDuong) const
    {
        if (quangDuong < 0)
            return 0;

        double chiPhiMoiKm = 5000; // mac dinh chi phi lan banh = 5000d/1km .

        // Tai trong cang lon -> chi phi cang cao
        if (taiTrong > 5)
        {
            chiPhiMoiKm += 3000;  // neu tai trong lon hon 5 thi + them 3000d vao chiphi/1km
        }
        else if (taiTrong > 2)	  // neu tai trong lon hon 2 thi + them 1500d vao chiphi/1km
        {
            chiPhiMoiKm += 1500;
        }

        // Xe nhieu truc -> chi phi van hanh cao hon
        if (soTrucBanhXe >= 4)	  // neu xe tai co nhieu hon 4 truc thi + them 2000d vao chiphi/1km
        {
            chiPhiMoiKm += 2000;
        }
        else if (soTrucBanhXe == 3) // neu xe tai co 3 truc thi + them 1000d vao chiphi/1km
        {
            chiPhiMoiKm += 1000;
        }

        // Xe qua cu -> chi phi van hanh tang
        int tuoiXe = 2026 - getNamSanXuat(); // tuoixe = 2026 - nam san xuat 

        if (tuoiXe > 10)
        {
            chiPhiMoiKm += 1000; // xe sai hon 10 nam roi thi máy cu nen van hanh ton tien hon nên +1000d/1km;
        }

        return quangDuong * chiPhiMoiKm; // tổng giá tiền phải tốn cũng mỗi chuyến đi
    }

    // =====================================================
    // 11. HAM SANG TAO
    // TINH CUOC VAN CHUYEN
    // =====================================================
    double TinhCuocVanChuyen(double quangDuong) const // Giá tiền 1 cuốc xe tai khách phải trả 
    {
        if (quangDuong < 0)
            return 0;

        // Cuoc van chuyen co su dung chi phi lan banh
        double chiPhiLanBanh = TinhChiPhiLanBanh(quangDuong);

        double phiVanChuyen = 0;

        // Tinh phi dua tren tai trong
        if (taiTrong <= 2)
        {
            phiVanChuyen = quangDuong * 5000;
        }
        else if (taiTrong <= 5)
        {
            phiVanChuyen = quangDuong * 8000;
        }
        else
        {
            phiVanChuyen = quangDuong * 12000;
        }

        // Thung dong lanh ton chi phi cao hon ( vi xe đông lạnh cần máy móc hơn để bảo quản đồ đông lạnh ) 
        if (loaiThungXe == "Dong lanh" ||
            loaiThungXe == "dong lanh")
        {
            phiVanChuyen += quangDuong * 3000;
        }

        return chiPhiLanBanh + phiVanChuyen;
    }

    // =====================================================
    // 12. HAM SANG TAO
    // DANH GIA KHA NANG VAN CHUYEN
    // =====================================================
    string DanhGiaKhaNangVanChuyen() const // đánh giá xem vận chuyển hàng nặng hay nhẹ
    {
        if (taiTrong <= 2)
        {
            return "Van chuyen hang nhe";
        }

        if (taiTrong <= 5)
        {
            return "Van chuyen hang trung binh";
        }

        return "Van chuyen hang nang";
    }

    // =====================================================
    // 13. HAM SANG TAO
    // PHAN LOAI THUNG XE
    // =====================================================
    string PhanLoaiThungXe() const // hàm phân loại thùng xe
    {
        if (loaiThungXe == "Dong lanh" ||
            loaiThungXe == "dong lanh")
        {
            return "Thung dong lanh";   // thùng mà có hệ thống giữ nhiệt đông lạnh
        }

        if (loaiThungXe == "Thung kin" ||
            loaiThungXe == "thung kin")
        {
            return "Thung kin"; // thùng mà có nóc 
        }

        if (loaiThungXe == "Thung bat" || 
            loaiThungXe == "thung bat")
        {
            return "Thung bat"; // thùng được che bằng miếng bạt
        }

        if (loaiThungXe == "Xe ben" ||
            loaiThungXe == "xe ben")
        {
            return "Xe ben"; // xe có thể nâng lên nâng xuống 
        }

        return "Khong xac dinh";
    }

    // =====================================================
    // 14. HAM SANG TAO
    // KIEM TRA TAI TRONG
    // =====================================================
    bool KiemTraTaiTrong() const
    {
        return taiTrong <= 5;
    }

    // =====================================================
    // 15. HAM SANG TAO
    // KIEM TRA XE CO NEN THAY THE KHONG
    // =====================================================
    bool KiemTraXeCoNenThayThe(int namHienTai = 2026) const
    {
        int tuoiXe = namHienTai - getNamSanXuat(); // hàm tuổi xe 

        double giaTriHienTai =
            TinhGiaTriHienTai(namHienTai); 

        // Chi phi lan banh trong 100 km
        double chiPhiLanBanh =
            TinhChiPhiLanBanh(100);

        // Xe quá cũ + giá trị còn lại thấp
        // + chi phí lăn bánh cao
        if (tuoiXe > 15 &&
            giaTriHienTai < getGiaGoc() * 0.3 && // giá trị hiện tại < giá gốc x 30% ( nghĩa là Giá trị hiện tại của xe đã thấp hơn 30% giá gốc.)
            chiPhiLanBanh > 1000000)
        {
            return true;
        }

        return false;
    }

    // =====================================================
    // 16. HAM SANG TAO
    // KIEM TRA CO DUOC VAO NOI DO KHONG
    // =====================================================
    bool DuocPhepVaoPho(int gioHienTai) const
    {
        // Xe <= 1.5 tan duoc phep vao
        if (taiTrong <= 1.5)
        {
            return true;
        }

        // Khung gio 6h - 9h
        if (gioHienTai >= 6 && gioHienTai < 9)
        {
            return false;
        }

        // Khung gio 16h - 20h
        if (gioHienTai >= 16 && gioHienTai < 20)
        {
            return false;
        }

        return true;
    }

    // =====================================================
    // 17. NHAP
    // =====================================================
    void Nhap(istream& in)  
    {
        // Goi ham Nhap cua lop cha
        PhuongTien::Nhap(in);

        // Nhap tai trong
        setColor(C_VIEN);
        cout << "  " << char(204) << char(205)
             << " Nhap Tai trong (tan): ";

        setColor(C_TEXT);
        in >> taiTrong;

        if (in.fail())
        {
            in.clear();
        }

        in.ignore(32767, '\n');

        // Nhap loai thung
        setColor(C_VIEN);
        cout << "  " << char(204) << char(205)
             << " Nhap Loai thung xe: ";

        setColor(C_TEXT);
        getline(in, loaiThungXe);

        // Nhap so truc
        setColor(C_VIEN);
        cout << "  " << char(204) << char(205)
             << " Nhap So truc banh xe: ";

        setColor(C_TEXT);
        in >> soTrucBanhXe;

        if (in.fail())
        {
            in.clear();
        }

        in.ignore(32767, '\n');
    }

    // =====================================================
    // 18. HIEN THI THONG TIN
    // =====================================================
    void HienThiThongTin(ostream& out) const  
    {
        // PhuongTien se tu dong goi GetThongSo()
        // cua XeTai do GetThongSo() la ham ao.
        PhuongTien::HienThiThongTin(out);
    }

    // =====================================================
    // 19. TOAN TU NHAP
    // =====================================================
    friend istream& operator>>(istream& in, XeTai& x)
    {
        x.Nhap(in);
        return in;
    }

    // =====================================================
    // 20. TOAN TU XUAT
    // =====================================================
    friend ostream& operator<<(ostream& out, const XeTai& x)
    {
        x.HienThiThongTin(out);
        return out;
    }
};
