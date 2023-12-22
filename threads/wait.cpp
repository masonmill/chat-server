#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

static bool shutdown = false;

void worker() {
    // wait for shutdown signal with sleep in between
    cout << "worker() starting\n";
    chrono::milliseconds timespan(500);
    while (!shutdown) {
        cout << "working\n";
        this_thread::sleep_for(timespan);  // avoids busy-waiting
    }
    cout << "wait() shutting down\n";
}

int main() {
    // main() thread which spawns a second wait() thread
    cout << "main() starting\n";
    thread t(worker);
    chrono::seconds timespan(2);
    this_thread::sleep_for(timespan);  // this gives up execution to the worker thread
    // the shutdown variable will be set to true in approximately 2 seconds
    shutdown = true;
    t.join();
    cout << "main() shutting down\n";
    return 0;
}