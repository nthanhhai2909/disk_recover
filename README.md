***Chương trình thực hiện phục hồi dữ liệu đã bị xóa (Delete) hoặc xóa vình viễn (Shift + Delete)***

**Cấu trúc chương trình**
*Class Helper*
- Lớp định các phương thức hỗ trợ cho toàn bộ chương trình. Gồm:
  + Các thao tác đọc file (đọc theo sector chỉ định trước, ....).
  + Chuyển đổi dữ liệu vector<char> to vector<uint8_t>,...
  + In dữ liệu hexa ra màn hình.
*Class Component, File, TrDIR*
- Các lớp đại diện để lưu trữ thông tin các file, folder trong volume => Tổ chức như cây thư mục.
- Kiến trúc: Sử dụng mẫu Composite để tổ chức.
- Lớp TreeDIR là lớp chính: Lưu trữ các thông tin về file, thư mục.
- Cách xây dựng cây:
  + Cây được xây dựng từ bảng RDET.
  + Mỗi entry trong bảng là một file hoặc thư mục. Mỗi entry (32 bytes) chỉ rút trích các thông tin chính như:
    + Trạng thái entry: Đã xóa ('e5') hay đang sử dụng (offset thứ 0).
    + Loại: File hay thư mục (offset thứ 11).
    + Tên file/thư mục: 8 bytes đầu entry chính và các entry phụ.
    + Đuôi mở rộng: Từ 8 bytes đầu entry chính và các entry phụ (entry phụ có offset thứ 11 là '0f').
    + Kích thước: 4 bytes cuối của mỡi entry - số nguyên không dấu 4 bytes.
    + Cluster bắt đầu (trong vùng chứa data): Số nguyên không dấu 4 bytes. Trong đó, 2 bytes cao là offset 20, 21 và 2 bytes thấp là offset 26, 27.
    + Trong trường hợp entry là thư mục: Đi đến vùng chứa data của thư mục sẽ có bảng SDET (Tương tự kiến trúc bảng RDET) để lấy thông tin của các file/thư mục con.
    + Cây được xây dựng 1 lần duy nhất, lúc khởi chạy chương trình (toàn bộ cây được load lên ram để tăng tốc cho việc tìm kiếm file cho quá trình phục hồi dữ liệu, đồng thời giúp hạn chế  việc xây dựng nhiều lần làm tăng quá trình đọc đĩa).
    + *Chú ý*: Cây được xây dựng 1 lần, do đó, nếu có thay đổi gì trong volume sẽ không được cập nhật ngay lập tức. Muốn update lại cây phải run lại chương trình để xây dựng lại cây thư mục.
*Class FAT*
- Lớp chính của volumn FAT.
- Lớp xây dựng các phương thức chính để phục hồi dữ liệu.

**Chức năng**
Chương trình gồm 3 chức năng chính:
*show tree*
- Chức năng: này sẽ in ra cây thư mục của volumn hiện tại.
- Cách thức hoạt động: Hàm thực hiện việc in ra các tập tin hoặc thư mục trong đối trượng *treeDir* của lớp Fat dưới dạng format cây thư mục (Cây được).
*recover all*
- Chức năng: Phục hồi toàn bộ file bị xóa hoặc xóa vĩnh viễn.
- Cơ chế: Chương trình sẽ tìm kiếm trong cây thư mục, các tập tin được đánh dấu là đã xóa, sau đó lần lượt dựa trên thông tin cluster bắt đầu của data và kích thước để phục hồi (Đọc số bytes bằng kích thước của files cần phục hồi, bắt đầu từ vị trí cluster bắt đầu và ghi vào file có tên tương ứng). Trong trường hợp là thư mục sẽ vào thư mục để tìm các file con bị đánh dấu xóa để phục hồi.
- *Chú ý:* Trường hợp phân mảnh có thể phục hồi sai, do chương trình chỉ lấy data trên các cluster liên tiếp nhau.
*recover file with ext*
- Chức năng: Phục hồi file với đuôi mở rộng cho trước (VD: *txt*, *pdf*, *docx*, ....).
- Cơ chế: Tương tự với *recover all*.

**Cách compile và thực thi chương trình**
- Chương trình chạy trên linux.
- Bild chương trình: Thực thi lệnh *make* trên terminal để tạo ra file thực thi *main*
- Run chương trình bằng lệnh: *sudo main* (dùng lệnh sudo để có đầy đủ quyền truy cập để đọc thông tin volumn ở cấp thấp - xem như file).
- Chọn option muốn thực thi theo menu hướng dẫn trên màn hình.