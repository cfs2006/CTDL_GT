#include "Internet.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

// Sử dụng _popen để gọi CMD
string CallPythonTranslate(string tuTiengAnh) {
    string cmd = "python dich_tu.py \"" + tuTiengAnh + "\"";
    string result = "";
    char buffer[128];
    
    // Mở pipe để đọc kết quả từ python
    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) return "";

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }
    _pclose(pipe);

    // Xóa ký tự xuống dòng thừa nếu có
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    
    return result;
}