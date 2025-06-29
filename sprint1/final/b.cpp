// Решение финальной задачи Спринт 1: B. Ловкость рук
// https://contest.yandex.ru/contest/22450/run-report/139699248/
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int k;
    cin >> k;
    vector<int> map;
    map.reserve(10);

    // Читаем в вектор входные данные, всё кроме цифр отбрасываем.
    for (int i = 0; i < 16; i++) {
        char sym;
        cin >> sym;
        if (isdigit(sym)) {
            map[sym - '0']++;
        }
    }

    // Если элемент присутствует и удовлетворяет правилам, начисляем балл.
    int counter = 0;
    for (int i = 1; i <= 9; i++) {
        if (map[i] && map[i] <= k * 2) {
            counter++;
        }
    }

    cout << counter << endl;
    return 0;
}
