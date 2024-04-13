#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
using namespace std;

#pragma warning (disable:4996)

int serverCoins = 0;
int clientCoins = 0;

void UpdateTimeInWindowTitle() {
    auto start = chrono::steady_clock::now();
    while (true) {
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        int elapsedMinutes = chrono::duration_cast<chrono::minutes>(diff).count();

        if (elapsedMinutes >= 1) {
            system("cls");
            cout << "SERVER: " << serverCoins << endl;
            cout << "CLIENT: " << clientCoins << endl;
            break;
        }


        int elapsedSeconds = chrono::duration_cast<chrono::seconds>(diff).count() % 60;
        int elapsedMilliseconds = chrono::duration_cast<chrono::milliseconds>(diff).count() % 1000;
        string timeStr = to_string(elapsedMinutes) + ":" + to_string(elapsedSeconds) + ":" + to_string(elapsedMilliseconds);

        SetConsoleTitleA(timeStr.c_str());

        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

int main() {
    setlocale(0, "");

    thread timeThread(UpdateTimeInWindowTitle);

    for (int i = 1; i < 10000; i++) {
        serverCoins++;
        clientCoins++;

        cout << i << "\n";
        this_thread::sleep_for(chrono::microseconds(200));
    }

    timeThread.join();

    return 0;
}


