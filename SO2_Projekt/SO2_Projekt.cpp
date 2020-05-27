#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include "Student.cpp"
#include "Table.cpp"

using namespace std;
bool running = true;
int maxQueueSize = 10;

vector<Student> men, tables, women;

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

        for (int i = 0; i < tables.size(); i++)
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
void generateIndexes() {
    while (running) {
        if (men.size() < maxQueueSize) {
            men.push_back(Student(true));
        }
        if (women.size() < maxQueueSize) {
            women.push_back(Student(false));
        }
    }
}

int main()
{
    cout << "Spawning 3 threads...\n";
    thread t1(refreshScreen);
    thread t2(getInput);
    //thread finisher();
    thread generator(generateIndexes);
    //all threads join here
    t1.join();
    t2.join();
    generator.join();

    cout << "Leaving...";
}