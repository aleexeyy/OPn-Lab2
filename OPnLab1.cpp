#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class Stack {
private:
    Node* head;

public:
    Stack() : head(nullptr) {
        readArrayFromConsole();
    }

    ~Stack() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    int pop() {
        if (!head) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        Node* temp = head;
        int value = temp->data;
        head = head->next;
        delete temp;
        return value;
    }

    int peek() {
        if (!head) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return head->data;
    }

    void readArrayFromConsole() {
        int n;
        cout << "Enter the number of elements: ";
        cin >> n;

        cout << "Enter " << n << " elements: ";
        for (int i = 0; i < n; ++i) {
            int element;
            cin >> element;
            push(element);
        }
    }
};

int main() {
    Stack stack;

    cout << "Top element: " << stack.peek() << endl;
    
    cout << "Popping elements: ";
    while (stack.peek() != -1) {
        cout << stack.pop() << " ";
    }
    cout << endl;

    return 0;
}
