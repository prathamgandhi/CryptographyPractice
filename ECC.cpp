#include <bits/stdc++.h>

using namespace std;

int modInverse(int A, int M)
{
    int m0 = M;
    int y = 0, x = 1;
 
    if (M == 1)
        return 0;
 
    while (A > 1) {
        int q = A / M;
        int t = M;
 
        M = A % M, A = t;
        t = y;
 
        y = x - q * y;
        x = t;
    }
 
    if (x < 0)
        x += m0;
 
    return x;
}



class Curve {
public:
    class Point {
    private:
        int x, y, a, b, MOD;
    public:

        Point(){

        }

        Point(int x_val, int y_val, int a_val, int b_val, int MOD_val){
            if((y_val*y_val)%MOD_val != ((x_val * x_val * x_val + a_val * x_val + b_val)%MOD_val)){
                throw invalid_argument("Point does not satisfy the curve");
            }
            else{
                x = x_val;
                y = y_val;
                a = a_val;
                b = b_val;
                MOD = MOD_val;
            }
        } 

        Point operator+(const Point &point){
            if(point.a != a or point.b != b or point.MOD != MOD){
                throw invalid_argument("Points should belong to the same curve");
            }
            // cout << this->printPoint() << "    " << point.printPoint() << endl;
            Point res;
            int x_, y_;
            if(point.x == x and point.y == y){
                int lambda = ((3*x*x + a)*modInverse(2*y, MOD))%MOD;
                x_ = (lambda*lambda - 2*x)%MOD;
                y_ = (lambda*(x-x_)-y)%MOD;
            }
            else if (point.x == x and point.y == -y){
                x_ = INT_MAX;
                y_ = INT_MAX;
            }
            else{
                int temp = point.x - x;
                temp = temp >= 0 ? temp : temp + MOD;
                int lambda = ((point.y - y)*modInverse(temp, MOD))%MOD;
                x_ = ((lambda * lambda) - x - point.x)%MOD;
                y_ = (lambda*(x - x_) - y)%MOD;
            }
            res.x = x_ >= 0 ? x_ : (x_ + MOD);
            res.y = y_ >= 0 ? y_ : (y_ + MOD);
            res.a = a;
            res.b = b;
            res.MOD = MOD;
            // cout << res.printPoint() << endl;
            return res;
        }

        Point operator-() const{
            Point res;
            res.x = x;
            res.y = -y;
            res.y = res.y >= 0 ? res.y : (res.y + MOD);
            res.a = a;
            res.b = b;
            res.MOD = MOD;
            return res;
        }

        Point operator-(const Point &point){
            if(point.a != a or point.b != b or point.MOD != MOD){
                throw invalid_argument("Points should belong to the same curve");
            }
            Point res;
            res = *this + (-point);
            res.a = a;
            res.b = b;
            res.MOD = MOD;
            return *this + (-point);
        }

        Point operator*(const int multiplier){
            int k = multiplier-1;
            Point res = *this, temp = *this;
            while(k--){
                res =  temp + res; 
                res.a = a;
                res.b = b;
                res.MOD = MOD;
            }
            return res;
        }

        string printPoint() const {
            string s = "(" + to_string(x) + "," + to_string(y) + ")";
            return s;
        }

    };

    Curve(int a_val, int b_val, int MOD_val) : a(a_val), b(b_val), MOD(MOD_val) {}

    Point createPoint(double x_val, double y_val) {
        return Point(x_val, y_val, a, b, MOD);
    }

    string printCurve(){
        string s = "(" + to_string(a) + "," + to_string(b) + "," + to_string(MOD) + ")";
        return s;
    }

private:
    int a, b, MOD;
};


int main(){
    cout << "Enter the parameters of the curve a, b and MOD : " << endl;
    int a, b, MOD, d, gx, gy;
    cin >> a >> b >> MOD;
    Curve curve(a, b, MOD);
    cout << "Enter the secret key : " << endl;
    cin >> d;
    cout << "Enter the coordinates of the base point : " << endl;
    cin >> gx >> gy;
    Curve::Point e1 = curve.createPoint(gx, gy);
    Curve::Point e2 = e1*d;
    cout << "The public key is : \ne1 - " << e1.printPoint() << "\ne2 - " << e2.printPoint() << "\nCurve - " << curve.printCurve() << endl; 
    cout << "Enter the random value for encryption : " << endl;
    int k;
    cin >> k;
    Curve::Point c1 = e1*k;
    cout << "Enter the plaintext as a point : " << endl;
    int p1, p2;
    cin >> p1 >> p2;
    Curve::Point p = curve.createPoint(p1, p2);
    Curve::Point c2 = p + e2*k;
    cout << "The ciphertext is " << c1.printPoint() << " " << c2.printPoint() << endl;
    Curve::Point decrypted = c2 - (c1*d);
    cout << "The decrypted plaintext is " << decrypted.printPoint() << endl;
    return 0;
}