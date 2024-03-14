#include <bits/stdc++.h>
using namespace std;
double infoD(vector<vector<string>> data, int x) {
    map<string, double> m;
    int n = data.size();
    for(auto it: data) {
        m[it[x]]++;
    }
    double info = 0;
    for(auto it: m) {
        info -= (it.second/n)*log2(it.second/n);
    }
    return info;
}
double gainA(vector<vector<string>> data, int x, int y, double infoD) {
    map<string, double> m;
    int n = data.size();
    for(auto it: data) {
        m[it[x]]++;
    }
    double infoA = 0;
    for(auto it: m) {
        double factor = 0;
        map<string, double> m2;
        for(auto it2: data) {
            if(it2[x]==it.first) {
                m2[it2[y]]++;
            }
        }
        for(auto it2: m2) {
            factor -= (it2.second/it.second)*log2(it2.second/it.second);
        }
        factor *= (it.second/n);
        infoA += factor;
    }
    return infoD - infoA;
}
int getSplitA(vector<vector<string>> data) {
    int dec = data[0].size() - 1;
    double t = infoD(data, dec);
    vector<pair<double, double>> v;
    for(int i = 0; i<dec; i++) {
        v.push_back({gainA(data, i, dec, t), i});
    }
    sort(v.begin(), v.end(), greater<pair<double, double>>());
    return v[0].second;
}
void getTree(vector<vector<string>> data) {
    int splitA = getSplitA(data);
    cout<<splitA<<endl;
    map<string, vector<vector<string>>> newDatas;
    int n = data.size();
    int m = data[0].size();
    for(auto it: data) {
        vector<string> temp;
        for(int i = 0; i<m; i++) {
            if(i!=splitA) {
                temp.push_back(it[i]);
            }
        }
        newDatas[it[splitA]].push_back(temp);
    }
    for(auto it: newDatas) {
        cout<<it.first<<": ";
        set<string> st;
        int last = it.second[0].size() - 1;
        for(auto it2: it.second) {
            st.insert(it2[last]);
        }
        if(st.size()==1) {
            cout<<*st.begin()<<endl;
            continue;
        }
        getTree(it.second);
        // cout<<it.first<<endl;
        // for(auto it2: it.second) {
        //     for(auto it3: it2) {
        //         cout<<it3<<" ";
        //     }
        //     cout<<endl;
        // }
        // cout<<endl;
    }
}
int main() {
    vector<vector<string>> data = {
        {"Sunny", "Hot", "High", "Weak", "No"},
        {"Sunny", "Hot", "High", "Strong", "No"},
        {"Overcast", "Hot", "High", "Weak", "Yes"},
        {"Rain", "Mild", "High", "Weak", "Yes"},
        {"Rain", "Cool", "Normal", "Weak", "Yes"},
        {"Rain", "Cool", "Normal", "Strong", "No"},
        {"Overcast", "Cool", "Normal", "Strong", "Yes"},
        {"Sunny", "Mild", "High", "Weak", "No"},
        {"Sunny", "Cool", "Normal", "Weak", "Yes"},
        {"Rain", "Mild", "Normal", "Weak", "Yes"},
        {"Sunny", "Mild", "Normal", "Strong", "Yes"},
        {"Overcast", "Mild", "High", "Strong", "Yes"},
        {"Overcast", "Hot", "Normal", "Weak", "Yes"},
        {"Rain", "Mild", "High", "Strong", "No"}
    };
    getTree(data);
    return 0;
}