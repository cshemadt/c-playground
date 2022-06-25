#include <stdio.h>
int iteration_binary_search(int x, int v[], int n);
int recursive_binary_search(int x,int low,int hight, int v[]);
int main() {
    int n=9;
    int v[]={1,2,3,5,7,8,12,19,100};   
    int ind=recursive_binary_search(1,0,n-1,v);
    printf("%d\n",ind);
}
int iteration_binary_search(int x, int v[], int n) {
    int low,mid,high;
    low=0;
    high=n-1;
    while(low<=high) {
        mid=(low+high)/2;
        if(x<v[mid]) 
            high=mid;
        else if(x>v[mid]) 
            low=mid+1;
        else
            return mid+1;
    }
    return -1;
}
int recursive_binary_search(int x,int low,int high, int v[]) {
    int mid=(low+high)/2;
    if(low>high)
        return -1;
    if(x==v[mid])
        return mid+1;
    if(x<v[mid])
        return recursive_binary_search(x,low,mid-1,v);
    if(x>v[mid])
        return recursive_binary_search(x,mid+1,high,v); 
}