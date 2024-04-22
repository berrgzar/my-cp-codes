
const int n= 2, m = 2;

struct matrix{
    array<array<int, n>, m> a;

    matrix(){
        for(int i=0; i<n; i++){
            for(int l=0; l<m; l++){
                a[i][l] = 0;
            }
        }
    }

    matrix operator*(const matrix &b){
        matrix c;

        for(int i=0; i<n; i++){
            for(int l=0; l<n; l++){
                for(int j=0; j<m; j++){
                    c[i][l] += a[i][j], b[j][l];
                }
            }
        }
        return c;
    }

    matrix operator+(const matrix &b){
        matrix c;
        for(int i=0; i<n; i++){
            for(int l=0; l<m; l++){
                c[i][l] = a[i][l] + b[i][l];
            }
        }
        return c;
    }

    matrix operator^(int x){
        matrix c;
        matrix tmp;
       
        c[0]={1, 0};
        c[1]={0, 1};

        for(int i=0; i<n; i++){
            for(int l=0; l<m; l++){
                tmp[i][l] = a[i][l];
            }
        }
 
        while(x){
            if(x&1) c = (c*tmp);
            tmp= tmp*tmp;
            x/=2;
        }  
        return c;
    }

    array<int, 2>& operator[](int x){
        return a[x];
    }
    const array<int, 2>& operator[](int x) const{
        return a[x];
    }  
};
