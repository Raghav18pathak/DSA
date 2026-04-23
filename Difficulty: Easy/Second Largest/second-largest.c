int getSecondLargest(int *arr, int n) {
    // code here
    int largest=arr[0];
    int slargest=-1;
    for(int i=1;i<n;i++){
        if(largest < arr[i]){
            slargest = largest;
            largest = arr[i];
        }
        else if(largest>arr[i] && arr[i]>slargest){
            slargest= arr[i];
        }
    }
    return slargest;
}
