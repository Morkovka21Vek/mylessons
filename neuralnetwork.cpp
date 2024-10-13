#include <iostream>

int main() {

    // Обучающие данные
    int rc0=-40, rc1=-10, rc2=15, rc3=38; // Градусы по цельсию
    int rf0=-40, rf1=14, rf2=59, rf3 = 100; // Градусы по фаренгейту
    // Лучше делать массивами, но я их не проходил

    float learning_rate = -0.001F; // Скорось обучения(+инвертирование ошибки)
    float weight = 1, bias = 1; // Объявление весов до обучения(лучше объявлять рандомно)
    float forward, loss; // Переменные для записи промежуточных значений

    int epoch;
    for (epoch=0; epoch<10000; epoch++) // для примера возьмем 1000 эпох
    {
	forward = rc0 * weight + bias; // вычисляем предсказание НН
        loss = forward - rf0; // вычисляем ошибку

	// корректируем веса
	weight += learning_rate * loss * rc0; 	
	bias += learning_rate * loss;
	/*
	по факту bias(смещение) корректируется так:
	bias += learning_rate * loss * 1;
	А в forward propogation вычисляется так:
	forward = rc0*weight+bias*1
	Т.к bias является тоже весом.
	*/

	// далее делаем тоже самое, но с другими данными
	// (Правильней это делать через for и массивы)
        forward = rc1 * weight + bias;
        loss = forward - rf1;
	weight += learning_rate * loss * rc1;
        bias += learning_rate * loss;

        forward = rc2 * weight + bias;
        loss = forward - rf2;
	weight += learning_rate * loss * rc2;
	bias += learning_rate * loss;

        forward = rc3 * weight + bias;
        loss = forward - rf3;
	weight += learning_rate * loss * rc3;
	bias += learning_rate * loss;

	//std::cout << "Epoch: " << epoch << "          Loss: " << loss << std::endl;
    }
    std::cout << "Epoch: " << epoch << "          Loss: " << loss << std::endl; // Выводим результат ошибки для последних данных последней эпохи
    std::cout << "Weight = " << weight << ", bias = " << bias << std::endl; 

    // Проверяем:
    int test_inp;
    std::cout << "Введите пожалуйста температуру в градусах цельсия:\n>>> ";
    std::cin >> test_inp;

    //forward = 20 * weight + bias;
    std::cout << test_inp << " градусов по цельсию в градусах по фаренгейту равны:" << std::endl
	    << "Предсказание нейросети: >> " << (test_inp * weight + bias) << std::endl
	    << "Реальное значение: >> " << (test_inp * 9 / 5 + 32) << std::endl;
    return 0;
}
