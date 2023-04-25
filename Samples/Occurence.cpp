#include <iostream>

using namespace std;

int main(){
    int arr[26] = {0};
    string s;
    cout << "Enter a string" << endl;
    cin >> s;
    for(int i = 0; i < s.length(); i++){
        arr[s[i]-97]++;
    }
    cout << "The frequency count of each character is " << endl;
    for(int i = 0; i < 26; i++){
        if(arr[i] != 0){
            cout << (char)(i + 97) << " : " << arr[i] << endl;
        }
    }
    return 0;
}