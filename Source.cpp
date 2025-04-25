#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Student {
    char fio[100];
    int age;
    char gender[10];
    int course;
    double rating;
};


void createFile(const char* filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cout << "������ �������� �����!" << endl;
        return;
    }


    int n;
    cout << "������� ���������� ���������: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Student student;
        cout << "������� ������ �������� #" << i + 1 << ":\n";
        cout << "���: ";
        cin.ignore();
        cin.getline(student.fio, 100);
        cout << "�������: ";
        cin >> student.age;
        cout << "���: ";
        cin >> student.gender;
        cout << "����: ";
        cin >> student.course;
        cout << "������������: ";
        cin >> student.rating;

        outfile << student.fio << ";" << student.age << ";" << student.gender << ";"
            << student.course << ";" << student.rating << endl;
    }

    outfile.close();
    cout << "���� ������� ������.\n";
}


void viewFile(const char* filename) {
    ifstream infile(filename);
    if (!infile) {
        cout << "������ �������� �����!" << endl;
        return;
    }

    cout << "���������� �����:\n";
    char line[256];
    while (infile.getline(line, 256)) {
        cout << line << endl;
    }

    infile.close();
}

void filterStudents(const char* inputFile, const char* outputFile, int n, char letter) {
    ifstream infile(inputFile);
    if (!infile) {
        cout << "������ �������� �������� �����!" << endl;
        return;
    }

    ofstream outfile(outputFile);
    if (!outfile) {
        cout << "������ �������� ��������� �����!" << endl;
        infile.close();
        return;
    }

    char line[256];
    while (infile.getline(line, 256)) {
        Student student;


        char* token = strtok(line, ";");
        strcpy(student.fio, token);

        token = strtok(nullptr, ";");
        student.age = atoi(token);

        token = strtok(nullptr, ";");
        strcpy(student.gender, token);

        token = strtok(nullptr, ";");
        student.course = atoi(token);

        token = strtok(nullptr, ";");
        student.rating = atof(token);

        
        if (student.course == n && student.fio[0] == letter) {
            outfile << student.fio << ";" << student.age << ";" << student.gender << ";"
                << student.course << ";" << student.rating << endl;
        }
    }

    infile.close();
    outfile.close();
    cout << "���������� ���������. ���������� �������� � ���� " << outputFile << ".\n";
}

int main() {
    setlocale(LC_ALL, "rus");
    const char* inputFile = "students.txt";
    const char* outputFile = "filtered_students.txt";

    int ch;
    do {
        cout << "����:\n";
        cout << "1. ������� ��������� ����\n";
        cout << "2. ����������� ��������� ����\n";
        cout << "3. ������� � ����������\n";
        cout << "��� �����: ";
        cin >> ch;

        switch (ch) {
        case 1:
            createFile(inputFile);
            break;
        case 2:
            viewFile(inputFile);
            break;
        case 3: {
            int course;
            char letter;
            cout << "������� ����: ";
            cin >> course;
            cout << "������� ������ ����� ���: ";
            cin >> letter;

            filterStudents(inputFile, outputFile, course, letter);

            cout << "\n���������� ���������������� �����:\n";
            viewFile(outputFile);
            break;
        }
        default:
            cout << "����� �� ���������.\n";
        }
    } while (ch >= 1 && ch <= 3);

    return 0;
}
