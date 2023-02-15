#include <fstream>
#include <iostream>

using namespace std;

struct Node {
    int data;
    int next;
};

struct BinLinkedList{
    private:
        fstream file;
        int head;
        int tail;
        int node_counter;
    
    public:
        BinLinkedList() {
            file.open("linked_list.bin", ios::binary | ios::out | ios::in);
            head = -1;
            tail = -1;
            node_counter = 0;
        }

        void addNodeEnd(int data){
            Node new_node;
            new_node.data = data;
            new_node.next = -1;

            int pos = file.tellp();
            if(pos == tail){
                cout << "There's going to be an infinite loop if we add this one in!" << endl;
                return;
            }
            file.seekp(0, ios::end);
            file.write((char*)&new_node, sizeof(Node));

            if (head == -1) {
                head = pos;
                tail = pos;
            } else {
                Node tail_node;
                file.seekg(tail, ios::beg);
                file.read((char*)&tail_node, sizeof(Node));
                tail_node.next = pos;
                file.seekp(tail, ios::beg);
                file.write((char*)&tail_node, sizeof(Node));
                tail = pos;
                file.seekp(0, ios::end);
                file.seekg(0, ios::end);     
            }

            node_counter++;
        }

        void addNodeBeg(int data){
            Node new_node;
            new_node.data = data;
            new_node.next = head;

            int pos = file.tellp();
            file.seekp(0, ios::end);
            file.write((char*)&new_node, sizeof(Node));

            if (head == -1) {
                tail = pos;
            }
            head = pos;

            node_counter++;
        }

        void printList() {
            int curr = head;
            while (curr != -1) {
                Node node;
                file.seekg(curr, ios::beg);
                file.read((char*)&node, sizeof(Node));
                cout << node.data << " ";
                curr = node.next;
            }
            cout << endl;
        }
};

int main(){
    BinLinkedList test_list;

    test_list.addNodeEnd(1);
    test_list.addNodeBeg(2);
    test_list.addNodeEnd(3);
    test_list.addNodeEnd(4);

    test_list.printList();
}

// class LinkedList {
// private:
//     fstream file;
//     int head;
//     int tail;
//     int node_counter;

// public:
//     LinkedList() {
//         file.open("linked_list.bin", ios::binary | ios::out | ios::in);
//         head = -1;
//         tail = -1;
//         node_counter = 0;
//     }

//     ~LinkedList() {
//         file.close();
//     }

//     // add a node to the end of the linked list
//     void addNode(int data) {
//         Node new_node;
//         new_node.data = data;
//         new_node.next = -1;

//         int pos = file.tellp();
//         file.seekp(0, ios::end);
//         file.write((char*)&new_node, sizeof(Node));

//         if (head == -1) {
//             head = pos;
//             tail = pos;
//         } else {
//             Node tail_node;
//             file.seekg(tail, ios::beg);
//             file.read((char*)&tail_node, sizeof(Node));
//             tail_node.next = pos;
//             tail = pos;
//             file.seekp(tail - sizeof(Node), ios::beg);
//             file.write((char*)&tail_node, sizeof(Node));
//         }

//         node_counter++;
//     }

//     // delete a node from the linked list
//     void deleteNode(int data) {
//         int prev = -1;
//         int curr = head;

//         while (curr != -1) {
//             Node node;
//             file.seekg(curr, ios::beg);
//             file.read((char*)&node, sizeof(Node));

//             if (node.data == data) {
//                 if (prev == -1) {
//                     head = node.next;
//                 } else {
//                     Node prev_node;
//                     file.seekg(prev, ios::beg);
//                     file.read((char*)&prev_node, sizeof(Node));
//                     prev_node.next = node.next;
//                     file.seekp(prev, ios::beg);
//                     file.write((char*)&prev_node, sizeof(Node));
//                 }
//                 node_counter--;
//                 break;
//             }
//             prev = curr;
//             curr = node.next;
//         }
//     }

//     // print the linked list
//     void printList() {
//         int curr = head;
//         while (curr != -1) {
//             Node node;
//             file.seekg(curr, ios::beg);
//             file.read((char*)&node, sizeof(Node));
//             cout << node.data << " ";
//             curr = node.next;
//         }
//         cout << endl;
//     }

//     // get the number of nodes in the linked list
//     int getSize() {
//         return node_counter;
//     }
// };
