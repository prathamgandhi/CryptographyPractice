#include <bits/stdc++.h>

#define N 3
#define MOD 26

using namespace std;

int modMultiply(int n1, int n2){
    return ((n1%MOD)*(n2%MOD))%MOD;
}

int modAdd(int n1, int n2){
    return ((n1%MOD)+(n2%MOD))%MOD;
}

int modInverse(int b, int a, int t1 = 0, int t2 = 1){
    if(b%a == 0){
        if(a != 1){
            throw invalid_argument("GCD not 1");
        }
        return t2 >= 0 ? t2%MOD : (t2%MOD + 26);
    }
    return modInverse(a, b%a, t2, t1 - ((b/a)*t2));
}

void printMatrix(vector<vector<int>> &matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> generateKeyMatrix(const string &key){
    vector<vector<int>> keyMatrix(N, vector<int> (N, -1));
    int i = 0, j = 0;
    for(int k = 0; k < key.size(); k++){
        keyMatrix[i][j++] = key[k] - 'a';
        if(j == N){
            j = 0;
            i++;
        }
    }
    return keyMatrix;
}

vector<vector<int>> generatePlainTextMatrix(const string &pt){
    
    vector<vector<int>> plainTextMatrix(N, vector<int> (1, 0));
    for(int i = 0; i < pt.size(); i++){
        plainTextMatrix[i][0] = pt[i] - 'a';
    }
    return plainTextMatrix;
}

vector<vector<int>> matrixMultiply(const vector<vector<int>> &m1, const vector<vector<int>> &m2){
    if(m1[0].size() != m2.size()){
        throw invalid_argument("Matrix dimensions not matching for multiplication");
    }
    vector<vector<int>> res(m1.size(), vector<int> (m2[0].size(), 0));
    for(int i = 0; i < m1.size(); i++){
        for(int j = 0; j < m2[0].size(); j++){
            for(int k = 0; k < m1[0].size(); k++){
                res[i][j] = modAdd(res[i][j], modMultiply(m1[i][k], m2[k][j]));
            }
        }
    }
    return res;
}

void printColumnMatrix(vector<vector<int>> &columnMatrix){
    if(columnMatrix[0].size() != 1){
        throw invalid_argument("Not a column matrix");
    }
    for(int i = 0; i < columnMatrix.size(); i++){
        cout << (char)(columnMatrix[i][0] + 'a');
    }
    cout << endl;
}
/*
vector<vector<int>> generateMinorMatrix(const vector<vector<int>> &matrix, int i, int j){
    
}
*/
int determinant(const vector<vector<int>> matrix){
    if(matrix.size() != matrix[0].size()){
        throw invalid_argument("matrix is not square");
    }
    if(matrix.size() == 1){
        return matrix[0][0];
    }
    else if(matrix.size() == 2){
        int val = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
        return val;
    }
    int ans = 0;
    for(int k = 0; k < matrix[0].size(); k++){
        vector<vector<int>> tempMatrix;
        for(int i = 1; i < matrix.size(); i++){
            vector<int> tempArray;
            for(int j = 0; j < matrix[0].size(); j++){
                if(j == k){
                    continue;
                }
                tempArray.push_back(matrix[i][j]);
            }
            tempMatrix.push_back(tempArray);

        }
        int tempVal = determinant(tempMatrix);
        ans = ans + (matrix[0][k])*(((k % 2 == 0) ? 1 : -1) * tempVal); 
    }
    return ans;
}

int getMinor(vector<vector<int>> &matrix, int i, int j){
    vector<vector<int>> tempMatrix;
    for(int k = 0; k < matrix.size(); k++){
        vector<int> tempArray;
        for(int l = 0; l < matrix[0].size(); l++){
            if(k == i or l == j) continue;
            tempArray.push_back(matrix[k][l]);
        }
        if(tempArray.size() != 0) tempMatrix.push_back(tempArray);
    }
    return determinant(tempMatrix);
}

void generateTransposeMatrix(vector<vector<int>> &matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = i; j < matrix[0].size(); j++){
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}

vector<vector<int>> generateAdjointMatrix(vector<vector<int>> &matrix){
    vector<vector<int>> cofactorMatrix(matrix.size(), vector<int> (matrix[0].size(), -1));
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            cofactorMatrix[i][j] = ((i+j)&1 ? -1 : 1) * getMinor(matrix, i, j);
        }
    }
    generateTransposeMatrix(cofactorMatrix);
    return cofactorMatrix;
}

vector<vector<int>> generateInverseMatrix(vector<vector<int>> &matrix){
    vector<vector<int>> adjointMatrix = generateAdjointMatrix(matrix);
    int det = determinant(matrix);
    det = modInverse(26, det);
    for(int i = 0; i < adjointMatrix.size(); i++){
        for(int j = 0; j < adjointMatrix[0].size(); j++){
            adjointMatrix[i][j] = (adjointMatrix[i][j]%MOD * det) % MOD;
            adjointMatrix[i][j] = adjointMatrix[i][j] < 0 ? adjointMatrix[i][j] + 26 : adjointMatrix[i][j];
        }
    }
    return adjointMatrix;
}

int main(){
    string key;
    cout << "Enter the key of size n^2" << endl;
    getline(cin, key);
    vector<vector<int>> keyMatrix = generateKeyMatrix(key);
    cout << "Enter the plaintext of size n" << N << endl;
    string pt;
    getline(cin, pt);
    if(key.size() != pt.size()*pt.size()){
        throw invalid_argument("Sizes not compatible");
    }


    vector<vector<int>> ptMatrix = generatePlainTextMatrix(pt);


    vector<vector<int>> encryptedMatrix = matrixMultiply(keyMatrix, ptMatrix);
    cout << "The encrypted text is : ";
    printColumnMatrix(encryptedMatrix);


    vector<vector<int>> inverseKey = generateInverseMatrix(keyMatrix);


    cout << "The decrypted text is : ";
    vector<vector<int>> decryptedColumn = matrixMultiply(inverseKey, encryptedMatrix);
    
    printColumnMatrix(decryptedColumn);
    return 0;
}
