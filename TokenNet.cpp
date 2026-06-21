#include <iostream>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>
#include <algorithm>
using namespace std;

// 1. ROUTER SETTINGS (AVL / Balanced BST via std::map)
class RouterSettings {
    map<int, string> routers;
public:
    void addRouter(int id, const string& config) {
        routers[id] = config;
    }
    void removeRouter(int id) {
        routers.erase(id);
    }
    string getConfig(int id) {
        if (routers.count(id)) return routers[id];
        return "Router not found";
    }
    void displayAll() {
        for (auto& r : routers)
            cout << "Router " << r.first << ": " << r.second << endl;
    }
};

// 2. PERMISSION UNDO (Stack)
class PermissionUndo {
    stack<pair<string, bool>> history;
public:
    void grantToken(const string& computer) {
        history.push({computer, true});
        cout << "Token GRANTED to " << computer << endl;
    }
    void revokeToken(const string& computer) {
        history.push({computer, false});
        cout << "Token REVOKED from " << computer << endl;
    }
    void undoLast() {
        if (history.empty()) { cout << "Nothing to undo." << endl; return; }
        auto last = history.top();
        history.pop();
        string action = last.second ? "grant" : "revoke";
        cout << "Undone: " << action << " for " << last.first << endl;
    }
};

// 3. REQUEST LINE (Queue) 
class RequestLine {
    queue<string> requests;
public:
    void addRequest(const string& computer) {
        requests.push(computer);
        cout << computer << " added to request line." << endl;
    }
    void processNext() {
        if (requests.empty()) { cout << "No pending requests." << endl; return; }
        cout << "Processing: " << requests.front() << endl;
        requests.pop();
    }
    int pendingCount() { return requests.size(); }
};

// 4. CHANNEL LOOKUP (Linear Search) 
class ChannelLookup {
    vector<string> channels;
public:
    void addChannel(const string& ch) { channels.push_back(ch); }
    int findChannel(const string& target) {
        for (int i = 0; i < (int)channels.size(); i++)
            if (channels[i] == target) return i;
        return -1;
    }
};

// 5. QUALITY SORTER (Merge Sort) 
struct Link {
    string name;
    int quality;
};

void merge(vector<Link>& arr, int l, int m, int r) {
    vector<Link> left(arr.begin()+l, arr.begin()+m+1);
    vector<Link> right(arr.begin()+m+1, arr.begin()+r+1);
    int i=0, j=0, k=l;
    while (i < (int)left.size() && j < (int)right.size())
        arr[k++] = (left[i].quality >= right[j].quality) ? left[i++] : right[j++];
    while (i < (int)left.size())  arr[k++] = left[i++];
    while (j < (int)right.size()) arr[k++] = right[j++];
}

void mergeSort(vector<Link>& arr, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);
    merge(arr, l, m, r);
}

// 6 & 7. COMPANY NETWORK + CHEAPEST ROUTE (Graph + Dijkstra) 
class CompanyNetwork {
    unordered_map<string, vector<pair<string,int>>> adj;
public:
    void addDevice(const string& name) { adj[name]; }
    void addLink(const string& a, const string& b, int cost) {
        adj[a].push_back({b, cost});
        adj[b].push_back({a, cost});
    }
    map<string,int> cheapestRoute(const string& source) {
        map<string,int> dist;
        for (auto& node : adj) dist[node.first] = INT_MAX;
        dist[source] = 0;
        priority_queue<pair<int,string>,
                        vector<pair<int,string>>,
                        greater<pair<int,string>>> pq;
        pq.push({0, source});
        while (!pq.empty()) {
            auto top = pq.top(); pq.pop();
            int d = top.first;
            const string& u = top.second;
            if (d > dist[u]) continue;
            for (auto& vw : adj[u]) {
                const string& v = vw.first;
                int w = vw.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
};

// 8. TRAFFIC CONTROLLER (Max-Heap Priority Queue) 
class TrafficController {
    priority_queue<pair<int,string>> pq;
public:
    void addStream(const string& name, int priority) {
        pq.push({priority, name});
        cout << "Stream '" << name << "' added with priority " << priority << endl;
    }
    void allocateBandwidth() {
        if (pq.empty()) { cout << "No streams waiting." << endl; return; }
        auto top = pq.top(); pq.pop();
        cout << "Bandwidth allocated to: '" << top.second
             << "' (priority " << top.first << ")" << endl;
    }
};

// MAIN
int main() {
    cout << "=== TokenNet System Demo ===\n\n";

    // 1. Router Settings
    cout << "-- Router Settings --\n";
    RouterSettings rs;
    rs.addRouter(101, "Core-Router: 10.0.0.1");
    rs.addRouter(202, "Edge-Router: 192.168.1.1");
    rs.addRouter(303, "Backup-Router: 172.16.0.1");
    rs.displayAll();
    cout << "Search 202: " << rs.getConfig(202) << "\n\n";

    // 2. Permission Undo
    cout << "-- Permission Undo --\n";
    PermissionUndo pu;
    pu.grantToken("PC-Alpha");
    pu.grantToken("PC-Beta");
    pu.revokeToken("PC-Alpha");
    pu.undoLast();
    cout << endl;

    // 3. Request Line
    cout << "-- Request Line --\n";
    RequestLine rl;
    rl.addRequest("PC-Gamma");
    rl.addRequest("PC-Delta");
    rl.processNext();
    cout << "Remaining: " << rl.pendingCount() << "\n\n";

    // 4. Channel Lookup
    cout << "-- Channel Lookup --\n";
    ChannelLookup cl;
    cl.addChannel("CH-7"); cl.addChannel("CH-3"); cl.addChannel("CH-11");
    int idx = cl.findChannel("CH-3");
    cout << "CH-3 found at index: " << idx << "\n\n";

    // 5. Quality Sorter
    cout << "-- Quality Sorter --\n";
    vector<Link> links = {{"Link-A",60},{"Link-B",90},{"Link-C",75}};
    mergeSort(links, 0, links.size()-1);
    for (auto& l : links)
        cout << l.name << ": quality=" << l.quality << endl;
    cout << endl;

    // 6 & 7. Company Network + Cheapest Route
    cout << "-- Company Network + Cheapest Route --\n";
    CompanyNetwork cn;
    cn.addDevice("HQ"); cn.addDevice("Branch-A"); cn.addDevice("Branch-B");
    cn.addLink("HQ", "Branch-A", 4);
    cn.addLink("HQ", "Branch-B", 8);
    cn.addLink("Branch-A", "Branch-B", 2);
    auto dists = cn.cheapestRoute("HQ");
    for (auto& d : dists)
        cout << "HQ -> " << d.first << ": cost " << d.second << endl;
    cout << endl;

    // 8. Traffic Controller
    cout << "-- Traffic Controller --\n";
    TrafficController tc;
    tc.addStream("File-Backup", 2);
    tc.addStream("VoIP-Call",   9);
    tc.addStream("Video-Conf",  7);
    tc.allocateBandwidth();
    tc.allocateBandwidth();

    return 0;
}
    
