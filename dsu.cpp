struct dsu{
    int n, comp;
    vector<int> p, s;
 
    dsu(int _n){
        n = _n;
        comp = n;
        p.resize(n);
        s.resize(n, 1);
 
        iota(p.begin(), p.end(), 0);
    }
 
    int find(int x){
        return p[x] = ((p[x]==x)?x:find(p[x]));
    }
 
    int merge(int x, int y){
        x = find(x); y = find(y);
 
        if(x==y) return 0;
 
        if(s[x] < s[y]) swap(x, y);
        comp--;
        p[y] = x; s[x] += s[y];
 
        return 1;
    }
 
 
};
