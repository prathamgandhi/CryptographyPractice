#include <bits/stdc++.h>

using namespace std;

int main(){
    int k;
    cout << "Enter the key : ";
    cin >> k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string s;
    cout << "Enter the string : " << endl;
    getline(cin, s);
    string encryptedText;
    for(int i = 0; i < s.length(); i++){
        encryptedText.push_back((char)((s[i]-'a')+k)%26 + 'a');
    }
    cout << "The encrypted text is " << encryptedText << endl;;
    string decryptedText;
    for(int i = 0; i < encryptedText.length(); i++){
        char ch = (char) (((encryptedText[i]-'a'+26-k)%26)+'a');
        decryptedText.push_back(ch);
   }
    cout << "The decrypted text is " << decryptedText << endl;
    return 0;
}
