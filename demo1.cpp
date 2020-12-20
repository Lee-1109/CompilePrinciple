#include <stdio.h>
#include "iostream"
using namespace std;
int main (void){
    char demo[1000];
    int a,b = 0;
    for(a = 0;; a++){
        cin>>demo[a];
        if(demo[a] == '\n')
            break;
    }
    for(int i = 0; i <= a; i++){
        if(i > 0 && demo[i] == ' ' && demo[i - 1] != ' ' ){
            cout<<demo[i - 1];
            b++;
        }
        if(demo[i - 1] != ' '&&demo[i] == '\n'){
            cout<<demo[i - 1];
            b++;
        }
    }
    cout<<endl<<b;
    return 0;
}