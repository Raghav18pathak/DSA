vector < int > sortedArray(vector < int > a, vector < int > b) {
    // Write your code here'
    vector<int> result;
    int i=0;
    int j=0;
    while(i<a.size() && j<b.size()){
        if(a[i]<=b[j]){
            if(result.empty()==true || result.back()!=a[i]){
            result.push_back(a[i]);
            }
            if(a[i]==b[j]) j++;
            i++;
        }
        else{
            if(result.empty()==true || result.back()!=b[j]){
            result.push_back(b[j]);
            }
            j++;
        }
        
    }
    while(i<a.size()){
        if(result.empty()==true || result.back()!=a[i]){
        result.push_back(a[i]);
        }
        i++;
    }
    while(j<b.size()){
        if(result.empty()==true || result.back()!=b[j]){
        result.push_back(b[j]);
        }
        j++;
    }
    return result;
}