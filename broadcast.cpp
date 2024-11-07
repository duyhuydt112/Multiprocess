#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include    <mutex>

using namespace std;

pthread_mutex_t mutexFuel, Name;
pthread_cond_t condFuel;
int fuel = 0, i=1;

void* fuel_filling(void* arg) {
   
   
    for (int i = 0; i < 6; i++) {
        pthread_mutex_lock(&mutexFuel);
        fuel += 60;
        cout <<"Station Get Fuel: " << fuel << endl;
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_broadcast(&condFuel);
        usleep(300000);
    }
    return NULL;
}

void* car(void* arg) { 

    pthread_mutex_lock(&Name);
    char threadName[16];
    char tName[16];
    sprintf(threadName, "Car-%d", i++); // use to cat string
    pthread_setname_np(pthread_self(), threadName); 
    pthread_getname_np(pthread_self(), tName, sizeof(tName));
    pthread_mutex_unlock(&Name);

    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40) {
        printf("No fuel. Waiting...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;
    cout << tName << " Got fuel. Now left: " << fuel << endl;
    pthread_mutex_unlock(&mutexFuel);
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t th[6];
    pthread_mutex_init(&mutexFuel, NULL);
     pthread_mutex_init(&Name, NULL);
    pthread_cond_init(&condFuel, NULL);
    for (int i = 0; i < 6; i++) {
        if (i == 4 || i == 5) {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    pthread_mutex_destroy(&Name);
    return 0;
}