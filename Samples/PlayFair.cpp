#include <bits/stdc++.h>

using namespace std;

int main(){
    string key;
    cout << "Enter the keyword" << endl;
    getline(cin, key);
    vector<vector<char>> matrix(5, vector<char> (5, '\0'));
    unordered_set<char> appeared;
    unordered_map<char, pair<int, int>> revMatrix;
    int i = 0, j = 0, final_i = 0, final_j = 0;
    bool breakerflag = false;
    for(int c = 0; c < key.length(); c++){
        if(appeared.size() == 26) break;
        if(appeared.find(key[c]) == appeared.end()){
            matrix[i][j++] = key[c];
            if(j == 5){
                j = 0;
                i++;
            }
            if(key[c] == 'i' or key[c] == 'j'){
                appeared.insert('i');
                appeared.insert('j');
            }
            else{
                appeared.insert(key[c]);
            }
        }
        
    }
    final_i = i;
    final_j = j;  
    char ch = 'a';
    for(int j = final_j; j < 5; j++){
        while(appeared.find(ch) != appeared.end()){
            ch++;
        }
        if(ch == 'i' or ch == 'j') ch++;
        matrix[final_i][j] = ch++;
    }
    for(int i = final_i+1; i < 5; i++){
        for(int j = 0; j < 5; j++){
            while(appeared.find(ch) != appeared.end()){
                ch++;
            }
            if(ch == 'i' or ch == 'j') ch++;
            matrix[i][j] = ch++;
        }
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            revMatrix[matrix[i][j]] = make_pair(i, j);
        }
    }

    // Encryption
    string plaintext;
    cout << "Enter the string to be encrypted" << endl;
    getline(cin, plaintext);
    vector<pair<char, char>> vp;
    for(int i = 0; i < plaintext.length();){
        if(i == plaintext.length()-1){
            vp.push_back(make_pair(plaintext[i], 'x'));
            i++;
            continue;
        }
        if(plaintext[i] == plaintext[i+1]){
            vp.push_back(make_pair(plaintext[i], 'x'));
            i++;
        }
        else{
            vp.push_back(make_pair(plaintext[i], plaintext[i+1]));
            i+=2;
        }
    }
    vector<pair<int, int>> encryptedvp;
    for(int i = 0; i < vp.size(); i++){
        if(revMatrix[vp[i].first].first == revMatrix[vp[i].second].first){
            encryptedvp.push_back(make_pair())
        }
    }
    return 0;
}