//NAME:SAAD ASIF ALI
//ROLL NO:L1F24BSCS0083

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

static void ignoreLine() {
    char ch;
    while (cin.get(ch)) {
        if (ch == '\n') break;
    }
}

static bool isSpace(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

static double parseDoubleManual(const string& token) {
    int i = 0;
    while (i < (int)token.size() && isSpace(token[i])) i++;

    int sign = 1;
    if (i < (int)token.size() && (token[i] == '+' || token[i] == '-')) {
        if (token[i] == '-') sign = -1;
        i++;
    }

    double value = 0.0;
    bool anyDigit = false;

    while (i < (int)token.size() && token[i] >= '0' && token[i] <= '9') {
        anyDigit = true;
        value = value * 10.0 + (token[i] - '0');
        i++;
    }

    if (i < (int)token.size() && token[i] == '.') {
        i++;
        double frac = 0.0;
        double div = 1.0;
        while (i < (int)token.size() && token[i] >= '0' && token[i] <= '9') {
            anyDigit = true;
            frac = frac * 10.0 + (token[i] - '0');
            div *= 10.0;
            i++;
        }
        value = value + frac / div;
    }

    if (!anyDigit) return 0.0;
    return sign * value;
}

static int parseIntManual(const string& token) {
    return (int)parseDoubleManual(token);
}

class Marks {
private:
    double quiz;
    double assignment;
    double mid;
    double finalExam;

public:
    Marks() : quiz(0), assignment(0), mid(0), finalExam(0) {}
    Marks(double q, double a, double m, double f)
        : quiz(q), assignment(a), mid(m), finalExam(f) {}

    void setQuiz(double q) { quiz = q; }
    void setAssignment(double a) { assignment = a; }
    void setMid(double m) { mid = m; }
    void setFinal(double f) { finalExam = f; }

    double getQuiz() const { return quiz; }
    double getAssignment() const { return assignment; }
    double getMid() const { return mid; }
    double getFinal() const { return finalExam; }

    double operator+() const {
        return quiz + assignment + mid + finalExam;
    }
};

class SportsProfile {
    string sportName;
    int score;
public:
    SportsProfile(string s="None", int sc=0) : sportName(s), score(sc) {}
    string getSportName() const { return sportName; }
    int getScore() const { return score; }

    void display() const {
        cout << "Sport: " << sportName << " | Score: " << score << "\n";
    }
};

class Person {
protected:
    string name;
    int age;
public:
    Person(string n="Unknown", int a=0) : name(n), age(a) {}
    virtual ~Person() {}
    string getName() const { return name; }
    int getAge() const { return age; }
    virtual void displayInfo() const = 0;
};

class Student : public virtual Person {
protected:
    string rollNumber;
    string program;
    int semester;
    char* email;
    Marks marks;
    SportsProfile sports;
    static int totalStudents;

    void copyEmail(const char* src) {
        if (email) delete[] email;
        int len = 0;
        while (src[len]) len++;
        email = new char[len + 1];
        for (int i = 0; i <= len; i++) email[i] = src[i];
    }

public:
    Student(string n="Unknown", int a=0, string r="N/A", string p="N/A",
            int s=1, const char* e="none@email.com",
            Marks m=Marks(), SportsProfile sp=SportsProfile())
        : Person(n,a), rollNumber(r), program(p), semester(s),
          email(nullptr), marks(m), sports(sp) {
        copyEmail(e);
        totalStudents++;
    }

    virtual ~Student() {
        delete[] email;
        totalStudents--;
    }

    Student(const Student& other) : Person(other.name, other.age), email(nullptr) {
        rollNumber = other.rollNumber;
        program = other.program;
        semester = other.semester;
        copyEmail(other.email);
        marks = other.marks;
        sports = other.sports;
        totalStudents++;
    }

    Student& operator=(const Student& other) {
        if (this == &other) return *this;
        name = other.name;
        age = other.age;
        rollNumber = other.rollNumber;
        program = other.program;
        semester = other.semester;
        copyEmail(other.email);
        marks = other.marks;
        sports = other.sports;
        return *this;
    }

    Student& operator++() { semester++; return *this; }
    bool operator==(const Student& other) const { return rollNumber == other.rollNumber; }

    string getRollNumber() const { return rollNumber; }
    string getProgram() const { return program; }
    int getSemester() const { return semester; }
    const char* getEmail() const { return email ? email : ""; }
    Marks getMarks() const { return marks; }
    SportsProfile getSportsProfile() const { return sports; }

    void displayInfo() const override {
        cout << "\n--- STUDENT ---\n";
        cout << "Name: " << name << "\nAge: " << age
             << "\nRoll: " << rollNumber
             << "\nProgram: " << program
             << "\nSemester: " << semester
             << "\nEmail: " << email << "\n";

        cout << "Marks: "
             << marks.getQuiz() << " "
             << marks.getAssignment() << " "
             << marks.getMid() << " "
             << marks.getFinal() << "\n";

        cout << "Total: " << +marks << "\n";
        sports.display();
    }

    friend ostream& operator<<(ostream& out, const Student& s) {
        out << s.name << "," << s.age << "," << s.rollNumber << ","
            << s.program << "," << s.semester << "," << s.email << ","
            << s.marks.getQuiz() << "," << s.marks.getAssignment() << ","
            << s.marks.getMid() << "," << s.marks.getFinal() << ","
            << s.sports.getSportName() << "," << s.sports.getScore();
        return out;
    }

    friend istream& operator>>(istream& in, Student& s) {
        cout << "Name: "; getline(in, s.name);
        cout << "Age: "; in >> s.age; ignoreLine();
        cout << "Roll: "; getline(in, s.rollNumber);
        cout << "Program: "; getline(in, s.program);
        cout << "Semester: "; in >> s.semester; ignoreLine();

        string em;
        cout << "Email: "; getline(in, em);
        s.copyEmail(em.c_str());

        double q,a,m,f;
        cout << "Quiz: "; in >> q;
        cout << "Assignment: "; in >> a;
        cout << "Mid: "; in >> m;
        cout << "Final: "; in >> f;
        ignoreLine();

        s.marks = Marks(q,a,m,f);

        string sp; int sc;
        cout << "Sport: "; getline(in, sp);
        cout << "Score: "; in >> sc; ignoreLine();
        s.sports = SportsProfile(sp, sc);

        return in;
    }

    static int getTotalStudents() { return totalStudents; }
};

int Student::totalStudents = 0;

class Instructor : public virtual Person {
protected:
    string employeeId;
    string designation;
public:
    Instructor(string n="Unknown", int a=0, string id="N/A", string des="N/A")
        : Person(n,a), employeeId(id), designation(des) {}
    virtual ~Instructor() {}

    virtual void displayInfo() const override {
        cout << "----- Instructor Info -----\n";
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Employee ID: " << employeeId << "\n";
        cout << "Designation: " << designation << "\n";
        cout << "---------------------------\n";
    }
};


class TeachingAssistant : public Student, public Instructor {
public:
    TeachingAssistant(string n="Unknown", int a=0,
                      string roll="N/A", string prog="N/A", int sem=1, const char* em="unknown@email.com",
                      Marks mk=Marks(), SportsProfile sp=SportsProfile(),
                      string empId="N/A", string des="TA")
        : Person(n,a),
          Student(n,a,roll,prog,sem,em,mk,sp),
          Instructor(n,a,empId,des) {}

    virtual void displayInfo() const override {
        cout << "===== Teaching Assistant =====\n";
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Roll: " << rollNumber << " | Program: " << program << " | Semester: " << semester << "\n";
        cout << "Email: " << (email ? email : "") << "\n";
        cout << "Employee ID: " << employeeId << " | Designation: " << designation << "\n";
        cout << "Total Marks: " << +marks << "\n";
        sports.display();
        cout << "==============================\n";
    }
};

class Course {
    string courseCode;
    string title;
    int creditHours;
public:
    Course(string c="N/A", string t="N/A", int ch=0) : courseCode(c), title(t), creditHours(ch) {}
    string getCourseCode() const { return courseCode; }
    string getTitle() const { return title; }
    int getCreditHours() const { return creditHours; }
    void display() const {
        cout << "Course: " << courseCode << " | " << title << " | Credit Hours: " << creditHours << "\n";
    }
};
class Enrollment {
    Student* studentPtr;
    Course* coursePtr;
public:
    Enrollment(Student* s = nullptr, Course* c = nullptr)
        : studentPtr(s), coursePtr(c) {}

            Student* getStudent() const { return studentPtr; }
    Course* getCourse() const { return coursePtr; }


    void display() const {
        if (!studentPtr || !coursePtr) {
            cout << "Invalid Enrollment\n";
            return;
        }

        cout << "Student: "
             << studentPtr->getName()
             << " (" << studentPtr->getRollNumber() << ")"
             << "  -->  Course: "
             << coursePtr->getCourseCode()
             << " - " << coursePtr->getTitle()
             << " ("
             << coursePtr->getCreditHours()
             << " CH)\n";
    }
};
Student* findStudentByRoll(Student** students, int studentCount, const string& roll) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i]->getRollNumber() == roll)
            return students[i];
    }
    return nullptr;
}

Course* findCourseByCode(Course** courses, int courseCount, const string& code) {
    for (int i = 0; i < courseCount; i++) {
        if (courses[i]->getCourseCode() == code)
            return courses[i];
    }
    return nullptr;
}
bool saveEnrollments(const Enrollment* enrollments, int enrollCount, const string& filename) {
    ofstream fout(filename.c_str());
    if (!fout) return false;

    for (int i = 0; i < enrollCount; i++) {
        fout << enrollments[i].getStudent()->getRollNumber() << ","
             << enrollments[i].getCourse()->getCourseCode() << "\n";
    }

    fout.close();
    return true;
}
bool loadEnrollments(
    Enrollment* enrollments,
    int& enrollCount,
    const string& filename,
    Student** students,
    int studentCount,
    Course** courses,
    int courseCount,
    int maxEnroll
) {
    ifstream fin(filename.c_str());
    if (!fin) {
        cout << "Enrollment file not found.\n";
        return false;
    }

    enrollCount = 0;
    string line;
    int skipped = 0;

    while (getline(fin, line) && enrollCount < maxEnroll) {
        if (line.empty()) continue;

        int pos = line.find(',');
        if (pos == string::npos) continue;

        string roll = line.substr(0, pos);
        string code = line.substr(pos + 1);

        int s = 0, e = roll.size() - 1;
        while (s <= e && isSpace(roll[s])) s++;
        while (e >= s && isSpace(roll[e])) e--;
        roll = (s <= e) ? roll.substr(s, e - s + 1) : "";

        s = 0; e = code.size() - 1;
        while (s <= e && isSpace(code[s])) s++;
        while (e >= s && isSpace(code[e])) e--;
        code = (s <= e) ? code.substr(s, e - s + 1) : "";

        Student* sPtr = findStudentByRoll(students, studentCount, roll);
        Course* cPtr = findCourseByCode(courses, courseCount, code);

        if (sPtr && cPtr) {
            enrollments[enrollCount++] = Enrollment(sPtr, cPtr);
        } else {
            skipped++;
        }
    }

    fin.close();

    cout << "Loaded " << enrollCount << " enrollments.\n";
    if (skipped > 0)
        cout << "Skipped " << skipped << " entries (student/course missing).\n";

    return true;
}

class DataSample {
    double* features;
    int featureCount;
public:
    DataSample() : features(0), featureCount(0) {}
    DataSample(int count) : features(0), featureCount(0) { init(count); }
    ~DataSample() { if (features) delete[] features; features = 0; featureCount = 0; }

    void init(int count) {
        if (features) delete[] features;
        featureCount = count;
        features = 0;
        if (featureCount > 0) {
            features = new double[featureCount];
            for (int i=0;i<featureCount;i++) features[i] = 0;
        }
    }

    DataSample(const DataSample& other) : features(0), featureCount(0) {
        init(other.featureCount);
        for (int i=0;i<featureCount;i++) features[i] = other.features[i];
    }

    DataSample& operator=(const DataSample& other) {
        if (this == &other) return *this;
        init(other.featureCount);
        for (int i=0;i<featureCount;i++) features[i] = other.features[i];
        return *this;
    }

    double& operator[](int idx) { return features[idx]; }
    const double& operator[](int idx) const { return features[idx]; }
    int getFeatureCount() const { return featureCount; }

    void display() const {
        cout << "[";
        for (int i=0;i<featureCount;i++) {
            cout << features[i];
            if (i < featureCount-1) cout << ", ";
        }
        cout << "]\n";
    }
};

class DataSet {
protected:
    DataSample* samples;
    int sampleCount;
    int featureCount;
public:
    DataSet() : samples(0), sampleCount(0), featureCount(0) {}
    virtual ~DataSet() { if (samples) delete[] samples; samples = 0; }

    int getSampleCount() const { return sampleCount; }
    int getFeatureCount() const { return featureCount; }
    DataSample& getSample(int idx) { return samples[idx]; }
    const DataSample& getSample(int idx) const { return samples[idx]; }

    virtual bool loadFromFile(const string& filename) = 0;
    virtual bool saveToFile(const string& filename) const = 0;

    void display() const {
        cout << "DataSet Samples: " << sampleCount << " | Features: " << featureCount << "\n";
        for (int i=0;i<sampleCount;i++) {
            cout << "Row " << (i+1) << ": ";
            samples[i].display();
        }
    }
};

class CSVDataSet : public DataSet {
    static bool hasLetters(const string& s) {
        for (int i = 0; i < (int)s.size(); i++) {
            char c = s[i];
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                return true;
        }
        return false;
    }

    static int countCommas(const string& line) {
        int c = 0;
        for (int i = 0; i < (int)line.size(); i++)
            if (line[i] == ',') c++;
        return c;
    }

public:
    bool loadFromFile(const string& filename) override {
        ifstream fin(filename.c_str());
        if (!fin) return false;

        string line;
        bool headerSkipped = false;
        int rows = 0;
        int cols = 0;

        while (getline(fin, line)) {
            if (line.empty()) continue;

            if (!headerSkipped && hasLetters(line)) {
                headerSkipped = true;
                continue;
            }

            rows++;
            int c = countCommas(line) + 1;
            if (c > cols) cols = c;
        }
        fin.close();

        if (rows == 0 || cols == 0) return false;

        if (samples) delete[] samples;
        sampleCount = rows;
        featureCount = cols;
        samples = new DataSample[sampleCount];
        for (int i = 0; i < sampleCount; i++)
            samples[i].init(featureCount);

        fin.open(filename.c_str());
        int r = 0;
        headerSkipped = false;

        while (getline(fin, line) && r < sampleCount) {
            if (line.empty()) continue;

            if (!headerSkipped && hasLetters(line)) {
                headerSkipped = true;
                continue;
            }

            int c = 0;
            string token = "";

            for (int i = 0; i <= (int)line.size(); i++) {
                if (i == (int)line.size() || line[i] == ',') {
                    samples[r][c++] = parseDoubleManual(token);
                    token = "";
                } else {
                    token += line[i];
                }
            }
            r++;
        }
        fin.close();
        return true;
    }

    bool saveToFile(const string& filename) const override {
        ofstream fout(filename.c_str());
        if (!fout) return false;

        for (int i = 0; i < sampleCount; i++) {
            for (int j = 0; j < featureCount; j++) {
                fout << samples[i][j];
                if (j < featureCount - 1) fout << ",";
            }
            fout << "\n";
        }
        fout.close();
        return true;
    }
};

class FeatureScaler {
    static void minMax(const DataSet& ds, int featureIndex, double& mn, double& mx) {
        mn = ds.getSample(0)[featureIndex];
        mx = ds.getSample(0)[featureIndex];
        for (int i=1;i<ds.getSampleCount();i++) {
            double v = ds.getSample(i)[featureIndex];
            if (v < mn) mn = v;
            if (v > mx) mx = v;
        }
    }
public:
    void normalize(DataSample& sample) {
        int n = sample.getFeatureCount();
        if (n <= 0) return;
        double mn = sample[0], mx = sample[0];
        for (int i=1;i<n;i++) {
            if (sample[i] < mn) mn = sample[i];
            if (sample[i] > mx) mx = sample[i];
        }
        double range = mx - mn;
        if (range == 0) return;
        for (int i=0;i<n;i++) sample[i] = (sample[i] - mn) / range;
    }

    void normalize(DataSet& ds) {
        if (ds.getSampleCount() <= 0 || ds.getFeatureCount() <= 0) return;
        for (int j=0;j<ds.getFeatureCount();j++) {
            double mn=0, mx=0;
            minMax(ds, j, mn, mx);
            double range = mx - mn;
            if (range == 0) continue;
            for (int i=0;i<ds.getSampleCount();i++) {
                double v = ds.getSample(i)[j];
                ds.getSample(i)[j] = (v - mn) / range;
            }
        }
    }
};

class PerformanceAnalyzer {
public:
    double totalMarks(const Student& s) const { return +s.getMarks(); }
    void showTotalMarks(const Student& s) const {
        cout << "Total Marks: " << totalMarks(s) << "\n";
    }
};

class ReportGenerator {
public:
    static void generateStudentReport(const Student& s, ostream& out) {
        out << "===== STUDENT REPORT =====\n";
        out << "Name: " << s.getName() << "\n";
        out << "Age: " << s.getAge() << "\n";
        out << "Roll: " << s.getRollNumber() << "\n";
        out << "Semester: " << s.getSemester() << "\n";
        out << "Email: " << s.getEmail() << "\n";
        Marks m = s.getMarks();
        out << "Marks: " << m.getQuiz() << " " << m.getAssignment() << " " << m.getMid() << " " << m.getFinal() << "\n";
        out << "Total: " << +m << "\n";
        out << "Sports: " << s.getSportsProfile().getSportName() << " " << s.getSportsProfile().getScore() << "\n";
        out << "==========================\n";
    }
};



bool saveAllStudents(Student** students, int count, const string& filename) {
    ofstream fout(filename.c_str());
    if (!fout) return false;
    
    for (int i = 0; i < count; i++) {
        fout << *students[i] << "\n";
    }
    fout.close();
    cout << "Saved " << count << " students to " << filename << "\n";
    return true;
}

bool loadAllStudents(Student** students, int& count, const string& filename, int maxStudents) {
    ifstream fin(filename.c_str());
    if (!fin) return false;
    
    for (int i = 0; i < count; i++) {
        delete students[i];
    }
    count = 0;
    
    string line;
    while (getline(fin, line) && count < maxStudents) {
        if (line.empty()) continue;
        
        string tokens[12];
        int tokenCount = 0;
        string current = "";
        
        for (int i = 0; i <= (int)line.size(); i++) {
            if (i == (int)line.size() || line[i] == ',') {
                tokens[tokenCount++] = current;
                current = "";
            } else {
                current += line[i];
            }
        }
        
        if (tokenCount >= 12) {
            Student* s = new Student(
                tokens[0],
                parseIntManual(tokens[1]),
                tokens[2],
                tokens[3],
                parseIntManual(tokens[4]),
                tokens[5].c_str(),
                Marks(
                    parseDoubleManual(tokens[6]),
                    parseDoubleManual(tokens[7]),
                    parseDoubleManual(tokens[8]),
                    parseDoubleManual(tokens[9])
                ),
                SportsProfile(tokens[10], parseIntManual(tokens[11]))
            );
            students[count++] = s;
        }
    }
    
    fin.close();
    cout << "Loaded " << count << " students from " << filename << "\n";
    return true;
}

bool exportMarksToCSV(Student** students, int count, const string& filename) {
    ofstream fout(filename.c_str());
    if (!fout) return false;
    
    for (int i = 0; i < count; i++) {
        Marks m = students[i]->getMarks();
        fout << m.getQuiz() << "," << m.getAssignment() << "," << m.getMid() << "," << m.getFinal() << "\n";
    }
    
    fout.close();
    cout << "Exported marks for " << count << " students to " << filename << "\n";
    return true;
}


int main() {
    Student* students[60];
    int studentCount = 0;

    Course* courses[30];
    int courseCount = 0;

    Enrollment enrollments[120];
    int enrollCount = 0;

    Instructor* instructors[30];
    int instructorCount = 0;


    CSVDataSet dataset;
    FeatureScaler scaler;
    PerformanceAnalyzer analyzer;

    while (true) {
        cout << "\n===== SPDS MENU =====\n";
        cout << "1) Add Student\n";
        cout << "2) Add Teaching Assistant\n";
        cout << "3) Add Instructor\n";
        cout << "4) Add Course\n";
        cout << "5) Display All Students & TAs\n";
        cout << "6) Display All Courses\n";
        cout << "7) Enroll Student in Course\n";
        cout << "8) Display Enrollments\n";
        cout << "9) Save All Students to File\n";
        cout << "10) Load All Students from File\n";
        cout << "11) Save Enrollments to File\n";
        cout << "12) Display All Instructors\n";
        cout << "13) Load CSV Dataset\n";
        cout << "14) Display Dataset\n";
        cout << "15) Normalize Dataset\n";
        cout << "16) Save Dataset to CSV\n";
        cout << "17) Analyze Student Total Marks\n";
        cout << "18) Export Student Marks to CSV\n";
        cout << "19) Generate Student Report (to file)\n";
        cout << "0) Exit\n";
        cout << "Choose: ";

        int choice;
        cin >> choice;
        ignoreLine();

        if (choice == 0) break;

        if (choice == 1) {
            if (studentCount >= 60) { cout << "Student limit reached.\n"; continue; }
            Student* s = new Student();
            cin >> *s;
            students[studentCount++] = s;
            cout << "Student added.\n";
        }

        else if (choice == 2) {
            if (studentCount >= 60) { cout << "Student limit reached.\n"; continue; }

            string n, roll, prog, emp, des, em;
            int a, sem;
            double q, asg, mid, fin;
            string sp;
            int sc;

            cout << "Name: "; getline(cin, n);
            cout << "Age: "; cin >> a; ignoreLine();
            cout << "Roll: "; getline(cin, roll);
            cout << "Program: "; getline(cin, prog);
            cout << "Semester: "; cin >> sem; ignoreLine();
            cout << "Email: "; getline(cin, em);

            cout << "Quiz marks: "; cin >> q;
            cout << "Assignment marks: "; cin >> asg;
            cout << "Mid marks: "; cin >> mid;
            cout << "Final marks: "; cin >> fin;
            ignoreLine();

            cout << "Sport Name: "; getline(cin, sp);
            cout << "Sport Score: "; cin >> sc; ignoreLine();

            cout << "Employee ID: "; getline(cin, emp);
            cout << "Designation: "; getline(cin, des);

            TeachingAssistant* ta = new TeachingAssistant(
                n, a, roll, prog, sem, em.c_str(),
                Marks(q, asg, mid, fin),
                SportsProfile(sp, sc),
                emp, des
            );

            students[studentCount++] = ta;
            cout << "Teaching Assistant added.\n";
        }

     else if (choice == 3) {
    if (instructorCount >= 30) {
        cout << "Instructor limit reached.\n";
        continue;
    }

    string n, empId, desig;
    int a;

    cout << "Name: "; getline(cin, n);
    cout << "Age: "; cin >> a; ignoreLine();
    cout << "Employee ID: "; getline(cin, empId);
    cout << "Designation: "; getline(cin, desig);

    instructors[instructorCount++] =
        new Instructor(n, a, empId, desig);

    cout << "Instructor added.\n";
}


        else if (choice == 4) {
            if (courseCount >= 30) { cout << "Course limit reached.\n"; continue; }
            string code, title;
            int ch;

            cout << "Course Code: "; getline(cin, code);
            cout << "Title: "; getline(cin, title);
            cout << "Credit Hours: "; cin >> ch; ignoreLine();

            courses[courseCount++] = new Course(code, title, ch);
            cout << "Course added.\n";
        }

        else if (choice == 5) {
            cout << "Students/TAs in system: " << studentCount << "\n";
            for (int i = 0; i < studentCount; i++) {
                Person* p = students[i];
                p->displayInfo();
            }
            cout << "TotalStudents(static): " << Student::getTotalStudents() << "\n";
        }

        else if (choice == 6) {
            if (courseCount == 0) {
                cout << "No courses available.\n";
                continue;
            }

            cout << "\n===== COURSE LIST =====\n";
            for (int i = 0; i < courseCount; i++) {
                cout << (i + 1) << ") ";
                courses[i]->display();
            }
        }

        else if (choice == 7) {
            if (enrollCount >= 120) { cout << "Enrollment limit reached.\n"; continue; }
            if (studentCount == 0 || courseCount == 0) {
                cout << "Add students and courses first.\n";
                continue;
            }

            cout << "Select Student index (1.." << studentCount << "): ";
            int si; cin >> si; ignoreLine();
            cout << "Select Course index (1.." << courseCount << "): ";
            int ci; cin >> ci; ignoreLine();

            if (si < 1 || si > studentCount || ci < 1 || ci > courseCount) {
                cout << "Invalid index.\n";
                continue;
            }

            enrollments[enrollCount++] = Enrollment(students[si - 1], courses[ci - 1]);
            cout << "Enrolled.\n";
        }

        else if (choice == 8) {
            if (enrollCount == 0) {
                cout << "No enrollments available.\n";
                continue;
            }

            cout << "\n===== ENROLLMENT LIST =====\n";
            for (int i = 0; i < enrollCount; i++) {
                cout << (i + 1) << ") ";
                enrollments[i].display();
            }
        }

        else if (choice == 9) {
            string file;
            cout << "Filename to save all students: ";
            getline(cin, file);

            if (saveAllStudents(students, studentCount, file))
                cout << "All students saved successfully.\n";
            else
                cout << "Failed to save students.\n";
        }

        else if (choice == 10) {
            string file;
            cout << "Filename to load students from: ";
            getline(cin, file);

            if (loadAllStudents(students, studentCount, file, 60))
                cout << "All students loaded successfully.\n";
            else
                cout << "Failed to load students.\n";
        }

        else if (choice == 11) {
            string file;
            cout << "Filename to save enrollments: ";
            getline(cin, file);

            if (saveEnrollments(enrollments, enrollCount, file))
                cout << "Enrollments saved successfully.\n";
            else
                cout << "Failed to save enrollments.\n";
        }

             else if (choice == 12) {
    if (instructorCount == 0) {
        cout << "No instructors available.\n";
        continue;
    }

    cout << "\n===== INSTRUCTOR LIST =====\n";
    for (int i = 0; i < instructorCount; i++) {
        instructors[i]->displayInfo();
    }
}

        else if (choice == 13) {
            string file;
            cout << "CSV filename to load: ";
            getline(cin, file);
            dataset.loadFromFile(file);
        }

        else if (choice == 14) {
            dataset.display();
        }

        else if (choice == 15) {
            scaler.normalize(dataset);
            cout << "Dataset normalized.\n";
        }

        else if (choice == 16) {
            string file;
            cout << "CSV filename to save: ";
            getline(cin, file);
            dataset.saveToFile(file);
        }

        else if (choice == 17) {
            if (studentCount == 0) { cout << "No students.\n"; continue; }
            int si;
            cout << "Select Student index: ";
            cin >> si; ignoreLine();
            analyzer.showTotalMarks(*students[si - 1]);
        }

        else if (choice == 18) {
            string file;
            cout << "CSV filename for marks export: ";
            getline(cin, file);
            exportMarksToCSV(students, studentCount, file);
        }

        else if (choice == 19) {
            int si;
            cout << "Select Student index: ";
            cin >> si; ignoreLine();

            string file;
            cout << "Report filename: ";
            getline(cin, file);

            ofstream out(file.c_str());
            ReportGenerator::generateStudentReport(*students[si - 1], out);
            out.close();
            cout << "Report generated.\n";
        }


        else {
            cout << "Invalid option.\n";
        }
    }

    for (int i = 0; i < studentCount; i++) delete students[i];
    for (int i = 0; i < courseCount; i++) delete courses[i];
    for (int i = 0; i < instructorCount; i++) delete instructors[i];

    cout << "Program exited safely.\n";
    return 0;
}
