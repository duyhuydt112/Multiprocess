#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

int main(){
    key_t key = ftok("NHA", 29);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    int* Value = (int*)shmat(shmid, (void*)0, 0);

    Value[2] = Value[2] + 10;
    
    // detach from shared memory
    shmdt(Value);
    
    return 0;
}