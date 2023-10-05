struct LCA {                                                
        int root, n, cnt;

        vector<vector<int>> adj;  
        vector<array<int, 21>> par;
        vector<int> ti, to, d;

        LCA(vector<vector<int>> aadj, int r){ 
            adj = aadj; n = adj.size();
            par.resize(n);
            d.assign(n, 0);
            root = r; cnt = 0;
            ti.resize(n); to.resize(n);

            d[root] = -1;
            dfs(root, root);

            for (int i = 1; i < 21; i++){
                for(int l = 0; l<n; l++){
                    par[l][i] = par[par[l][i-1]][i-1];
                }
            }
        }
        
        void dfs(int v, int p){
            par[v][0] = p;
            ti[v] = cnt++;
            d[v] = d[p]+1;
            for (auto i: adj[v]){
                if (i != p) dfs(i, v); 
            }
            to[v] = cnt++;
        }

        bool ia(int u, int v){
            return ti[u] <= ti[v] && to[u] >= to[v];
        }

        int operator()(int u, int v){

            if(ia(u, v)) return u;
            if(ia(v, u)) return v;

            for(int i = 20; i>=0; i--){
                if(!ia(par[u][i], v)) u=par[u][i];
            }

            return par[u][0];
        }
      
      int distance(int u, int v){
        return d[u]+d[v]-2*d[(*this)(u, v)];
      }
};  
