
struct scc{
    int n, cnt;
    vector<vector<int>> g, rg;
    vector<int> ans, vis, order, comp;

    scc(int _n, vector<vector<int>> _g){
        g = _g;
        n = _n;
        cnt = 0;
        rg.resize(n);
        ans.resize(n, 0);
        vis.resize(n, 0);

        for(int i=0; i<n; i++){
            for(auto l: g[i]){
                rg[l].push_back(i);
            }
        }
        
        for(int i = 0; i< n; i++){
            if(!vis[i]) dfs(i);
        }

        fill(vis.begin(), vis.end(), 0);

        reverse(order.begin(), order.end());

        for(auto i: order){
            if(!vis[i]){
                dfs2(i);

                for(auto l: comp) ans[l] = cnt;
                cnt++; comp.clear();
            }
        }
    }

    void dfs(int v){
        vis[v] = 1;
        for(auto i: g[v]){
            if(!vis[i]) dfs(i); 
        }
        order.push_back(v);
    }

    void dfs2(int v){
        vis[v] = 1;
        for(auto i: rg[v]){
            if(!vis[i]) dfs2(i); 
        }
        comp.push_back(v);
    }

};
