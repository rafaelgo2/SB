#include <iostrea>
#include <thread>

using namespace std;

void count(int &a, int i){
    while(a != 99999*i){
        a += i;
    }
}

int main(){
    int a = 0;
    thread increment(a, 1);
    thread decrement(a, -1);
    thread show()
    return 0;
}