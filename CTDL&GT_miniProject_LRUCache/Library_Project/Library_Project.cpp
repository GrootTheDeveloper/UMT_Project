
#include "header.h"
#include <iostream>
#include <cstdlib> // Thư viện cho hàm system
#include <iomanip> // Thư viện cho setw

using namespace std;

void pauseAndClear() {
    cout << "Press Enter to continue...";
    cin.ignore(); 
    cin.get(); 
    system("CLS"); 
}

void menu() {
    cout << "Library Management System using LRU Cache\n";
    cout << "1. Add/Update a book\n";
    cout << "2. Get a book\n";
    cout << "3. Display cache\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    int capacity;
    cout << "Enter cache capacity: ";
    cin >> capacity;
    LRUCache cache(capacity);

    int choice, key;
    string value;
    while (true) {
        menu();
        cin >> choice;
        cin.ignore(); 
        switch (choice) {
        case 1:
            cout << "Enter book ID: ";
            cin >> key;
            cin.ignore();
            cout << "Enter book's name: ";
            getline(cin, value);
            cache.put(key, value);
            cout << "Book added/updated.\n";
            cin.ignore(); 
            pauseAndClear();
            break;
        case 2:

            cache.display();
            cout << '\n';
            cout << "Enter book ID: ";
            cin >> key;
            value = cache.get(key);
            if (value == "") {
                cout << "Book not found in cache.\n";
            }
            else {
                cout << "Book's name: " << value << endl;
            }
            cin.ignore(); 
            pauseAndClear();
            break;
        case 3:
            cout << "Current cache content: \n";
            cache.display();
            cin.ignore();
            pauseAndClear();
            break;
        case 4:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid option. Please try again.\n";
            cin.ignore(); 
            pauseAndClear();
        }
    }

    return 0;
}

// Định nghĩa hàm khởi tạo của Node
// Constructor
Node::Node(int k, const std::string& v) : key(k), value(v), prev(nullptr), next(nullptr) {}

// Định nghĩa hàm khởi tạo của DoublyLinkedList
// Constructor
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

// Định nghĩa các hàm của DoublyLinkedList
void DoublyLinkedList::moveToFront(Node* node) {
    if (node == head) return;

    if (node->prev) node->prev->next = node->next;

    if (node->next) node->next->prev = node->prev;

    if (node == tail) tail = tail->prev;

    node->next = head;
    node->prev = nullptr;
        
    if (head) head->prev = node;

    head = node;

    if (!tail) tail = head;
}



void DoublyLinkedList::addToFront(Node* node) {
    node->prev = nullptr;

    node->next = head;

    if (head) head->prev = node;

    head = node;

    if (!tail) tail = node;
}


void DoublyLinkedList::remove(Node* node) {
    if (node->prev) node->prev->next = node->next;

    if (node->next) node->next->prev = node->prev;

    if (node == head) head = node->next;

    if (node == tail) tail = node->prev;

    delete node;
}

// Định nghĩa hàm khởi tạo của HashTable

HashTable::HashTable() : table(TABLE_SIZE, nullptr) {}

int HashTable::hash(int key) {
    return key % TABLE_SIZE;
}

Node*& HashTable::operator[](int key) {
    return table[hash(key)];
}

void HashTable::erase(int key) {
    int idx = hash(key);
    table[idx] = nullptr;
}

// Định nghĩa hàm khởi tạo của LRUCache
//Constructor này khởi tạo bộ nhớ đệm LRU với dung lượng tối đa (capacity) 
//được truyền vào và thiết lập kích thước ban đầu của bộ nhớ đệm (size) là 0.
LRUCache::LRUCache(int cap) : capacity(cap), size(0) {}

// Định nghĩa các hàm của LRUCache

std::string LRUCache::get(int key) {
    Node* result = map[key];
    if (!result) {
        return ""; // Không tìm thấy mục
    }
    else {
        list.moveToFront(result);
        return result->value;
    }
}
void LRUCache::put(int key, const std::string& value) {
    Node* node = map[key];
    if (node) {
        node->value = value;
        list.moveToFront(node);
    }
    else {
        if (size == capacity) {
            Node* toRemove = list.tail;
            map.erase(toRemove->key);
            list.remove(toRemove);
            size--;
        }

        Node* newNode = new Node(key, value);

        list.addToFront(newNode);

        map[key] = newNode;

        size++;
    }
}

void LRUCache::display() {
    Node* curr = list.head;
    cout << left << setw(10) << "ID" << setw(20) << "NAME" << "PRIORITY" << endl;
    cout << "-----------------------------------------" << endl;
    int priority = 1;
    while (curr) {
        cout << left << setw(10) << curr->key << setw(20) << curr->value << priority << endl;
        curr = curr->next;
        priority++;
    }
    cout << endl;
}