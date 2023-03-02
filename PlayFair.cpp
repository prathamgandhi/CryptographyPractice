#include <bits/stdc++.h>

using namespace std;

void fillKeyMatrix(vector<vector<char>> &keyMatrix, const string &key){
    int k = 0, i=0, j=0;
    int dict[26] = { 0 };
    while(k < key.length()){
        if(dict[key[k]-'a'] != 1) {
            keyMatrix[i][j++] = key[k] == 'j' ? 'i' : key[k];
            if(key[k] == 'j') dict[key[k] - 'i'] = 1;
            dict[key[k]-'a'] = 1;
            if(j == 5){
                i++;
                j=0;
            }
        }
        k++;
    }
    char curr = 'a';
    for(; i < 5; i++){
        for(; j < 5; j++){
            while(dict[curr-'a'] == 1){
                curr++;
                if(curr == 'j') curr++;
            } 
            keyMatrix[i][j] = curr;
            dict[curr-'a'] = 1;
            curr++;
            if(curr == 'j') curr++;
        }
        j = 0;
    }
}

void printMatrix(vector<vector<char>> &keyMatrix){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << keyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

vector<pair<char, char>> createDigram(const string &pt){
    vector<pair<char, char>> processed_pt;
    int i = 0;
    while(i < pt.length()){
        char first, second;
        if(i+1 == pt.length()){
            first = pt[i] == 'j' ? 'i' : pt[i];
            second = 'z';
        }
        else{
            first = pt[i] == 'j' ? 'i' : pt[i];
            if(pt[i+1] == first){
                second = 'z';
            }
            else{
                second = pt[i+1] == 'j' ? 'i' : pt[i+1];
                if(first == second) {
                    second = 'z';
                }
                else{
                    i++;
                }
            }
        }
        processed_pt.push_back(make_pair(first, second));
        i++;
    }
    return processed_pt;
}

pair<char, char> encryptSearch(pair<char, char> &p, vector<vector<char>> &keyMatrix){
    pair<char, char> pe;
    int i1, i2, j1, j2;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(keyMatrix[i][j] == p.first){
                i1 = i;
                j1 = j;
            }
            if(keyMatrix[i][j] == p.second){
                i2 = i;
                j2 = j;
            }
        }
    }
    if(i1 == i2){
        pe.first = keyMatrix[i1][(j1 + 1)%5];
        pe.second = keyMatrix[i2][(j2 + 1)%5];
    }
    else if(j1 == j2){
        pe.first = keyMatrix[(i1 + 1)%5][j1];
        pe.second = keyMatrix[(i2 + 1)%5][j2];
    }
    else{
        pe.first = keyMatrix[i1][j2];
        pe.second = keyMatrix[i2][j1];
    }
    return pe;
}

pair<char, char> decryptSearch(pair<char, char> &p, vector<vector<char>> &keyMatrix){
    pair<char, char> pe;
    int i1, i2, j1, j2;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(keyMatrix[i][j] == p.first){
                i1 = i;
                j1 = j;
            }
            if(keyMatrix[i][j] == p.second){
                i2 = i;
                j2 = j;
            }
        }
    }
    if(i1 == i2){
        pe.first = keyMatrix[i1][(j1 + 4)%5];
        pe.second = keyMatrix[i2][(j2 + 4)%5];
    }
    else if(j1 == j2){
        pe.first = keyMatrix[(i1 + 4)%5][j1];
        pe.second = keyMatrix[(i2 + 4)%5][j2];
    }
    else{
        pe.first = keyMatrix[i1][j2];
        pe.second = keyMatrix[i2][j1];
    }
    return pe;
}

/*
 *  a b c d
 *  (1,0) f g h
 *  i j k (2,3)
 *  m n o p
 */

int main(){
    int n;
    cout << "Enter the size of the key : " << endl;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter the key : " << endl;
    string key;
    getline(cin, key);
    vector<vector<char>> keyMatrix(5, vector<char> (5, '\0'));
    fillKeyMatrix(keyMatrix, key);
    cout << "The key matrix is : " << endl;
    printMatrix(keyMatrix);
    cout << "Enter the plaintext : " << endl;
    string pt;
    getline(cin, pt);
    vector<pair<char, char>> processed_pt = createDigram(pt);
    cout << "The created digrams are : " << endl;
    for(int i = 0; i < processed_pt.size(); i++){
        cout << processed_pt[i].first << processed_pt[i].second << " ";
    }
    vector<pair<char, char>> encryptedDigrams;
    for(int i = 0; i < processed_pt.size(); i++){
        encryptedDigrams.push_back(encryptSearch(processed_pt[i], keyMatrix));
    }
    cout << "The encrypted digrams are : " << endl;
    for(int i = 0; i < processed_pt.size(); i++){
        cout << encryptedDigrams[i].first << encryptedDigrams[i].second << " ";
    }
    cout << endl;
    vector<pair<char, char>> decryptedDigrams;
    for(int i = 0; i < encryptedDigrams.size(); i++){
        decryptedDigrams.push_back(decryptSearch(encryptedDigrams[i], keyMatrix));
    }
    cout << "The decrypted digrams are : " << endl;
    for(int i = 0; i < decryptedDigrams.size(); i++){
        cout << decryptedDigrams[i].first <<  decryptedDigrams[i].second << " ";
    }
    cout << endl;
    return 0;

}
