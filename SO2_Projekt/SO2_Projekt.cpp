#pragma once
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include "Student.h"
#include "Table.h"

using namespace std;
bool running = true;
int maxQueueSize = 8;
int tableSize = 4;
int manIndex = 0;
int womanIndex = 0;

vector<Student*> men, women;
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
        cout << "Studenci:";
        for (int i = 0; i < men.size(); i++)
        {
            if (!men.at(i)->tableAssigned)
                cout << "y, ";
        }
        //cout << endl << "Current size:" << men.size() << endl << endl;
        cout << endl << endl;
        cout << "Stoliki:"<< endl;
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
        cout << "Studentki:";
        for (int i = 0; i < women.size(); i++)
        {
            if (!women.at(i)->tableAssigned)
                cout << "x, ";
        }
       // cout << endl << "Current size:" << women.size() << endl;

        cout << "\n\nNacisnij ENTER, aby zakonczyc..";
       // this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

// Generate students.
void generateMenIndexes() {
    while (running) {
        if (men.size() < maxQueueSize) {
            _myMutex.lock();
            Student *student = new Student(manIndex, false, &running, tables, &_myMutex);
            men.push_back(student);
            student->startThread();
            ++manIndex;
            _myMutex.unlock();
        }
        this_thread::sleep_for(std::chrono::milliseconds(rand()%500 + 1000));
    }
}

void generateWomenIndexes() {
    while (running) {
        if (women.size() < maxQueueSize) {
            _myMutex.lock();
            Student* student = new Student(manIndex, true, &running, tables, &_myMutex);
            women.push_back(student);
            student->startThread();
            ++womanIndex;
            _myMutex.unlock();
        }
        this_thread::sleep_for(std::chrono::milliseconds(rand()%1500 + 1000));
    }
}

// Execute once.
void generateTables() {
    tables = new vector<Table>();
    for (int i = 0; i < tableSize; ++i) {
        tables->push_back(Table(i));
    }
}

void threadManager() {
    while (running) {
        for (int i = 0; i < women.size(); ++i) {
            std::lock_guard<std::mutex> lock(_myMutex);
            if (women.at(i)->dateFinshed) {
                women.at(i)->thread->join();
                women.erase(women.begin() + i);
            }
        }

        for (int i = 0; i < men.size(); ++i) {
            std::lock_guard<std::mutex> lock(_myMutex);
            if (men.at(i)->dateFinshed) {
                men.at(i)->thread->join();
                men.erase(men.begin() + i);
            }
        }
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
    thread manager(threadManager);




    //all threads join here
    drawer.join();
    finisher.join();
    menGenerator.join();
    womenGenerator.join();
    manager.join();

    cout << "Leaving...";

}