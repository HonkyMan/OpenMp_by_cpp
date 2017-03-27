Объяснение закомментированных методов:

const double E; //Точность рассчета корней матрицы
	int n; //Размерность матрицы
	inline int find_max_elem_in_row(int i); //Возвращает номер строки с максимальным элементом на i -ом столбце
	inline bool diag_check(); //a[i][i] не должен равняться 0
	bool test_for_ans(); //Проверка Х ов
	double abs(double x); //Модуль числа
	
	/////////////Конструкторы
	yakob() : n(0), A(NULL), b(NULL), x(NULL), del(NULL), x0(NULL), E(0.0) { A = new double *[n]; b = new double[n]; del = new double[n]; x0 = new double[n]; }
	yakob(int k, int e = 0.0001) : n(k), E(e), A(NULL), b(NULL), x(NULL), x0(NULL), del(NULL)
	{
		A = new double *[n]; b = new double[n]; x = new double[n]; del = new double[n]; x0 = new double[n];
		for (int i(0); i < n; i++)
			x0[i] = 0;
	}
	~yakob() { delete[] * A; delete[]b; }
	//////////////~Деструкторы
	
	inline void ifend(); //Проверка на заполнение размера матрицы
	bool prevelance(); //Диагональное преобладание: если |a[i][i]| > Sum(a[i][j]) (i != j) 
	void create(); //Создание матрицы
	void show(); //Вывод 
	void alpha_meth(); // преобразует Ах = b => x = ax + b;
	void approximation(); // Массив X приближений;
	void method(); //Метод простого итерационного приближения (Метод Якоби);
	void reshuffle(); //Перестановка строк таким образом, чтобы на диагонали стояли наибольшие по модулю к/ф матрицы;
	void answer(); //Конечное приближение вектора (Ответ)