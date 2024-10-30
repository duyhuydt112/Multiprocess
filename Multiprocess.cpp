#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h> 
#include <sys/wait.h>   // Để sử dụng wait()
using namespace std; 

void Clarifition(int mode){
    key_t key = ftok("NHA", 29);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    int* Value = (int*)shmat(shmid, (void*)0, 0);
    if(mode == 1){
        Value[0] = 10;
        cout << "Initial: " << Value[0] << endl; 
        while(1){
            cout << "Dad: " << Value[0] << endl; 
            // sleep(1);
        }
        
        // shmdt(Value);
        // shmctl(shmid, IPC_RMID, NULL);

    }
    else{
        
        while(1){
            Value[0] += 10;
            cout << "Child: " << Value[0] << endl; 
            // sleep(1);
        }

        // shmdt(Value);
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
