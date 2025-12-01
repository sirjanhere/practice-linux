#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>

using namespace std;

mutex coutMutex;  // to synchronize console output

void printTable(int num) {
    lock_guard<mutex> lock(coutMutex);  // lock for the whole block

    cout << "----------------------------------------\n";
    cout << "Multiplication Table of " << num << ":\n";
    cout << "----------------------------------------\n";

    for (int i = 1; i <= 10; i++) {
        cout << num << " x " << i << " = " << num * i << endl;
    }

    cout << "----------------------------------------\n\n";
}

void sumOfCubes(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += 1LL * i * i * i;
    }

    lock_guard<mutex> lock(coutMutex);  // lock before printing

    cout << "----------------------------------------\n";
    cout << "Sum of cubes calculation:\n";
    cout << "First " << n << " natural numbers.\n";
    cout << "Sum of cubes = " << sum << endl;
    cout << "----------------------------------------\n\n";
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <number_for_table> <n_for_sum_of_cubes>\n";
        return 1;
    }

    int tableNum = atoi(argv[1]);
    int n = atoi(argv[2]);

    cout << "Creating threads...\n\n";

    thread t1(printTable, tableNum);
    thread t2(sumOfCubes, n);

    t1.join();
    t2.join();

    cout << "Both threads completed.\n";

    return 0;
}
