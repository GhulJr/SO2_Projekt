#pragma once
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include "Student.h"
#include "Table.h"

using namespace std;
bool running = true;
int maxQueueSize = 10;
int tableSize = 7;

vector<Student> men, women;
vector<Table>* tables;

std::mutex _myMutex;

void getInput() {
    getchar();
    running = false;
}

void refreshScreen()
{
    while (running) {
        system("cls");
        for (int i = 0; i < men.size(); i++)
        {
            cout << "y, ";
        }
        cout << endl << "Current size:" << men.size() << endl << endl;

        for (int i = 0; i < tables->size(); i++)
        {

           // _myMutex.lock();
            char y = tables->at(i).isManSpotFree() ? '.' : 'y';
            char x = tables->at(i).isWomanSpotFree() ? '.' : 'x';
          //  _myMutex.unlock();
            cout << "|"<<y<<" "<<x<<"| ";

            if ((i + 1) % 4 == 0) {
                cout << endl;
            }
        }
        cout << endl << endl;

        for (int i = 0; i < women.size(); i++)
        {
            cout << "x, ";
        }
        cout << endl << "Current size:" << women.size() << endl;

        cout << "\n\nNacisnij ENTER, aby zakonczyc..";
       // this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

// Generate students.
void generateMenIndexes() {
    while (running) {
       // _myMutex.lock();
        if (men.size() < maxQueueSize) {
            Student student(false, &running, tables, &_myMutex);
            men.push_back(student);
            student.startThread();
        }
        //_myMutex.unlock();
        this_thread::sleep_for(std::chrono::milliseconds(rand()%2000 + 1000));
    }
}

void generateWomenIndexes() {
    while (running) {
        //_myMutex.lock();
        if (women.size() < maxQueueSize) {
            Student student(true, &running, tables, &_myMutex);
            women.push_back(student);
            student.startThread();
        }
        //_myMutex.unlock();
        this_thread::sleep_for(std::chrono::milliseconds(rand()%4000 + 1000));
    }
}

// Execute once.
void generateTables() {
    tables = new vector<Table>();
    for (int i = 0; i < tableSize; ++i) {
        tables->push_back(Table(i));
    }
}

int main()
{
    // Init tables.
    generateTables();

    // Init threads.
    cout << "Spawning 3 threads...\n";
    thread drawer(refreshScreen);
    thread finisher(getInput);

    thread menGenerator(generateMenIndexes);
    thread womenGenerator(generateWomenIndexes);


    //all threads join here
    drawer.join();
    finisher.join();
    menGenerator.join();
    womenGenerator.join();

    cout << "Leaving...";

}