#include <iostream>
using namespace std;

int f1(int x){
    if (x > 10)      return 2*x;
    else if (x > 0)  return -x;
    else             return 2*x;
}

int main(){
    int so;
    cin >> so;
    cout << f1(so) << endl;
    return 0;
}