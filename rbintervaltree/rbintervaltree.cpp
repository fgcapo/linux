#include <map>
#include <iostream>
using namespace std;

map<int, bool> ds;
/*
// candidate's code
void insert(int s, int e) {
    auto sit = ds.upper_bound(s);
    auto eit = ds.upper_bound(e);

    while (sit != eit) {
        auto temp = eit;
        sit++; // should be ++sit?
        ds.erase(temp);
    }

    if (eit != ds.end() && *eit == false) ds[e] = true;

    if (sit != ds.begin()) {
        sit--;
        if (*sit == true) ds[s] = false;
    }
}
*/

//void insert(int s, int e) { ds[s] = false; ds[e]= true; }
void insert(int s, int e) {
    auto sit = ds.upper_bound(s);
    auto eit = ds.upper_bound(e);

    while (sit != eit && eit != ds.end()) {
        auto temp = eit;
        sit++; // should be ++sit?
        ds.erase(temp);
    }

    if (eit == ds.end()) {
        ds[e] = true;
    }
    else if (eit->second == false) {
        ds[e] = true;
    }

    //
    if (sit != ds.begin()) {
        --sit;
        if (sit->second == true) ds[s] = false;
    }
    else {
        ds[s] = false;
    }
}


void print() {
    for (auto p: ds) {
        cout << p.first;
        if (p.second) cout << '*';
        cout << ' ';
    }
    cout << endl;
}

int main() {
    insert(0, 10);
    insert(5, 15);
    insert(100, 200);
    print();
    
    insert(99, 101);
    print();
    
    insert(6, 199);
    print();
}
