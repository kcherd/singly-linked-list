#include "Header.h"

int menu(bool j)
{
	int variant;
	if (j == 0)
	{
		cout << "* * * * * * * Список* * * * * * *" << endl;
		cout << "Выберите действие:" << endl;
		cout << "1. Опрос размера списка\n"
			<< "2. Очистка списка\n"
			<< "3. Проверка списка на пустоту\n"
			<< "4. Опрос наличия заданного значения\n"
			<< "5. Чтение значения с заданным номером в списке\n"
			<< "6. Изменение значения с заданным номером в списке\n"
			<< "7. Получение позиции в списке для заданного значения\n"
			<< "8. Включение нового значения\n"
			<< "9. Включение нового значения в позицию с заданным номером\n"
			<< "10. Удаление заданного значения из списка\n"
			<< "11. Удаление значения из позиции с заданным номером\n"
			<< "12. Запрос итератора произвольного доступа begin()\n"
			<< "13. Запрос «неустановленного» итератора end()\n"
			<< "14. Доступ к значению элемента через итератор по чтению\n"
			<< "15. Доступ к значению элемента через итератор по записи\n"
			<< "16. Операция ++ для итератора\n"
			<< "17. Сравнение текущего итератора с end (равенство)\n"
			<< "18. Сравнение текущего итератора с end (неравенство)\n"
			<< "0. Вывод списка на экран\n"
			<< "19. Выход из программы\n" << endl;
	}
	cout << " >>> ";
	cin >> variant;
	return variant;
}

int main()
{
	setlocale(LC_ALL, "rus");
	List<int> arr;
	List<int>::Iterator iter, iter2;
	int variant = menu(0);
	bool temp;
	int pos, val, num;

	while (variant != 19)
	{
		switch (variant)
		{
		case 0:
			cout << "Вывод списка на экран" << endl;
			arr.print();
			break;
		case 1:
			cout << "Опрос размера списка" << endl;
			cout << arr.getSize() << endl;
			break;
		case 2:
			cout << "Очистка списка" << endl;
			arr.clear();
			break;
		case 3:
			cout << "Проверка списка на пустоту" << endl;
			cout << arr.isEmpty() << endl;
			break;
		case 4:
			cout << "Опрос наличия заданного значения" << endl;
				cout << "Введите значение: ";
			cin >> val;
			cout << arr.contains(val) << endl;
			cout << "Количество просмотренных узлов: " << arr.getViewedCount() << endl;
			break;
		case 5:
			cout << "Чтение значения с заданным номером в списке" << endl;
			cout << "Введите номер: ";
			cin >> pos;
			try
			{
				cout << arr.get(pos) << endl;
			}
			catch (ArrayException &exception)
			{
				std::cerr << "An array exception occurred (" << exception.what() << ")\n";
			}
			catch (std::exception &exception)
			{
				std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
			}
			cout << "Количество просмотренных узлов: " << arr.getViewedCount() << endl;
			break;
		case 6:
			cout << "Изменение значения с заданным номером в списке" << endl;
			cout << "Введите номер: ";
			cin >> pos;
			cout << "Введите значение: ";
			cin >> val;
			cout << arr.replace(val, pos) << endl;
			cout << "Количество просмотренных узлов: " << arr.getViewedCount() << endl;
			break;
		case 7:
			cout << "Получение позиции в списке для заданного значения" << endl;
			cout << "Введите значение: ";
			cin >> val;
			try
			{
				cout << arr.indexOf(val) << endl;
			}
			catch (ArrayException &exception)
			{
				std::cerr << "An array exception occurred (" << exception.what() << ")\n";
			}
			catch (std::exception &exception)
			{
				std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
			}
			cout << "Количество просмотренных узлов: " << arr.getViewedCount() << endl;
			break;
		case 8:
			cout << "Включение нового значения" << endl;
			cout << "Введите значение: ";
			cin >> val;
			cout << arr.add(val) << endl;
			cout << "Количество просмотренных узлов: " << arr.getViewedCount() << endl;
			break;
		case 9:
			cout << "Включение нового значения в позицию с заданным номером" << endl;
			cout << "Введите значение: ";
			cin >> val;
			cout << "Введите номер: ";
			cin >> pos;
			cout << arr.add_pos(val, pos);
			cout << "Количество просмотренных узлов: " << arr.getViewedCount() << endl;
			break;
		case 10:
			cout << "Удаление заданного значения из списка" << endl;
			cout << "Введите значение: ";
			cin >> val;
			cout << arr.remove(val) << endl;
			cout << "Количество просмотренных узлов: " << arr.getViewedCount() << endl;
			break;
		case 11:
			cout << "Удаление значения из позиции с заданным номером" << endl;
			cout << "Введите номер: ";
			cin >> pos;
			cout << arr.removeAt(pos);
			cout << "Количество просмотренных узлов: " << arr.getViewedCount() << endl;
			break;
		case 12:
			cout << "Запрос итератора произвольного доступа begin" << endl;
			iter = arr.begin();
			break;
		case 13:
			cout << "Запрос «неустановленного» итератора end" << endl;
			iter = arr.end();
			break;
		case 14:
			cout << "Доступ к значению элемента через итератор по чтению" << endl;
			try
			{
				cout << *iter << endl;
			}
			catch (ArrayException &exception)
			{
				std::cerr << "An array exception occurred (" << exception.what() << ")\n";
			}
			catch (std::exception &exception)
			{
				std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
			}
			break;
		case 15:
			cout << "Доступ к значению элемента через итератор по записи" << endl;
			cout << "Введите значение: ";
			cin >> val;
			try
			{
				*iter = val;
			}
			catch (ArrayException &exception)
			{
				std::cerr << "An array exception occurred (" << exception.what() << ")\n";
			}
			catch (std::exception &exception)
			{
				std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
			}
			break;
		case 16:
			cout << "Операция ++ для итератора" << endl;
			++iter;
			break;
		case 17:
			cout << "Сравнение текущего итератора с end (равенство)" << endl;
			iter2 = arr.end();
			temp = iter == iter2;
			cout << temp << endl;
			break;
		case 18:
			cout << "Сравнение текущего итератора с end (неравенство)" << endl;
			iter2 = arr.end();
			temp = iter != iter2;
			cout << temp << endl;
			break;
		}
		variant = menu(1);
	}

	system("pause");
	return 0;
}