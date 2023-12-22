# Threads

A simple demonstration of multithreading in C++

- `thread.cpp`: create, start, and join on a single thread
- `wait.cpp`: create and start a worker thread, simulate work being done, then send a shutdown message

## Compile

The Makefile has recipes to build the thread and wait programs

```
# build
$ make thread
$ make wait
# OR
$ make all

# clean
$ make clean
```

## Run the thread example

In the terminal, run the thread executable

```
$ ./thread
```

The main thread will start and spawn the worker thread

```
$ ./thread
main() starting
```

Before `join()` is called, the main thread can do work at the same time as the worker thread

```
$ ./thread
main() starting
main() can do other work here
worker() starting
```

Once `join()` is called on the worker thread, the main thread stops execution and waits for the worker thread to exit

```
$ ./thread
main() starting
main() can do other work here
worker() starting
main() waiting for worker() to exit
worker() shutting down
main() shutting down
```

## Run the wait example

In the terminal, run the wait executable

```
$ ./thread
```

Once again, he main thread will start and spawn the worker thread

```
$ ./wait
main() starting
worker() starting
```

The worker thread will work until a shutdown signal is received

```
$ ./wait
main() starting
worker() starting
working
working
working
working
```

Once the main thread sets gobal variable `shutdown` to true, the worker thread exits

```
$ ./wait
main() starting
worker() starting
working
working
working
working
wait() shutting down
main() shutting down
```
