#include <iostream>
#include <fstream>
using namespace std;

const int maxstudents = 30;
const int maxnamelength = 50;
const int days = 30;

int stringLength(char str[]) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

void stringCopy(char dest[], char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

bool stringCompare(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

void signUp() {
    char username[50], password[50], confirm[50];
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Confirm password: ";
    cin >> confirm;

    if (!stringCompare(password, confirm)) {
        cout << "Passwords do not match!\n";
        return;
    }

    ofstream fout("users.txt", ios::app);
    fout << username << "," << password << endl;
    fout.close();
    cout << "Account created.\n";
}

bool signIn() {
    char username[50], password[50], line[100];
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream fin("users.txt");
    while (fin.getline(line, 100)) {
        char fileUser[50], filePass[50];
        int i = 0, j = 0;
        while (line[i] != ',' && line[i] != '\0') fileUser[j++] = line[i++];
        fileUser[j] = '\0';
        i++; j = 0;
        while (line[i] != '\0') filePass[j++] = line[i++];
        filePass[j] = '\0';

        if (stringCompare(username, fileUser) && stringCompare(password, filePass)) {
            fin.close();
            cout << "Login success.\n";
            return true;
        }
    }
    fin.close();
    cout << "Invalid credentials.\n";
    return false;
}

void changePassword() {
    char username[50], oldPass[50], newPass[50], confirm[50];
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter current password: ";
    cin >> oldPass;

    ifstream fin("users.txt");
    ofstream temp("temp.txt");
    char line[100];
    bool updated = false;

    while (fin.getline(line, 100)) {
        char user[50], pass[50];
        int i = 0, j = 0;
        while (line[i] != ',' && line[i] != '\0') user[j++] = line[i++];
        user[j] = '\0';
        i++; j = 0;
        while (line[i] != '\0') pass[j++] = line[i++];
        pass[j] = '\0';

        if (stringCompare(username, user) && stringCompare(oldPass, pass)) {
            cout << "Enter new password: ";
            cin >> newPass;
            cout << "Confirm new password: ";
            cin >> confirm;

            if (stringCompare(newPass, confirm)) {
                temp << username << "," << newPass << endl;
                updated = true;
                cout << "Password updated.\n";
            } else {
                cout << "New passwords do not match.\n";
                temp << user << "," << pass << endl;
            }
        } else {
            temp << user << "," << pass << endl;
        }
    }

    fin.close();
    temp.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (!updated) {
        cout << "Incorrect username or password.\n";
    }
}

void loadStudentsFromFile(char** names, char** ids, int& count) {
    ifstream fin("students.txt");
    count = 0;
    char line[100];
    while (fin.getline(line, 100)) {
        int i = 0, j = 0;
        while (line[i] != ',' && line[i] != '\0') ids[count][j++] = line[i++];
        ids[count][j] = '\0';
        i++; j = 0;
        while (line[i] != '\0') names[count][j++] = line[i++];
        names[count][j] = '\0';
        count++;
    }
    fin.close();
}

void loadAttendanceFromFile(int attendance[30][30], int totalStudents) {
    ifstream fin("attendance.txt");
    char dummyID[20];
    for (int i = 0; i < totalStudents; i++) {
        fin >> dummyID;
        for (int j = 0; j < 30; j++) {
            fin >> attendance[i][j];
        }
    }
    fin.close();
}

void addStudents(char** names, char** ids, int& count) {
    cout << "How many students? ";
    cin >> count;
    for (int i = 0; i < count; i++) {
          while(true){
        cout<<"Enter ID:";
        cin>>ids[i];
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"Invalid input. Please enter a number."<<endl;
        
        }
        else{
            cin.ignore(1000,'\n');
            break;
 
        }
    }
        cout << "Enter name: ";
        cin.getline(names[i], maxnamelength);
    }

    ofstream fout("students.txt");
    for (int i = 0; i < count; i++) {
        fout << ids[i] << "," << names[i] << endl;
    }
    fout.close();
}

void markMyAttendance(char** names, char** ids, int attendance[30][30], int totalStudents, int day) {
    cout << "\n--- Mark Attendance for Day " << day + 1 << " ---\n";
    for (int i = 0; i < totalStudents; i++) {
        cout << "Is " << names[i] << " (ID: " << ids[i] << ") present? (1=Yes, 0=No): ";
        cin >> attendance[i][day];
        while (attendance[i][day] != 0 && attendance[i][day] != 1) {
            cout << "Invalid input. Enter 1 or 0: ";
            cin >> attendance[i][day];
        }
    }

    ofstream fout("attendance.txt");
    for (int i = 0; i < totalStudents; i++) {
        fout << ids[i] << ",";
        for (int j = 0; j < 30; j++) {
            fout << attendance[i][j] << " ";
        }
        fout << endl;
    }
    fout.close();
}

void viewClassReport(char** names, int attendance[30][30], int totalStudents) {
    cout << "\n--- Full Class Report ---\n";
    cout << "Name\t\tPresent\t\t%age\n";
    for (int i = 0; i < totalStudents; i++) {
        int present = 0;
        for (int j = 0; j < 30; j++) present += attendance[i][j];
        float percent = (present / 30.0) * 100;
        cout << names[i] << "\t\t" << present << "\t\t" << percent << "%\n";
    }
}

void viewStudentReport(char** names, int attendance[30][30], int totalStudents) {
    int index;
    cout << "Enter student number (1-" << totalStudents << "): ";
    cin >> index;

    if (index < 1 || index > totalStudents) {
        cout << "Invalid student number.\n";
        return;
    }

    index--;
    int present = 0;
    for (int j = 0; j < 30; j++) present += attendance[index][j];
    float percent = (present / 30.0) * 100;

    cout << "\nReport for " << names[index] << ":\n";
    cout << "Days Present: " << present << "/30\n";
    cout << "Percentage: " << percent << "%\n";
    cout << "Status: ";
    if (percent < 75) {
        cout << "Defaulter\n";
    } else {
        cout << "Good\n";
    }
}

void viewDefaulters(char** names, int attendance[30][30], int totalStudents) {
    cout << "\n--- Defaulters (Attendance < 75%) ---\n";
    for (int i = 0; i < totalStudents; i++) {
        int present = 0;
        for (int j = 0; j < 30; j++) present += attendance[i][j];
        float percent = (present / 30.0) * 100;
        if (percent < 75) {
            cout << names[i] << " - " << percent << "%\n";
        }
    }
}

void searchStudentAttendance(char** names, char** ids, int attendance[30][30], int totalStudents) {
    char query[50];
    bool found = false;

    cout << "\nEnter student name or ID to search: ";
    cin.ignore();
    cin.getline(query, 50);

    for (int i = 0; i < totalStudents; i++) {
        if (stringCompare(names[i], query) || stringCompare(ids[i], query)) {
            found = true;
            int present = 0;
            for (int j = 0; j < 30; j++) present += attendance[i][j];
            float percent = (present / 30.0) * 100;

            cout << "\nAttendance details for " << names[i] << ":\n";
            cout << "ID: " << ids[i] << "\n";
            cout << "Days Present: " << present << "/30\n";
            cout << "Percentage: " << percent << "%\n";
            cout << "Status: ";
            if (percent < 75) {
                cout << "Defaulter\n";
            } else {
                cout << "Good\n";
            }
            break;
        }
    }

    if (!found) {
        cout << "Student not found.\n";
    }
}

int main() {
    int choice;
    char** studentNames = new char*[maxstudents];
    char** studentIDs = new char*[maxstudents];
    for (int i = 0; i < maxstudents; i++) {
        studentNames[i] = new char[maxnamelength];
        studentIDs[i] = new char[20];
    }

    int attendance[30][30] = {};
    int studentCount = 0;

    loadStudentsFromFile(studentNames, studentIDs, studentCount);
    loadAttendanceFromFile(attendance, studentCount);

    while (true) {
        cout << "\n--- Attendance Recorder ---\n";
        cout << "1. Sign Up\n2. Sign In\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) signUp();
        else if (choice == 2) {
            if (signIn()) {
                int sub;
                do {
                    cout << "\n--- Menu ---\n";
                    cout << "1. Add Students\n";
                    cout << "2. Mark Attendance\n";
                    cout << "3. View Full Class Report\n";
                    cout << "4. View Individual Report\n";
                    cout << "5. View Defaulters List\n";
                    cout << "6. Search Student Attendance\n";
                    cout << "7. Change Password\n";
                    cout << "8. Sign Out\n";
                    cout << "Choice: ";
                    cin >> sub;

                    if (sub == 1) addStudents(studentNames, studentIDs, studentCount);
                    else if (sub == 2) {
                        int day;
                        cout << "Enter day (1-30): ";
                        cin >> day;
                        if (day >= 1 && day <= 30)
                            markMyAttendance(studentNames, studentIDs, attendance, studentCount, day - 1);
                        else
                            cout << "Invalid day!\n";
                    }
                    else if (sub == 3) viewClassReport(studentNames, attendance, studentCount);
                    else if (sub == 4) viewStudentReport(studentNames, attendance, studentCount);
                    else if (sub == 5) viewDefaulters(studentNames, attendance, studentCount);
                    else if (sub == 6) searchStudentAttendance(studentNames, studentIDs, attendance, studentCount);
                    else if (sub == 7) changePassword();

                } while (sub != 8);
            }
        }
        else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        }
        else cout << "Invalid option!\n";
    }

    for (int i = 0; i < maxstudents; i++) {
        delete[] studentNames[i];
        delete[] studentIDs[i];
    }
    delete[] studentNames;
    delete[] studentIDs;

    return 0;
}
