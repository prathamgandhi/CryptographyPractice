#include <bits/stdc++.h>

using namespace std;

vector<int> mult(vector<vector<int>> &key, vector<int> &pt){
    vector<int> ret(pt.size());
    for(int i = 0; i < key.size(); i++){
        for(int j = 0; j < key[0].size(); j++){
            ret[i] = (ret[i]%26 + key[i][j]*pt[j]%26)%26; 
        }
    }
    return ret;
}

vector<int> mult(vector<vector<double>> &key, vector<int> &pt){
    vector<int> ret(pt.size());
    for(int i = 0; i < key.size(); i++){
        for(int j = 0; j < key[0].size(); j++){
            ret[i] = (ret[i]%26 + (int)(key[i][j]*pt[j])%26)%26; 
        }
    }
    return ret;
}

void getCofactor(vector<vector<int>> &matrix, vector<vector<int>> &temp, int p, int q, int n){
    int i = 0, j = 0;
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(row != p and col != q){
                temp[i][j++] = matrix[row][col];
                if(j == n-1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(vector<vector<int>> &matrix, int n){
    int D = 0;

    if(n == 1){
        return matrix[0][0];
    }
    vector<vector<int>> temp(matrix.size(), vector<int> (matrix[0].size()));
    int sign = 1;
    for(int f = 0; f < n; f++){
        getCofactor(matrix, temp, 0, f, n);
        D += sign * matrix[0][f] * determinant(temp, n-1);
        sign = -sign;
    }
    return D;
}


vector<vector<int>> adjoint(vector<vector<int>> &matrix){
    vector<vector<int>> adj(matrix.size(), vector<int> (matrix.size()));

    if(matrix.size() == 1){
        adj[0][0] = 1;        
    }
    int sign = 1;
    vector<vector<int>> temp(matrix.size(), vector<int> (matrix.size()));
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            getCofactor(matrix, temp, i, j, matrix.size());
            sign = ((i+j)%2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, matrix.size()-1));
        }
    }
    return adj;
}

bool inverse(vector<vector<int>> &matrix, vector<vector<double>> &inverse){
    int det = determinant(matrix, matrix.size());
    if(det == 0){
        cout << "Singular matrix, can't find its inverse";
        return false;
    }
    vector<vector<int>> adj = adjoint(matrix);
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            inverse[i][j] = adj[i][j] / float(det);
        }
    }
    return true;
}

int main(){
    string key, pt;
    cout << "Enter the key" << endl;
    getline(cin, key);
    cout << "Enter the pt" << endl;
    getline(cin, pt);
    vector<vector<int>> keyMatrix(pt.size(), vector<int> (pt.size(), -1));
    vector<int> ptMatrix(pt.size());
    int l = 0, m = 0;
    for(int i = 0; i < key.size(); i++){
        keyMatrix[l][m++] = key[i]-'a';
        if(m == pt.size()){
            l++;
            m = 0;
        }
    }

    for(int i = 0; i < pt.size(); i++){
        ptMatrix[i] = pt[i]-'a';
    }
    vector<int> cipher = mult(keyMatrix, ptMatrix);
    cout << "The cipher text is " << endl;
    for(int i = 0; i < cipher.size(); i++){
        cout << (char)(cipher[i]+'a');
    }
    cout << endl;
    vector<vector<double>> inv(keyMatrix.size(), vector<double> (keyMatrix.size()));
    bool possible = inverse(keyMatrix, inv);
    if(!possible){
        return -1;
    }
    else{
        vector<int> res = mult(inv, cipher);
        cout << "The decrypted text is " << endl;
        for(int i = 0; i < res.size(); i++){
            cout << (char)(res[i]+'a');
        }        
    }
    cout << endl;
    return 0;
}