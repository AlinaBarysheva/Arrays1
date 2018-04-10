//Нам дан одномерный массив.Написать программы,которые выполняют следующие действия:
//1).Смещает данный массив на указанное пользователем число шагов и в указанное пользователем направление(вправо или влево),а освободившиеся "ячейки" в начале(в конце) запоняет нулями
//2).Смещает данный массив на указанное пользователем число шагов и в указанное пользователем направление(вправо или влево),а "упавшие" элементы из "хвоста"("носа") перемещает в начало(конец) этого же массива,не меняя при этом  порядок(гусеница)
//3).Смещает данный массив на указанное пользователем число шагов и в указанное пользователем направление(вправо или влево),а "упавшие" элементы из "хвоста"("носа") массива должны записаться в другой массив с той же стороны,не меняя при этом порядка.
// Обеспечить защиту от "дурака".

#include <iostream>
#include <random>

using namespace std;

/// Функция для вывод элементов массива в консоль.
void print(int *arr, int count) {
	cout << "[ ";
	for (int i = 0; i < count; ++i) {
		cout << arr[i] << ", ";
	}
	cout << "]";
}

void first(int *arr, int count, bool to_left, int step_count) {
	if (to_left) {
		for (int i = step_count; i < count; ++i) {
			arr[i - step_count] = arr[i];
		}

		for (int i = count - step_count; i < count; ++i) {
			arr[i] = 0;
		}
	} else {
		for (int i = count - step_count; i >= 0; --i) {
			arr[i + step_count] = arr[i];
		}

		for (int i = 0; i < step_count; ++i) {
			arr[i] = 0;
		}
	}
	
	print(arr, count);
}

void second(int *arr, int count, bool to_left, int step_count) {
	int *temp = new int[step_count];
	if (to_left) {		
		for (int i = 0; i < step_count; ++i) {
			temp[step_count - i - 1] = arr[i];
		}

		for (int i = count - 1; i >= step_count; --i) {
			arr[i - step_count] = arr[i];
		}

		for (int i = count - step_count; i < count; ++i) {
			arr[i] = temp[count - i - 1];
		}
	} else {
		for (int i = count - step_count; i < count; ++i) {
			temp[i - step_count] = arr[i];
		}

		for (int i = count - step_count; i >= 0; --i) {
			arr[i + step_count] = arr[i];
		}

		for (int i = 0; i < step_count; ++i) {
			arr[i] = temp[i];
		}
	}
	
	print(arr, count);
}

void third(int *arr, int count, bool to_left, int step_count) {
	int *temp = new int[step_count];
	if (to_left) {
		for (int i = 0; i < step_count; ++i) {
			temp[i] = arr[i];
		}

		for (int i = step_count; i < count; ++i) {
			arr[i - step_count] = arr[i];
		}

		for (int i = count - step_count; i < count; ++i) {
			arr[i] = 0;
		}
	}
	else {
		for (int i = count - step_count; i < count; ++i) {
			temp[i - count + step_count] = arr[i];
		}

		for (int i = count - step_count; i >= 0; --i) {
			arr[i + step_count] = arr[i];
		}

		for (int i = 0; i < step_count; ++i) {
			arr[i] = 0;
		}
	}
	
	print(arr, count);
	cout << endl;
	print(temp, step_count);
}

int main() {
	setlocale(LC_ALL, "Russian");

	int num;				                   // Номер задания.
	cout << "Выберите задание (от 1 до 3): ";
	cin >> num;

	int count;				                    // Размерность массива.
	cout << "Введите размерность массива: ";
	cin >> count;

	int step_count;				                     // Шаг.
	cout << "Введите шаг сдвига: ";
	cin >> step_count;
	
	char dir;				                    // Направление: r - право, l - лево.
	cout << "Выберите направление (r - право или l - лево): ";
	cin >> dir;

	// Сдвиг не должен быть отрицательным.
	if (step_count < 0) {                                     //Защита от "дурака"
		cout << "Ошибка." << endl;
		return 0;
	}
	
	// Направление может быть только вправо или влево.
	if (dir != 'r' && dir != 'l') {                          //Защита от "дурака"
		cout << "Ошибка." << endl;
		return 0;
	}
	
	// Всего три варианта задания.
	if (num < 1 && num > 3) {                                //Защита от "дурака"
		cout << "Ошибка." << endl;
		return 0;
	}

	int *arr = new int[count];	                                // Выделяем память под массив.

					                                // Заполнение массива случайными числами.
	default_random_engine generator;				// Генератор. Производит значения от 0..1
	uniform_int_distribution<int> distribution(0, 9);		// Равномерное распределение. Приводит значения 0..1 к указанному диапозону.
	for (int i = 0; i < count; ++i) {
		arr[i] = distribution(generator);			// Генерация случайного числа.
	}

	print(arr, count);
	cout << endl;
	
	// Если величина сдвига больше размерности массива, то берём остаток от деления.
	step_count %= count;
	
	bool to_left = dir == 'l' ? true : false;
	switch (num) {
	case 1:
		first(arr, count, to_left, step_count);
		break;
	case 2:
		second(arr, count, to_left, step_count);
		break;
	case 3:
		third(arr, count, to_left, step_count);
		break;
	default:
		break;
	}		

	cout << endl;
	system("pause");
	return 0;
}
