
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N=1e5+37;
vector<array<int, 5>> adj[N];
vector<array<int, 2>> gh(N*2);
int par[N+5][20], mi[N+5][20], ti[N+5], to[N+5], cnt, st[(int)30*N]; 
vector<int> roots(N*2), L(30*N, -1), R(30*N, -1),  pos(N*2);

void dfs(int v, int p, int co){
    ti[v] = cnt++;
    par[v][0] = p; mi[v][0] = co;

    for (auto [i, x, c, s, gh]: adj[v]){
        if (i == p) continue;

        dfs(i, v, s);
    }

    to[v] = cnt++;
}

void build(int v, int l, int r){
    st[v] = 0;
    if (l<r){
        L[v]=cnt++; R[v]=cnt++;
        int mid=(l+r)/2;
        build(L[v], l, mid); build(R[v], mid+1, r);

    }
}

void update(int v, int v2,  int l, int r, int pos, int val){
  // cout<<v<<" "<<v2<<" "<<endl;

    if (l==r) st[v] = val;
    else if (l < r && v2!=-1 && v!=-1){
        int mid = (l+r) / 2;

        if (pos <= mid){
            L[v] = cnt++;
            R[v] = R[v2];

            update(L[v], L[v2], l, mid, pos, val);
        }
        else{
            L[v] = L[v2];
            R[v] = cnt++;

            update(R[v], R[v2], mid+1, r, pos, val);
        }

        st[v] = st[L[v]]+ st[R[v]];

    }
}

int get(int v, int l, int r, int val){
    if(l>r) return 0;

    if(gh[l][0] >= val) return 0;

    if(gh[r][0] < val) return st[v];

    int mid=(l+r)/2;

    return get(L[v], l, mid, val)+get(R[v], mid+1, r, val);

}

void dfs1(int v, int p){
    for(auto [i, x, c, s, gh]: adj[v]){
        if(i == p ) continue;
        roots[i]=cnt++;

        update(roots[i], roots[v], 0, N-1, pos[gh], c);

        dfs1(i, v);
    }
}

int ia(int x, int y){
    return (ti[x] <= ti[y] && to[x] >= to[y]);
}

int lca(int x, int y){
    if(ia(x, y)) return x;
    if(ia(y, x)) return y;

    for(int i=19; i>=0; i--){
        if(!ia(par[x][i], y)) x=par[x][i];
    }

    return par[x][0];
}

int g(int x, int y){

    int k=1e18;
    if(x == y) return k;

    for(int i=19; i>=0; i--){
        if(!ia(par[x][i], y)){
            k = min(k, mi[x][i]);
            x = par[x][i];
        }
    }

    return min(k, mi[x][0]);
}


void ans(){
    int x, y, e; cin >> x >> y >> e;
    x--; y--;

    int f=lca(x, y);
    int k = min(g(x, f), g(y, f));
    int s = 0;

    for (int l = 29; l >= 0; l--){
        int tmp = s + (1ll<<l);
        if (tmp <= k){

            int a= get(roots[x], 0, N-1, tmp) +get(roots[y], 0, N-1, tmp);
            a -= 2*get(roots[f], 0, N-1, tmp);

            //if(x==f) a=get(roots[y], 0, N-1, tmp) ;
           // cout<<x<<" "<<y<<" "<<f<<" "<<a<<"\n";
            if(a <= e) s = tmp;
        }
    }

    cout << s << "\n";

}


 

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);


    int n; cin>>n;
    int x, y, v, c, s;

    for (int i = 0; i < 2*N; i++){
        gh[i] = {(int)1e18, i};
    }

    for (int i = 0; i < n-1; i++){
        cin >> x >> y >> v >> c >> s;
        gh[i] = {v, i};
        x--; y--;
        adj[x].push_back({y, v, c, s, i});
        adj[y].push_back({x, v, c, s, i});

    }

    for (int i = 0; i < n; i++){
        for (int l = 0; l < 20; l++){
            mi[i][l] = 1e18;
        }
    }


    sort(gh.begin(), gh.end());

    for(int i=0; i<N; i++) pos[gh[i][1]] = i;


    dfs(0, 0, 1e18);

    for (int i = 1; i < 20; i++){
        for (int j = 0; j < N; j++){
            par[j][i] = par[par[j][i-1]][i-1];
            mi[j][i] = min(mi[j][i-1], mi[par[j][i-1]][i-1]); 
        }
    }


    cnt=1;

    build(0, 0, N);

    dfs1(0, 0);

    int q; cin >> q;

    while(q--){
        ans();
    }

    cerr<<"tadaaa\n";
}  
