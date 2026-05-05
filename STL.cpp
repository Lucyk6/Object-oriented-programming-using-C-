#include <iostream>  // Подключаем библиотеку для работы с вводом/выводом (cout, cin)
#include <vector>   // Подключаем библиотеку для работы с вектором (std::vector)
#include <algorithm> // Подключаем библиотеку алгоритмов STL (find, min_element, max_element, count, reverse)

int main() {
    setlocale(LC_ALL, "Russian");

    // Создаём вектор целых чисел и инициализируем его значениями
    std::vector<int> vec = { 5, 2, 8, 2, 1, 9, 2 };

    // Задаём целевое число для поиска
    int target = 8;

    // Задаём число, которое будем подсчитывать в векторе
    int X = 2;

    // 1. Вывод элементов вектора двумя способами
    std::cout << "1. Вывод элементов:" << std::endl;

    std::cout << "Через итератор: ";
    // Цикл с использованием итераторов:
    // auto it = vec.begin() — создаём итератор, указывающий на первый элемент вектора
    // it != vec.end() — условие продолжения цикла: пока итератор не достиг конца вектора
    // ++it — перемещаем итератор к следующему элементу
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";  // *it — разыменование итератора (получаем значение элемента)

    std::cout << std::endl << "Через range-based for: ";
    // Range-based for — упрощённый цикл для перебора всех элементов контейнера:
    // const auto& e — создаём константную ссылку на текущий элемент (чтобы избежать копирования)
    // : vec — указываем контейнер, который перебираем
    for (const auto& e : vec)
        std::cout << e << " ";
    std::cout << std::endl << std::endl;

    // 2. Поиск элемента с помощью std::find
    std::cout << "2. Поиск элемента " << target << ": ";
    // std::find ищет первое вхождение target в диапазоне [vec.begin(), vec.end())
    // Возвращает итератор на найденный элемент или vec.end(), если элемент не найден
    auto found = std::find(vec.begin(), vec.end(), target);

    // Проверяем результат поиска: если итератор не равен vec.end(), значит элемент найден
    std::cout << (found != vec.end() ? "найдено" : "не найдено") << std::endl << std::endl;

    // 3. Поиск минимального и максимального элементов
    // std::min_element находит итератор на минимальный элемент в диапазоне
    auto min_el = std::min_element(vec.begin(), vec.end());

    // std::max_element находит итератор на максимальный элемент в диапазоне
    auto max_el = std::max_element(vec.begin(), vec.end());

    // Выводим значения, разыменовывая итераторы (*min_el, *max_el)
    std::cout << "3. Минимум: " << *min_el << ", максимум: " << *max_el << std::endl << std::endl;

    // 4. Подсчёт вхождений числа X в векторе
    // std::count подсчитывает, сколько раз X встречается в диапазоне [vec.begin(), vec.end())
    int cnt = std::count(vec.begin(), vec.end(), X);

    // Выводим результат подсчёта
    std::cout << "4. Число " << X << " встречается " << cnt << " раз(а)" << std::endl << std::endl;

    // 5. Разворот вектора с помощью std::reverse
    std::cout << "5. До разворота: ";
    // Выводим вектор до разворота с помощью range-based for
    for (const auto& e : vec)
        std::cout << e << " ";

    // std::reverse разворачивает элементы вектора в диапазоне [vec.begin(), vec.end())
    // Работает «на месте» — изменяет исходный вектор
    std::reverse(vec.begin(), vec.end());

    std::cout << std::endl << "После разворота: ";
    // Выводим вектор после разворота
    for (const auto& e : vec)
        std::cout << e << " ";
    std::cout << std::endl;

    return 0;  
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    //6
    vector<int> v = { 5,1,9,3 };

    sort(v.begin(), v.end(), [](int a, int b)
        {
            return a > b;
        });

    for (int x : v)
        cout << x << " ";

    sort(v.begin(), v.end(), [](int a, int b)
    {
            return a < b;
    });

    for (int x : v)
        cout << x << " ";
    return 0;
}
//7
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = { 1, 2, 3, 2, 4, 2, 5 };
    int X = 2;
    bool found_once = false;

    for (auto it = vec.begin(); it != vec.end(); ) {
        if (*it == X) {
            if (!found_once) {
                found_once = true;
                ++it; // Переходим к следующему элементу
            }
            else {
                it = vec.erase(it); // erase возвращает следующий валидный итератор
            }
        }
        else {
            ++it;
        }
    }

    for (int num : vec) {
        std::cout << num << " ";
    }
    return 0;
}
//8
// Обычная функция — принимает число, возвращает true, если > 10
bool isGreaterThanTen(int n) {
    return n > 10;
}

int main() {
    std::vector<int> vec = { 5, 15, 3, 20, 8, 25, 12, 7,32,56,7,2, }; // Исходный вектор


    // std::remove_if перемещает элементы, удовлетворяющие условию (больше 10), в конец
    auto new_end = std::remove_if(vec.begin(), vec.end(), isGreaterThanTen);

    // Удаляем перемещённые элементы из вектора
    vec.erase(new_end, vec.end());


    // Вывод результата
    for (int num : vec) {
        std::cout << num << " "; // Выводим оставшиеся элементы
    }
    // Результат: 5 3 8
    return 0;
}
//9
int main() {
    std::vector<int> vec = { 3, 1, 4, 1, 5, 9, 2, 6, 5 }; // Вектор с дубликатами

    // Сортируем вектор — обязательное условие для работы std::unique
    std::sort(vec.begin(), vec.end());

    // std::unique перемещает дубликаты в конец вектора и возвращает итератор
    // на первый дублирующий элемент
    auto new_end = std::unique(vec.begin(), vec.end());

    // Удаляем дубликаты из вектора
    vec.erase(new_end, vec.end());

    // Вывод результата
    for (int num : vec) {
        std::cout << num << " "; // Выводим уникальные элементы
    }
    // Результат: 1 2 3 4 5 6 9
    return 0;
}
//10
#include <iostream>
#include <vector>
#include <algorithm>

// Класс-функтор: объект, который можно вызывать как функцию
struct SquareFunctor {
    int operator()(int n) const {
        return n * n;
    }
};

int main() {
    std::vector<int> original = {1, 2, 3, 4, 5};
    std::vector<int> squares(original.size());

    // Создаём временный объект функтора и передаём его
    std::transform(original.begin(), original.end(), squares.begin(), SquareFunctor());

    for (int num : squares) {
        std::cout << num << " ";
    }
    // Результат: 1 4 9 16 25
    return 0;
}
//Алгоритм	Назначение	Пример использования
//std::find	Поиск элемента	find(vec.begin(), vec.end(), target)
//std::count	Подсчёт вхождений	count(vec.begin(), vec.end(), X)
//std::min_element / std::max_element	Поиск минимума / максимума	min_element(vec.begin(), vec.end())
//std::reverse	Разворот вектора	reverse(vec.begin(), vec.end())
//std::sort	Сортировка	sort(vec.begin(), vec.end())
//std::remove_if	Перемещение элементов по условию	remove_if(..., isGreaterThanTen)
//std::unique	Удаление соседних дубликатов	unique(vec.begin(), vec.end())
//std::transform	Преобразование элементов	transform(..., SquareFunctor())
