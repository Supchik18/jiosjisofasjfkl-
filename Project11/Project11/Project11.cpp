#include <iostream>
#include <thread>
#include <vector>

// Класс MergeSort для реализации алгоритма сортировки слиянием
class MergeSort {
public:
    // Метод merge для объединения двух отсортированных частей массива
    void merge(std::vector<int>& arr, int left, int mid, int right) {
        // Размеры левой и правой частей массива
        int n1 = mid - left + 1;
        int n2 = right - mid;

        // Создаем временные массивы для левой и правой частей
        std::vector<int> leftArr(n1);
        std::vector<int> rightArr(n2);

        // Копируем элементы из оригинального массива в временные массивы
        for (int i = 0; i < n1; i++)
            leftArr[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            rightArr[j] = arr[mid + 1 + j];

        // Индексы для временных массивов и оригинального массива
        int i = 0, j = 0, k = left;

        // Объединяем элементы из временных массивов в оригинальный массив
        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            }
            else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }

        // Добавляем оставшиеся элементы из левой части
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }

        // Добавляем оставшиеся элементы из правой части
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }

    // Метод sort для рекурсивной сортировки массива
    void sort(std::vector<int>& arr, int left, int right) {
        // Если левый индекс меньше правого, то продолжаем сортировку
        if (left < right) {
            // Нахождение середины массива
            int mid = left + (right - left) / 2;

            // Рекурсивная сортировка левой и правой частей
            sort(arr, left, mid);
            sort(arr, mid + 1, right);

            // Объединение отсортированных частей
            merge(arr, left, mid, right);
        }
    }

    // Метод sort для сортировки всего массива
    void sort(std::vector<int>& arr) {
        sort(arr, 0, arr.size() - 1);
    }
};

int main() {
    // Размер массива
    int n = 10;

    // Создаем массив целых чисел
    std::vector<int> arr(n);

    // Ввод элементов массива от пользователя
    std::cout << "Enter " << n << " numbers: ";
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];

    // Создаем объект класса MergeSort
    MergeSort mergeSort;

    // Создаем анонимную функцию для сортировки массива в отдельном потоке
    std::thread mergeSortThread([&mergeSort, &arr]() {
        mergeSort.sort(arr);
        });

    // Ожидаем завершения сортировки в дочернем потоке
    mergeSortThread.join();

    // Вывод отсортированного массива
    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return 0;
}