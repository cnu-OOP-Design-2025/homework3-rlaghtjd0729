//main.cpp
#include <iostream>
#include <algorithm>
#include <cstdlib> 
#include <iomanip>
#include <cmath> // float 값을 정수와 비교하기 위해 추가
#include "homework3.h"

using namespace std;

StudentStruct *students = nullptr;
int numOfStudent = 0;

void printStudentList(){
   int idx = 0;

   for(idx = 0; idx < numOfStudent; ++idx){
        float midterm = students[idx].record.midterm;
        float final = students[idx].record.final;
        float total = midterm + final;
        
        // C++의 float 비교 문제 때문에 floor()를 사용하여 정수부만 비교합니다.
        
        // 1. ID와 Name 출력
        std::cout << "ID: " << students[idx].id 
                  << ",\t Name: " << students[idx].name; 
        
        // 2. Midterm 출력: 정수일 경우 .0 생략, 소수점일 경우 1자리 출력
        std::cout << ",\t Midterm: ";
        if (midterm == floor(midterm)) {
            std::cout << (int)midterm; // 정수 출력 (예: 91)
        } else {
            std::cout << std::fixed << std::setprecision(1) << midterm; // 소수점 출력 (예: 90.7)
        }
        
        // 3. Final 출력: 정수일 경우 .0 생략, 소수점일 경우 1자리 출력
        std::cout << ",\t Final: ";
        if (final == floor(final)) {
            std::cout << (int)final; // 정수 출력 (예: 91)
        } else {
            std::cout << std::fixed << std::setprecision(1) << final; // 소수점 출력 (예: 91.3)
        }
        
        // 4. Total 출력: 정수일 경우 .0 생략, 소수점일 경우 1자리 출력
        std::cout << ",\t Total: ";
        if (total == floor(total)) {
            std::cout << (int)total; // 정수 출력 (예: 157)
        } else {
            std::cout << std::fixed << std::setprecision(1) << total; // 소수점 출력 (예: 181.7)
        }
        
        std::cout << std::endl;
        
        // 모든 출력 설정 초기화 (다음 반복에 영향 없도록)
        std::cout.unsetf(std::ios_base::floatfield);
        std::cout << std::setprecision(6);
   }
   
   cout << "---------------------------" << endl;
}


struct SortByID{
    bool operator()(const StudentStruct& a, const StudentStruct& b) const{
        return a.id < b.id;
    }
};


struct SortByName{
    bool operator()(const StudentStruct& a, const StudentStruct& b) const{
        return a.name < b.name;
    }
};

struct SortByMidterm{
    // 내림차순 정렬
    bool operator()(const StudentStruct& a, const StudentStruct& b) const{
        return a.record.midterm > b.record.midterm;
    }
};

struct SortByFinal{
    // 내림차순 정렬
    bool operator()(const StudentStruct& a, const StudentStruct& b) const{
        return a.record.final > b.record.final;
    }
};

struct SortByTotal{
    // 내림차순 정렬
    bool operator()(const StudentStruct& a, const StudentStruct& b) const{
        return (a.record.midterm + a.record.final) > (b.record.midterm + b.record.final);
    }
};


void doTest1(){
    cout << "---------------------------" << endl;
    cout << "Test 1" << endl;

    printStudentList();

    cout << "Sort by ID" << endl;
    std::sort(students, students + numOfStudent, SortByID{});
    printStudentList();

    cout << "Sort by Name" << endl;
    std::sort(students, students + numOfStudent, SortByName{});
    printStudentList();

    cout << "Sort by Midterm" << endl;
    std::sort(students, students + numOfStudent, SortByMidterm{});
    printStudentList();

    cout << "Sort by Final" << endl;
    std::sort(students, students + numOfStudent, SortByFinal{});
    printStudentList();

    cout << " Sort by Total" << endl;
    std::sort(students, students + numOfStudent, SortByTotal{});
    printStudentList();
}


void doTest2(){
    cout << "---------------------------" << endl;
    cout << "Test 2" << endl;

    cout << "Sort by ID" << endl;
    auto sortByID = [](const StudentStruct &a, const StudentStruct &b) -> bool {
        return a.id < b.id;
    };
    std::sort(students, students + numOfStudent, sortByID);
    printStudentList();

    cout << "Sort by Name" << endl;
    auto sortByName = [](const StudentStruct &a, const StudentStruct &b) -> bool {
        return a.name < b.name;
    };
    std::sort(students, students + numOfStudent, sortByName);
    printStudentList();

    cout << "Sort by Midterm" << endl;
    auto sortByMidterm = [](const StudentStruct &a, const StudentStruct &b) -> bool {
        return a.record.midterm > b.record.midterm;
    };
    std::sort(students, students + numOfStudent, sortByMidterm);
    printStudentList();


    cout << "Sort by Final" << endl;
    auto sortByFinal = [](const StudentStruct &a, const StudentStruct &b) -> bool {
        return a.record.final > b.record.final;
    };
    std::sort(students, students + numOfStudent, sortByFinal);
    printStudentList();

    cout << " Sort by Total" << endl;
    auto sortByTotal = [](const StudentStruct &a, const StudentStruct &b) -> bool {
        // [BUG FIX]: b.record.final이 아니라 b.record.midterm + b.record.final로 수정되었습니다.
        return (a.record.midterm + a.record.final) > (b.record.midterm + b.record.final);
    };
    std::sort(students, students + numOfStudent, sortByTotal);
    printStudentList();

}

int main(int argc, char **argv) {
    const int MAX_STUDENTS = 100;
    students = new StudentStruct[MAX_STUDENTS];

    fillStudentRecord(students, numOfStudent);


    if(argc == 2){
        int select = atoi(argv[1]);
        switch(select){
            case 1:
                doTest1();
                delete[] students;
                return 0;
            case 2:
                doTest2();
                delete[] students;
                return 0;
        }
    }

    doTest1();
    doTest2();


    delete[] students;
    return 0;
}