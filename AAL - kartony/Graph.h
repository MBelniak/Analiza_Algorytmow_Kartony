/*
Klasa Graph implementuje strukturê danych - graf skierowany wa¿ony - przystosowan¹ do rozwi¹zania problemu pakowania kartonów.
Micha³ Belniak grupa 5I3, prowadz¹cy: £ukasz Skonieczny
Projekt: AAL-11-LS kartony
*/

#include <vector>
#include <algorithm>
#ifndef GRAPH_H
#define GRAPH_H
class Graph {
protected:
	struct Vertice {	//struktura wierzcho³ka
		unsigned number;
		float width, length, height, volume;  //width>=length>=height
		std::vector<Vertice*> children, parents;	//wskaŸniki odpowiadaj¹ce krawêdziom w grafie.
		bool is_Deleted;		//flaga oznaczaj¹ca, czy wierzcho³ek zosta³ usuniêty z grafu. Gdyby usuwaæ wierzcho³ek z wektora wierzcho³ków, pozosta³e wierzcho³ki mog³y by zmieniæ pozycjê.
	};

	std::vector<Vertice> vertices;	
	float v_total;	//ca³kowita objêtoœæ kartonów
	int findRoot();	//zwraca pozycjê w wektorze pierwszego wierzcho³ka, który jest korzeniem drzewa.
	static bool compare(Vertice first, Vertice second)
	{
		return first.volume>second.volume;
	}

public:
	void addVertice(float dims[3]);//Dodanie pude³ka o wymiarach dims[] do grafu jako wierzcho³ek.
	void findParentsAndChildren();		//Wyszukanie rodziców i dzieci ka¿dego wierzcho³ka jeszcze raz.
};

//Dodanie wierzcho³ka do grafu.
void Graph::addVertice(float dims[3])
{
	struct Vertice v;
	v.number = vertices.size()+1;
	v.width = dims[0];
	v.length = dims[1];
	v.height = dims[2];
	v.volume = v.width*v.length*v.height;
	v.is_Deleted = false;
	vertices.push_back(v);
	v_total += v.volume;
}

int Graph::findRoot()
{
	for (unsigned i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].is_Deleted)
			continue;
		if (vertices[i].parents.size() == 0)
			return i;
	}
	return -1;
}

//Szukanie krawêdzi w grafie. O(n^2) 
void Graph::findParentsAndChildren()
{
	std::sort(vertices.begin(), vertices.end(), &(Graph::compare)); //Presortowanie
	for (unsigned i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].is_Deleted)
			continue;
		for (unsigned k = i + 1; k < vertices.size(); k++)	//Nie musimy analizowaæ pude³ek wiêkszych, bo wiêksze analizuj¹ mniejsze.
		{
			if (vertices[k].is_Deleted)
				continue;
			if (vertices[k].width < vertices[i].width && vertices[k].length < vertices[i].length && vertices[k].height < vertices[i].height)
			{
				vertices[i].children.push_back(&vertices[k]);
				vertices[k].parents.push_back(&vertices[i]);
			}
		}
	}
}
#endif

