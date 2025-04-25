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
        cout << "Ошибка создания файла!" << endl;
        return;
    }


    int n;
    cout << "Введите количество студентов: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Student student;
        cout << "Введите данные студента #" << i + 1 << ":\n";
        cout << "ФИО: ";
        cin.ignore();
        cin.getline(student.fio, 100);
        cout << "Возраст: ";
        cin >> student.age;
        cout << "Пол: ";
        cin >> student.gender;
        cout << "Курс: ";
        cin >> student.course;
        cout << "Успеваемость: ";
        cin >> student.rating;

        outfile << student.fio << ";" << student.age << ";" << student.gender << ";"
            << student.course << ";" << student.rating << endl;
    }

    outfile.close();
    cout << "Файл успешно создан.\n";
}


void viewFile(const char* filename) {
    ifstream infile(filename);
    if (!infile) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    cout << "Содержимое файла:\n";
    char line[256];
    while (infile.getline(line, 256)) {
        cout << line << endl;
    }

    infile.close();
}

void filterStudents(const char* inputFile, const char* outputFile, int n, char letter) {
    ifstream infile(inputFile);
    if (!infile) {
        cout << "Ошибка открытия входного файла!" << endl;
        return;
    }

    ofstream outfile(outputFile);
    if (!outfile) {
        cout << "Ошибка создания выходного файла!" << endl;
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
    cout << "Фильтрация завершена. Результаты записаны в файл " << outputFile << ".\n";
}

int main() {
    setlocale(LC_ALL, "rus");
    const char* inputFile = "students.txt";
    const char* outputFile = "filtered_students.txt";

    int ch;
    do {
        cout << "Меню:\n";
        cout << "1. Создать текстовый файл\n";
        cout << "2. Просмотреть текстовый файл\n";
        cout << "3. Перейти к фильтрации\n";
        cout << "Ваш выбор: ";
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
            cout << "Введите курс: ";
            cin >> course;
            cout << "Введите первую букву ФИО: ";
            cin >> letter;

            filterStudents(inputFile, outputFile, course, letter);

            cout << "\nСодержимое отфильтрованного файла:\n";
            viewFile(outputFile);
            break;
        }
        default:
            cout << "Выход из программы.\n";
        }
    } while (ch >= 1 && ch <= 3);

    return 0;
}
