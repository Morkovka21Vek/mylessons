#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double number, answer;
    cout << ">>>";
    cin >> number;
    answer = sqrt(number);
    cout << "sqrt(" << number << ") = " << answer << endl;
    //cout << "sqrt = " << answer << endl;
    return 0;
}
