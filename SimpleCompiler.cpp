//Areeb Hayat
//i210435@nu.edu.pk


#include<iostream>
#include<iomanip>
#include<string>
#include<conio.h>
#include <fstream>
#include "Queue.h"
#include "stack.h"
#include "Functions.h"
#include "Image.h"
using namespace std;


bool extratags(string str)
{
	int ret = 0;
	int i = 0;
	string copy;
	int tagat = 0;
	bool b = false;
	bool e = false;

	while (str[i] != '\0' && !b && !e)
	{
		if (str == "|src|")
			return true;
		if (str == "|post_exp|")
		{
			return true;
		}
		if (str == "|pre_exp|")
		{
			return true;
		}
		if (str[i] == '|' && (str[i + 1] == 'h' || str[i + 1] == 't' || str[i + 1] == 'p'))
		{

			b = true;
			int j = 0;
			while (str[j] != '\0')
			{
				if (j == i)
				{
					j++;
					while (str[j] != '|')
						j++;
				}
				if (str[j] != '|')
					cout << str[j];
				j++;
			}
			cout << " ";

		}
		else if (str[i] == '\\' && (str[i + 1] == 'h' || str[i + 1] == 't' || str[i + 1] == 'p' || (str[i + 1] == 's' && str[i + 2] == 'o')))
		{
			e = true;
			int j = 0;
			while (str[j] != '\0')
			{
				if (j == i - 1)
				{
					j++;
					while (str[j] != '|')
						j++;
				}
				if (str[j] != '|')
					cout << str[j];
				j++;
			}
			cout << " ";
		}
		i++;
	}
	if (b || e)
		return true;
	else
		return false;
}

bool chktag(string str)
{
	int i = 0;
	if (str == "|chk|" || str == "|\\chk|")
	{
		return true;
	}
	return false;
}

void exefile(string path)
{
	string reading;
	string storing;
	ofstream exe;
	exe.open("f:\\university\\ds\\assignment 2\\test_files\\execute.txt", ios::in);
	ifstream read;
	read.open(path, ios::in);
	while (reading != "|\\start|")
	{
		getline(read, reading);
		storing = reading;
		storing += " \\n\n";
		exe << storing;
	}
	storing = reading;
	storing += " \\n\n";
	read.close();
	exe.close();
	string str;
	read.open("f:\\university\\ds\\assignment 2\\test_files\\execute.txt", ios::in);
	/*while (reading != "|\\start|")
	{
		read >> reading;
		if (reading == "\\n")
			str += "\n";
		else
			str += reading;
		str += " ";
	}*/
	exe.open("f:\\university\\ds\\assignment 2\\test_files\\execute.txt", ios::in);
	exe << str;
}


string execode(string path)
{
	exefile(path);
	ifstream my_file("f:\\university\\ds\\assignment 2\\test_files\\execute.txt", ios::in);
	string str;
	string str2;
	string opentag;
	bool tag = false;
	bool* post = new bool;
	*post = true;
	int i = 0;
	//str = " ";
	string store;
	while (str != "|\\start|")
	{
		my_file >> str;
		if (str == "\\n")
		{
			my_file >> str;
			cout << endl;
			store += "\n";
			if (str == "|\\start|")
				break;
		}
		if (str == "|\\start|")
		{
			break;
		}
		if (str == "|head|")
		{
			while (my_file >> str && (str != "|\\head|"))
			{
				if (str == "\\n")
				{
					my_file >> str;
					cout << endl;
					store += "\n";
					if ((str == "|\\head|"))
						break;
				}
				i = 0;
				i += tab(str, store);
				while (str[i] != '\0')
				{
					if (str[i] != '\t')
					{
						cout << str[i];
						store += str[i];
					}
					i++;
				}

				cout << " ";
				store += " ";
			}
		}
		if (str == "|paragraph|")
		{
			if (str == "|\\start|")
				break;
			while (my_file >> str && (str != "|\\paragraph|"))
			{
				while /*if*/ (str == "\\n")
				{
					cout << endl;
					store += "\n";
					getline(my_file, str);
					if (str[0] == '\t')
					{
						store += "\t";
						break;
					}//my_file >> str;
					//cout << endl;
					//if ((str == "|\\paragraph|"))
					//	break;
				}
				i = 0;
				if (chktag(str))
				{
					//cout << endl << "CHK CHECK HO RAHA HAI" << endl << endl;
					my_file >> str;
					while /*if*/ (str == "\\n")
					{
						cout << endl;
						getline(my_file, str);
						int a = 0;
						while (str[a] != '\0' && str[a] != '\t')
							a++;
						if (str[a] != '\0' && str[a] != '\\')
							break;
						//my_file >> str;
						//cout << endl;
						//if ((str == "|\\paragraph|"))
						//	break;
					}
				}
				if (str == "|\\start|")
					break;
				i += tab(str, store);
				if (extratags(str))
				{
					if (str == "|src|")
					{
						string imgsrc;
						my_file >> str;
						int d = 1;
						while (str[d] != '\\')
							d++;
						d++;
						while (str[d] != '\0')
						{
							imgsrc += str[d];
							d++;
						}
						int g = task4(imgsrc);
						cout << g << ".";
						store += to_string(g);
						my_file >> str;
					}
					if (str == "|post_exp|")
					{
						string banana;
						my_file >> str;
						while (str != "|\\post_exp|" && str != "|\\post_exp|." && str != "|\\post_exp|,")
						{
							banana += str;
							my_file >> str;
						}
						banana += '\0';
						//cout << banana << endl;
						if (invalid_exp(banana))
						{
							cout << " Invalid Expression ";
							store += " Invalid Expression ";
						}
						else
						{
							banana = posfx(banana);
							cout << banana;
							store += banana;
						}

						if (str == "\\n")
						{
							my_file >> str;
							cout << endl;
							store += "\n";
							if (str == "|\\paragraph|")
								break;
						}
					}
					else if (str == "|pre_exp|")
					{
						string banana;
						my_file >> str;
						while (str != "|\\pre_exp|" && str != "|\\pre_exp|." && str != "|\\pre_exp|,")
						{
							banana += str;
							my_file >> str;
						}
						if (invalid_exp(banana))
						{
							cout << " Invalid Expression ";
							store += " Invalid Expression ";
						}
						else
						{
							banana = prefx(banana);
							cout << banana;
							store += banana;
						}

						if (str == "\\n")
						{
							my_file >> str;
							cout << endl;
							store += "\n";
							if (str == "|\\paragraph|")
								break;
						}
					}
					else
					{
						my_file >> str;
						/*while*/ if (str == "\\n")
						{
							my_file >> str;
							cout << endl;
							store += "\n";
							if (str == "|\\paragraph|")
								break;
						}
					}
				}
				if (extratags(str))
				{
					if (str == "|src|")
					{
						string imgsrc;
						my_file >> str;
						int d = 1;
						while (str[d] != '\\')
							d++;
						d++;
						while (str[d] != '\0')
						{
							imgsrc += str[d];
							d++;
						}
						int g = task4(imgsrc);
						cout << g << ".";
						store += to_string(g);
						my_file >> str;
					}
					if (str == "|post_exp|")
					{
						string banana;
						my_file >> str;
						while (str != "|\\post_exp|" && str != "|\\post_exp|." && str != "|\\post_exp|,")
						{
							banana += str;
							my_file >> str;
						}
						banana += '\0';
						//cout << banana << endl;
						if (invalid_exp(banana))
						{
							cout << " Invalid Expression ";
							store += " Invalid Expression ";
						}
						else
						{
							banana = posfx(banana);
							cout << banana;
							store += banana;
						}

						if (str == "\\n")
						{
							my_file >> str;
							cout << endl;
							store += "\n";
							if (str == "|\\paragraph|")
								break;
						}
					}
					else if (str == "|pre_exp|")
					{
						string banana;
						my_file >> str;
						while (str != "|\\pre_exp|" && str != "|\\pre_exp|." && str != "|\\pre_exp|,")
						{
							banana += str;
							my_file >> str;
						}
						if (invalid_exp(banana))
						{
							cout << " Invalid Expression ";
							store += " Invalid Expression ";
						}
						else
						{
							banana = prefx(banana);
							cout << banana;
							store += banana;
						}

						if (str == "\\n")
						{
							my_file >> str;
							cout << endl;
							store += "\n";
							if (str == "|\\paragraph|")
								break;
						}
					}
					else
					{
						my_file >> str;
						/*while*/ if (str == "\\n")
						{
							my_file >> str;
							store += "\n";
							cout << endl;
							if (str == "|\\paragraph|")
								break;
						}
					}
				}

				if (str == "|sol_exp|")
				{
					string banana;
					my_file >> str;
					while (str != "|\\sol_exp|" && str != "|\\sol_exp|." && str != "|\\sol_exp|,")
					{
						banana += str;
						my_file >> str;
					}
					my_file >> str;
					if (invalid_exp(banana))
					{
						cout << " Invalid Expression ";
						store += " Invalid Expression ";
					}
					else
					{
						solve(banana, store);
					}

					if (str == "\\n")
					{
						my_file >> str;
						cout << endl;
						store += "\n";
						if (str == "|\\paragraph|")
							break;
					}
				}

				if (str == "|\\start|")
					break;
				while (str[i] != '\0')
				{
					if (str[i] != '\t')
					{
						cout << str[i];
						store += str[i];
					}
					i++;
				}

				cout << " ";
				store += " ";
			}/*
			cout << endl << endl;*/
		}

		if (chktag(str))
		{
			/*while*/ if (str == "\\n")
			{
				my_file >> str;
				cout << endl;
				store += "\n";
				if (str == "|\\chk|")
					break;
			}
			if (str == "|\\start|")
				break;
			while (my_file >> str && (str != "|\\chk|"))
			{
				/*while*/ if (str == "\\n")
				{
					my_file >> str;
					cout << endl;
					store += "\n";
					if (str == "|\\chk|")
						break;
				}
				i = 0;
				i += tab(str, store);
				if (extratags(str))
				{
					if (str == "|src|")
					{
						string imgsrc;
						my_file >> str;
						int d = 1;
						while (str[d] != '\\')
							d++;
						d++;
						while (str[d] != '\0')
						{
							imgsrc += str[d];
							d++;
						}
						int g = task4(imgsrc);
						cout << g << ".";
						store += to_string(g);
						my_file >> str;
					}
					if (str == "|post_exp|")
					{
						string banana;
						my_file >> str;
						while (str != "|\\post_exp|" && str != "|\\post_exp|." && str != "|\\post_exp|,")
						{
							banana += str;
							my_file >> str;
						}
						banana += '\0';
						//cout << banana << endl;
						if (invalid_exp(banana))
						{
							cout << " Invalid Expression ";
							store += " Invalid Expression ";
						}
						else
						{
							banana = posfx(banana);
							cout << banana;
							store += banana;
						}

						if (str == "\\n")
						{
							my_file >> str;
							cout << endl;
							store += "\n";
							if (str == "|\\paragraph|")
								break;
						}
					}
					else if (str == "|pre_exp|")
					{
						string banana;
						my_file >> str;
						while (str != "|\\pre_exp|" && str != "|\\pre_exp|." && str != "|\\pre_exp|,")
						{
							banana += str;
							my_file >> str;
						}
						if (invalid_exp(banana))
						{
							cout << " Invalid Expression ";
							store += " Invalid Expression ";
						}
						else
						{
							banana = prefx(banana);
							cout << banana;
							store += banana;
						}

						if (str == "\\n")
						{
							my_file >> str;
							cout << endl;
							store += "\n";
							if (str == "|\\paragraph|")
								break;
						}
					}
					else
					{
						my_file >> str;
						/*while*/ if (str == "\\n")
						{
							my_file >> str;
							cout << endl;
							store += "\n";
							if (str == "|\\paragraph|")
								break;
						}
					}
				}
				if (extratags(str))
				{
					if (str == "|src|")
					{
						string imgsrc;
						my_file >> str;
						int d = 1;
						while (str[d] != '\\')
							d++;
						d++;
						while (str[d] != '\0')
						{
							imgsrc += str[d];
							d++;
						}
						int g = task4(imgsrc);
						cout << g << ".";
						store += to_string(g);
						my_file >> str;
					}
					if (str == "|post_exp|")
					{
						string banana;
						my_file >> str;
						while (str != "|\\post_exp|" && str != "|\\post_exp|." && str != "|\\post_exp|,")
						{
							banana += str;
							my_file >> str;
						}
						banana += '\0';
						//cout << banana << endl;
						if (invalid_exp(banana))
						{
							cout << " Invalid Expression ";
							store += " Invalid Expression ";
						}
						else
						{
							banana = posfx(banana);
							cout << banana;
							store += banana;
						}

						if (str == "\\n")
						{
							my_file >> str;
							cout << endl;
							store += "\n";
							if (str == "|\\paragraph|")
								break;
						}
					}
					else if (str == "|pre_exp|")
					{
						string banana;
						my_file >> str;
						while (str != "|\\pre_exp|" && str != "|\\pre_exp|." && str != "|\\pre_exp|,")
						{
							banana += str;
							my_file >> str;
						}
						if (invalid_exp(banana))
						{
							cout << " Invalid Expression ";
							store += " Invalid Expression ";
						}
						else
						{
							banana = prefx(banana);
							cout << banana;
							store += banana;
						}

						if (str == "\\n")
						{
							my_file >> str;
							cout << endl;
							store += "\n";
							if (str == "|\\paragraph|")
								break;
						}
					}
					else
					{
						my_file >> str;
						/*while*/ if (str == "\\n")
						{
							my_file >> str;
							cout << endl;
							store += "\n";
							if (str == "|\\paragraph|")
								break;
						}
					}
				}
				if (str == "|sol_exp|")
				{
					string banana;
					my_file >> str;
					while (str != "|\\sol_exp|" && str != "|\\sol_exp|." && str != "|\\sol_exp|,")
					{
						banana += str;
						my_file >> str;
					}
					my_file >> str;
					if (invalid_exp(banana))
					{
						cout << " Invalid Expression ";
						store += " Invalid Expression ";
					}
					else
					{
						solve(banana, store);
					}

					if (str == "\\n")
					{
						my_file >> str;
						cout << endl;
						store += "\n";
						if (str == "|\\paragraph|")
							break;
					}
				}
				while (str[i] != '\0')
				{
					if (str[i] != '\t')
					{
						cout << str[i];
						store += str[i];
					}
					i++;
				}

				cout << " ";
				store += " ";
			}
		}
	}
	return store;
}

void writeAllFiles(string str)
{
	string path = "f:\\university\\ds\\assignment 2\\Output_files\\All_Result.txt";
	ofstream write;
	write.open(path, ios::app);
	if (!write.is_open())
	{
		cout << "File not found" << endl;
		return;
	}
	write << str;
	//write << endl << endl;
}


string getpriorty(string path)
{
	string str = "\0";
	ifstream read;
	read.open(path, ios::in);
	while (!read.eof())
	{
		if (str == "|priorty|")
			break;
		read >> str;
	}
	read >> str;
	return str;
}

void PriortyBasedMenu()
{
	string path = "f:\\university\\ds\\assignment 2\\test_files\\";
	Queue<string> lru;
	string pri;

	pri = getpriorty("f:\\university\\ds\\assignment 2\\test_files\\test-1.txt");
	lru.enqueue(pri);

	pri = getpriorty("f:\\university\\ds\\assignment 2\\test_files\\test-2.txt");
	lru.enqueue(pri);

	pri = getpriorty("f:\\university\\ds\\assignment 2\\test_files\\test-3.txt");
	lru.enqueue(pri);

	pri = getpriorty("f:\\university\\ds\\assignment 2\\test_files\\test-4.txt");
	lru.enqueue(pri);


	cout << "\nStarting LRU Queue: ";
	lru.print();
	cout << endl;

	char choice = 'y';
	string filename;
	char fileq = 0;
	int hits = 0, faults = 0;

	while (choice == 'y' || choice == 'Y')
	{
		path = "f:\\university\\ds\\assignment 2\\test_files\\";
		cout << "Enter file name: ";
		cin >> filename;
		cout << endl;
		int i = 0;
		while (filename[i] != '\0')
		{
			i++;
		}

		while (filename[i - 1] < '1' || filename[i - 1] > '7')
		{
			cout << "Invalid file name\nPlease enter a valid file name" << endl;
			cout << "Enter file name: ";
			cin >> filename;
			cout << endl;
			i = 0;
			while (filename[i] != '\0')
			{
				i++;
			}
			fileq = filename[i - 1];
		}

		fileq = filename[i - 1];
		filename += ".txt";
		path += filename;

		cout << fileq << endl;

		ifstream file;
		file.open(path, ios::in);
		if (!file.is_open())
			cout << "File Not fount" << endl;
		else
		{
			if (lru.found(getpriorty(path)))
			{
				lru.deleteat(getpriorty(path));
				lru.enqueue(getpriorty(path));
				hits++;
			}
			else
			{
				lru.dequeue();
				lru.enqueue(getpriorty(path));
				faults++;
			}

			bool test = tagcheck(path);

			if (test == false)
			{
				cout << "\nsyntax error" << endl;
				//writeAllFiles("\nSYNTAX ERROR");
			}
			else
				execode(path);
			//writeAllFiles(execode(path));
		}

		cout << "\nThe current LRU Queue: ";
		lru.print();
		cout << endl;

		cout << endl << "Do you wish to continue (Y/N): ";
		cin >> choice;
		cout << endl << endl;
	}

	cout << "\n\nTotal hits: " << hits << endl;
	cout << "Total faults: " << faults << endl << endl;

	/*string h = to_string(hits);
	string f = to_string(faults);
	writeAllFiles("\n\nLRU Results: \n");
	writeAllFiles("Total Hits: ");
	writeAllFiles(h);
	writeAllFiles("\t\t");
	writeAllFiles("Total Faults: ");
	writeAllFiles(f);
	writeAllFiles("\n");*/
}



void NameBasedMenu()
{
	string path = "f:\\university\\ds\\assignment 2\\test_files\\";
	Queue<string> lru;

	lru.enqueue("test-1");
	lru.enqueue("test-2");
	lru.enqueue("test-3");
	lru.enqueue("test-4");

	cout << "\nStarting LRU Queue: ";
	lru.print();
	cout << endl;

	char choice = 'y';
	string filename;
	string fileq = "\0";
	int hits = 0, faults = 0;

	while (choice == 'y' || choice == 'Y')
	{
		path = "f:\\university\\ds\\assignment 2\\test_files\\";
		cout << "Enter file name: ";
		cin >> filename;
		cout << endl;
		int i = 0;
		while (filename[i] != '\0')
		{
			i++;
		}

		while (filename[i - 1] < '1' || filename[i - 1] > '7')
		{
			cout << "Invalid file name\nPlease enter a valid file name" << endl;
			cout << "Enter file name: ";
			cin >> filename;
			cout << endl;
			i = 0;
			while (filename[i] != '\0')
			{
				i++;
			}
			fileq = filename[i - 1];
		}

		fileq = "test-";
		fileq += filename[i - 1];
		filename += ".txt";
		path += filename;

		cout << fileq << endl;

		ifstream file;
		file.open(path, ios::in);
		if (!file.is_open())
			cout << "File Not fount" << endl;
		else
		{
			if (lru.found(fileq))
			{
				lru.deleteat(fileq);
				lru.enqueue(fileq);
				hits++;
			}
			else
			{
				lru.dequeue();
				lru.enqueue(fileq);
				faults++;
			}

			bool test = tagcheck(path);

			if (test == false)
			{
				//cout << "\nsyntax error" << endl;
				writeAllFiles("\nSYNTAX ERROR");
			}
			else
				//execode(path);
				writeAllFiles(execode(path));
		}

		cout << "\nThe current LRU Queue: ";
		lru.print();
		cout << endl;

		cout << endl << "Do you wish to continue (Y/N): ";
		cin >> choice;
		cout << endl << endl;
	}

	cout << "\n\nTotal hits: " << hits << endl;
	cout << "Total faults: " << faults << endl << endl;

	string h = to_string(hits);
	string f = to_string(faults);
	writeAllFiles("\n\nLRU Results: \n");
	writeAllFiles("Total Hits: ");
	writeAllFiles(h);
	writeAllFiles("\t\t");
	writeAllFiles("Total Faults: ");
	writeAllFiles(f);
	writeAllFiles("\n");
}



int main()
{
	NameBasedMenu();
	//PriortyBasedMenu();

	return 0;
}