#include <iostream>
#include <thread>

using namespace std;

int a = 0;
thread *showV;

void count(int i){
    while(abs(a) < 99){
        a += i;
    }
}

void show(){
    while(abs(a) < 99){
        cout << a << endl;
    }
}

int main(){
    thread increment(count, 1);
    thread decrement(count, -1);
    showV = new thread(show);
    increment.join();
    decrement.join();
    showV->join();
    cout << "Resultado: " << a << endl;
    return 0;
}