/*
Plik z klas� rozszerzaj�c� klas� Graph, kt�ra implementuj� struktur� danych dla problemu oraz algorytm rozwi�zuj�cy problem. 
Posiada r�wnie� funkcj� wypisuj�c� rozwi�zanie na standardowe wyj�cie.
Micha� Belniak grupa 5I3, prowadz�cy: �ukasz Skonieczny
Projekt: AAL-11-LS kartony
*/

#ifndef MATRIOSHKAPACKING_H
#define MATRIOSHKAPACKING_H
#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"


class MPacking : public Graph
{
private:
	float v_gained;		//ca�kowita obj�to�� zaoszcz�dzona dzi�ki pakowaniu.
	void sortDims(float dims[3])		//metoda sortuj�ca wymiary pude�ka, aby width>=length>=height
	{
		float a;
		for (int i = 2; i >= 0; i--)
			for (int j = 0; j < i; j++)
				if (dims[j + 1] > dims[j])
				{
					a = dims[j];
					dims[j] = dims[j + 1];
					dims[j + 1] = a;
				}
	}

	void rebuild();						//Usuni�cie i wyszukanie rodzic�w i dzieci ka�dego wierzcho�ka jeszcze raz.
	float getMaxAlternative(Vertice* parent_analyzed, Vertice* child);	//zwraca obj�to��s najwi�kszego pude�ka, jakie mo�e zmie�ci� parent_analyzed poza child.
	int findChildIndex(Vertice* child);	//Zwraca pozycj� wierzcho�ka w wektorze wierzcho�k�w.
	void removeChild(Vertice *parent, int child_number);
	void continuePath(std::vector<int>* path, int rootIndex); //Szuka kolejnego wierzcho�ka dla �cie�ki path i wierzcho�ka o pozycji rootIndex w wektorze. G��wny algorytm programu.
	std::vector<std::vector<int>> paths; //Wektor �cie�ek znalezionych do tej pory przez algorytm.

public:
	MPacking();
	MPacking(std::string file_name);
	MPacking(int complexity, bool hardCases);	//hardCases = true oznacza generowanie co jaki� czas 10 wierzcho�k�w - pude�ek - o tych samych wymiarach.
	void findBestPaths();	//Znaj� rozwi�zanie problemu.
	void writePaths();		//Wypisz rozwi�zanie.
	void regenerateGraph();	//Przywr�c graf do stanu sprzed wykonania algorytmu.
	
	void writeVertices()	//Wypisz informacje o ka�dym wierzcho�ku.
	{
		for (unsigned i = 0; i<vertices.size(); i++)
		{
			std::cout << vertices[i].number << std::endl << "children: ";
			for (unsigned k = 0; k<vertices[i].children.size(); k++)
				std::cout << vertices[i].children[k]->number << ", ";
			std::cout << "\n parents: ";
			for (unsigned k = 0; k<vertices[i].parents.size(); k++)
				std::cout << vertices[i].parents[k]->number << ", ";
			std::cout << "\n";
			std::cout << "volume: " << vertices[i].volume<<std::endl<< std::endl;
		}
	}

	bool isCreated()
	{
		return vertices.size()!=0;
	}
};

MPacking::MPacking()
{
	std::cout << "Write next dimensions as follows:\n"
		"200.4[ENTER]\n"
		"182[ENTER]\n"
		"135.25[ENTER]\n";
	std::cout << "any other character to finish\n";
	v_total = v_gained = 0;
	float dims[3];
	std::string dim;
	int k = 0;
	while(std::cin.good())
	{	
		std::cout << ">";
		std::cin >> dim;
		try
		{
			dims[k] = stof(dim);
		}
		catch (std::invalid_argument e)
		{
			std::cout << std::endl;
			break;
		}

		k++;
		
		if (k == 3)
		{
			sortDims(dims);
			addVertice(dims);
			k = 0;
			std::cout << std::endl;
		}
	}

}

MPacking::MPacking(std::string file_name)
{

	v_total = v_gained = 0;
	std::string line;
	std::ifstream input_file;
	input_file.open(file_name, std::ios::in);
	if (input_file.is_open())
	{
		int k = 0;
		float dims[3];
		while (getline(input_file, line))
		{
			try {
				dims[k] = std::stof(line);
			}
			catch (std::invalid_argument e)
			{
				break;
			}

			k++;

			if (k == 3)
			{
				sortDims(dims);
				addVertice(dims);
				k = 0;
				getline(input_file, line);
			}	
		}

		input_file.close();
	}
	else
	{
		std::cout << "Cannot open a file." << std::endl;
	}
}

MPacking::MPacking(int complexity, bool hardCases)
{
	v_total = v_gained = 0;
	float dims[3];

	for (int i = 0; i < complexity; i++)
	{
		if (hardCases  && complexity>=40 && (i % (complexity / 20) == 0) && rand()>(RAND_MAX/2))	//Generowanie trudnych przypadk�w - pude�ka o tych samych wymiarach
		{
			dims[0] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1000));
			dims[2] = dims[1] = dims[0];
			for (int k = 0; k < complexity/10; k++)
			{
				addVertice(dims);
				i++;
			}
			dims[2] = dims[1] = dims[0] = dims[0] + 10.0f;
			for (int k = 0; k < complexity / 10; k++)
			{
				addVertice(dims);
				i++;
			}
		}
		else
		{
			dims[0] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1000));
			dims[1] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1000));
			dims[2] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1000));
			sortDims(dims);
			addVertice(dims);
		}
	}
}


//Wypisanie rozwi�zania
void MPacking::writePaths()
{
	for (std::vector<int> path : paths)
	{
		for (int i : path)
		{
			std::cout << i;
			if (path.at(path.size()-1)!= i)
				std::cout << "<-";
		}
		std::cout << std::endl<<std::endl;
	}

	std::cout << "Total volume of cartons: " << v_total << std::endl;
	std::cout << "Volume gained:  " << v_gained << std::endl;
}

//Znajd� rzowi�zanie.
void MPacking::findBestPaths()
{
	findParentsAndChildren();				
	int rootIndex;

	while ((rootIndex = findRoot())!=-1)	//Dop�ki w grafie istnieje wierzcho�ek.
	{
		std::vector<int> path;
		continuePath(&path, rootIndex);	//Znajd� �cie�k� dla danego roota
		paths.push_back(path);	//Dodaj �cie�k� do wektora dotychczasowych �cie�ek.
		rebuild();		//Znajd� rodzic�w i dzieci jeszcze raz.
	}
}


void MPacking::rebuild()
{
	for (unsigned i = 0; i<vertices.size(); i++)
	{
		vertices[i].children.clear();
		vertices[i].parents.clear();
	}

	findParentsAndChildren();
}


float MPacking::getMaxAlternative(Vertice* parent_analyzed, Vertice* child) //Je�li pierwszy argument rzeczywi�cie jest rodzicem, to musi mie� przyjamniej jedno dziecko.
{
	if (parent_analyzed->children[0] == child)
	{
		if (parent_analyzed->children.size() == 1)
			return 0;
		return parent_analyzed->children[1]->volume;
	}

	return parent_analyzed->children[0]->volume;
}

int MPacking::findChildIndex(Vertice* child)		
{
	for (unsigned i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].is_Deleted)
			continue;
		if (vertices[i].number == child->number)
			return i;
	}

	return -1;
}

//G��wna funkcja algorytmu. Po znalezieniu kolejnego wierzcho�ka w �cie�ce jest wywo�ywana dla tego znalezionego wierzcho�ka.
//W ten spos�b �cie�ka buduje si� wierzcho�ek po wierzcho�ku.
void MPacking::continuePath(std::vector<int>* path, int rootIndex)
{
	path->push_back(vertices[rootIndex].number);	//Dodaj wierzcho�ek do �cie�ki
	int bestChildInVertices;

	while (1)
	{
		if (!vertices[rootIndex].children.size())				//root jest li�ciem - nie ma dzieci, wi�c koniec �cie�ki.
		{
			vertices[rootIndex].is_Deleted = true;
			return;
		}

		int bestChildIndex = 0;									//Dzieci s� wcze�niej umieszczane w wektorze od najwi�kszego do najmniejszego, 
		bestChildInVertices = findChildIndex(vertices[rootIndex].children[bestChildIndex]);			//wi�c najlepszy na ten moment b�dzie na pozycji 0 w wektorze.

		if (vertices[rootIndex].children[bestChildIndex]->parents.size() > 1)							//Przypadek, �e bestChild mo�e by� umieszczony w wielu kartonach. 
		{																								//Trzeba zdecydowa�, czy nie lepiej zostawi� go dla innego pude�ka.
		
			float rootAlter = getMaxAlternative(&(vertices[rootIndex]), vertices[rootIndex].children[bestChildIndex]);	//Sprawdzamy, jaka jest najlepsza inna opcja dla roota.
			if (rootAlter == 0)			//root nie ma innych dzieci, wi�c mo�emy do niego w�o�y� ten karton (bestChild).
			{
				v_gained += vertices[rootIndex].children[bestChildIndex]->volume;
				vertices[rootIndex].is_Deleted = true;
				
				for (Vertice* v : vertices[rootIndex].children[bestChildIndex]->parents)
				{
					removeChild(v, bestChildInVertices);	//Dzi�ki usuni�ciu tego dziecka z innych jego rodzic�w, dla tych innych rodzic�w najlepsze dziecko b�dzie na 0 pozycji w wektorze.
				}
				continuePath(path, bestChildInVertices);	//Tworzymy �cie�k� dalej
				return;
			}
			else		//root ma kilka alternatyw, trzeba sprawdzi�, czy nie ma lepszych alternatyw od innych.
			{
				float minChildAlter = rootAlter;
				float temp = 0;

				for (unsigned i = 0; i < vertices[rootIndex].children[bestChildIndex]->parents.size(); i++)	//Przegl�damy rodzic�w bestChilda i sprawdzamy, jakie maj� najlepsze alternatywy i wybieramy najmniejsz� z nich.
				{
					if (vertices[rootIndex].children[bestChildIndex]->parents[i]->is_Deleted || vertices[rootIndex].children[bestChildIndex]->parents[i] == &vertices[rootIndex])
						continue;	//Nie bierzemy pod uwag� usuni�tych wierzcho�k�w oraz roota.
					if ((temp = getMaxAlternative(vertices[rootIndex].children[bestChildIndex]->parents[i], vertices[rootIndex].children[bestChildIndex])) < minChildAlter)
						minChildAlter = temp;
				}

				if (minChildAlter < rootAlter)		//Kt�ry� rodzic nie ma lepszej alternatywy od roota, wi�c trzeba zostawi� pude�ko bestChild tamtemu rodzicowi i sprawdzi� nast�pny najlepszy.
				{
					vertices[rootIndex].children.erase(vertices[rootIndex].children.begin() + bestChildIndex);	//Usuwamy tymczasowo najlepsze dziecko roota i sprawdzamy kolejnego kandydata (while)
				}
				else		//root ma najs�absze alternatywy, wi�c powinien spakowa� to pude�ko.
				{
					v_gained += vertices[rootIndex].children[bestChildIndex]->volume;
					vertices[rootIndex].is_Deleted = true;
					for (Vertice* v : vertices[rootIndex].children[bestChildIndex]->parents)
					{
						removeChild(v, bestChildInVertices);//Dzi�ki usuni�ciu tego dziecka z innych jego rodzic�w, dla tych innych rodzic�w najlepsze dziecko b�dzie na 0 pozycji w wektorze.
					}
					continuePath(path, bestChildInVertices); //Tworzymy �cie�k� dalej
					return;
				}
			}//else
		}//if
		else		//bestChild ma tylko jednego rodzica, wi�c pakujemy je w roota.
		{
			v_gained += vertices[rootIndex].children[bestChildIndex]->volume;
			vertices[rootIndex].is_Deleted = true;
			continuePath(path, bestChildInVertices);	//Tworzymy �cie�k� dalej
			return;
		}
	}//while

	return;
}

void MPacking::regenerateGraph()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].is_Deleted = false;
	}
	
	rebuild();
	paths.clear();
}

void MPacking::removeChild(Vertice* parent, int child_number)
{
	for (int i = 0; i < parent->children.size(); i++)
	{
		if (parent->children[i]->number == child_number)
		{
			parent->children.erase(parent->children.begin() + i);
			break;
		}
	}
}
#endif