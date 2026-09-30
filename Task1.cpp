#include <iostream>
#include <string>

using namespace std;

struct SongNode {
    int id;
    string name;
    string duration;
    SongNode* next;
    SongNode* prev;

    SongNode(int sId, string sName, string sDuration) {
        id = sId;
        name = sName;
        duration = sDuration;
        next = nullptr;
        prev = nullptr;
    }
};

class Playlist {
private:
    SongNode* head;
    SongNode* tail;
    SongNode* current;

public:
    Playlist() : head(nullptr), tail(nullptr), current(nullptr) {}

    ~Playlist() {
        SongNode* temp = head;
        while (temp != nullptr) {
            SongNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }

    void addSong(int id, const string& name, const string& duration) {
        SongNode* newNode = new SongNode(id, name, duration);
        if (!head) {
            head = tail = current = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "\n[Success] Song \"" << name << "\" added successfully!\n";
    }

    void deleteSong(int id) {
        if (!head) {
            cout << "\n[Error] Playlist is empty.\n";
            return;
        }

        SongNode* temp = head;
        while (temp != nullptr && temp->id != id) {
            temp = temp->next;
        }

        if (!temp) {
            cout << "\n[Error] Song with ID " << id << " not found.\n";
            return;
        }

        if (temp == current) {
            if (current->next) current = current->next;
            else current = current->prev;
        }

        if (temp == head) head = head->next;
        if (temp == tail) tail = tail->prev;

        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;

        delete temp;
        cout << "\n[Success] Song with ID " << id << " deleted successfully.\n";
    }

    void displayForward() {
        if (!head) {
            cout << "\n[Info] Playlist is empty.\n";
            return;
        }
        cout << "\n Playlist (Forward) \n";
        SongNode* temp = head;
        while (temp != nullptr) {
            cout << "ID: " << temp->id << " | Name: " << temp->name << " | Duration: " << temp->duration;
            if (temp == current) cout << "  <-- [Currently Playing]";
            cout << "\n";
            temp = temp->next;
        }
    }

    void displayBackward() {
        if (!tail) {
            cout << "\n[Info] Playlist is empty.\n";
            return;
        }
        cout << "\n Playlist (Backward) \n";
        SongNode* temp = tail;
        while (temp != nullptr) {
            cout << "ID: " << temp->id << " | Name: " << temp->name << " | Duration: " << temp->duration;
            if (temp == current) cout << "  <-- [Currently Playing]";
            cout << "\n";
            temp = temp->prev;
        }
    }

    void searchSong(int id) {
        SongNode* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                cout << "\n[Song Found] ID: " << temp->id << " | Name: " << temp->name << " | Duration: " << temp->duration << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "\n[Error] Song with ID " << id << " not found.\n";
    }

    void playNext() {
        if (!current) {
            cout << "\n[Error] Playlist is empty.\n";
            return;
        }
        if (current->next) {
            current = current->next;
            cout << "\n[Now Playing] ID: " << current->id << " | " << current->name << "\n";
        } else {
            cout << "\n[Info] You reached the end of the playlist.\n";
        }
    }

    void playPrevious() {
        if (!current) {
            cout << "\n[Error] Playlist is empty.\n";
            return;
        }
        if (current->prev) {
            current = current->prev;
            cout << "\n[Now Playing] ID: " << current->id << " | " << current->name << "\n";
        } else {
            cout << "\n[Info] You are at the start of the playlist.\n";
        }
    }

    void reversePlaylist() {
        if (!head || !head->next) {
            cout << "\n[Info] Playlist reversed.\n";
            return;
        }

        SongNode* temp = nullptr;
        SongNode* curr = head;
        tail = head;

        while (curr != nullptr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }

        if (temp != nullptr) {
            head = temp->prev;
        }
        cout << "\n[Success] Playlist reversed in place successfully!\n";
    }
};

int main() {
    Playlist p;
    int choice, id;
    string name, duration;

    do {
        cout << "\n PLAYLIST MANAGEMENT MENU \n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist Forward\n";
        cout << "4. Display Playlist Backward\n";
        cout << "5. Search Song by ID\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Reverse Playlist\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Song ID: ";
                cin >> id;
                cout << "Enter Song Name (use _ for spaces, e.g. Song_Name): ";
                cin >> name;
                cout << "Enter Duration (e.g. 5:55): ";
                cin >> duration;
                p.addSong(id, name, duration);
                break;
            case 2:
                cout << "Enter Song ID to delete: ";
                cin >> id;
                p.deleteSong(id);
                break;
            case 3:
                p.displayForward();
                break;
            case 4:
                p.displayBackward();
                break;
            case 5:
                cout << "Enter Song ID to search: ";
                cin >> id;
                p.searchSong(id);
                break;
            case 6:
                p.playNext();
                break;
            case 7:
                p.playPrevious();
                break;
            case 8:
                p.reversePlaylist();
                break;
            case 0:
                cout << "Exiting\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 0);

    return 0;
}