#include <bits/stdc++.h>
using namespace std;

struct node{
    int x, y;
    node(){};

    node(int a, int b){
        x = a; y = b;
    }   
    bool  operator<(node a){
        if(a.x == x){
            return y<a.y;
        }
        return x<a.x;
    }
    bool operator ==(node a){
        return(a.x == x &&a.y==y);
    }
};
    
int x(node a, node b){
    return a.x-b.x;
}

int y(node a, node b){
    return a.y-b.y;
} 

int clock_wise(node a, node b, node c){
    int val = x(a, c)*y(b, c)-y(a, c)*x(b, c);
    if(val<0) return -1;
    else if(val==0) return 0;
    return 1;
}


    
struct convex_hull{
    int n;
    vector<node> convex;


    convex_hull(vector<node> a){
        n = a.size();
        sort(a.begin(), a.end());

        vector<node> upper, lower;

        upper.push_back(a[0]);
        upper.push_back(a[1]);
        for(int i=2; i<n; i++) {
            int v = upper.size();
            while(v>=2&&clock_wise(a[i], upper[v-1], upper[v-2])<0){
                upper.pop_back();
                v = upper.size();
            };
            upper.push_back(a[i]);
        }

        lower.push_back(a[0]);
        lower.push_back(a[1]);
            for(int i=2; i<n; i++){
            int v = lower.size();
            while(v>=2&&clock_wise(a[i], lower[v-1], lower[v-2])>0){
                lower.pop_back();
                v = lower.size();
            };
            lower.push_back(a[i]);
        }

        for(int i=lower.size()-1; i>=0; i--){
            if(lower[i]==upper[0]) continue;
            int v = upper.size();
            if(clock_wise(lower[i], upper[v-1], upper[v-2])>0){
                upper.push_back(lower[i]);
            }
        }
        convex = upper;
        n = convex.size();



    }

    node operator[](int x){
        return convex[x];
    }

};
