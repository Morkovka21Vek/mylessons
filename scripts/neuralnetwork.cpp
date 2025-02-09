#include <iostream>
#include <vector>

int main() {

    // Обучающие данные

    int celsius[] = {-40, -10, 15, 38}; // Градусы по цельсию

    int fahrenheit[] = {-40, 14, 59, 100}; // Градусы по фаренгейту

    float learning_rate = -0.001F; // Скорось обучения(+инвертирование ошибки)
    float weight = 1, bias = 1;    // Объявление весов до обучения(лучше объявлять рандомно)
    float forward, loss;           // Переменные для записи промежуточных значений

    int epoch;
    for (epoch=0; epoch<10000; epoch++) // для примера возьмем 10000 эпох
    {
      for (int i = 0; i < sizeof(celsius) / sizeof(int); i++) {
	      forward = celsius[i] * weight + bias; // вычисляем предсказание НН
        loss = forward - fahrenheit[i];       // вычисляем ошибку
	      // корректируем веса
  	    weight += learning_rate * loss * celsius[i];
	      bias += learning_rate * loss;
      }

  	  /*
  	    по факту bias(смещение) корректируется так:
     	  bias += learning_rate * loss * 1;
       	А в forward propogation вычисляется так:
  	    forward = celsius*weight+bias*1
  	    Т.к bias является тоже весом.
     	*/
    }

    std::cout << "Epoch: " << epoch << "\tLoss: " << loss << std::endl; // Выводим результат ошибки для последних данных последней эпохи
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
