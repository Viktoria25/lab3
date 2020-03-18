#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main(void) 
	{
	int i = 0, j = 0;
	fstream fin;
	fin.open("23.csv", ios::in);

	vector<double> year;
	vector<vector<double> > temp(128, vector <double>(13));
	string line, word;

	getline(fin, line);

	while (!fin.eof()) 
		{
		getline(fin, line);
		stringstream s(line);

		while (getline(s, word, ',')) 
			{
			if (stod(word) < 1000.) 
				{
				temp[i][j] = stod(word);
				j++;
				}else year.push_back(stoi(word));
			}
		i++;
		j = 0;
		}	
		
	fin.close();

	int mounth, start_year;
	cout << "Enter number month: ";
	cin >> mounth;
	cout << "Enter start year from " << year[0] << " to " << year[127] << ": ";
	cin >> start_year;

	vector<double> arr0;
	vector<double> arr;
	int p = 0;
	int n = 0;
	int m;
	for (i = start_year - year[0]; i < 183; i++) 
		{
		if (temp[i][mounth - 1] != 999.9) 
			{
			arr0.push_back(i + year[0]);
			arr.push_back(temp[i][mounth - 1]);
			n++;
			}
		if (arr0.size() == 13)
			break;
		}

	double* a = new double[12];
	double* b = new double[12];
	double* c = new double[13];
	double* d = new double[12];

	double* h = new double[12];
	for (i = 0; i < 12; i++) h[i] = arr0[i + 1] - arr0[i];

	double** A = new double* [11];
	for (i = 0; i < 11; i++) A[i] = new double[11];

	for (i = 1; i < 10; i++) 
		{
		j = i - 1;
		A[i][j] = h[i];
		A[i][j + 1] = 2 * (h[i] + h[i + 1]);
		A[i][j + 2] = h[i + 1];
		}
		
	A[0][0] = 2 * (h[0] + h[1]);
	A[0][1] = h[1];
	A[10][9] = h[9];
	A[10][10] = 2 * (h[9] + h[10]);

	double** F = new double* [11];
	for (i = 0; i < 11; i++) F[i] = new double[1];
	for (i = 1; i < 12; i++) F[i - 1][0] = 3 * ((arr[i + 1] - arr[i]) / h[i] - (arr[i] - arr[i - 1]) / h[i - 1]);

	for (i = 1; i < 11; i++) 
		{
		F[i][0] -= (A[i][i - 1] * F[i - 1][0] / A[i - 1][i - 1]);
		A[i][i] -= (A[i][i - 1] * A[i - 1][i] / A[i - 1][i - 1]);
		}

	for (i = 1; i < 11; i++) 
		{
		F[i][0] -= (A[i][i - 1] * F[i - 1][0] / A[i - 1][i - 1]);
		A[i][i] -= (A[i][i - 1] * A[i - 1][i] / A[i - 1][i - 1]);
		}

	c[11] = F[10][0] / A[10][10];
	for (i = 9; i >= 0; i--) c[i + 1] = (F[i][0] - A[i][i + 1] * c[i + 2]) / A[i][i];
	
	c[0] = 0;
	c[12] = 0;

	for (i = 0; i < 12; i++) 
		{
		a[i] = arr[i];
		b[i] = (arr[i + 1] - arr[i]) / h[i] - c[i] * h[i] - (c[i + 1] - c[i]) * h[i] / 3;
		d[i] = (c[i + 1] - c[i]) / (3 * h[i]);
		}
	
	fin.open("coef.txt", ios::out);
	if (fin.is_open()) for (i = 0; i < 12; i++) fin << a[i] << " " << b[i] << " " << c[i] << " " << d[i] << endl;
		
	fin.close();
	fin.open("x.txt", ios::out);
	if (fin.is_open()) for (i = 0; i < 12; i++) fin << arr0[i] << " " << arr[i] << endl;
	
	fin.close();
	
	delete[] a;
	delete[] b;
	delete[] c;
	delete[] d;
	delete[] h;
	
	for (int i = 0; i < 11; i++) 
		{
		delete[] A[i];
		delete[] F[i];
		}
		
	delete[] A;
	delete[] F;
	
	return 0;
}
