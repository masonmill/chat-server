#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

void worker() {
    // worker thread
    cout << "worker() starting\n";
    chrono::seconds timespan(5);
    this_thread::sleep_for(timespan);
    cout << "worker() shutting down\n";
}

int main() {
    // test threading
    cout << "main() starting\n";
    thread t(worker);
    cout << "main() can do other work here\n";
    chrono::seconds timespan(2);
    this_thread::sleep_for(timespan);
    // ...
    cout << "main() waiting for worker() to exit\n";
    t.join();
    cout << "main() shutting down\n";
    return 0;
}