#include <stdio.h>

struct item {
    int id;
    int Q;
    int year;
};

int main() {

    struct item m;
    int n;

    scanf("%d", &n);

   
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &m.id[i], &m.Q[i], &m.year[i]);
    }

    
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", m.id[i], m.Q[i], m.year[i]);
    }

    
    int temp = year[0];

    for (int i = 1; i < n; i++) {
        if (m.year[0] > m.year[i]) {
            temp = m.year[i];
        }
    }
    for(int i=0; i<n; i++){
        if(temp=m.year[i]){
            printf("Oldest item : %d %d %d",m.id[i],m.Q[i],m.year[i]);
        }
    }

    
    return 0;
}