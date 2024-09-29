# Vxworks_semaphore

## VxWorks Task Synchronization with Semaphores

This VxWorks project demonstrates the use of a binary semaphore to synchronize access to a critical section of code between two tasks. 

### Project Structure

- **main.c:** Contains the main program logic, including task definitions, semaphore creation, and task spawning.

### Functionality

The project consists of three functions:

1. **start()**: This function is responsible for spawning two tasks: `task1` and `task2`. 

2. **task1()**: 
    - Creates a binary semaphore `semMutex` with priority queuing enabled. The semaphore is initialized to the full state (`SEM_FULL`).
    - Acquires the semaphore using `semTake(semMutex, WAIT_FOREVER)`. This blocks task2 from entering the critical section until `task1` releases the semaphore.
    - Enters the critical section and simulates work with a delay.
    - Prints the status of both tasks within the critical section using `taskStatusString()`.
    - Releases the semaphore using `semGive(semMutex)`, allowing other tasks waiting on the semaphore to acquire it.

3. **task2()**: 
    - Attempts to acquire the semaphore using `semTake(semMutex, WAIT_FOREVER)`. This blocks `task2` until `task1` releases the semaphore.
    - Once acquired, `task2` enters the critical section.
    - Prints its status to demonstrate that it has acquired the semaphore after `task1` released it.
    - Releases the semaphore using `semGive(semMutex)`.

### How it Works

The binary semaphore acts as a lock, ensuring that only one task can access the critical section at a time. 

1. `task1` acquires the semaphore, entering the critical section.
2. `task2` attempts to acquire the semaphore but is blocked as `task1` holds it.
3. `task1` completes its work in the critical section and releases the semaphore.
4. `task2` is unblocked, acquires the semaphore, and enters the critical section.

This ensures that the critical section is accessed sequentially, preventing race conditions and data corruption.

<p align="center">
  <img src="https://github.com/user-attachments/assets/f9b43e3a-1c73-40c7-b1de-810981098408" alt="Image">
</p>


### Building and Running the Project

1. This code is intended to be run within a VxWorks environment.
2. Include the necessary header files and libraries.
3. Compile and link the code using a VxWorks cross-compiler.
4. Download and run the executable on a VxWorks target.

### Notes

- This code uses the VxWorks task library (`taskLib.h`) and semaphore library (`semLib.h`). 
- The `taskDelay()` function introduces a delay to simulate work within the critical section.
- The `taskStatusString()` function retrieves the status of a task.

This project demonstrates a fundamental concept of real-time operating systems: using semaphores for synchronization. Understanding this concept is crucial for developing robust and reliable multi-threaded applications in VxWorks.
content_copy
Use code with caution.
