#include <stdio.h>
#include <iostream>
#include <map>
#include <queue>
#include <memory>
#include <vector>

using namespace std;


struct Node {
    vector<Node*> neighbors;
    bool hub;
};

void printQueue(queue<pair<Node*, int>> q) {
    while(q.size()) {
        auto p = q.front();
        q.pop();
        cout << '(' << p.first << ", " << p.second << ") ";
    }
    cout << endl;
}


/*vector<pair<Node*, int>> */ void findHubs(Node* cur, int R) {
    vector<Node*> ret;
    map<Node*, int> visited;
    queue<pair<Node*, int>> toVisit;

    toVisit.push(make_pair(cur, 0));
    while(toVisit.size()) {
        Node *n;
        int depth;
        
        tie(n, depth) = toVisit.front();
        toVisit.pop();
    
        if(visited.count(n)) {
            if (visited[n] > depth + 1) {
                visited[n] = depth + 1;
            }
        }
        else {
            visited[n] = depth + 1;
            if (depth + 1 <= R) {
                for (auto neighbor : n->neighbors) {
                    if (neighbor != n) {
                        toVisit.push(make_pair(neighbor, depth + 1));
                    }
                }
            }
        }
    
    
    }





}

int main() {
 

    return 0;
}
