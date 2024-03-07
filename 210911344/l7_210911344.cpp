#include<bits/stdc++.h>
using namespace std;
vector<vector<char>> prune(map<vector<char>, int> c, int ms) {
    vector<vector<char>> ans;
    for(auto it: c) {
        if(it.second>=ms) {
            ans.push_back(it.first);
        }
    }
    return ans;
}
map<vector<char>, int> join(vector<vector<char>> l, int pass) {
    map<vector<char>, int> ans;
    int n = l.size();
    for(int i = 0; i<n; i++) {
        for(int j = i+1; j<n; j++) {
            bool merge = true;
            for(int k = 0; k<pass; k++) {
                if(l[i][k]!=l[j][k]) {
                    merge = false;
                }
            }
            if(merge) {
                vector<char> temp = l[i];
                temp.push_back(l[j][pass]);
                ans[temp] = 0;
            }
        }
    }
    return ans;
}
int count(vector<char> arr, vector<vector<char>>& db) {
    int ans = 0;
    for(auto it: db) {
        vector<char> fin(it.size() + arr.size());
        auto lst = set_intersection(it.begin(), it.end(), arr.begin(), arr.end(), fin.begin());
        int inters = lst-fin.begin();
        ans+=(arr.size()==inters);
    }
    return ans;
}
int main() {
    vector<vector<char>> db = {{'A', 'B', 'E'}, {'B', 'D'}, {'B', 'C'}, {'A', 'B', 'D'}, {'A', 'C'}, {'B', 'C'}, {'A', 'C'}, {'A', 'B', 'C', 'E'}, {'A', 'B', 'C'}};
    vector<vector<char>> ans;
    sort(db.begin(), db.end());
    map<vector<char>, int> c;
    vector<vector<char>> l;
    int ms = 2;
    for(auto it:db) {
        for(auto it2: it) {
            c[{it2}] = 0;
        }
    }
    int pass = 0;
    while(true) {
        for(auto& it: c) {
            it.second = count(it.first, db);
        }
        l = prune(c, ms);
        if(l.size()==0) {
            break;
        }
        for(auto it: l) {
            ans.push_back(it);
        }
        c = join(l, pass++);
    }
    for(auto it: ans) {
        for(auto it2: it) {
            cout<<it2<<" ";
        }
        cout<<endl;
    }
    return 0;
}