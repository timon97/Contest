/*
Спринт 2 задача A. Дек
https://contest.yandex.ru/contest/22781/run-report/139815186/

-- ПРИНЦИП РАБОТЫ --
    Выполнил реализацию структуры данных дек, на основе кольцевого буфера, который
реализован на основе std::vector. При создании дека задается его размер и выделяется
память. back_ - хранит индекс "хвоста", то есть та ячейка куда будет добавлен элемент
при вызове push_back(). аналогично и с front_ - хранит индекс "головы", для добавления
в начало push_front(). size_  - следит за размерностью, чтобы не выйти за пределы
выделенной памяти.
    сохранение индексация в векторе как в кольцевом буфере выполняется благодаря операции % на
максимальный размер вектора - за основу взял пример в уроке спринта про реализацию очереди.

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
    Рассмотрим каждый метод более подробно.
    Для методов push_back и push_front есть проверка на выход из диапазона max_size.
-push_back() - сначала вычисляет индекс back_, а затем заполняет нужный элемент 
-push_front() - сначала заполняет нужный элемент по индексу front_, а затем обновляет front_.
    Для методов pop_back и pop_front() есть проверка на наличие элементов в деке.
-pop_back()- поскольку back_ указывает на сл. элемент для заполнения, то сначала вычисляем
индекс предыдущего элемента, а затем получаем значение и выводим.
-pop_front() - front_ указывает на последний добавленный элемент, поэтому сначала вычитываем
значение по текущему индексу, а затем актуализируем индекс front_.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
    Чтение данных от пользователя в цикле и их последовательная обработка будет занимать
O(N) - где N это кол-во операций над стеком, которые пользователь будет вводить, см. int command_num.
Потому что мы последовательно перебираем весь ввод в input.

    Непосредственно операции добавления и удаления элементов в стек стоят О(1).
Потому что мы по факту всегда только обращаемся к элементу массива по индексу,
который предварительно рассчитываем, а чтение или изменение данных в элементе массива по
заранее известному индексу стоят О(1).

    Таким образом результирующая сложность для данного решения, ввод данных их обработка и
добавление и удаление в/из стек будет стоить: O(1) + O(N) = O(N), то есть наихудшая сложность
из рассматриавемых.

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
    Поскольку в реализации дека у меня используется кольцевой буфер на основе вектора,
память для которого заранее алоцирована, то есть дополнительных операций алокаций,
реаллокаций и освобождений памяти не будет - это значит какой размер задашь, столько памяти и
выделиться - то есть O(N), где N - это размер дека (на основе вектора, то есть фактически размер вектора),
переданный пользователем, см. int deque_size.
*/

#include <iostream>
#include <vector>
#include <optional>

using namespace std;

class Deque {
public:
    Deque(int max_size)
        : max_size_{max_size}
        , front_{0}
        , back_{0}
        , size_{0}
    {
        deque.reserve(max_size);
    }

    int push_back(int value) {
        if (size_ == max_size_) {
            return -1;
        }
        deque[back_] = value;
        back_ = (back_ + 1) % max_size_;
        size_++;
        return 0;
    }

    optional<int> pop_back() {
        if (size_ == 0) {
            return nullopt;
        } else {
            back_ = (back_ - 1 + max_size_) % max_size_;
            size_--;
            return deque[back_];
        }
    }

    int push_front(int value) {
        if (size_ == max_size_) {
            return -1;
        }
        front_ = (front_ - 1 + max_size_) % max_size_;
        deque[front_] = value;
        size_++;
        return 0;
    }

    optional<int> pop_front() {
        if (size_ == 0) {
            return nullopt;
        } else {
            int tmp = front_;
            front_ = (front_ + 1 + max_size_) % max_size_;
            size_--;
            return deque[tmp];
        }
    }

private:
    vector<int> deque;
    int max_size_;
    int front_;
    int back_;
    int size_;
};

static inline int get_input() {
    int tmp;
    cin >> tmp;
    cin.ignore();
    return tmp;
}

static inline void print_optional_value(const optional<int>& value) {
    if (value.has_value()) {
        cout << value.value() << endl;
    } else {
        cout << "error" << endl;
    }
}

int main() {
    int command_num = get_input();
    int deque_size = get_input();
    Deque deq{deque_size};

    while (command_num) {
        string cmd;
        cin >> cmd;
        if (cmd == "push_back") {
            if (deq.push_back(get_input())) {
                cout << "error" << endl;
            }
        } else if (cmd == "pop_back") {
            print_optional_value(deq.pop_back());
        } else if (cmd == "push_front") {
            if (deq.push_front(get_input())) {
                cout << "error" << endl;
            }
        } else if (cmd == "pop_front") {
            print_optional_value(deq.pop_front());
        }
        command_num--;
    }

    return 0;
}
