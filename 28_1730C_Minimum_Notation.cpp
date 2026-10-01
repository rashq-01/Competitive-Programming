#include<bits/stdc++.h>

using namespace std;

void fun(){
    string s;
    cin>>s;

    int n = s.length();
    char minDig = '9';
    string res = "";

    for(int i=n-1;i>=0;--i){
        if(s[i]>minDig){
            res += min((char)(s[i] + 1) , '9');
        }else{
            minDig = s[i];
            res +=s[i];
        }
    }

    sort(res.begin() , res.end());
    cout<<res<<endl;

}

int main(){
    int T;
    cin>>T;
    while(T--){
        fun();
    }

    return 0;
}