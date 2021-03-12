#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;
const int maxCntOfStudents = 1000;
struct Student {
	string name, lastName, patronymic;
	string educationalForm;
	char gender;
	int groupNumber, numberInGroup;
	float grades[8];
	string day, month;
	int date, year, seconds, minute, hour;
	bool record;
	float middleMark;
	Student() {
		record = false;
	}
};
void writeToFile(Student* mas) {
	ofstream fout("students.txt");
	int posNow = 0;
	while (mas[posNow].record != false) {
		fout << mas[posNow].lastName << ' ' << mas[posNow].name << ' ' << mas[posNow].patronymic << endl << mas[posNow].gender << endl <<
			mas[posNow].groupNumber << ' ' << mas[posNow].numberInGroup << endl;
		for (int i = 0; i < 8; i++)
			fout << mas[posNow].grades[i] << ' ';
		fout << endl << mas[posNow].educationalForm << endl;
		fout << mas[posNow].day << ' ' << mas[posNow].month << ' ' << mas[posNow].date << ' ';
		if (mas[posNow].hour < 10)
			fout << 0;
		fout << mas[posNow].hour << ':';
		if (mas[posNow].minute < 10)
			fout << 0;
		fout << mas[posNow].minute << ':';
		if (mas[posNow].seconds < 10)
			fout << 0;
		fout << mas[posNow].seconds << ' ';
		fout << mas[posNow].year;
		fout << endl;
		posNow++;
	}
	fout.close();
}
void bubleSort(Student* mas) {
	int len = 0;
	while (mas[len].record != false)
		len++;
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - i - 1; j++) {
			if (mas[j].middleMark > mas[j + 1].middleMark) {
				Student q = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = q;
			}
		}
	}
}
void newEntry(Student* mas) {
	int posToAdd = 0;
	while (mas[posToAdd].record != false)
		posToAdd++;
	cout << "Please, enter last name, first name, "
		"patronymic, gender, group number, "
		"number in the group list, grades"
		"for the last session "
		"(total 3 exams and 5 differentiated credits), "
		"form of study, time stamp on entering or changing data "
		"(in the following form: Sat Feb 10 12:05:12 2020)\n";
	cin >> mas[posToAdd].lastName >> mas[posToAdd].name >> mas[posToAdd].patronymic >>
		mas[posToAdd].groupNumber >> mas[posToAdd].numberInGroup >> mas[posToAdd].gender;
	cin >> mas[posToAdd].educationalForm;
	float sum = 0;
	for (int i = 0; i < 8; i++) {
		cin >> mas[posToAdd].grades[i];
		sum += mas[posToAdd].grades[i];
	}
	mas[posToAdd].middleMark = sum / 8.0;
	cin >> mas[posToAdd].day >> mas[posToAdd].month >> mas[posToAdd].date;
	scanf("%d:%d:%d", &mas[posToAdd].hour, &mas[posToAdd].minute, &mas[posToAdd].seconds);
	cin >> mas[posToAdd].year;
	mas[posToAdd].record = true;
	writeToFile(mas);
}
void studentToTheScreen(Student* mas, int posNow) {
	cout << mas[posNow].lastName << ' ' << mas[posNow].name << ' ' << mas[posNow].patronymic << endl << mas[posNow].gender << endl <<
		mas[posNow].groupNumber << ' ' << mas[posNow].numberInGroup << endl;
	for (int i = 0; i < 8; i++)
		cout << mas[posNow].grades[i] << ' ';
	cout << endl << mas[posNow].educationalForm << endl;
	cout << mas[posNow].day << ' ' << mas[posNow].month << ' ' << mas[posNow].date << ' ';
	if (mas[posNow].hour < 10)
		cout << 0;
	cout << mas[posNow].hour << ':';
	if (mas[posNow].minute < 10)
		cout << 0;
	cout << mas[posNow].minute << ':';
	if (mas[posNow].seconds < 10)
		cout << 0;
	cout << mas[posNow].seconds << ' ';
	cout << mas[posNow].year;
	cout << endl;
}
void allStudentsToTheScreen(Student* mas) {
	int posNow = 0;
	while (mas[posNow].record != false) {
		studentToTheScreen(mas, posNow);
		posNow++;
	}
}
void changeRecord(Student* mas) {
	int posToEdit;
	cout << "enter the number of the record to edit (ENTRIES ARE NUMBERED FROM 0, to find out the number in the list, run the command 3)\n";
	cout << "Run the command 3? Y/N\n";
	char command;
	cin >> command;
	if (command == 'Y')
		allStudentsToTheScreen(mas);
	cout << "\nenter the number of the record to edit";
	cin >> posToEdit;
	cout << "Please,enter new information about: last name, first name, "
		"patronymic, gender, group number, "
		"number in the group list, grades"
		"for the last session "
		"(total 3 exams and 5 differentiated credits), "
		"form of study, time stamp on entering or changing data "
		"(in the following form: Sat Feb 10 12:05:12 2020)\n";
	cin >> mas[posToEdit].lastName >> mas[posToEdit].name >> mas[posToEdit].patronymic >>
		mas[posToEdit].groupNumber >> mas[posToEdit].numberInGroup >> mas[posToEdit].gender;
	cin >> mas[posToEdit].educationalForm;
	float sum = 0;
	for (int i = 0; i < 8; i++) {
		cin >> mas[posToEdit].grades[i];
		sum += mas[posToEdit].grades[i];
	}
	mas[posToEdit].middleMark = sum / 8.0;
	cin >> mas[posToEdit].day >> mas[posToEdit].month >> mas[posToEdit].date;
	scanf("%d:%d:%d", &mas[posToEdit].hour, &mas[posToEdit].minute, &mas[posToEdit].seconds);
	cin >> mas[posToEdit].year;
	mas[posToEdit].record = true;
	writeToFile(mas);
}
void studentsOfGroupNumberNToTheScreen(Student* mas) {
	int posNow = 0;
	int n;
	cout << "Enter num of group N";
	cin >> n;
	while (mas[posNow].record != false) {
		if (mas[posNow].groupNumber == n) {
			studentToTheScreen(mas, posNow);
		}
		posNow++;
	}
}
void cntOfMW(Student* mas) {
	int posNow = 0;
	int cntM = 0, cntF = 0;
	while (mas[posNow].record != false) {
		if (mas[posNow].gender == 'F')
			cntF++;
		if (mas[posNow].gender == 'M')
			cntM++;
		posNow++;
	}
	cout << "Man: " << cntM << endl;
	cout << "woman: " << cntF;
}
void topOfStudents(Student* mas) {
	int len = 0;
	while (mas[len].record != false)
		len++;
	bubleSort(mas);
	for (int posNow = 0; posNow < len; posNow++) {
		cout << mas[posNow].lastName << ' ' << mas[posNow].name << ' ' << mas[posNow].patronymic << "\nmiddle Mark: " << mas[posNow].middleMark << endl;
	}
}
void receiveScholarship(Student* mas) {
	int cntOfReceiveScholarship = 0;
	int posNow = 0;
	while (mas[posNow].record != false) {
		bool receive = 1;
		if (mas[posNow].educationalForm == "day") {
			for (int i = 0; i < 8; i++)
				if (mas[posNow].grades[i] < 4)
					receive = 0;
		}
		else
			receive = 0;
		if (receive)
			cntOfReceiveScholarship++;
		posNow++;
	}
	cout << "Count = " << cntOfReceiveScholarship;
}
void distributionByEstimate(Student* mas) {
	int posNow = 0;
	int unsurprisingly[maxCntOfStudents] = { 0 };
	int good[maxCntOfStudents] = { 0 };
	int excellent[maxCntOfStudents] = { 0 };
	int unsurprisinglyCnt = 0;
	int goodCnt = 0;
	int excellentCnt = 0;
	while (mas[posNow].record == 1) {
		bool twoOrThree = 0;
		bool four = 0;
		bool five = 0;
		for (int i = 0; i < 8; i++) {
			if (mas[posNow].grades[i] < 4)
				twoOrThree = 1;
			if (mas[posNow].grades[i] == 4)
				four = 1;
			if (mas[posNow].grades[i] == 5)
				five = 1;
		}
		if (twoOrThree) {
			unsurprisingly[unsurprisinglyCnt] = posNow;
			unsurprisinglyCnt++;
		}
		else if (four) {
			good[goodCnt] = posNow;
			goodCnt++;
		}
		else if (five) {
			excellent[excellentCnt] = posNow;
			excellentCnt++;
		}
		posNow++;
	}
	cout << "\nstudents who will not receive a scholarship:\n";
	for (int i = 0; i < unsurprisinglyCnt; i++)
		studentToTheScreen(mas, unsurprisingly[i]);
	cout << "\nstudents who study only for good and  excellent:\n";
	for (int i = 0; i < goodCnt; i++)
		studentToTheScreen(mas, good[i]);
	cout << "\nstudents who only get excellent grades:\n";
	for (int i = 0; i < excellentCnt; i++)
		studentToTheScreen(mas, excellent[i]);
}
void studentsWithNumberKInGroupToTheScreen(Student* mas) {
	cout << "Enter K\n";
	int k;
	cin >> k;
	int posNow = 0;
	while (mas[posNow].record == 1) {
		if (mas[posNow].numberInGroup == k)
			studentToTheScreen(mas, posNow);
		posNow++;
	}
}
void inDateToTheScreen(Student* mas) {
	cout << "enter the day month year\n";
	int d;
	string m;
	int y;
	cin >> d >> m >> y;
	int posNow = 0;
	cout << "entries on this day:\n";
	while (mas[posNow].record == 1) {
		if (mas[posNow].date == d && mas[posNow].month == m && mas[posNow].year == y)
			studentToTheScreen(mas, posNow);
		posNow++;
	}
	posNow = 0;
	cout << "in the afternoon:\n";
	while (mas[posNow].record == 1) {
		if (mas[posNow].hour >= 12)
			studentToTheScreen(mas, posNow);
		posNow++;
	}
	posNow = 0;
	cout << "until noon:\n";
	while (mas[posNow].record == 1) {
		if (mas[posNow].hour < 12)
			studentToTheScreen(mas, posNow);
		posNow++;
	}
}
int main() {
	Student mas[maxCntOfStudents];
	int com = 0;
	cout << "1. Create a new student record.\n"

		"2. Making changes to an existing record.\n"

		"3. Output of all student data.\n"

		"4. Output of information about all students of group N. N - initialized by the user.\n"

		"5. Output of the top most successful students with the highest rated average score for the last session.\n"

		"6. Output the number of male and female students.\n"

		"7. Determining the number of students who will receive a scholarship(the scholarship is awarded if the student does not have triplesand full - time education).\n"

		"8. Output of data on students who do not receive a scholarship; study only on good and excellent; study only on excellent;\n"

		"9. Output data about students who have a number in the list - k.\n"

		"10. Output of all entries made on the day that the user enters.Output of all entries made after noon.Output of all entries made before noon.\n";
	while (com != -1) {
		cout << "\nenter number of command (1...10), or -1 to stop\n";
		cin >> com;
		switch (com) {
		case(1):
			newEntry(mas);
			break;
		case(2):
			changeRecord(mas);
			break;
		case(3):
			allStudentsToTheScreen(mas);
			break;
		case(4):
			studentsOfGroupNumberNToTheScreen(mas);
			break;
		case(5):
			topOfStudents(mas);
			break;
		case(6):
			cntOfMW(mas);
			break;
		case(7):
			receiveScholarship(mas);
			break;
		case(8):
			distributionByEstimate(mas);
			break;
		case(9):
			studentsWithNumberKInGroupToTheScreen(mas);
			break;
		case(10):
			inDateToTheScreen(mas);
			break;
		}
	}
	return 0;
}