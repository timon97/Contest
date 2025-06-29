/* Решение финальной задачи Спринт 1: A. Ближайший ноль
   https://contest.yandex.ru/contest/22450/run-report/139699403/
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int size;
    cin >> size;
    vector<int> vec;
    vec.reserve(size);

    // Считываем исходный массив и сетим ненулевые элементы максимальным значением
    for (int i = 0; i < size; i++) {
        int elem;
        cin >> elem;
        if (elem) {
            elem = size;
        }
        vec.push_back(elem);
    }

    // Проходим с лева на право в поисках ближайшего нуля и если ноль был найден рассчитываем расстояние
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] != 0) {
            vec[i] = vec[i - 1] + 1;
        }
    }

    // Проходим с права на лево в поисках ближайшего нуля и если ноль был найдем рассчитываем расстояние,
    // а так же если значение уже было рассчитано, то находим минимальное расстояние.
    for (int i = vec.size() - 2; i >= 0 ; i--) {
        if (vec[i] != 0) {
            vec[i] = min(vec[i], vec[i + 1] + 1);
        }
    }

    for (auto elem : vec) {
        cout << elem << " ";
    }

    return 0;
}
