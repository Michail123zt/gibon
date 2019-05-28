// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
//структура узлов
typedef struct Node
{
	int value; //значение в узле
	struct Node *next, *pred; //указатели на элементы структуры
} NODE, *pNODE;
//список элементов
typedef struct List
{
	pNODE top;
	int len;
}LIST, *pLIST;

pLIST createList() {     //выделение динамической памяти для хранения списка
	pLIST pL;
	pL = (pLIST)malloc(sizeof(LIST));
	if (!pL) return NULL;
	pL->top = NULL;
	pL->len = 0;
	return pL;
}

	int isEmpty(pLIST pL) {           //проверка списка на наличие элементов
		if (pL->top&&pL->len) return 0;
		return 1;
	}

	pNODE getPointer(pLIST pL, int date) {             //определение места вставки следующего узла
		pNODE temp;
		if (isEmpty(pL)) return NULL;
		else {
			temp = pL->top;
			if (date >= temp->value) return temp;
			while (temp->next && temp->next->value > date) temp = temp->next;
			return temp;
		}
	}

	int addNodeAfter(pLIST pL, pNODE pN, int newdate) {       //добавление узла
		pNODE pnew = (pNODE)malloc(sizeof(NODE));
		if (pnew) {
			pL->len++;
			pnew->value = newdate;
			if (isEmpty(pL) || newdate >= pL->top->value)
			{
				pnew->next = pL->top;
				pnew->pred = NULL;
				if (!isEmpty(pL)) pL->top->pred = pnew;
				pL->top = pnew;
				return 1;
			}
			if (!(pN->next)) {
				pnew->next = pN->next;
				pnew->pred = pN;
				pN->next = pnew;
				return 1;
			}
			pN->next->pred = pnew;
			pnew->next = pN->next;
			pnew->pred = pN;
			pN->next = pnew;
			return 1;
		}
		return 0;
	}

		pNODE findNode(pLIST pL, int date) {       //нахождение узла в списке
		pNODE p = pL->top, temp = p;
		//if (isempty(pL)) return NULL;
		while (temp&&temp->value != date) {
			p = temp;
			temp = temp->next;
		}
		if (temp) return p;
		return NULL;
	}

		int delNode(pLIST pL, pNODE pN) {         //удаление узла

			if (!pN) return 0;
			pNODE temp = pN->next;
			pN->next = temp->next;
			free(temp);
			pL->len--;
			return 1;
		}

		void clearList(pLIST pL) {    //очищение памяти отведенной для списка
			if (!isEmpty(pL)) {
				while (pL->top->next)
				{
					delNode(pL, pL->top);
				}
				pL->len--;
				free(pL->top);
			}
		}

		void deleteList(pLIST pL) {   //удалить
			clearList(pL);
			free(pL);
			printf("List delete!\n");
		}

		void showList(pLIST pL) {    //вывод списка 
			pNODE temp = pL->top;
			if (isEmpty(pL)) printf("List is empty!\n");
			else
			{
				printf("Length list:%d\n", pL->len);    //выввести
				while (temp) {
					printf_s("adres: %p \t element: %d \t next:%p\n", temp, temp->value, temp->next);
					temp = temp->next;
				}
			}
		}


		//задаем назначения кнопкам
		int main()
		{
			pNODE p;
			pLIST work_list = createList();
			char exit = 1;
			int com;
			while (exit)
			{
				puts("1 - add");
				puts("2 - find");
				puts("3 - delete");
				puts("4 - print");
				puts("5 - clear list");
				puts("0 - exit");
				scanf_s("%d", &com);

				switch (com)
				{
				case(0):
				{
					exit = 0;
					break;
				}
				case (1):
				{
					printf("Input number:");
					scanf_s("%d", &com);
					addNodeAfter(work_list, getPointer(work_list, com), com);
					break;
				}
				case(2):
				{
					printf("Input number:");
					scanf_s("%d", &com);
					pNODE to_show = findNode(work_list, com);
					if (to_show)
						printf("Number %d find in List, adres Number:%p\n", com, to_show);
					else
						printf("Number %d not find in List!\n", com);
					break;
				}
				case(3):
				{
					printf("Input number:");
					scanf_s("%d", &com);
					if (!isEmpty(work_list) && com == work_list->top->value) {
						p = work_list->top;
						work_list->top = work_list->top->next;
						free(p);
						work_list->len--;
						printf("Udalenie %d zaversheno!\n\n", com);
					}
					else
						if (delNode(work_list, getPointer(work_list, com))) printf("Udalenie %d");
						else
							printf("A integer %d does not contain in list!\n", com);
					break;
				}
				case(4):
				{
					showList(work_list);
					break;
				}
				case(5):
				{
					clearList(work_list);
					showList(work_list);
					break;
				}
				deleteList(work_list);
				return 0;

				}
			}
		}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
