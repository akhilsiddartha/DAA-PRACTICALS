#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;


unsigned long long factorialIterative(int n)
{
    unsigned long long result = 1;
    int i = 1;

    while (i <= n)
    {
        result = result * i;
        i++;
    }

    return result;
}


unsigned long long factorialRecursive(int n)
{
    if (n == 0 || n == 1)
        return 1;

    return n * factorialRecursive(n - 1);
}

int main()
{
    int n;

    cout << "Enter a non-negative integer : ";

    if (!(cin >> n) || n < 0)
    {
        cout << "Invalid input! Please enter a non-negative integer." << endl;
        return 1;
    }

    // Measure Iterative Implementation
    auto startIter = high_resolution_clock::now();
    unsigned long long resIter = factorialIterative(n);
    auto endIter = high_resolution_clock::now();

    duration<double, nano> durationIter = endIter - startIter;

    // Measure Recursive Implementation
    auto startRec = high_resolution_clock::now();
    unsigned long long resRec = factorialRecursive(n);
    auto endRec = high_resolution_clock::now();

    duration<double, nano> durationRec = endRec - startRec;

    // Output Results
    cout << "\n--- Results for " << n << "! ---" << endl;
    cout << "Iterative Result : " << resIter << endl;
    cout << "Iterative Time   : " << durationIter.count() << " ns" << endl;
    cout << "-------------------------------" << endl;
    cout << "Recursive Result : " << resRec << endl;
    cout << "Recursive Time   : " << durationRec.count() << " ns" << endl;

    return 0;
}