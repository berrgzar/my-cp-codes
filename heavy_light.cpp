#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9+37, N = 2e5+37;


//segtree struct ** bunu vectore segment tree atabilmek için yapıoz

struct segtree{
	int n, tl, tr, pos, val;
	vector<int> st, va;
	
	int base = -INF;

	int merge(int a, int b){
		return max(a, b);
	}

	segtree(){}; // vectore atıyabilemek için

	segtree(vector<int> a){
		n = a.size(); va = a; 
		st.resize(4*n, base);

		build(1, 0, n-1);
	}

	void build(int v, int l, int r){
		if(l==r) st[v] = va[l];
		else{
			int mid = (l+r) / 2;
			build(v*2, l, mid);
			build(v*2+1, mid+1, r);

			st[v] = merge(st[v*2], st[v*2+1]);
		}
	}

	void update(int v, int l, int r){
		if(l == r) st[v] = val;
		else{
			int mid = (l+r)/2;

			if(pos<=mid) update(v*2, l, mid);
			else update(v*2+1, mid+1, r);

			st[v] = merge(st[v*2], st[v*2+1]);
		}
	}
	void update(int v, int x){
		pos = v; val = x;
		update(1, 0, n-1);		
	}
	int get(int v, int l, int r){
		if(l>tr || r < tl) return base;
		if(l>= tl && r<= tr) return st[v];
		int mid = (l+r) / 2;
		return merge(get(v*2, l, mid), get(v*2+1, mid+1, r));
	}
	int operator()(int l, int r){
		tl = l; tr = r;
		return get(1, 0, n-1);
	}

};


vector<int> adj[N], s(N, 1), depth(N), val(N), par(N), top(N); 
vector<int> seg_id(N), seg_pos(N);
int chain_count=0;

vector<int> chain_index, chain_value;
vector<segtree> seg;

// chainleri oluştur
	// 1 gerekli her bilgiyi bul
		// time in time out // ancestor bulmak için
		// depth
		// subtree size vb

	void dfs(int v, int p){
		depth[v] = depth[p] + 1;
		par[v] = p;
		for (auto i: adj[v]){
			if(i!=p){
				dfs(i, v);
			 	s[v] += s[i];
			}
		}	
	}	


	// 2 chain 
		// en "ağır" olanı seç
		// segment treeleri vectore at
		// bütün nodeların hangi chainde ve hangi indexte olduğunu bul

	void hld(int v, int p){
		chain_index.push_back(v);
		chain_value.push_back(val[v]);
		int id = -1;
		
		for(auto i: adj[v]){
			if(i==p) continue;

			if(id == -1) id = i;
			else if(s[id] < s[i]) id = i; 
		}

		// id = en büyük subtree
		// leaf sayısı kadar chainimiz var

		if(id==-1){ // if leaf
			reverse(chain_index.begin(), chain_index.end());
			reverse(chain_value.begin(), chain_value.end());

			for(int i =0; i<chain_index.size();  i++){
				int v = chain_index[i];
				seg_id[v] = chain_count;
				seg_pos[v] = i;
			}

			top[chain_count]=chain_index.back();
			seg.push_back(segtree(chain_value));
			chain_count++;
			chain_index.clear();
			chain_value.clear();
			// her noktanın hangi chainde olduğunu 
			// ve her noktanın hangi indexte olduğunu bilmek istiyoruz
		}
		else{// leaf değilsen devam etmelisin
			hld(id, v); 
		}

		for(auto i: adj[v]){
			if(i==p || i == id) continue;
			hld(i, v); // yeni chainler başlattı
		}
	}
// query halletme	

int query(int a, int b){
	int ans = 0;

	while(seg_id[a] != seg_id[b]){
		int a_id = seg_id[a], b_id = seg_id[b];

		if(depth[top[a_id]] < depth[top[b_id]]){
			swap(a, b); swap(a_id, b_id);
		}

		ans = max(ans, seg[a_id](seg_pos[a], seg_pos[top[a_id]]));
		a = par[top[a_id]];
	}

	// aynı chaindeler
	if(seg_pos[a] > seg_pos[b]) swap(a, b);
	int a_id = seg_id[a];
	ans = max(ans, seg[a_id](seg_pos[a], seg_pos[b]));

	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n, q; cin >> n >> q;


	for(int i=0; i<n; i++) cin >> val[i];


	for(int i = 0; i<n-1; i++){
		int x, y; cin >> x >> y;
		x--; y--;
		
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	dfs(0, 0); hld(0, 0);

	while(q--){
		int type, a, b; cin >> type >> a >> b;

		if(type == 1){ // node a nın değerini b ye değiştir
			a--;
			seg[seg_id[a]].update(seg_pos[a], b);
		}
		else{ // a dan b ye maximum değeri bul
			a--; b--; 

			cout<<query(a, b)<<" "; // a ve b arasındaki maxı bul
		}
	}


}


	
	







