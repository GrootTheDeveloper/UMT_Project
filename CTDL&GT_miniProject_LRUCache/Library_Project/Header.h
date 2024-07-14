#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>
using namespace std;

// Khai báo lớp Node cho danh sách liên kết đôi

class Node {
public:
    int key;
    string value;
    Node* prev;
    Node* next;
    Node(int k, const string& v);  // Constructor
};

// Khai báo lớp DoublyLinkedList để quản lý thứ tự các mục
class DoublyLinkedList {
public:
    Node* head;  // Con trỏ tới node đầu tiên trong danh sách
    Node* tail;  // Con trỏ tới node cuối cùng trong danh sách

    DoublyLinkedList();  // Hàm khởi tạo

    void moveToFront(Node* node);  // Di chuyển một node lên đầu danh sách
    void addToFront(Node* node);   // Thêm một node vào đầu danh sách
    void remove(Node* node);       // Loại bỏ một node khỏi danh sách
};

// Khai báo lớp HashTable để lưu trữ các mục
const int TABLE_SIZE = 1000;

class HashTable {
private:
    vector<Node*> table;
    int hash(int key);

public:
    HashTable();
    Node*& operator[](int key);
    void erase(int key);
};
// Khai báo lớp LRUCache để quản lý bộ nhớ cache
class LRUCache {
private:
    int capacity;
    int size;
    DoublyLinkedList list;
    HashTable map;

public:
    LRUCache(int cap);

    string get(int key);
    void put(int key, const string& value);
    void display();
};

#endif
