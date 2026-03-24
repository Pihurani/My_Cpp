#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
public:
    int id;
    string name;
    float marks;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "ID: " << id << " | Name: " << name << " | Marks: " << marks << endl;
    }
};

// Save student to file
void saveToFile(Student s) {
    ofstream file("students.txt", ios::app);
    file << s.id << " " << s.name << " " << s.marks << endl;
    file.close();
}

// Display all students
void displayAll() {
    ifstream file("students.txt");
    Student s;

    while (file >> s.id >> s.name >> s.marks) {
        s.display();
    }

    file.close();
}

// Search student
void searchStudent(int id) {
    ifstream file("students.txt");
    Student s;
    bool found = false;

    while (file >> s.id >> s.name >> s.marks) {
        if (s.id == id) {
            cout << "Student Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student not found!\n";
    }

    file.close();
}

// Delete student
void deleteStudent(int id) {
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    Student s;
    bool found = false;

    while (file >> s.id >> s.name >> s.marks) {
        if (s.id != id) {
            temp << s.id << " " << s.name << " " << s.marks << endl;
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student deleted successfully!\n";
    else
        cout << "Student not found!\n";
}

// Main Menu
int main() {
    int choice, id;
    Student s;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                s.input();
                saveToFile(s);
                break;

            case 2:
                displayAll();
                break;

            case 3:
                cout << "Enter ID to search: ";
                cin >> id;
                searchStudent(id);
                break;

            case 4:
                cout << "Enter ID to delete: ";
                cin >> id;
                deleteStudent(id);
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}