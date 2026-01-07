#include <iostream>
#include <windows.h>
#include "Dictionary.h"
#include "Internet.h"

using namespace std;

// Hàm kiểm tra hợp lệ online (Tách ra cho gọn main)
// Trả về: Nghĩa tiếng Việt nếu hợp lệ, Rỗng nếu vô nghĩa
string KiemTraVaLayNghia(string tuTiengAnh) {
    string ketQua = CallPythonTranslate(tuTiengAnh);
    if (ketQua == "#INVALID" || ketQua == "") {
        return ""; // Báo lỗi
    }
    return ketQua; // Trả về nghĩa chuẩn
}

// Logic Tra Cứu (Có vòng lặp kiểm tra)
void TraCuuKiemTra(HashTable &ht) {
    string tuCanTra, nghiaOnline;
    
    while (true) {
        cout << "Nhap tu tieng Anh (go '0' de quay lai): ";
        getline(cin, tuCanTra);
        if (tuCanTra == "0") return;

        // 1. Kiểm tra trong RAM trước
        Node* local = SearchWord(ht, tuCanTra);
        if (local != NULL) {
            cout << "--> [OFFLINE] Nghia la: " << local->nghiaTiengViet << endl;
            break; // Tìm thấy thì thoát
        } 
        
        // 2. Nếu không có, hỏi Online để kiểm tra tính hợp lệ
        cout << "Dang kiem tra online..." << endl;
        nghiaOnline = KiemTraVaLayNghia(tuCanTra);

        if (nghiaOnline != "") {
            cout << "--> [ONLINE] Tu hop le! Nghia la: " << nghiaOnline << endl;
            AddWord(ht, tuCanTra, nghiaOnline);
            cout << "(Da luu vao tu dien)" << endl;
            break; // Hợp lệ thì thoát
        } else {
            cout << "!!! CANH BAO: Tu '" << tuCanTra << "' khong co nghia hoac sai chinh ta. Vui long nhap lai!\n";
            // Vòng lặp while sẽ quay lại đầu để bắt nhập lại
        }
    }
}

// Logic Sửa Từ Tiếng Anh (Có vòng lặp kiểm tra từ mới)
void SuaTuTiengAnh(HashTable &ht) {
    string tuCu, tuMoi, nghiaMoiCuaTuMoi;

    // Bước 1: Nhập từ cũ cần sửa
    cout << "Nhap tu cu muon sua: ";
    getline(cin, tuCu);

    if (SearchWord(ht, tuCu) == NULL) {
        cout << "--> Loi: Khong tim thay tu '" << tuCu << "' trong tu dien.\n";
        return;
    }

    // Bước 2: Nhập từ mới (Vòng lặp kiểm tra xem từ mới có nghĩa không)
    while (true) {
        cout << "Nhap tu tieng Anh MOI thay the cho '" << tuCu << "': ";
        getline(cin, tuMoi);

        // Kiểm tra xem từ mới có nghĩa không
        cout << "Dang kiem tra tu moi..." << endl;
        nghiaMoiCuaTuMoi = KiemTraVaLayNghia(tuMoi);

        if (nghiaMoiCuaTuMoi != "") {
            // Từ mới OK -> Tiến hành đổi
            RenameWord(ht, tuCu, tuMoi, nghiaMoiCuaTuMoi);
            cout << "--> THANH CONG: Da doi '" << tuCu << "' thanh '" << tuMoi << "' (" << nghiaMoiCuaTuMoi << ").\n";
            break;
        } else {
            cout << "!!! CANH BAO: Tu moi '" << tuMoi << "' khong co nghia. Hay nhap tu khac!\n";
        }
    }
}

int main() {
    SetConsoleOutputCP(65001); 
    HashTable myDictionary;
    InitHashTable(myDictionary);
    LoadFromFile(myDictionary, "dulieu.txt");

    int choice;
    while (true) {
        cout << "\n=== TU DIEN THONG MINH (VER 2.0 - VALIDATION) ===\n";
        cout << "1. Them tu tieng Anh(Tra cuu)\n";
        cout << "2. Xem toan bo\n";
        cout << "3. Sua tu tieng Anh\n"; // Chức năng mới đổi ở đây
        cout << "4. Xoa mot tu\n";
        cout << "0. Thoat\n";
        cout << "Chon: "; cin >> choice;
        cin.ignore(); 

        if (choice == 0) {
            SaveToFile(myDictionary, "dulieu.txt");
            break;
        }
        
        switch (choice) {
            case 1:
                TraCuuKiemTra(myDictionary);
                break;
            case 2:
                DisplayAll(myDictionary);
                break;
            case 3:
                SuaTuTiengAnh(myDictionary);
                break;
            case 4: {
                string tuCanXoa;
                cout << "Nhap tu tieng Anh can xoa: ";
                getline(cin, tuCanXoa);
                if (DeleteWord(myDictionary, tuCanXoa)) {
                    cout << "--> Da xoa tu '" << tuCanXoa << "' khoi tu dien.\n";
                } else {
                    cout << "--> Khong tim thay tu '" << tuCanXoa << "' trong tu dien.\n";
                }
                break;
            }
            default: cout << "Sai roi!\n";
        }
    }
    return 0;
}