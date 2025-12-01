#include <iostream>
#include <thread>
#include <cstdlib>   // for atoi

using namespace std;

// Function executed by the thread
void computeSum(long long n) {
    long long sum = 0;
    for (long long i = 1; i <= n; i++) {
        sum += i;
    }
    cout << "Sum of first " << n << " natural numbers = " << sum << endl;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <N>" << endl;
        return 1;
    }

    long long n = atoll(argv[1]);

    if (n < 0) {
        cerr << "N must be a non-negative integer." << endl;
        return 1;
    }

    // Create a thread and assign the computeSum function to it
    thread worker(computeSum, n);

    // Wait for the thread to finish
    worker.join();

    return 0;
}
