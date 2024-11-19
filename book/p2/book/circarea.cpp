#include <iostream>
int main(){
    float rad;
    const float PI = 3.14159F;
    using namespace std;
    cout << "R: >>>";
    cin >> rad;
    float area = PI * rad * rad;
    cout << "S = " << area << endl;
    return 0;
}
