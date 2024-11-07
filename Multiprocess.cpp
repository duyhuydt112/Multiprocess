#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h> 
#include <sys/wait.h>   // Để sử dụng wait()
#include <thread>
#include <chrono>
#include <mutex>
using namespace std; 

mutex mtx;

void Thread_Function(int index, int* &value){

    while(1){
        std::lock_guard<std::mutex> lock(mtx);
        value[0] += 2; 
        cout << "Dad Thread " << index << " ("<< getpid() << "): " << value[0] << endl;
        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Clarifition(int mode){
    key_t key = ftok("NHA", 29);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    int* Value = (int*)shmat(shmid, (void*)0, 0);
    if(mode == 1){
        Value[0] = 10;
        cout << "Initial: " << Value[0] << endl; 
        thread Plus1(Thread_Function, 0, ref(Value));
        thread Plus2(Thread_Function, 1, ref(Value));
        thread Plus3(Thread_Function, 2, ref(Value));
        thread Plus4(Thread_Function, 3, ref(Value));
        Plus1.join();
        Plus2.join();
        Plus3.join();
        Plus4.join();
        shmdt(Value);
        shmctl(shmid, IPC_RMID, NULL);

    }
    else{
        while(1){
            // Value[0] += 10;
            cout << "Child ("<< getpid() << "): " <<Value[0] << endl; 
            sleep(1);
        }
        shmdt(Value);
    }
}



int main() 
{ 
    pid_t c_pid = fork(); 

    if (c_pid == -1) { 
        perror("fork"); 
        exit(EXIT_FAILURE); 
    } 
    else if (c_pid > 0) { 
        Clarifition(1);
        // wait(nullptr); // Chờ process con hoàn thành
        cout << "printed from child process " << getpid() << endl; 
    } 
    else { 
        Clarifition(2);
        cout << "printed from child process " << getpid() << endl; 
    } 

    return 0; 
}
