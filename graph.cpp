#include <iostream>

using namespace std;
int main() {
	int vertex, edges;
	cout << "enter number vertex" << endl;
	cin >> vertex;
	cout << "enter number edges" << endl;
	cin >> edges;
	int** matrix = new int* [edges];
	for (int i = 0; i < edges; ++i) {
		matrix[i] = new int[vertex];
	}
	for (int i = 0; i < vertex; ++i) {
		for (int j = 0; j < edges; ++j) {
			matrix[i][j] = 0;
		}
	}

	cout << "enter begin and end edges:" << endl << endl;
	for (int i = 0; i < edges; ++i)
	{
		int x, y = 0;
		cout << "edges " << i + 1 << ":" << endl;
		cout << "begin=";
		cin >> x;
		cout << "end=";
		cin >> y;
		cout << endl;
		matrix[x - 1][i] = 1;
		matrix[y - 1][i] = 1; //-1 для ориентированного графа
	}
	for (int i = 0; i < vertex; ++i) {
		for (int j = 0; j < edges; ++j)
		{
			cout  << matrix[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}


