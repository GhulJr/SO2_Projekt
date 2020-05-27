#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;
bool running = true;

vector<int> men = { 1,1,2 };
vector<int> tables = { 1,1,1,1,1,1,1,1,1,1 };
vector<int> women = { 1,1,1,1 };

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

int main()
{
    std::cout << "Spawning 3 threads...\n";
    std::thread t1(refreshScreen);
    std::thread t2(getInput);

    //all threads join here
    t1.join();
    t2.join();

    cout << "Leaving...";
}