#include <iostream>

using namespace std;

// Node structure for Circular Linked List 
struct PersonNode {
    int id;
    PersonNode* next;

    PersonNode(int personId) : id(personId), next(nullptr) {}
};

class JosephusSimulation {
private:
    PersonNode* head;

public:
    JosephusSimulation() : head(nullptr) {}

    // Destructor 
    ~JosephusSimulation() {
        if (!head) return;
        PersonNode* curr = head;
        PersonNode* nextNode = nullptr;

        // Breaking circle to avoid infinite loop 
        if (head->next) {
            PersonNode* tail = head;
            while (tail->next != head) {
                tail = tail->next;
            }
            tail->next = nullptr;
        }

        while (curr != nullptr) {
            nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = nullptr;
    }

    //Creating Circle of n people
    void createCircle(int N) {
        if (N <= 0) return;

        head = new PersonNode(1);
        PersonNode* prevNode = head;

        for (int i = 2; i <= N; i++) {
            PersonNode* newNode = new PersonNode(i);
            prevNode->next = newNode;
            prevNode = newNode;
        }
        prevNode->next = head; 
    }

    //Simulate Elimination Process,Display Order and Output Survivor
    void simulate(int N, int k) {
        if (N <= 0 || k <= 0) {
            cout << "Invalid input Number of people  and step count  must be greater than 0.\n";
            return;
        }

        createCircle(N);
        cout << "       JOSEPHUS ELIMINATION PROCESS      \n";

        PersonNode* curr = head;
        PersonNode* prev = nullptr;

        // Finding the tail node 
        while (curr->next != head) {
            curr = curr->next;
        }
        prev = curr;
        curr = head;

        int stepCount = 1;

        // Continue until only 1 person remains
        while (curr->next != curr) {
            // Traversing k-1 nodes 
            for (int count = 1; count < k; count++) {
                prev = curr;
                curr = curr->next;
            }

            // Printing eliminated person and relink around eliminated node
            cout << "Step " << stepCount++ << ": Person " << curr->id << " eliminated.\n";
            prev->next = curr->next;
            delete curr; // Free memory

            // Resume counting from next person
            curr = prev->next;
        }

        // Output as final survivor details
    
        cout << " SURVIVOR: Person " << curr->id << " \n";
  

        delete curr; // Free survivor node memory
        head = nullptr;
    }
};

int main() {
    int N, k;

    cout << "   JOSEPHUS PROBLEM SIMULATION   ";
    cout << "Enter total number of people N : ";
    cin >> N;
    cout << "Enter elimination step count k: ";
    cin >> k;

    JosephusSimulation sim;
    sim.simulate(N, k);

    return 0;
}