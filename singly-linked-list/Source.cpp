#include "Header.h"

int menu(bool j)
{
	int variant;
	if (j == 0)
	{
		cout << "* * * * * * * ������* * * * * * *" << endl;
		cout << "�������� ��������:" << endl;
		cout << "1. ����� ������� ������\n"
			<< "2. ������� ������\n"
			<< "3. �������� ������ �� �������\n"
			<< "4. ����� ������� ��������� ��������\n"
			<< "5. ������ �������� � �������� ������� � ������\n"
			<< "6. ��������� �������� � �������� ������� � ������\n"
			<< "7. ��������� ������� � ������ ��� ��������� ��������\n"
			<< "8. ��������� ������ ��������\n"
			<< "9. ��������� ������ �������� � ������� � �������� �������\n"
			<< "10. �������� ��������� �������� �� ������\n"
			<< "11. �������� �������� �� ������� � �������� �������\n"
			<< "12. ������ ��������� ������������� ������� begin()\n"
			<< "13. ������ ����������������� ��������� end()\n"
			<< "14. ������ � �������� �������� ����� �������� �� ������\n"
			<< "15. ������ � �������� �������� ����� �������� �� ������\n"
			<< "16. �������� ++ ��� ���������\n"
			<< "17. ��������� �������� ��������� � end (���������)\n"
			<< "18. ��������� �������� ��������� � end (�����������)\n"
			<< "0. ����� ������ �� �����\n"
			<< "19. ����� �� ���������\n" << endl;
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
			cout << "����� ������ �� �����" << endl;
			arr.print();
			break;
		case 1:
			cout << "����� ������� ������" << endl;
			cout << arr.getSize() << endl;
			break;
		case 2:
			cout << "������� ������" << endl;
			arr.clear();
			break;
		case 3:
			cout << "�������� ������ �� �������" << endl;
			cout << arr.isEmpty() << endl;
			break;
		case 4:
			cout << "����� ������� ��������� ��������" << endl;
				cout << "������� ��������: ";
			cin >> val;
			cout << arr.contains(val) << endl;
			cout << "���������� ������������� �����: " << arr.getViewedCount() << endl;
			break;
		case 5:
			cout << "������ �������� � �������� ������� � ������" << endl;
			cout << "������� �����: ";
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
			cout << "���������� ������������� �����: " << arr.getViewedCount() << endl;
			break;
		case 6:
			cout << "��������� �������� � �������� ������� � ������" << endl;
			cout << "������� �����: ";
			cin >> pos;
			cout << "������� ��������: ";
			cin >> val;
			cout << arr.replace(val, pos) << endl;
			cout << "���������� ������������� �����: " << arr.getViewedCount() << endl;
			break;
		case 7:
			cout << "��������� ������� � ������ ��� ��������� ��������" << endl;
			cout << "������� ��������: ";
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
			cout << "���������� ������������� �����: " << arr.getViewedCount() << endl;
			break;
		case 8:
			cout << "��������� ������ ��������" << endl;
			cout << "������� ��������: ";
			cin >> val;
			cout << arr.add(val) << endl;
			cout << "���������� ������������� �����: " << arr.getViewedCount() << endl;
			break;
		case 9:
			cout << "��������� ������ �������� � ������� � �������� �������" << endl;
			cout << "������� ��������: ";
			cin >> val;
			cout << "������� �����: ";
			cin >> pos;
			cout << arr.add_pos(val, pos);
			cout << "���������� ������������� �����: " << arr.getViewedCount() << endl;
			break;
		case 10:
			cout << "�������� ��������� �������� �� ������" << endl;
			cout << "������� ��������: ";
			cin >> val;
			cout << arr.remove(val) << endl;
			cout << "���������� ������������� �����: " << arr.getViewedCount() << endl;
			break;
		case 11:
			cout << "�������� �������� �� ������� � �������� �������" << endl;
			cout << "������� �����: ";
			cin >> pos;
			cout << arr.removeAt(pos);
			cout << "���������� ������������� �����: " << arr.getViewedCount() << endl;
			break;
		case 12:
			cout << "������ ��������� ������������� ������� begin" << endl;
			iter = arr.begin();
			break;
		case 13:
			cout << "������ ����������������� ��������� end" << endl;
			iter = arr.end();
			break;
		case 14:
			cout << "������ � �������� �������� ����� �������� �� ������" << endl;
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
			cout << "������ � �������� �������� ����� �������� �� ������" << endl;
			cout << "������� ��������: ";
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
			cout << "�������� ++ ��� ���������" << endl;
			++iter;
			break;
		case 17:
			cout << "��������� �������� ��������� � end (���������)" << endl;
			iter2 = arr.end();
			temp = iter == iter2;
			cout << temp << endl;
			break;
		case 18:
			cout << "��������� �������� ��������� � end (�����������)" << endl;
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