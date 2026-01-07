#include "Dictionary.h"
#include <fstream>

// Khởi tạo bảng băm (gán tất cả bằng NULL)
void InitHashTable(HashTable &ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.buckets[i] = NULL;
    }
}

// Hàm băm: Lấy ký tự đầu tiên
int HashFunction(string tuTiengAnh) {
    char firstChar = tolower(tuTiengAnh[0]); // Chuyển về chữ thường
    if (firstChar >= 'a' && firstChar <= 'z') {
        return firstChar - 'a'; // a->0, b->1...
    }
    return 0; // Mặc định vào 0 nếu ký tự lạ
}

// Thêm từ vào ĐẦU danh sách (Insert Head) -> Tốc độ cực nhanh O(1)
void AddWord(HashTable &ht, string anh, string viet) {
    int index = HashFunction(anh);
    
    Node* p = new Node;
    p->tuTiengAnh = anh;
    p->nghiaTiengViet = viet;
    p->next = ht.buckets[index]; // Trỏ next của node mới vào node đầu cũ
    ht.buckets[index] = p;       // Cập nhật node đầu mới là p
}

// Tìm kiếm từ
Node* SearchWord(HashTable ht, string anh) {
    int index = HashFunction(anh);
    Node* p = ht.buckets[index];
    
    while (p != NULL) {
        if (p->tuTiengAnh == anh) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// Hiển thị toàn bộ từ điển
void DisplayAll(HashTable ht) {
    cout << "\n--- KIEM TRA CAU TRUC BANG BAM ---\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        // Chỉ in những dòng có dữ liệu
        if (ht.buckets[i] != NULL) {
            // In chỉ số index và chữ cái đại diện
            cout << "(" << (char)('a' + i) << "): ";
            
            Node* p = ht.buckets[i];
            while (p != NULL) {
                // In mũi tên để thể hiện liên kết
                cout << "[" << p->tuTiengAnh << "] -> "; 
                p = p->next;
            }
            cout << "NULL" << endl; // Kết thúc danh sách là NULL
        }
    }
    cout << "----------------------------------\n";
}

// Hàm lưu dữ liệu từ RAM xuống ổ cứng
void SaveToFile(HashTable ht, string filename) {
    ofstream f(filename); // Mở file để ghi (tự tạo nếu chưa có)
    if (!f.is_open()) {
        cout << "Loi: Khong mo duoc file de ghi!" << endl;
        return;
    }

    // Duyệt qua tất cả 26 ngăn
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* p = ht.buckets[i];
        while (p != NULL) {
            // Ghi theo định dạng: hello|xin chào
            f << p->tuTiengAnh << "|" << p->nghiaTiengViet << endl;
            p = p->next;
        }
    }
    f.close();
    cout << "--> Da luu toan bo du lieu vao file '" << filename << "'." << endl;
}

// Hàm nạp dữ liệu từ ổ cứng lên RAM
void LoadFromFile(HashTable &ht, string filename) {
    ifstream f(filename); // Mở file để đọc
    if (!f.is_open()) {
        // Lần đầu chạy chưa có file thì không sao
        return; 
    }

    string line;
    while (getline(f, line)) {
        // Dòng đọc được: "hello|xin chào" -> Cần tách ra
        int pos = line.find("|");
        if (pos != string::npos) {
            string anh = line.substr(0, pos);
            string viet = line.substr(pos + 1);
            
            // Thêm vào Hash Table
            AddWord(ht, anh, viet);
        }
    }
    f.close();
    cout << "--> Da nap du lieu tu file cu len RAM." << endl;
}


// Hàm Xóa từ: Xử lý kỹ con trỏ để không đứt chuỗi
bool DeleteWord(HashTable &ht, string anh) {
    int index = HashFunction(anh);
    Node* p = ht.buckets[index];
    Node* prev = NULL; // Con trỏ lưu node đứng trước p

    while (p != NULL) {
        if (p->tuTiengAnh == anh) {
            // -- Trường hợp 1: Từ cần xóa nằm ngay đầu danh sách --
            if (prev == NULL) {
                ht.buckets[index] = p->next; // Đầu danh sách trỏ sang thằng kế tiếp
            }
            // -- Trường hợp 2: Từ cần xóa nằm ở giữa hoặc cuối --
            else {
                prev->next = p->next; // Nối thằng trước với thằng sau, bỏ qua p
            }

            delete p; // Giải phóng bộ nhớ của p
            return true; // Xóa thành công
        }
        
        // Nếu chưa tìm thấy, dịch chuyển cả 2 con trỏ đi tiếp
        prev = p;
        p = p->next;
    }
    return false; // Không tìm thấy để xóa
}

bool RenameWord(HashTable &ht, string tuCu, string tuMoi, string nghiaMoi) {
    // 1. Xóa từ cũ trước
    bool xoaThanhCong = DeleteWord(ht, tuCu);
    
    // 2. Nếu xóa được thì mới thêm từ mới vào
    if (xoaThanhCong) {
        AddWord(ht, tuMoi, nghiaMoi);
        return true;
    }
    
    return false; // Không tìm thấy từ cũ để sửa
}