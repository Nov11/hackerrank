#include<bits/stdc++.h>

using namespace std;
//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops
struct Workshop {
    int start;
    int end;
    int duration;
    Workshop(int start, int duration):start(start), duration(duration), end(start + duration){
        
    }
};

struct Available_Workshops{
    int n;
    vector<Workshop> v;
};

Available_Workshops* initialize (int start_time[], int duration[], int n) {
    Available_Workshops* result = new Available_Workshops;
    result->n = n;
    for(int i = 0; i < n; i++){
        result->v.push_back(Workshop(start_time[i], duration[i]));
    }
    return result;
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
    vector<Workshop> & tmp = ptr->v;
    sort(tmp.begin(), tmp.end(), [](const Workshop&a,const Workshop& b){return a.end < b.end;});
    int result = 0;
    int e = 0;
    for(auto& item : tmp){
        if(item.start >= e){
            result++;
            e = item.end;
        }
    }
    
    return result;
}
int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
