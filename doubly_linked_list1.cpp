// doubly_linked_list1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>

/*
* Node Declaration
*/
using namespace std;
struct node
{
	int info;
	struct node *next;
	struct node *prev;
}*start;

/*
Class Declaration
*/
class double_llist
{
public:
	void create_list(int value);
	void add_begin(int value);
	void add_after(int value, int position);
	void delete_element(int value);
	void display_dlist();
	void save_dlist();
	void load_dlist();

	double_llist()
	{
		start = NULL;
	}
};

/*
* Main Menu
*/
int main()
{
	int choice, element, position;
	double_llist dl;
	while (1)
	{
		cout << endl << "----------------------------" << endl;
		cout << endl << "Operacijos:" << endl;
		cout << "1.Create Node" << endl;
		cout << "2.Add at begining" << endl;
		cout << "3.Add after position" << endl;
		cout << "4.Delete" << endl;
		cout << "5.Save to file" << endl;
		cout << "6.Load file" << endl;
		cout << "7.Quit" << endl;
		cout << "Enter your choice : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter the element: ";
			cin >> element;
			dl.create_list(element);
			dl.display_dlist();
			cout << endl;
			break;
		case 2:
			cout << "Enter the element: ";
			cin >> element;
			dl.add_begin(element);
			dl.display_dlist();
			cout << endl;
			break;
		case 3:
			cout << "Enter the element: ";
			cin >> element;
			cout << "Insert Element after postion: ";
			cin >> position;
			dl.add_after(element, position);
			dl.display_dlist();
			cout << endl;
			break;
		case 4:
			if (start == NULL)
			{
				cout << "List empty,nothing to delete" << endl;
				break;
			}
			cout << "Enter the element for deletion: ";
			cin >> element;
			dl.delete_element(element);
			dl.display_dlist();
			cout << endl;
			break;
		case 5:
			if (start == NULL)
			{
				cout << "List empty,nothing to save" << endl;
				break;
			}
			dl.save_dlist();
			cout << endl;
			break;
		case 6:
			dl.load_dlist();
			dl.display_dlist();
			cout << endl;
			break;
		case 7:
			exit(1);
		default:
			cout << "Wrong choice" << endl;
		}
	}
	return 0;
}

/*
* Create Double Link List
*/
void double_llist::create_list(int value)
{
	struct node *s, *temp;
	temp = new(struct node);
	temp->info = value;
	temp->next = NULL;
	if (start == NULL)
	{
		temp->prev = NULL;
		start = temp;
	}
	else
	{
		s = start;
		while (s->next != NULL)
			s = s->next;
		s->next = temp;
		temp->prev = s;
	}
}

/*
* Insertion at the beginning
*/
void double_llist::add_begin(int value)
{
	if (start == NULL)
	{
		cout << "First Create the list." << endl;
		return;
	}
	struct node *temp;
	temp = new(struct node);
	temp->prev = NULL;
	temp->info = value;
	temp->next = start;
	start->prev = temp;
	start = temp;
	cout << "Element Inserted" << endl;
}

/*
* Insertion of element at a particular position
*/
void double_llist::add_after(int value, int pos)
{
	if (start == NULL)
	{
		cout << "First Create the list." << endl;
		return;
	}
	struct node *tmp, *q;
	int i;
	q = start;
	for (i = 0; i < pos - 1; i++)
	{
		q = q->next;
		if (q == NULL)
		{
			cout << "There are less than ";
			cout << pos << " elements." << endl;
			return;
		}
	}
	tmp = new(struct node);
	tmp->info = value;
	if (q->next == NULL)
	{
		q->next = tmp;
		tmp->next = NULL;
		tmp->prev = q;
	}
	else
	{
		tmp->next = q->next;
		tmp->next->prev = tmp;
		q->next = tmp;
		tmp->prev = q;
	}
	cout << "Element Inserted" << endl;
}

/*
* Deletion of element from the list
*/
void double_llist::delete_element(int value)
{
	struct node *tmp, *q;
	/*first element deletion*/
	if (start->info == value)
	{
		tmp = start;
		start = start->next;
		start->prev = NULL;
		cout << "Element Deleted" << endl;
		free(tmp);
		return;
	}
	q = start;
	while (q->next->next != NULL)
	{
		/*Element deleted in between*/
		if (q->next->info == value)
		{
			tmp = q->next;
			q->next = tmp->next;
			tmp->next->prev = q;
			cout << "Element Deleted" << endl;
			free(tmp);
			return;
		}
		q = q->next;
	}
	/*last element deleted*/
	if (q->next->info == value)
	{
		tmp = q->next;
		free(tmp);
		q->next = NULL;
		cout << "Element Deleted" << endl;
		return;
	}
	cout << "Element " << value << " not found" << endl;
}

/*
* Display elements of Doubly Link List
*/
void double_llist::display_dlist()
{
	struct node *q;
	if (start == NULL)
	{
		cout << "\nList empty,nothing to display" << endl;
		return;
	}
	q = start;
	cout << "\nThe Doubly Link List is :" << endl;
	while (q != NULL)
	{
		cout << q->info << " <-> ";
		q = q->next;
	}
	cout << "NULL" << endl;
}

/*
* Save elements to file
*/
void double_llist::save_dlist()
{

	ofstream listfile;
	listfile.open("rezultatai.txt", ios::out | ios::trunc);
	node *temp;
	temp = start;
	if (!listfile) {
		cout << "\nError";
	}
	else {
		while (temp != NULL)
		{
			listfile << temp->info << " <-> ";
			temp = temp->next;
		}
		listfile << "NULL";
	}
	listfile.close();
	cout << "\nLinked list has been saved in file rezultatai.txt in current folder.";

}


/*
* Load elements from file
*/
void double_llist::load_dlist()
{
	streamoff length;
	node *temp;
	node *prev;
	ifstream listfile;
	listfile.open("prad_duomenys.txt");
	prev = NULL;
	if (listfile.good()) {
		listfile.seekg(0, ios::end);
		length = listfile.tellg();
		if (length != 0) {
			listfile.seekg(0);
			while (!listfile.eof())
			{
				temp = new(struct node);
				if (start == NULL)
					start = temp;
				listfile >> temp->info;
				temp->prev = prev;
				temp->next = NULL;
				if (prev != NULL)
					prev->next = temp;
				prev = temp;
			}
			listfile.close();
			cout << "\nLinked list has been loaded from prad_duomenys.txt";
		}
	}
}