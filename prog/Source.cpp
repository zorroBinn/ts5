#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <Windows.h>
using namespace std;

// ������� ��� ������ ������� ��������� �� �����
vector<vector<int>> read_matrix(ifstream& in) {
    int n; // ���������� ������ � �����
    in >> n;
    vector<vector<int>> matrix(n, vector<int>(n)); // ������� ���������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> matrix[i][j]; // ��������� ������� �������
        }
    }
    return matrix;
}

// ������� ��� ���������� ����������� ���� ����� ����� ��������� � �����
vector<int> find_shortest_path(const vector<vector<int>>& matrix, int start, int end) {
    int n = matrix.size(); // ���������� ������ � �����
    vector<int> dist(n, -1); // ������ ���������� �� ��������� ������� �� ���������
    vector<int> prev(n, -1); // ������ ���������� ������ � ���������� ����
    queue<int> q; // ������� ��� ������ ����� � ������
    q.push(start); // ��������� ��������� ������� � �������
    dist[start] = 0; // ���������� �� ��������� ������� �� ���� ����� ����
    while (!q.empty()) { // ���� ������� �� �����
        int v = q.front(); // ����� ������ ������� �� �������
        q.pop(); // ������� �� �� �������
        for (int u = 0; u < n; u++) { // ���������� ��� �������� �������
            if (matrix[v][u] == 1 && dist[u] == -1) { // ���� ���� ����� � ������� �� ��������
                q.push(u); // ��������� ������� � �������
                dist[u] = dist[v] + 1; // ��������� ���������� �� ���
                prev[u] = v; // ���������� ���������� ������� � ����
            }
        }
    }
    vector<int> path; // ������ ��� �������� ����������� ����
    if (dist[end] != -1) { // ���� ���������� ���� �� �������� �������
        int v = end; // �������� � �������� �������
        while (v != start) { // ���� �� ������ �� ���������
            path.push_back(v); // ��������� ������� � ����
            v = prev[v]; // ��������� � ���������� ������� � ����
        }
        path.push_back(start); // ��������� ��������� ������� � ����
        reverse(path.begin(), path.end()); // ������������� ���� � ���������� �������
    }
    return path;
}

// ������� ��� ������ ���������� �� ����� � � ����
void print_result(const vector<vector<int>>& matrix, const vector<int>& path, ofstream& out) {
    int n = matrix.size(); // ���������� ������ � �����
    cout << "������� ���������:" << endl;
    out << "������� ���������:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
            out << matrix[i][j] << " ";
        }
        cout << endl;
        out << endl;
    }
    cout << "���������� ����:" << endl;
    out << "���������� ����:" << endl;
    if (path.empty()) { // ���� ���� �� ����������
        cout << "��� ����" << endl;
        out << "��� ����" << endl;
    }
    else { // ���� ���� ����������
        for (int v : path) { // ���������� ��� ������� � ����
            cout << v + 1 << " "; // ������� ������� �� ����� (� ������ ��������� � �������)
            out << v + 1 << " "; // ���������� ������� � ����
        }
        cout << endl;
        out << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ifstream in("input.dat"); // ��������� ���� ��� ������
    if (!in) { // ���� ���� �� ������
        cerr << "������ ��� �������� ����� input.dat" << endl; // ������� ��������� �� ������
        return 1; // ��������� ��������� � ����� ������
    }
    vector<vector<int>> matrix = read_matrix(in); // ������ ������� ��������� �� �����
    int start, end; // ��������� � �������� �������
    in >> start >> end; // ��������� �� �� �����
    start--; end--; // ��������� �� �� ������� ��� �������� ������ � ���������
    in.close(); // ��������� ���� ��� ������
    vector<int> path = find_shortest_path(matrix, start, end); // ������� ���������� ���� ����� ���������
    ofstream out("output.dat"); // ��������� ���� ��� ������
    if (!out) { // ���� ���� �� ������
        cerr << "������ ��� �������� ����� output.dat" << endl; // ������� ��������� �� ������
        return 2; // ��������� ��������� � ����� ������
    }
    print_result(matrix, path, out); // ������� ��������� �� ����� � � ����
    out.close(); // ��������� ���� ��� ������
    return 0; // ��������� ��������� �������
}