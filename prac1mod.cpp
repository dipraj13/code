#include <iostream> 
#include <vector>
#include <stack>
#include <queue>
#include <omp.h>

using namespace std;

class Graph{
    
    public :
    int size;
    vector<vector<int>> adjlist;

    Graph(int num){
        size = num;
        adjlist.resize(num);
    }

    void addEdge(int u, int v){
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }

    void parallelbfs(int start){
        queue<int> q;
        vector<int> visited(size, false);

        visited[start] = true;
        q.push(start);

        while(!q.empty()){
            int currentSize = q.size();
            vector<int> currentLevel;

            for(int i = 0;i< currentSize;i++){
                currentLevel.push_back(q.front());
                q.pop();
            }
            #pragma omp parallel for
            for(int i =0;i<currentLevel.size();i++){

                int node = currentLevel[i];
                #pragma omp critical
                {cout << node << " ";}

                for(int j = 0;j < adjlist[node].size();j++){
                    int neb = adjlist[node][j];
                    #pragma omp critical
                    {if(!visited[neb]){
                        visited[neb] = true;
                        q.push(neb);
                    }}

                }
            }
            cout << endl;
        }
    }

    void paralleldfs(int start){
        stack<int> s;
        vector<bool> visited(size, false);

        s.push(start);
        
        while(!s.empty()){
            int node;
            #pragma omp critical 
            {node = s.top();
            s.pop();}

            if(!visited[node]){
                visited[node] = true;
                #pragma omp critical
                {cout << node << " ";}
            }
            #pragma omp parallel for
            for(int i =0 ;i < adjlist[node].size();i++){
                int neb = adjlist[node][i];

                #pragma omp critical
                {if(!visited[neb]){
                    s.push(neb);
                }}
            }
            
        }
        cout << endl;

    }

};

int main(){
    int size;
    cout << "Enter the size of the Graph : ";
    cin >> size;

    Graph g(size);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    int sNode = 0;

    cout << "Parallel BFS from node "<<sNode << ":\n";
    g.parallelbfs(sNode);

    cout << "Parallel DFS from node "<<sNode << ":\n";
    g.paralleldfs(sNode);

    return 0;
}