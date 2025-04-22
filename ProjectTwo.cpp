#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


// Define Course structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Global course map (key = courseNumber)
map<string, Course> courses;

// Helper to trim whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

// Load courses from file into map
void loadData(const string& filename) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error: Could not open file \"" << filename << "\".\n";
        return;
    }

    courses.clear(); // Clear previous data

    while (getline(file, line)) {
        stringstream ss(line);
        string number, title, prereq;

        getline(ss, number, ',');
        getline(ss, title, ',');

        Course course;
        course.courseNumber = trim(number);
        course.courseTitle = trim(title);

        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(trim(prereq));
        }

        courses[course.courseNumber] = course;
    }

    cout << "Courses loaded successfully from \"" << filename << "\".\n";
}

// Print course list sorted alphanumerically
void printCourseList() {
    if (courses.empty()) {
        cout << "No courses loaded.\n";
        return;
    }

    vector<string> sortedKeys;
    for (const auto& pair : courses) {
        sortedKeys.push_back(pair.first);
    }

    sort(sortedKeys.begin(), sortedKeys.end());

    cout << "\nCourse List:\n";
    for (const auto& key : sortedKeys) {
        const Course& course = courses[key];
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

// Print a specific course and its prerequisites
void printCourseInfo(const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it == courses.end()) {
        cout << "Course \"" << courseNumber << "\" not found.\n";
        return;
    }

    const Course& course = it->second;
    cout << course.courseNumber << ", " << course.courseTitle << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None\n";
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1)
                cout << ", ";
        }
        cout << endl;
    }
}

// Show menu options
void showMenu() {
    cout << "\nMenu:\n";
    cout << "  1. Load Data Structure\n";
    cout << "  2. Print Course List\n";
    cout << "  3. Print Course\n";
    cout << "  9. Exit\n";
    cout << "Enter option: ";
}

// Main function
int main() {
    int choice;
    string filename, courseNumber;

    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // Clear newline from buffer

        switch (choice) {
        case 1:
            cout << "Enter file name: ";
            getline(cin, filename);
            loadData(filename);
            break;
        case 2:
            printCourseList();
            break;
        case 3:
            cout << "Enter course number (e.g., CS101): ";
            getline(cin, courseNumber);
            printCourseInfo(courseNumber);
            break;
        case 9:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
