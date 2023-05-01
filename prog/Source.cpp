#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <Windows.h>
using namespace std;

// Функция для чтения матрицы смежности из файла
vector<vector<int>> read_matrix(ifstream& in) {
    int n; // Количество вершин в графе
    in >> n;
    vector<vector<int>> matrix(n, vector<int>(n)); // Матрица смежности
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> matrix[i][j]; // Считываем элемент матрицы
        }
    }
    return matrix;
}

// Функция для нахождения кратчайшего пути между двумя вершинами в графе
vector<int> find_shortest_path(const vector<vector<int>>& matrix, int start, int end) {
    int n = matrix.size(); // Количество вершин в графе
    vector<int> dist(n, -1); // Массив расстояний от начальной вершины до остальных
    vector<int> prev(n, -1); // Массив предыдущих вершин в кратчайшем пути
    queue<int> q; // Очередь для обхода графа в ширину
    q.push(start); // Добавляем начальную вершину в очередь
    dist[start] = 0; // Расстояние от начальной вершины до себя равно нулю
    while (!q.empty()) { // Пока очередь не пуста
        int v = q.front(); // Берем первую вершину из очереди
        q.pop(); // Удаляем ее из очереди
        for (int u = 0; u < n; u++) { // Перебираем все соседние вершины
            if (matrix[v][u] == 1 && dist[u] == -1) { // Если есть ребро и вершина не посещена
                q.push(u); // Добавляем вершину в очередь
                dist[u] = dist[v] + 1; // Обновляем расстояние до нее
                prev[u] = v; // Запоминаем предыдущую вершину в пути
            }
        }
    }
    vector<int> path; // Вектор для хранения кратчайшего пути
    if (dist[end] != -1) { // Если существует путь до конечной вершины
        int v = end; // Начинаем с конечной вершины
        while (v != start) { // Пока не дойдем до начальной
            path.push_back(v); // Добавляем вершину в путь
            v = prev[v]; // Переходим к предыдущей вершине в пути
        }
        path.push_back(start); // Добавляем начальную вершину в путь
        reverse(path.begin(), path.end()); // Разворачиваем путь в правильном порядке
    }
    return path;
}

// Функция для вывода результата на экран и в файл
void print_result(const vector<vector<int>>& matrix, const vector<int>& path, ofstream& out) {
    int n = matrix.size(); // Количество вершин в графе
    cout << "Матрица смежности:" << endl;
    out << "Матрица смежности:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
            out << matrix[i][j] << " ";
        }
        cout << endl;
        out << endl;
    }
    cout << "Кратчайший путь:" << endl;
    out << "Кратчайший путь:" << endl;
    if (path.empty()) { // Если путь не существует
        cout << "Нет пути" << endl;
        out << "Нет пути" << endl;
    }
    else { // Если путь существует
        for (int v : path) { // Перебираем все вершины в пути
            cout << v + 1 << " "; // Выводим вершину на экран (с учетом нумерации с единицы)
            out << v + 1 << " "; // Записываем вершину в файл
        }
        cout << endl;
        out << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ifstream in("input.dat"); // Открываем файл для чтения
    if (!in) { // Если файл не открыт
        cerr << "Ошибка при открытии файла input.dat" << endl; // Выводим сообщение об ошибке
        return 1; // Завершаем программу с кодом ошибки
    }
    vector<vector<int>> matrix = read_matrix(in); // Читаем матрицу смежности из файла
    int start, end; // Начальная и конечная вершины
    in >> start >> end; // Считываем их из файла
    start--; end--; // Уменьшаем их на единицу для удобства работы с индексами
    in.close(); // Закрываем файл для чтения
    vector<int> path = find_shortest_path(matrix, start, end); // Находим кратчайший путь между вершинами
    ofstream out("output.dat"); // Открываем файл для записи
    if (!out) { // Если файл не открыт
        cerr << "Ошибка при открытии файла output.dat" << endl; // Выводим сообщение об ошибке
        return 2; // Завершаем программу с кодом ошибки
    }
    print_result(matrix, path, out); // Выводим результат на экран и в файл
    out.close(); // Закрываем файл для записи
    return 0; // Завершаем программу успешно
}