#include <pthread.h>
#include <iostream>
#include <thread>
using namespace std;

pthread_mutex_t mutex;
int value;
void* Funtion(void* hello){
 char thread_name[16];
    snprintf(thread_name, sizeof(thread_name), "Bao_Cu %ld", pthread_self()); // Tạo tên cho luồng dựa trên ID của nó
    pthread_setname_np(pthread_self(), thread_name); // Đặt tên cho luồng
    for(int i = 0; i < 100000000; i++){
        pthread_mutex_lock(&mutex);
        value++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* Return_Valuable(void *hello){
    int x;
    
    return  
}

int main(){
    int return_value;
    pthread_mutex_init(&mutex, NULL);
    pthread_t Thread[6];
    pthread_t Return_value;
    pthread_create(&Return_value, NULL, )
    for(int i = 0; i < 6; i++){
        if(pthread_create(Thread + i, NULL, Funtion, NULL) != 0){
            perror("Failed to create thread");
            return 1;
        }
    }
    
    for(int i = 0; i < 6; i++){
        if(pthread_join(Thread[i], NULL) != 0){
            perror("Failed to join thread");
            return 1;
        }


    }
    pthread_join(&Return_value, )
    cout << value << endl;
    // while(1);
    pthread_mutex_destroy(&mutex);
}