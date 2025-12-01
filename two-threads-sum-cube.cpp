#include <iostream>
#include <thread>
using namespace std;

// Function to compute sum of first n natural numbers
void computeSum(int n) {
    long long sum = (long long)n * (n + 1) / 2;
    cout << "Sum of first " << n << " natural numbers = " << sum << endl;
}

// Function to compute cube of a number
void computeCube(int x) {
    long long cube = 1LL * x * x * x;
    cout << "Cube of " << x << " = " << cube << endl;
}

int main() {
    int n1, n2;

    cout << "Enter a number for sum calculation: ";
    cin >> n1;

    cout << "Enter a number for cube calculation: ";
    cin >> n2;

    // Create two threads
    thread t1(computeSum, n1);
    thread t2(computeCube, n2);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    cout << "Both threads have finished execution." << endl;

    return 0;
}
