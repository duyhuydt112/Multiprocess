#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

int main(){
    key_t key = ftok("NHA", 29);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    int* Value = (int*)shmat(shmid, (void*)0, 0);
     for (int i = 1; i < 10; i++) {
        Value[i] = i * 10;  // Ghi số nguyên vào mảng
    }

    cout << "Data written in memory: " << Value[2] << endl;

    while(Value[2] == 20){
       
    }
    cout << "Data written in memory: " << Value[2] << endl;
    shmdt(Value);
    shmctl(shmid, IPC_RMID, NULL);
    // detach from shared memory
    
    return 0;
}