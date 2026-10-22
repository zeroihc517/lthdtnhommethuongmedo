int main() {
    // Thiết lập bảng mã console sang 437 để hiển thị các ký tự vẽ khung viền (mã ASCII mở rộng)
    SetConsoleOutputCP(437); 
    // Khởi tạo đối tượng quản lý danh sách phương tiện
    QuanLyPhuongTien ql;
    int luaChon;
    // Vòng lặp chính của chương trình, chạy cho đến khi người dùng chọn 0
    do {
        system("cls"); // Xóa màn hình trước khi in menu mới
        // VẼ KHUNG VÀ HIỂN THỊ MENU CHÍNH
        setColor(C_VIEN);
        cout << "\n  " << char(201) << string(M_W_FRAME, char(205)) << char(187) << "\n";
        inTieuDeMenu("QUAN LY PHUONG TIEN GIAO THONG", C_TIEU_DE);
        inTieuDeMenu("MTMD - Toan Ung Dung va Phan Vi Du", C_VIEN);
        setColor(C_VIEN); cout << "  " << char(204) << string(M_W_FRAME, char(205)) << char(185) << "\n";
        inDongMenu("1", "Them phuong tien (Oto, Xe may, Xe tai)", C_TIEU_DE);
        inDongMenu("2", "Hien thi danh sach phuong tien", C_TIEU_DE);
        inDongMenu("3", "Tinh tong phi bao tri", C_TIEU_DE);
        inDongMenu("4", "Tra cuu chi tiet & Tu van xe", C_CHON);
        inDongMenu("5", "Them du lieu mau (Test nhanh)", C_TIEU_DE); 
        inDongMenu("0", "Thoat chuong trinh", C_LOI);
        setColor(C_VIEN); cout << "  " << char(200) << string(M_W_FRAME, char(205)) << char(188) << "\n\n";
        // Nhận lựa chọn từ người dùng
        inHieuUng("  >> Nhap lua chon cua ban: ", C_TIEU_DE, 0);
        setColor(C_TEXT); cin >> luaChon;
        // XỬ LÝ LỖI NHẬP DỮ LIỆU
        // Nếu người dùng nhập sai kiểu (VD: nhập chữ cái thay vì số)
        if (cin.fail()) { 
            cin.clear();                  // Xóa cờ lỗi của luồng nhập
            cin.ignore(32767, '\n');      // Xóa bộ đệm, bỏ qua các ký tự bị kẹt
            luaChon = -1;                 // Gán một giá trị không hợp lệ để văng vào default
        } else {
            cin.ignore(32767, '\n'); // Xóa dấu enter thừa trong bộ đệm sau khi nhập số
        }
        // XỬ LÝ CÁC CHỨC NĂNG THEO LỰA CHỌN
        switch (luaChon) {
            case 1: { // Chức năng thêm phương tiện mới
                int loaiXe;
                // Vòng lặp menu phụ chọn loại phương tiện
                do {
                    system("cls"); // Xóa màn hình trước khi hiện menu phụ
                    // Hiện thị Menu phụ dạng khung chia ô
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
                    // Xử lý lỗi trôi lệnh cho Menu phụ tương tự như menu chính
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(32767, '\n');
                        loaiXe = -1;
                    } else {
                        cin.ignore(32767, '\n');
                    }
                    if (loaiXe == 0) {
                        inHieuUng("\n  => Da quay lai Menu chinh!\n", C_CHON);
                        break; // Thoát vòng lặp phụ, trở về menu chính
                    }
                    // Khởi tạo một con trỏ lớp cơ sở để gom code xử lý đa hình
                    PhuongTien* pt = NULL; 
                    // Cấp phát vùng nhớ động cho đối tượng tương ứng với loại xe được chọn
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
                    // Nếu người dùng chọn đúng loại xe (đối tượng đã được cấp phát)
                    if (pt != NULL) {
                        // Tính đa hình: toán tử >> được nạp chồng sẽ tự động gọi đúng hàm Nhap() của lớp con
                        cin >> *pt; 
                        // Thêm đối tượng vào danh sách quản lý
                        ql.ThemPhuongTien(pt);
                        inHieuUng("\n  => Da them phuong tien thanh cong!\n", C_CHON);
                        // Vẽ bảng và hiển thị lại thông tin phương tiện vừa được thêm vào
                        ql.InTieuDeBang();
                        setColor(C_VIEN); cout << "  " << char(186) << " ";
                        setColor(C_TEXT); cout << *pt; 
                        setColor(C_VIEN); cout << " " << char(186) << "\n";
                        cout << "  " << char(200) << string(W_FRAME, char(205)) << char(188) << "\n";
                        setColor(C_TEXT);
                    }
                    // Dừng màn hình để người dùng đọc kết quả trước khi vòng lặp lặp lại
                    setColor(C_VIEN); cout << "\n  ";
                    system("pause");
                } while (true); // Chạy liên tục cho đến khi người dùng nhập 0 (gặp lệnh break)
                break; // Kết thúc case 1 của menu chính
            }
            case 2: 
                // Gọi hàm hiển thị toàn bộ danh sách
                ql.HienThiDanhSach(); 
                break;
            case 3: 
                // Gọi hàm tính và in tổng phí bảo trì
                ql.TinhTongPhiBaoTri(); 
                break;
            case 4: 
                // Gọi hàm kiểm tra các tính năng riêng biệt (mở rộng của từng lớp con)
                ql.KiemTraTinhNangMoRong(); 
                break;
            case 5: {
                // Thêm dữ liệu mẫu cứng (hardcode) để tiện việc test chức năng không phải nhập tay nhiều lần
                ql.ThemPhuongTien(new XeOto("51F-123.45", "Toyota", 2020, 800000000, 5, "Sedan"));
                ql.ThemPhuongTien(new XeMay("59A-999.99", "Honda", 2022, 50000000, 150, "Xe con tay", 12000, 11000));
                ql.ThemPhuongTien(new XeTai("60C-567.89", "Isuzu", 2018, 1200000000, 8.5, 3, "Dong lanh"));
                inHieuUng("\n  => Da nap du lieu mau (1 Xe Oto, 1 Xe May, 1 Xe Tai) de test nhanh chuc nang!\n", C_CHON);
                break;
            }
            case 0:
                // Hiệu ứng chữ chạy khi thoát chương trình
                cout << "\n";
                inHieuUng("  DANG THOAT CHUONG TRINH", C_LOI, 10);
                inHieuUng("...", C_LOI, 100);
                inHieuUng("\n  TAM BIET!\n\n", C_CHON, 10);
                break;
            default:
                // Báo lỗi nếu chọn sai chức năng ngoài menu
                inHieuUng("\n  [LOI] Lua chon khong hop le! Vui long nhap lai.\n", C_LOI);
                break;
        }
        // Dừng màn hình để đọc thông báo (ngoại trừ lúc chọn thoát)
        if (luaChon != 0) {
            setColor(C_VIEN); cout << "\n  ";
            system("pause");
        }
    } while (luaChon != 0); // Tiếp tục nếu người dùng không chọn 0
    return 0; // Kết thúc hàm main
}
