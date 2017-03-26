// 09-512 KG

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

class yakob
{
private:
	const double E;
	int n;
	double **A, *b, *x, *del, *x0;
	inline int find_max_elem_in_row(int i); //Возвращает номер строки с максимальным элементом на i -ом столбце
	inline bool diag_check(); //a[i][i] не должен равняться 0
	bool test_for_ans(); //Проверка Х ов
	double abs(double x); //Модуль числа
public:
	yakob() : n(0), A(NULL), b(NULL), x(NULL), del(NULL), x0(NULL), E(0.0) { A = new double *[n]; b = new double[n]; del = new double[n]; x0 = new double[n]; }
	yakob(int k, int e = 0.0001) : n(k), E(e), A(NULL), b(NULL), x(NULL), x0(NULL), del(NULL)
	{
		A = new double *[n]; b = new double[n]; x = new double[n]; del = new double[n]; x0 = new double[n];
		for (int i(0); i < n; i++)
			x0[i] = 0;
	}
	~yakob() { delete[] * A; delete[]b; }

	inline void ifend(); //Проверка на заполнение размера матрицы
	bool prevelance(); //Диагональное преобладание: если |a[i][i]| > Sum(a[i][j]) (i != j) 
	void create(); //Создание матрицы
	void show(); //Вывод 
	void alpha_meth(); // преобразует Ах = b => x = ax + b;
	void approximation(); // Массив X приближений;
	void method(); //Метод простого итерационного приближения (Метод Якоби);
	void reshuffle(); //Перестановка строк таким образом, чтобы на диагонали стояли наибольшие по модулю к/ф матрицы;
	void answer();
};

inline void yakob::ifend()
{
	if (n == 0)
	{
		cout << "The size of matrix not found";
		system("pause");
		exit(0);
	}
}

inline bool yakob::diag_check()
{
	bool p = true;
	for (int i(0); i < n && p; i++)
	{
		if (A[i][i] == 0) p = false;
	}
	return p;
}

void yakob::create()
{
	yakob::ifend();
	ifstream in("input.txt");
	if (!in) exit(0);
	for (int i(0); i < n; i++)
	{
		A[i] = new double[n];
	}
	for (int i(0); i < n; i++)
	{
		for (int j(0); j < n; j++)
			in >> A[i][j];
		in >> b[i];
	}
}

void yakob::show()
{
	yakob::ifend();
	cout << endl;
	for (int i(0); i < n; i++)
	{
		for (int j(0); j < n; j++)
		{
			cout << A[i][j] << " * x" << j + 1;
			if (j == n - 1)
				cout << " = " << b[i];
			else
				cout << " + ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	yakob obj(3);
	obj.create();
	cout << "Entered matrix:" << endl;
	obj.show();
	obj.method();

	system("pause");
	return 0;
}

void yakob::method()
{
	if (!yakob::prevelance())
		yakob::reshuffle();
	if (!yakob::diag_check()) exit(-1);

	cout << "reshuffle: " << endl;
	show();
	cout << endl;

	yakob::alpha_meth();
	ofstream out("output.txt");
	cout << "Begin aproxiation: X = ( ";
	out << "Begin aproxiation: X = ( ";
	for (int i(0); i < n; i++)
	{
		x[i] = b[i];
		cout << x[i];
		out << x[i];
		if (i != n - 1) { cout << ", "; out << ", "; }
		else { cout << " ); "; out << " );"; }
	}
	out << endl;
	cout << endl;

	int i = 1;
	while (!yakob::test_for_ans())
	{
		yakob::approximation();
		i++;
		if (i > 100000)
		{
			cout << endl << endl << "ERROR_ITERATION #" << --i << endl << endl << "My memory is out. I can't count this sh*t, sorry..." << endl << "But i can show what i have)" << endl;
			break;
		}
	}
	yakob::approximation();

	yakob::answer();
}
bool yakob::prevelance()
{
	bool p(true);
	for (int i(0); i < n && p; i++)
	{
		double max = A[i][i], sum(0);
		for (int j(0); j < n; j++)
		{
			sum += A[i][j];
		}
		p = (sum > max) ? false : true;
	}
	return p;
}
void yakob::reshuffle()
{
	int *counter = new int[n];
	for (int i(0); i < n; i++)
	{
		counter[i] = yakob::find_max_elem_in_row(i);
	}

	double **E = new double *[n];
	double *k = new double[n];
	for (int i(0); i < n; i++)
	{
		E[i] = new double[n];
	}
	for (int i(0); i < n; i++)
	{
		if (i != counter[i])
		{
			for (int j(0); j < n; j++)
			{
				E[i][j] = A[counter[i]][j];
			}
			k[i] = b[counter[i]];
		}
	}
	for (int i(0); i < n; i++)
	{
		if (i != counter[i])
		{
			for (int j(0); j < n; j++)
			{
				A[i][j] = E[i][j];
			}
			b[i] = k[i];
		}
	}
	delete[]counter;
	delete[]E;
	delete[]k;
}
void yakob::alpha_meth()
{
	for (int i(0); i < n; i++)
	{
		del[i] = A[i][i];
		for (int j(0); j < n; j++)
		{
			A[i][j] /= (-1) * del[i];
		}
		b[i] /= del[i];
		A[i][i] = 0;
		cout << endl << "step #" << i << endl;
		yakob::show();
		cout << endl;
	}
}
bool yakob::test_for_ans()
{
	double norm;
	double max = abs(x0[0] - x[0]);

	for (int i(1); i < n; i++)
	{
		if (norm = abs(x0[i] - x[i]) > max) max = norm;
	}
	if (max > E) return false;
	return true;
}
void yakob::approximation()
{
	for (int i(0); i < n; i++)
	{
		x0[i] = x[i];
	}

	double *sum = new double[n];
	for (int i(0); i < n; i++)
	{
		sum[i] = 0;
		for (int j(0); j < n; j++)
		{
			sum[i] += A[i][j] * x[j];
		}
	}
	for (int i(0); i < n; i++)
	{
		x[i] = b[i] + sum[i];
	}
	delete[] sum;
}

inline int yakob::find_max_elem_in_row(int i)
{
	double max = A[i][i];
	int ret = i;
	for (int j(0); j < n; j++)
	{
		if (A[j][i] > max) { max = A[j][i]; ret = j; }
	}
	return ret;
}

void yakob::answer()
{
	ofstream out("output.txt");
	cout << endl << "Close aproxiation: X = ( ";
	out << endl << "Close aproxiation: X = ( ";
	for (int i(0); i < n; i++)
	{
		cout << x[i]; out << x[i];
		if (i != n - 1) { cout << ", "; out << ", "; }
		else { cout << " ); ";  out << " );"; }
	}
	out << endl;
	cout << endl;
}

double yakob::abs(double x)
{
	return (x >= 0) ? x : -x;
}