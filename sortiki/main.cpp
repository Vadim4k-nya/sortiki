#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>

// структура для хранения данных сортироваки
struct SortResult {
    long long comparisons = 0;
    long long swaps = 0;
};

// генератор случайных массивов
std::vector<int> generateRandomVector(int size) {
    std::vector<int> arr(size);
    srand(time(0));
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

// Функция для сортировки пузырьком
SortResult bubbleSort(std::vector<int>& arr) {
    SortResult result;
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            result.comparisons++;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
                result.swaps++;
            }
        }
        if (!swapped) break;
    }
    return result;
}

// Функция для сортировки вставками
SortResult insertionSort(std::vector<int>& arr) {
    SortResult result;
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            result.comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                result.swaps++;
                j = j - 1;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
    }
    return result;
}

// Функция для сортировки выбором
SortResult selectionSort(std::vector<int>& arr) {
    SortResult result;
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            result.comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(arr[min_idx], arr[i]);
            result.swaps++;
        }
    }
    return result;
}

void printHeader(int size) {
    std::cout << "================================================================" << std::endl;
    std::cout << "                  ТЕСТИРОВАНИЕ ДЛЯ N = " << size << std::endl;
    std::cout << "================================================================" << std::endl;
    std::cout << "  "
        << std::setw(20) << std::left << "Алгоритм"
        << std::setw(20) << std::right << "Сравнения"
        << std::setw(20) << std::right << "Перестановки" << std::endl;
    std::cout << std::string(64, '-') << std::endl;
}

void printResult(const std::string& name, const SortResult& result) {
    std::cout << "  "
        << std::setw(20) << std::left << name
        << std::setw(20) << std::right << result.comparisons
        << std::setw(20) << std::right << result.swaps << std::endl;
}

void runTest(int size) {
    std::vector<int> original_data = generateRandomVector(size);

    // 1. Тест Сортировки Пузырьком
    std::vector<int> data_bubble = original_data;
    SortResult res_bubble = bubbleSort(data_bubble);

    // 2. Тест Сортировки Вставками
    std::vector<int> data_insertion = original_data;
    SortResult res_insertion = insertionSort(data_insertion);

    // 3. Тест Сортировки Выбором
    std::vector<int> data_selection = original_data;
    SortResult res_selection = selectionSort(data_selection);

    // Вывод результатов
    printHeader(size);
    printResult("Пузырьком", res_bubble);
    printResult("Вставками", res_insertion);
    printResult("Выбором", res_selection);
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    runTest(10);
    std::cout << std::endl;
    runTest(100);
    std::cout << std::endl;
    runTest(1000);
    std::cout << std::endl;
    return 0;
}
