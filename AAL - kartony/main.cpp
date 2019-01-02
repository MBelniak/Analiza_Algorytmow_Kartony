/*
Funkcja main programu.
Micha³ Belniak grupa 5I3, prowadz¹cy: £ukasz Skonieczny
Projekt: AAL-11-LS kartony
*/

#include "MPacking.h"
#include "EfficiencyTest.h"
#include <iostream>
#include <string.h>

using namespace std;
int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "Usage: ./kartony [-p [<file_name>]]\n"
			"               [-c <complexity>]\n"
			"               [-t <portions_per_step> <step1> [step2] [step3] ...]\n" 
			"               [-t -g [-n] <step1> [step2] [step3] ...]"<< endl;
	}
	else if (argc == 2 && !strcmp(argv[1], "-p"))		//Wybrano opcjê -p czyli wczytanie danych ze standardowego wejœcia.
	{
		MPacking task;
		if (task.isCreated())		//obiekt task jest niestworzony, jeœli liczba wierzcho³ków  grafie wynosi 0
		{
			task.findBestPaths();
			task.writePaths();
		}
	}
	else if (argc == 3)
	{
		if (!strcmp(argv[1], "-c"))			//Wybrano opcjê rozwi¹zania losowego problemu o wielkoœci argv[2]
		{
			int complexity = atoi(argv[2]);
			if (!complexity)
				cout << "complexity must be an integer >0." << endl;
			MPacking task(complexity, false);
			if (task.isCreated())
			{
				task.findBestPaths();
				task.writePaths();
			}
		}
		else if (!strcmp(argv[1], "-p"))	//Wybrano opcjê rozwi¹zania problemu z pliku tekstowego
		{
			string file_name = argv[2];
			MPacking task(file_name);
			if (task.isCreated())
			{
				task.findBestPaths();
				task.writePaths();
			}
		}
	}
	else
	{
		if (argc >= 4 && !strcmp(argv[1], "-t"))	//Wybrano opcjê testu wydajnoœciowego
		{
			int steps;
			if (!strcmp(argv[3], "-n"))
				steps = argc - 4;
			else
				steps = argc - 3;

			int* complexities = new int[steps];

			for (int i = 0; i < steps; i++)
			{
				if (!strcmp(argv[3], "-n"))
					complexities[i] = atoi(argv[i + 4]);
				else
					complexities[i] = atoi(argv[i + 3]);
				if (!complexities[i])
				{
					cout << "complexity must be an integer >0." << endl;
					return 0;
				}
			}
			if (!strcmp(argv[2], "-g"))		//Wyniki w formie tabeli
			{
				if (!strcmp(argv[3], "-n"))
					EfficiencyTest test(complexities, steps, false);
				else
					EfficiencyTest test(complexities, steps, true);
			}
			else	//Wyniki dla kazdej porcji
			{
				int portions = atoi(argv[2]);
				if (!portions)
				{
					cout << "portions_per_step must be an integer >0." << endl;
					return 0;
				}
				EfficiencyTest test(portions, complexities, argc - 3);
			}
			delete complexities;
		}
		else
		{
			cout << "Usage: ./kartony [-p [<file_name>]]\n"
				"               [-c <complexity>]\n"
				"               [-t <portions_per_step> <step1> [step2] [step3] ...]\n" 
				"               [-t -g [-n] <step1> [step2] [step3] ...]" << endl;
		}
	}
	return 0;
}

