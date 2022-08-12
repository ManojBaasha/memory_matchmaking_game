#include <iostream>
using namespace std;
#include <chrono>
#include <thread>

//Example code to show how to use time library

int main()
{
    system("CLS");
    int n;
    cout << "Secret Board" << endl;
    std::chrono::seconds dura(1);
    std::this_thread::sleep_for( dura );
    system("CLS");

    cin >> n;
    cout << n << flush;

    cout << "Secret Board" << flush;
    std::this_thread::sleep_for( dura );
    
    system("CLS");
    cout << "Good-Bye" << endl;
}