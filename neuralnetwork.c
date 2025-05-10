#include <stdio.h>

int main() {

    // Обучающие данные
    int celsius[] = {-40, -10, 15, 38}; // Градусы по цельсию
    int fahrenheit[] = {-40, 14, 59, 100}; // Градусы по фаренгейту

    float learning_rate = -0.001F; // Скорось обучения(+инвертирование ошибки)
    float weight = 1;
    float bias = 1;
    float forward;
    float loss;

    int epoch;
    for (epoch = 0; epoch < 10000; epoch++) // для примера возьмем 10000 эпох
    {
        for (int i = 0; i < sizeof(celsius) / sizeof(celsius[0]); i++) {
            forward = celsius[i] * weight + bias; // вычисляем предсказание НН
            loss = forward - fahrenheit[i]; // вычисляем ошибку
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

    printf("Epoch: %d\tLoss: %f\n\n", epoch, loss);
    printf("Weight = %f, bias = %f\n", weight, bias);

    // Проверяем:
    int test_inp;
    printf("Введите пожалуйста температуру в градусах цельсия: ");
    scanf("%d", &test_inp);

    printf("%d градусов по цельсию в градусах по фаренгейту равны:\n"
           "Предсказание нейросети: >> %f\n"
           "Реальное значение: >> %f\n",
           test_inp, (weight * test_inp + bias), (1.8F * test_inp + 32));
    return 0;
}
