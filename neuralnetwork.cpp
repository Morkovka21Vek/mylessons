#include <iostream>

int main() {
    int rc0=-40, rc1=-10, rc2=15, rc3=38;
    int rf0=-40, rf1=14, rf2=59, rf3 = 100;
    float learning_rate = -0.001F;
    float weight = 1, bias = 1;
    int epoch;
    float forward, loss;
    for (epoch=0; epoch<10000; epoch++)
    {
	forward = rc0*weight+bias;
        loss = forward-rf0;
	weight += learning_rate * loss * rc0;
	bias += learning_rate * loss;
	/*
	по факту bias вычисляется так:
	bias += learning_rate * loss * 1;
	А в forward propogation так:
	forward = rc0*weight+bias*1
	Т.к bias является тоже весом.
	*/

        forward = rc1*weight+bias;
        loss = forward-rf1;
	weight += learning_rate * loss * rc1;
        bias += learning_rate * loss;

        forward = rc2*weight+bias;
        loss = forward-rf2;
	weight += learning_rate * loss * rc2;
	bias += learning_rate * loss;

        forward = rc3*weight+bias;
        loss = forward-rf3;
	weight += learning_rate * loss * rc3;
	bias += learning_rate * loss;

	//std::cout << "Epoch: " << epoch << "          Loss: " << loss << std::endl;
    }
    std::cout << "Epoch: " << epoch << "          Loss: " << loss << std::endl;
    std::cout << "Weight = " << weight << ", bias = " << bias << std::endl;
}
