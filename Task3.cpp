#include <iostream>
#include <string>

using namespace std;

struct BitNode {
    int bit;
    BitNode* next;
    BitNode* prev;

    BitNode(int b) : bit(b), next(nullptr), prev(nullptr) {}
};
//Class
class BinaryDLL {
public:
    BitNode* head;
    BitNode* tail;

    BinaryDLL() : head(nullptr), tail(nullptr) {}

    // Copy Constructor 
    BinaryDLL(const BinaryDLL& other) : head(nullptr), tail(nullptr) {
        BitNode* temp = other.head;
        while (temp) {
            appendBit(temp->bit);
            temp = temp->next;
        }
    }

    // Copy Assignment Operator 
    BinaryDLL& operator=(const BinaryDLL& other) {
        if (this != &other) {
            clear();
            BitNode* temp = other.head;
            while (temp) {
                appendBit(temp->bit);
                temp = temp->next;
            }
        }
        return *this;
    }

    // Destructor
    ~BinaryDLL() {
        clear();
    }

    void clear() {
        BitNode* temp = head;
        while (temp) {
            BitNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = nullptr;
    }

    void appendBit(int bit) {
        BitNode* newNode = new BitNode(bit);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void prependBit(int bit) {
        BitNode* newNode = new BitNode(bit);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    int length() const {
        int count = 0;
        BitNode* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void storeBinary(const string& str) {
        clear();
        for (char ch : str) {
            if (ch == '0' || ch == '1') {
                appendBit(ch - '0');
            }
        }
        while (length() % 8 != 0 || length() == 0) {
            prependBit(0);
        }
    }

    BinaryDLL onesComplement() const {
        BinaryDLL res;
        BitNode* temp = head;
        while (temp) {
            res.appendBit(1 - temp->bit);
            temp = temp->next;
        }
        return res;
    }

    BinaryDLL add(const BinaryDLL& other) const {
        BinaryDLL res;
        BitNode* p1 = this->tail;
        BitNode* p2 = other.tail;
        int carry = 0;

        while (p1 != nullptr || p2 != nullptr || carry != 0) {
            int sum = carry;
            if (p1) { sum += p1->bit; p1 = p1->prev; }
            if (p2) { sum += p2->bit; p2 = p2->prev; }

            carry = sum / 2;
            res.prependBit(sum % 2);
        }

        while (res.length() % 8 != 0) {
            res.prependBit(0);
        }
        return res;
    }

    BinaryDLL twosComplement() const {
        BinaryDLL comp = onesComplement();
        BinaryDLL one;
        one.storeBinary("1");
        return comp.add(one);
    }

    BinaryDLL multiply(const BinaryDLL& other) const {
        BinaryDLL result;
        result.storeBinary("0");

        BitNode* p2 = other.tail;
        int shift = 0;

        while (p2) {
            if (p2->bit == 1) {
                BinaryDLL temp;
                BitNode* p1 = this->head;
                while (p1) {
                    temp.appendBit(p1->bit);
                    p1 = p1->next;
                }
                for (int i = 0; i < shift; i++) {
                    temp.appendBit(0);
                }
                while (temp.length() % 8 != 0) {
                    temp.prependBit(0);
                }
                result = result.add(temp);
            }
            shift++;
            p2 = p2->prev;
        }
        return result;
    }

    long long toDecimal() const {
        long long dec = 0;
        BitNode* temp = head;
        while (temp) {
            dec = (dec * 2) + temp->bit;
            temp = temp->next;
        }
        return dec;
    }

    void display() const {
        BitNode* temp = head;
        int count = 0;
        while (temp) {
            cout << temp->bit;
            count++;
            if (count % 8 == 0) cout << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
};
//Main Function
int main() {
    BinaryDLL num1, num2;
    string binStr1, binStr2;

    cout << "   BINARY ARITHMETIC SYSTEM (DLL)        \n";

    cout << "Enter first binary number (e.g., 1011): ";
    cin >> binStr1;
    num1.storeBinary(binStr1);

    cout << "Enter second binary number (e.g., 0101): ";
    cin >> binStr2;
    num2.storeBinary(binStr2);

    cout << "\nStored 8-bit Block Formats\n";
    cout << "Binary 1: "; num1.display();
    cout << "Binary 2: "; num2.display();

    cout << "\nComplements (of Binary 1)\n";
    cout << "1's Complement: "; num1.onesComplement().display();
    cout << "2's Complement: "; num1.twosComplement().display();

    cout << "\nBinary Addition\n";
    BinaryDLL sum = num1.add(num2);
    cout << "Sum (Binary):     "; sum.display();
    cout << "Sum (Decimal):    " << sum.toDecimal() << "\n";

    cout << "\nBinary Multiplication\n";
    BinaryDLL prod = num1.multiply(num2);
    cout << "Product (Binary): "; prod.display();
    cout << "Product (Decimal): " << prod.toDecimal() << "\n";

    return 0;
}