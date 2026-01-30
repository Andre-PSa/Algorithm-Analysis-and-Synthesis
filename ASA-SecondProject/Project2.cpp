#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;

struct Vertice{
    vector<int> successors;
    bool visited = false;
};

void topologicalOrder(vector<Vertice> *Vertices, Vertice *v, vector<int> *ordered, int idx){
    v->visited = true;
    for (int i = 0; i < (int)v->successors.size(); i++){
        Vertice *successor = &((*Vertices)[v->successors[i]]);
        if (!successor->visited){
            topologicalOrder(Vertices,successor,ordered,v->successors[i]);
        }
    }
    ordered->push_back(idx);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m1, m2, k;
    long long M;
    cin >> n >> M >> m1 >> m2 >> k;
    int num_trucks = m2-m1+1;
    vector<vector<pair<int,int>>> Trucks(num_trucks);
    vector<Vertice> Vertices(n+1);
    for (int i = 0; i < k; i++){
        int dad;
        int kid;
        cin >> dad >> kid;
        Vertices[dad].successors.push_back(kid);
    }

    //Criação de uma ordem topológica(O(n + k))
    vector<int> ordered;
    for (int i = 1; i <= n; i++){
        Vertice *v = &Vertices[i];
        if (!v->visited){
            topologicalOrder(&Vertices,v,&ordered,i);
        }
    }

    //Aplicação do algoritmo
    vector<long long> vetorNCaminhos(n+1,0);
    for(int A = n-1; A >= 0; A--){
        int A_idx = ordered[A];
        vetorNCaminhos[A_idx]=1;
        for(int B = A; B >= 0; B--){
            int B_idx = ordered[B];
            Vertice v= Vertices[B_idx];
            if (vetorNCaminhos[B_idx]>0){
                int decreaseByM = 1;
                for (int successor = 0; successor < (int)v.successors.size(); successor++){
                    int s_idx = v.successors[successor];
                    vetorNCaminhos[s_idx]+=vetorNCaminhos[B_idx]; //Caminhos pelos sucessores de B
                    if (vetorNCaminhos[s_idx] > M){
                        vetorNCaminhos[s_idx]-=decreaseByM*M;
                        if (vetorNCaminhos[s_idx] > M){
                            decreaseByM++;
                            vetorNCaminhos[s_idx]-=M;
                        }
                    }
                }
            }
        }
        vetorNCaminhos[A_idx] = 0;
        for (int B_idx = 1; B_idx <= n; B_idx++){
            if (vetorNCaminhos[B_idx] > 0){
                
                long long n_paths = vetorNCaminhos[B_idx];
                long long pair_truck = 1 + (n_paths % M);
                if (pair_truck >= m1 && pair_truck <= m2){
                    Trucks[pair_truck - m1].push_back({A_idx, B_idx});
                }
            }
            vetorNCaminhos[B_idx]=0;
        }
    }
        
    for(int i = 0; i < num_trucks; i++){
        auto& pares = Trucks[i];
        sort(pares.begin(), pares.end());
        cout << "C" << i + m1;
        for(const auto& pair : Trucks[i]){
            cout << " " << pair.first << "," << pair.second;
        }
        cout << "\n";
    }
}