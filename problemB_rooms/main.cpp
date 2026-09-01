#include <bits/stdc++.h>

using namespace std;

int main() {

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    int m;
    
    cin >>  m;

    vector<pair<long long,long long>> meetings(m);

    for (int i = 0; i < m; i++) {

        long long s, e;

        cin >> s >> e;

        meetings[i] = {s, e};

    }

    // TODO: compute minimum number of rooms required

    // Por recomendacion del profesor, se asume que el vector meetings
    // ya esta ordenado por el tiempo de inicio de cada reunion.

    vector<pair<long long, long long>> rooms2; 
    
    int j;

    for(int i = 0; i < meetings.size(); i++){
        j = 0;
        if(rooms2.size()==0){
            rooms2.push_back(meetings[i]);
        } else{
            while(true){
                if(rooms2[j].second <= meetings[i].first){
                    rooms2[j] = meetings[i];
                    break;
                } else if(j == rooms2.size()-1){
                    rooms2.push_back(meetings[i]);
                    break;
                } else{
                    j++;
                }
            }
        }

    }

    int rooms = 0;

    rooms = rooms2.size();

    cout << rooms << "\n";

    return 0;

}
