#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

void print_state(int generation, int counter, int** current_array); //вывод на консоль текущего состояния
bool set_next_generation(int* generation, int*counter, int** current_array); //генерация следующего поколения
int count_alive_orbits(int** cells_array, int row, int col); //посчитать количество соседних живых клеток


int rows_num = 0;
int cols_num = 0;

int main()
{
	setlocale(LC_ALL, "Russian");
	std::ifstream fstart("start.txt");
	std::string instr;
	bool state_changed = true; //флаг того, что хоть одна клетка поменяла свое состояние
	int clear_console = -1; //как выводить на консоль

	
	while ((clear_console < 0) || (clear_console > 2))
	{
		std::cout << "Очищать консоль между выводами состояний?\n";
		std::cout << "0 - не очищать консоль\n";
		std::cout << "1 - очищать консоль, выводить через каждые 3 секунды\n";
		std::cout << "2 - очищать консоль, выводить по нажатию клавиши\n\n\n";
		std::cin >> clear_console;
	}

	std::cout << "\n";

	int generation = 1;
	int alive_counter; //кол-во живых клеток в поколении

	if (!(fstart.is_open())) //если не удалось открыть файл
	{
		std::cout << "Файл не существует";
		return 0;
	}

	if (!fstart.eof())  //проверка на конец файла
	{
		fstart >> instr; //считать следующее слово из файла
		rows_num = std::stoi(instr); //преобразовать в целое число и сохранить в переменную - количество строк
	}

	if (!fstart.eof()) //проверка на конец файла
	{
		fstart >> instr; //считать следующее слово из файла
		cols_num = std::stoi(instr); //преобразовать в целое число и сохранить в переменную - количество столбцов
	}


	if ((rows_num <= 0) || (cols_num <= 0)) //кол-во строк и столбцов должно быть больше 0
	{
		std::cout << "Ошибочное количество строк или столбцов";
		fstart.close();
		return 0;
	}

	int** int_array = new int* [rows_num]; //создать массив указателей
	for (int i = 0; i < rows_num; ++i)
	{
		int_array[i] = new int[cols_num](); //создать массивы чисел, заполненные нулями
	}


	//заполнить живые клетки в стартовом массиве - информация из файла
	int alive_row;
	int alive_col;
	
	alive_counter = 0;
	do
	{
		 alive_row = -1;
		 alive_col = -1;
		 if (!(fstart.eof()))
		 {
			 fstart >> instr; //считать следующее слово из файла - номер строки
			 alive_row = std::stoi(instr);
		 }
		

		 if (!(fstart.eof()))
		 {
			 fstart >> instr; //считать следующее слово из файла - номер строки
			 alive_col = std::stoi(instr);
		 }
		

		 if ((alive_row >= 0) && (alive_col >= 0))
		 {
			 int_array[alive_row][alive_col] = 1;
			 ++alive_counter;
			
		 }

	} while (!(fstart.eof()));


	print_state(generation, alive_counter, int_array); 


	if (clear_console)
	{
		char c;
		
		switch (clear_console)
		{
		case 1:
			sleep(3);
			std::system("clear");
			break;
		case 2:
			std::cin >> c;
			std::system("clear");
			break;
		}
	}

	while (state_changed && (alive_counter > 0))
	{
		state_changed = set_next_generation(&generation, &alive_counter, int_array);
		print_state(generation, alive_counter, int_array);
    }

	
	if (alive_counter == 0)
	{
		std::cout << "All cells are dead. Game over.";
	}
	else if (!state_changed)
		std::cout << "The world has stagnated. Game over.";


	for (int i = 0; i < rows_num; ++i)
	{
		delete[] int_array[i];
	}
	delete[] int_array;
	fstart.close();

	return 0;
}

//вывод на консоль текущего состояния
void print_state(int generation, int counter, int** current_array)
{
	if ((rows_num <= 0) || (cols_num <= 0))
	{
		return;
	}

	for (int i = 0; i < rows_num; ++i)
	{
		for (int j = 0; j < cols_num; ++j)
		{
			if (current_array[i][j] > 0)
			{
				std::cout << "* ";
			}
			else
			{
				std::cout << "- ";
			}		
			
		}
		std::cout << "\n";		
	}
	std::cout << "Generation: " << generation << ". Alive cells: " << counter << "\n\n";

	//std::cout << "\n\n\n";
}

//генерация следующего поколения
bool set_next_generation(int* generation, int* counter, int** current_array)
{
	int result = false;
	++(*generation);
	*counter = 0;
	int cell_alive_orbits;

	int** next_array = new int* [rows_num]; //массив next_array для хранения следующего поколения
	for (int i = 0; i < rows_num; ++i)
		next_array[i] = new int[cols_num]();

	for (int i = 0; i<rows_num; ++i)
		for (int j = 0; j < cols_num; ++j)
		{
			cell_alive_orbits = count_alive_orbits(current_array, i, j); //посчитать количество живых вокруг клетки
			if (current_array[i][j] && 1)  //если клетка живая
			{
				next_array[i][j] = ((cell_alive_orbits == 2) || (cell_alive_orbits == 3)); //нужно 2 или 3 живых вокруг для продолжения жизни
			}
			else //если клетка мертвая
			{
				next_array[i][j] = (cell_alive_orbits == 3); //если рядом ровно 3 живых, клетка становится жива
			}

			*counter += next_array[i][j];
			result = result || (next_array[i][j] != current_array[i][j]);
		}
	
	for (int i = 0; i<rows_num; ++i)
		for (int j = 0; j < cols_num; ++j)
		{
			current_array[i][j] = next_array[i][j];
		}

	for (int i = 0; i < rows_num; ++i)
	{
		delete[] next_array[i];
	}
	delete[] next_array;

	return result;
}

//посчитать количество соседних живых клеток
int count_alive_orbits(int** cells_array, int row, int col)
{
	int orbits_counter = 0;
	int max_row = rows_num - 1; 
	int max_col = cols_num - 1;

	if ((row < 0) || (row > max_row) || (col < 0) || col > max_col)
	{
		return  orbits_counter;
	}
		
	orbits_counter += (row > 0) && cells_array[row - 1][col];  //клетка выше 
	orbits_counter += (row < max_row) && cells_array[row + 1][col]; //клетка ниже
	orbits_counter += (col > 0) && cells_array[row][col-1]; //клетка слева
	orbits_counter += (col < max_col) && cells_array[row][col + 1]; //клетка справа
	orbits_counter += (row > 0) && (col > 0) && cells_array[row - 1][col - 1];  //клетка выше слева
	orbits_counter += (row < max_row) && (col > 0) && cells_array[row + 1][col - 1];  //клетка ниже слева
	orbits_counter += (row < max_row) && (col < max_col) && cells_array[row + 1][col + 1]; //клетка справа внизу
	orbits_counter += (row > 0) && (col < max_col) && cells_array[row - 1][col + 1]; //клетка справа вверху
	
	return orbits_counter;

}