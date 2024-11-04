#include <pthread.h>
#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;
 pthread_mutex_t mutex;
int primes[10] = {1,2,3,4,5,6,7,8,9,10};

void* Seperate(void *arg){
    // pthread_mutex_lock(&mutex);
    int index = *(int*)arg;
    cout << "Value: " << primes[index] << endl;
    //  pthread_mutex_unlock(&mutex);
    return NULL;
}


// int value;
// void* Funtion(void* hello){
//  char thread_name[16];
//     snprintf(thread_name, sizeof(thread_name), "Bao_Cu %ld", pthread_self()); // Tạo tên cho luồng dựa trên ID của nó
//     pthread_setname_np(pthread_self(), thread_name); // Đặt tên cho luồng
//     for(int i = 0; i < 100000000; i++){
//         pthread_mutex_lock(&mutex);
//         value++;
//         pthread_mutex_unlock(&mutex);
//     }
//     return NULL;
// }

void* Return_Valuable(void *hello){
    // cout << *(int*)hello << endl;
    // cout << &hello << endl;
    int* x = (int*)malloc(sizeof(int));
    *x = 10;
    cout << x << endl;
    free(hello);
    return (void*)x;
}

int main(){
    int* return_value;
    // pthread_mutex_init(&mutex, NULL);
    pthread_t Thread[6];
    pthread_t Return_value;
    pthread_t Separate_thread[10];
    // int i;
      for(int i = 0; i < 10; i++){
        int* a = (int*)malloc(sizeof(int));
        *a = i;
        if(pthread_create(Separate_thread+i , NULL, Seperate, a) != 0){
            perror("Failed to create thread");
            // return 1;
        }
        
    }
 
    for(int i = 0; i < 10; i++){
        if(pthread_join(Separate_thread[i], NULL) != 0){
            perror("Failed to create thread");
            return 1;
        }
    }
    // pthread_create(&Return_value, NULL, Return_Valuable, NULL);
    // for(int i = 0; i < 6; i++){
    //     if(pthread_create(Thread + i, NULL, Funtion, NULL) != 0){
    //         perror("Failed to create thread");
    //         return 1;
    //     }
    // }
    
    // for(int i = 0; i < 6; i++){
    //     if(pthread_join(Thread[i], NULL) != 0){
    //         perror("Failed to join thread");
    //         return 1;
    //     }


    // }
    // pthread_join(Return_value, (void **)&return_value);
    // cout << *return_value << endl;
    // cout << return_value << endl;
    // while(1);
    // pthread_mutex_destroy(&mutex);

}