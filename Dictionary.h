#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <iostream>
using namespace std;

#define TABLE_SIZE 26 // Kích thước bảng băm (A-Z)

// Cấu trúc một Node
struct Node {
    string tuTiengAnh;
    string nghiaTiengViet;
    Node* next;
};

// Cấu trúc Bảng băm
struct HashTable {
    Node* buckets[TABLE_SIZE];
};

// --- KHAI BÁO CÁC HÀM ---
void InitHashTable(HashTable &ht);
int HashFunction(string tuTiengAnh);
void AddWord(HashTable &ht, string anh, string viet);
Node* SearchWord(HashTable ht, string anh);
void DisplayAll(HashTable ht);
void SaveToFile(HashTable ht, string filename);
void LoadFromFile(HashTable &ht, string filename);
bool RenameWord(HashTable &ht, string tuCu, string tuMoi, string nghiaMoi);
bool DeleteWord(HashTable &ht, string anh);

#endif