// User function Template for C

int search(int arr[], int n, int x) {
    // Code here
    int u=-1;
    for(int i=0;i<n;i++){
        if(arr[i]==x){
            u=i;
            break;
        }
    }
    return u;
}