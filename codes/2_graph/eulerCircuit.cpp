//O(E)
//the graph shoud store edge as the second parameter of a pair
bool changeStart = false;
int start = 0;
deque<int> eulerCircuit;
bool usedEdges[200005];
 
void changeCircuitStart(int s) {
    eulerCircuit.pop_back();
    while(eulerCircuit.back() != s) {
        eulerCircuit.pf(eulerCircuit.back());
        eulerCircuit.pop_back();
    }
    eulerCircuit.pf(s);
}
//in case we had to add an edge between odd degree vertices
void circuitToPath(int e) {
    eulerCircuit.pop_back();
    while(eulerCircuit.back() != e) {
        eulerCircuit.pf(eulerCircuit.back());
        eulerCircuit.pop_back();
    }
}
void findCircuit(int u) {
    for(auto p : g[u]) {
        int v = p.F;
        int id = p.S;
        if(!usedEdges[id]) {
            if(changeStart) {
                changeStart = false;
                changeCircuitStart(u); start = u;
            }
            usedEdges[id] = true;
            eulerCircuit.pb(v);
            if(v == start) {
                if(u != v)  {
                    changeStart = true;
                }
            }
            else {
                findCircuit(v);   
            }
        }
    }
    // circuit is at eulerCircuit
    // for euler path changePath to start then use circuitToPath with end
}
 
