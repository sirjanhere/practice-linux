#include <iostream>
#include <thread>
#include <cstdlib>   // For atoi

using namespace std;

// Function to calculate sum of squares of first n natural numbers
void sumOfSquares(int n) {
    long long sum = 0;

    for (int i = 1; i <= n; i++) {
        sum += 1LL * i * i;
    }

    cout << "Sum of squares of first " << n << " natural numbers = " << sum << endl;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <n>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        cerr << "Please enter a positive integer." << endl;
        return 1;
    }

    cout << "Creating thread to compute sum of squares..." << endl;

    // Create a thread and pass n to the function
    thread t(sumOfSquares, n);

    // Wait for thread to finish
    t.join();

    cout << "Thread execution complete." << endl;

    return 0;
}
