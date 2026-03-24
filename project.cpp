#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

    void display() const {
        cout << "ID: " << id 
             << " | Name: " << name 
             << " | Marks: " << marks << endl;
    }
};

vector<Student> students;

// Load data from file
void loadFromFile() {
    ifstream file("students.txt");
    Student s;

    while (file >> s.id >> s.name >> s.marks) {
        students.push_back(s);
    }
    file.close();
}

// Save all data to file
void saveToFile() {
    ofstream file("students.txt");
    for (auto &s : students) {
        file << s.id << " " << s.name << " " << s.marks << endl;
    }
    file.close();
}

// Add student
void addStudent() {
    Student s;
    s.input();
    students.push_back(s);
    saveToFile();
    cout << "✅ Student added successfully!\n";
}

// Display all students
void displayAll() {
    if (students.empty()) {
        cout << "⚠️ No records found!\n";
        return;
    }

    for (auto &s : students) {
        s.display();
    }
}

// Search student
void searchStudent() {
    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    for (auto &s : students) {
        if (s.id == id) {
            cout << "✅ Student Found:\n";
            s.display();
            return;
        }
    }
    cout << "❌ Student not found!\n";
}

// Delete student
void deleteStudent() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    for (auto it = students.begin(); it != students.end(); it++) {
        if (it->id == id) {
            students.erase(it);
            saveToFile();
            cout << "✅ Student deleted!\n";
            return;
        }
    }
    cout << "❌ Student not found!\n";
}

// Update student
void updateStudent() {
    int id;
    cout << "Enter ID to update: ";
    cin >> id;

    for (auto &s : students) {
        if (s.id == id) {
            cout << "Enter new details:\n";
            s.input();
            saveToFile();
            cout << "✅ Updated successfully!\n";
            return;
        }
    }
    cout << "❌ Student not found!\n";
}

// Sort students by marks
void sortStudents() {
    sort(students.begin(), students.end(), [](Student a, Student b) {
        return a.marks > b.marks;
    });

    cout << "📊 Sorted by marks (High → Low)\n";
    displayAll();
}

// Main menu
int main() {
    int choice;

    loadFromFile();

    do {
        cout << "\n===== 🎓 STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student\n";
        cout << "6. Sort by Marks\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: sortStudents(); break;
            case 7: cout << "👋 Exiting...\n"; break;
            default: cout << "⚠️ Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}