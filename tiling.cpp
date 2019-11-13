#include "tiling.hpp"
using namespace std;

double _dist_(Point &p, Point &q){
    return sqrt(pow(p.x-q.x,2) + pow(p.y-q.y,2) + pow(p.z-q.z,2));
}

double _areaTriangle_(Point &a,Point &b,Point &c){
    double sa = _dist_(c,b);
    double sb = _dist_(a,c);
    double sc = _dist_(a,b);
    double s = (sa+sb+sc)/2;
    return sqrt(s*(s-sa)*(s-sb)*(s-sc));
}

void optimalTiling(vector<Point> &c1, vector<Point> &c2, vector<Point> &path){
    int c1s = c1.size() + 1, c2s = c2.size() + 1;

    double dp[c1s][c2s];
    int bk[c1s][c2s];

    // Initialize the arrays :
    rep(i,0,c1s) rep(j,0,c2s) dp[i][j] = INT_MAX;
    rep(i,0,c1s) rep(j,0,c2s) bk[i][j] = 0;

    // Base cases :
        dp[0][0] = 0;
        rep(i,1,c1s){
            dp[i][0] = dp[i-1][0] + _areaTriangle_(c2[0],c1[i%c1.size()],c1[i-1]);
            bk[i][0] = 1;
        }
        rep(i,1,c2s){
            dp[0][i] = dp[0][i-1] + _areaTriangle_(c1[0],c2[i%c2.size()],c2[i-1]);
            bk[0][i] = 2;
        }

    // DP recursion :
        rep(i,1,c1s){
            rep(j,1,c2s){
                dp[i][j] = dp[i-1][j] + _areaTriangle_(c2[j%c2.size()],c1[i%c1.size()],c1[i-1]);
                bk[i][j] = 1;

                double temp = dp[i][j-1] + _areaTriangle_(c2[j-1],c2[j%c2.size()],c1[i%c1.size()]);
                if(temp<dp[i][j]){
                    dp[i][j] = temp;
                    bk[i][j] = 2;
                }
            }
        }


    // Getting the result fromm backtracking :
    int p=c1s,q=c2s;
    path.pb(c2[q % c2.size()]);
    path.pb(c1[p % c1.size()]);
    while(p!=0 && q!=0){
        if(bk[p][q]==2){
            q--;
            path.pb(c2[q]);
        }
        else{
            p--;
            path.pb(c1[p]);
        }
    }

    // Check the path
    cout<<path.size()<<"\n";
    rep(i,0,path.size()) cout<<path[i].x<<" "<<path[i].y<<" "<<path[i].z<<"\n";
}
