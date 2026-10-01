#include<bits/stdc++.h>

using namespace std;


void solve(){

    int n;
    cin>>n;

    string s;
    cin>>s;

    int ans = n-1;

    for(int i=0;i+2<n;i++){
        if(s[i] == s[i+2]){
            ans--;
        }
    }

    cout<<ans<<endl;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}