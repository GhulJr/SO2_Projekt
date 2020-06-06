#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include "Student.cpp"
#include "Table.cpp"

using namespace std;
bool running = true;
int maxQueueSize = 10;
int tableSize = 7;

vector<Student> men, women;
vector<Table>* tables;

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
            cout << "|. .| ";
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
        this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

// Generate students.
void generateMenIndexes() {
    while (running) {
        if (men.size() < maxQueueSize) {
            men.push_back(Student(true, *tables));
        }
        this_thread::sleep_for(std::chrono::milliseconds(rand()%2000 + 1000));
    }
}

void generateWomenIndexes() {
    while (running) {
        if (women.size() < maxQueueSize) {
            women.push_back(Student(false, *tables));
        }
        this_thread::sleep_for(std::chrono::milliseconds(rand()%2000 + 1000));
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