#include <iostream>
#include <queue>
#include <list>
#include <set>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#define INF 0x3f3f3f3f

using namespace std;

typedef pair<int, int> iPair;

class Graph {
    int V;


public:

    //ориентированный граф представляется в виде списка смежности
    //adj[i] - список вершин, смежных с вершиной i
    list<pair<int, int> >* adj;

    Graph(int V);
    ~Graph();

    void addEdge(int u, int v, int w);

    // prints shortest path from s
    void Dijkstra_shortest_path(int s);

    void printAdjMatrix();
};


Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair>[V];
}

Graph::~Graph()
{
    delete[] adj;
}


void Graph::addEdge(int u, int v, int weight)
{
    adj[u].push_back(make_pair(v, weight));
}


void Graph::Dijkstra_shortest_path(int src)
{
    priority_queue< iPair, vector<iPair>, greater<iPair> > pq;

    vector<int> dist(V, INF);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
       
        int u = pq.top().second;
        pq.pop();

  
        list<pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            
            int v = (*i).first;
            int weight = (*i).second;

            
            if (dist[v] > dist[u] + weight) {
                
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    /*std::cout << "Vertex Distance from vertex" << ' ' << src << std::endl;
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);*/
}

void Graph::printAdjMatrix()
{
    list<pair<int, int> >::iterator i;
    for (int j = 0; j < V; j++) {
        for (i = adj[j].begin(); i != adj[j].end(); ++i) {
            // j - source,  (*i).first - destination,  (*i).second - weight
            cout << '[' << j << ' ' << (*i).first << ' ' << (*i).second << ']' << endl;
        }
    }
}


int main()
{
    std::ofstream outFile("C:\\Users\\sasha\\PycharmProjects\\graphGenerator\\output.csv");
    if (!outFile) return -3;

    srand(unsigned(time(0)));

    clock_t t;
    int V = 100;

    outFile << "Number of vertexes,Number of edges,Time\n";

    for (int i = 1; i < 31; i++)
    {
        std::ifstream inFile("C:\\Users\\sasha\\PycharmProjects\\graphGenerator\\graph"+ to_string(i), std::ios::binary);
        if (!inFile) return -2; 

      
        Graph g(V);
        int numberOfEdges = 0;

        while (true) {
            int u, v, weight;
            inFile >> u;
            inFile >> v;
            
            //пропускаем {'weight':
            inFile.seekg(11, std::ios::cur);
            inFile >> weight;

            //пропускаем }
            inFile.seekg(1, std::ios::cur);

            if (!inFile)
                break;

            //std::cout << u << ' ' << v << ' ' << weight << std::endl;

            g.addEdge(u, v, weight);
            numberOfEdges++;
        }

        

        t = clock();
        g.Dijkstra_shortest_path(0);
        t = clock() - t;


        //Время затраченное только на алгоритм Дейкстры (без учета затрат на чтение файла)
        std::cout << "Graph " << i;
        std::printf(" Time: %d clicks (%f seconds).\n \n", t, ((float)t) / CLOCKS_PER_SEC);
        

        outFile << V << ',' << numberOfEdges << ',' << ((float)t) / CLOCKS_PER_SEC << '\n';

        V += 50;
        inFile.close();
    }

    
  
   
    outFile.close();
    return 0;
}
