#include <unistd.h>

#include <iostream>
#include <thread>

using namespace std;

void worker() {
    // worker thread
    cout << "worker() starting\n";
    sleep(5);
    cout << "worker() shutting down\n";
}

int main() {
    // test threading
    cout << "main() starting\n";
    thread t(worker);
    cout << "main() can do other work here\n";
    // ...
    cout << "main() waiting for worker() to exit\n";
    t.join();
    cout << "main() shutting down\n";
    return 0;
}