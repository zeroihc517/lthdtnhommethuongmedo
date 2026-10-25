#define C_VIEN    11    // Màu của đường viền khung giao diện, màu xanh dương sáng 
#define C_TIEU_DE 14    // Màu dùng để hiển thị tiêu đề menu, màu vàng sáng
#define C_TEXT    15    // Màu chữ nội dung thông thường, màu trắng sáng
#define C_CHON    10    // Màu dùng để làm nổi bật lựa chọn hoặc mục được chọn, màu xanh lá sáng
#define C_LOI     12    // Màu dùng để hiển thị thông báo lỗi, màu đỏ sáng
#define W_BIENSO   12   // Độ rộng cột biển số phương tiện
#define W_HANG     15   // Độ rộng cột hãng sản xuất phương tiện
#define W_NAMSX    8    // Độ rộng cột năm sản xuất
#define W_LOAI     10   // Độ rộng cột loại phương tiện
#define W_THONGSO  33   // Độ rộng cột thông số kỹ thuật
#define W_PHI      18   // Độ rộng cột phí
#define W_FRAME    98   // Chiều rộng tổng thể của khung giao diện, đơn vị tính là số ký tự hiển thị trên một dòng Console
#define M_W_IN     50   // Chiều rộng vùng nội dung bên trong menu
#define M_W_FRAME  52   // Chiều rộng khung menu

// Hàm thiết lập màu sắc chữ trên Console
void setColor(int color) {
    // GetStdHandle(STD_OUTPUT_HANDLE): Lấy handle (định danh) của thiết bị xuất chuẩn, tức cửa sổ Console đang được sử dụng để hiển thị kết quả.
    // SetConsoleTextAttribute(..., color): Thiết lập thuộc tính hiển thị cho Console, trong đó color là mã màu được truyền vào hàm.
    // Nhờ đó, các ký tự được in ra sau lời gọi hàm sẽ sử dụng màu đã thiết lập cho đến khi thuộc tính màu được thay đổi bằng một lời gọi khác.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Hàm in văn bản theo hiệu ứng từng ký tự
void inHieuUng(string text, int color, int delay = 5) {
    setColor(color);                                        // Thiết lập màu sắc cho toàn bộ văn bản sẽ được in.
    for (size_t i = 0; i < text.length(); i++) {            // Duyệt lần lượt từng ký tự trong chuỗi text, size_t là kiểu số nguyên không âm thường dùng để biểu diễn kích thước.
        cout << text[i];                                    // In ký tự tại vị trí i mà không tự động xuống dòng.
        Sleep(delay);                                       // Tạm dừng chương trình trong delay mili giây, tạo hiệu ứng văn bản xuất hiện lần lượt từng ký tự.
    }
}

// Hàm in tiêu đề menu căn giữa
void inTieuDeMenu(string title, int color) {
    setColor(C_VIEN); cout << "  " << char(186) << " ";     // In phần viền bên trái của dòng menu.
    setColor(color);                                        // Chuyển sang màu được chỉ định để hiển thị tiêu đề.
    // Tính số khoảng trắng cần chèn bên trái tiêu đề.
    // Ép kiểu title.length() sang int để phép tính được thực hiện
    // thuận tiện với kiểu số nguyên có dấu.
    int padLeft = (M_W_IN - (int)title.length()) / 2;
    // Tính số khoảng trắng bên phải sao cho tổng độ rộng
    // của khoảng trắng và tiêu đề bằng M_W_IN.
    int padRight = M_W_IN - (int)title.length() - padLeft;
    cout << string(padLeft, ' ') << title << string(padRight, ' ');     // In khoảng trắng bên trái, nội dung tiêu đề và khoảng trắng bên phải, tiêu đề được căn giữa trong vùng nội dung.
    setColor(C_VIEN); cout << " " << char(186) << "\n";                 // Chuyển về màu viền để in cạnh phải của dòng menu.
}

// Hàm in một dòng lựa chọn trong menu
void inDongMenu(string stt, string text, int sttColor = C_TIEU_DE) {
    setColor(C_VIEN); cout << "  " << char(186) << " ";                 // In viền trái của dòng menu bằng màu viền.
    setColor(sttColor);                                                 // Thiết lập màu cho phần số thứ tự của lựa chọn. Nếu không truyền sttColor, chương trình mặc định dùng C_TIEU_DE.
    string prefix = stt + ". ";                                         // Ghép số thứ tự với dấu chấm và khoảng trắng.
    // Căn trái phần số thứ tự trong vùng rộng 4 ký tự.
    // Nếu ngắn hơn 4 ký tự, setw(4) tự bổ sung khoảng trắng bên phải.
    // setw() chỉ tác động đến lần xuất dữ liệu kế tiếp.
    cout << left << setw(4) << prefix;
    setColor(C_TEXT);                                                   // Chuyển sang màu chữ thông thường để in nội dung lựa chọn.
    cout << left << setw(46) << text;                                   // Căn trái nội dung trong vùng rộng 46 ký tự, nội dung ngắn hơn sẽ được bổ sung khoảng trắng bên phải.
    setColor(C_VIEN); cout << " " << char(186) << "\n";                 // Chuyển về màu viền, in cạnh phải và kết thúc dòng.
}

// Hàm định dạng tiền tệ bằng cách thêm dấu chấm vào hàng nghìn
string DinhDangTien(double tien) {
    // Chuyển số tiền từ kiểu double sang long long, bỏ phần thập phân
    long long giaTri = (long long)tien;
    // Tạo đối tượng stringstream để chuyển số thành chuỗi
    stringstream ss;
    ss << giaTri;
    // Lấy chuỗi biểu diễn số tiền
    string s = ss.str();
    // Lấy độ dài của chuỗi
    int n = s.length();
    // Chèn dấu chấm vào giữa các nhóm 3 chữ số, tính từ phải sang trái
    for (int i = n - 3; i > 0; i -= 3) {
        s.insert(i, ".");
    }
    return s;        // Trả về chuỗi tiền tệ đã được định dạng
}

string toLower(string str) {
    // Duyệt qua từng ký tự trong chuỗi
    for (int i = 0; i < str.length(); i++) {
        // Kiểm tra ký tự có phải chữ in hoa từ 'A' đến 'Z' không
        if (str[i] >= 'A' && str[i] <= 'Z') {
            // Chuyển chữ in hoa thành chữ thường bằng cách cộng 32
            str[i] = str[i] + 32;
        }
    }
    // Trả về chuỗi sau khi đã chuyển thành chữ thường
    return str;
}
