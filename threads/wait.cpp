#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

static bool shutdown = false;

void waiting() {
    // wait for shutdown signal with wait in between
    cout << "wait() starting\n";
    chrono::milliseconds timespan(100);
    while (!shutdown) {
        cout << "working\n";
        this_thread::sleep_for(timespan);
    }
    cout << "wait() shutting down\n";
}

int main() {
    // main() thread which spawns a second wait() thread
    cout << "main() starting\n";
    thread t(waiting);
    chrono::seconds timespan(1);
    this_thread::sleep_for(timespan);
    shutdown = true;
    t.join();
    cout << "main() shutting down\n";
    return 0;
}