#include <iostream>
#include <cmath>  // 包含cmath庫以使用數學函數
using namespace std;

int main() {
    // 基本數學函數
    double x = -3.7;
    cout << "abs(" << x << ") = " << abs(x) << endl; // 計算整數絕對值
    cout << "fabs(" << x << ") = " << fabs(x) << endl; // 計算浮點數絕對值
    cout << "fmod(7.5, 2.3) = " << fmod(7.5, 2.3) << endl; // 計算浮點數的餘數

    // 冪和指數函數
    double base = 2.0;
    double exponent = 3.0;
    cout << base << " ^ " << exponent << " = " << pow(base, exponent) << endl; // 計算2的3次方
    cout << "sqrt(16) = " << sqrt(16) << endl; // 計算16的平方根
    cout << "cbrt(27) = " << cbrt(27) << endl; // 計算27的立方根
    cout << "exp(1) = " << exp(1) << endl; // 計算e的1次方
    cout << "exp2(3) = " << exp2(3) << endl; // 計算2的3次方
    cout << "log(M_E) = " << log(M_E) << endl; // 計算自然對數，以e為底
    cout << "log10(100) = " << log10(100) << endl; // 計算10的對數，以10為底
    cout << "log2(8) = " << log2(8) << endl; // 計算8的對數，以2為底

    // 三角函數
    double angle = M_PI / 4;  // 45度角，M_PI是pi的常數
    cout << "sin(" << angle << ") = " << sin(angle) << endl; // 計算正弦值
    cout << "cos(" << angle << ") = " << cos(angle) << endl; // 計算餘弦值
    cout << "tan(" << angle << ") = " << tan(angle) << endl; // 計算正切值
    cout << "asin(0.707) = " << asin(0.707) << endl; // 計算反正弦值
    cout << "acos(0.707) = " << acos(0.707) << endl; // 計算反餘弦值
    cout << "atan(1) = " << atan(1) << endl; // 計算反正切值
    cout << "atan2(1, 1) = " << atan2(1, 1) << endl; // 計算反正切值，考慮到象限

    // 雙曲函數
    double value = 1.0;
    cout << "sinh(" << value << ") = " << sinh(value) << endl; // 計算雙曲正弦值
    cout << "cosh(" << value << ") = " << cosh(value) << endl; // 計算雙曲餘弦值
    cout << "tanh(" << value << ") = " << tanh(value) << endl; // 計算雙曲正切值
    cout << "asinh(1) = " << asinh(1) << endl; // 計算反雙曲正弦值
    cout << "acosh(2) = " << acosh(2) << endl; // 計算反雙曲餘弦值
    cout << "atanh(0.5) = " << atanh(0.5) << endl; // 計算反雙曲正切值

    // 其他數學函數
    cout << "ceil(4.3) = " << ceil(4.3) << endl; // 向上取整
    cout << "floor(4.7) = " << floor(4.7) << endl; // 向下取整
    cout << "round(4.5) = " << round(4.5) << endl; // 四捨五入
    cout << "trunc(4.7) = " << trunc(4.7) << endl; // 去掉小數部分
    cout << "hypot(3, 4) = " << hypot(3, 4) << endl; // 計算直角三角形的斜邊長

    return 0;
}
