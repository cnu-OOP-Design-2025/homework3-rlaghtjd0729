//main.cpp
#include <iostream>
#include <algorithm>
#include <cstdlib> 
#include <iomanip>
#include "homework3.h"

using namespace std;

StudentStruct *students = nullptr;
int numOfStudent = 0;

void printStudentList(){
   int idx = 0;

   // ******************************************************
   // 수정된 부분: std::fixed를 제거하고 std::setprecision(1)만 유지
   // 이렇게 하면 정수 값 뒤에 강제로 .0이 붙는 것을 방지할 수 있습니다.
   // ******************************************************
   std::cout << std::setprecision(1); 

   for(idx = 0; idx < numOfStudent; ++idx){
        std::cout << "ID: " << students[idx].id 
                  << ",\t Name: " << students[idx].name
                  << ",\t Midterm: " << students[idx].record.midterm 
                  << ",\t Final: " << students[idx].record.final
                  << ",\t Total: " << students[idx].record.midterm + students[idx].record.final << std::endl;
   }
   
   // 출력 상태를 복원
   std::cout.unsetf(std::ios_base::floatfield); // fixed가 없으니 setprecision만 복원
   std::cout << std::setprecision(6); 
   
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
    // 내림차순 정렬: a > b 일 때 true
    bool operator()(const StudentStruct& a, const StudentStruct& b) const{
        return a.record.midterm > b.record.midterm;
    }
};

struct SortByFinal{
    // 내림차순 정렬: a > b 일 때 true
    bool operator()(const StudentStruct& a, const StudentStruct& b) const{
        return a.record.final > b.record.final;
    }
};

struct SortByTotal{
    // 내림차순 정렬: a > b 일 때 true
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
        // 이 부분은 이미 이전 질문에서 b.record.final이 아닌 b.record.midterm + b.record.final로 수정해야 할 로직이 포함되어 있습니다.
        // 현재 코드는 이전 답변에서 수정되었던 Total 비교 로직을 유지합니다.
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