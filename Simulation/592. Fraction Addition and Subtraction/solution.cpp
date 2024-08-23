/*
 *  土法煉鋼猜解expression然後計算 irreducible fraction
 *  即使這樣也得到了AC
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
    void calculate(int& num1, int& deno1, int num2, int deno2) {
        //cout << num1 << "/" << deno1 << "," << num2 << "/" << deno2 << endl;
        num1 *= deno2;
        num2 *= deno1;
        num1 = num1 + num2;
        deno1 *= deno2;
        if(num1 == 0) deno1 = 1;
        else {
            int g = __gcd(num1, deno1);
            if(g != 1) {
                num1 /= g;
                deno1 /= g;
            }
            if(deno1 < 0) {
                num1 *= -1;
                deno1 *= -1;
            }
        }
    }
public:
    string fractionAddition(string expression) {
        int numerator = 0, denominator = 1;
        int sign{1}, num{}, deno{}, place{};
        expression.push_back('+');
        for(auto& c : expression) {
            if(c == '-' || c == '+') {
                num *= sign;
                sign = c == '-' ? -1 : 1;
                calculate(numerator, denominator, num, deno);
                num = 0;
                deno = 0;
                place = 0;
            } else if(c == '/') {
                place = 1;
            } else {
                if(place == 0) {
                    num = num * 10 + (c - '0');
                } else {
                    deno = deno * 10 + (c - '0');
                }
                //cout << c << "," << num << "," << deno << endl;
            }
        }
        return to_string(numerator) + "/" + to_string(denominator);
    }
};

/*  參考解答 : https://leetcode.com/problems/fraction-addition-and-subtraction/solutions/103384/small-simple-c-java-python/
 *  使用istringstream 因為定義了int a, b和char _ 
 *  所以會直接讀取 (整數 char 整數) 這樣的形式近來 可以減少很多parse的code
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    string fractionAddition(string expression) {
        istringstream in(expression);
        int A = 0, B = 1, a, b;
        char _;
        while (in >> a >> _ >> b) {
            A = A * b + a * B;
            B *= b;
            int g = abs(__gcd(A, B));
            A /= g;
            B /= g;
        }
        return to_string(A) + '/' + to_string(B);
    }
};
