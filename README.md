🔐 TokenNet — Virtual Distributed Network Token Ring
Problem Statement No. 44 

2.1 Project Title
TokenNet: Virtual Distributed Network Token Ring System  - A C++ implementation of a secure corporate communication network that manages token-based access, router configurations, request processing, link quality routing, and bandwidth allocation using appropriate Data Structures and Algorithms.

2.2 Problem Statement
TokenNet is a secure corporate communication network where computers must hold a digital permission token to transmit data. The existing system suffers from several critical issues:
* Router configuration retrieval is slow and inconsistent
* When a security token is accidentally revoked, there is no way to restore it
* Computers requesting network access pile up randomly with no order
* The system cannot rank links by quality (speed, reliability, error rate)
* There is no model of the corporate network topology, making cost-efficient routing impossible
* Bandwidth is not allocated to highest priority streams
This project designs and implements a new system in C++ that resolves all these issues using appropriate data structures.

2.3 Objectives
1. Implement fast and consistent router configuration retrieval using a balanced BST
2. Enable instant token state rollback using a Stack-based undo mechanism
3. Enforce strict order processing of network access requests using a Queue
4. Support channel lookup among unsorted available connections using Linear Search
5. Provide quality-based sorting of network links using Merge Sort
6. Model the corporate network topology using a weighted Graph
7. Find the cheapest routing path using Dijkstra's Algorithm
8. Allocate bandwidth to highest priority streams using a Max-Heap Priority Queue

2.4 System Overview / Architecture
TokenNet System
│
├── RouterSettings       → std::map (Balanced BST / Red-Black Tree)
├── PermissionUndo       → std::stack (LIFO — undo token grant/revoke)
├── RequestLine          → std::queue (FIFO — ordered access requests)
├── ChannelLookup        → Linear Search on std::vector
├── QualitySorter        → Merge Sort on vector<Link>
├── CompanyNetwork       → Graph (Adjacency List via unordered_map)
│   └── cheapestRoute()  → Dijkstra's Algorithm (Min-Heap)
└── TrafficController    → std::priority_queue (Max-Heap)
Each module is implemented as an independent C++ class, making the system modular and easy to extend.


2.5 Data Structures and Algorithms Used
Feature	Data Structure / Algorithm	Syllabus Module
Router Settings	std::map (Balanced BST)	Module 4 — AVL / Balanced Trees
Permission Undo	std::stack (LIFO)	Module 3 — Stacks
Request Line	std::queue (FIFO)	Module 4 — Queues
Channel Lookup	Linear Search	Module 2 — Searching Algorithms
Quality Sorter	Merge Sort	Module 2 — Sorting Algorithms
Company Network	Graph — Adjacency List	Module 5 — Graphs
Cheapest Route	Dijkstra's Algorithm	Module 5 — Graph Applications
Traffic Controller	Max-Heap Priority Queue	Module 4 — Trees / Heaps




2.6 Implementation Approach
The system is implemented as a single C++ file (tokennet.cpp) with 8 independent classes, each solving one specific problem:
* RouterSettings uses std::map which internally uses a Red-Black Tree, guaranteeing O(log n) insert, delete, and search for all router configurations.
* PermissionUndo uses std::stack<pair<string,bool>> to push every token action. Calling undoLast() pops and reverses it in O(1).
* RequestLine uses std::queue<string> so access requests are processed strictly in the order received — FIFO.
* ChannelLookup performs a linear scan of an unsorted vector<string> channel list — correct for unsorted data.
* QualitySorter implements Merge Sort on a vector<Link> struct, sorting by quality score in descending order — O(n log n) guaranteed.
* CompanyNetwork stores the network as an adjacency list using unordered_map<string, vector<pair<string,int>>>. Dijkstra's algorithm runs on this graph using a priority_queue min-heap.
* TrafficController uses std::priority_queue<pair<int,string>> (max-heap) to always serve the highest priority data stream first.


2.7 Time and Space Complexity Analysis
Feature	Time Complexity	Space Complexity
Router Settings (BST)	O(log n) insert/search/delete	O(n)
Permission Undo (Stack)	O(1) push/pop	O(n)
Request Line (Queue)	O(1) enqueue/dequeue	O(n)
Channel Lookup (Linear Search)	O(n) worst case	O(1)
Quality Sorter (Merge Sort)	O(n log n) all cases	O(n)
Company Network (Graph)	O(V + E) to build	O(V + E)
Cheapest Route (Dijkstra)	O((V + E) log V)	O(V)
Traffic Controller (Max-Heap)	O(log n) insert/remove	O(n)


2.8 Execution Steps
Prerequisites
* A C++ compiler supporting C++17 (g++ recommended)

Compile
g++ -std=c++17 -o tokennet tokennet.cpp

Run
./tokennet

On Windows
g++ -std=c++17 -o tokennet.exe tokennet.cpp
tokennet.exe

Online Compiler
You can also paste the code at https://www.onlinegdb.com and set language to C++17.


2.9 Sample Inputs and Outputs
=== TokenNet System Demo ===

-- Router Settings --
Router 101: Core-Router: 10.0.0.1
Router 202: Edge-Router: 192.168.1.1
Router 303: Backup-Router: 172.16.0.1
Search 202: Edge-Router: 192.168.1.1

-- Permission Undo --
Token GRANTED to PC-Alpha
Token GRANTED to PC-Beta
Token REVOKED from PC-Alpha
Undone: revoke for PC-Alpha

-- Request Line --
PC-Gamma added to request line.
PC-Delta added to request line.
Processing: PC-Gamma
Remaining: 1

-- Channel Lookup --
CH-3 found at index: 1

-- Quality Sorter --
Link-B: quality=90
Link-C: quality=75
Link-A: quality=60

-- Company Network + Cheapest Route --
HQ -> Branch-A: cost 4
HQ -> Branch-B: cost 6
HQ -> HQ: cost 0

-- Traffic Controller --
Stream 'File-Backup' added with priority 2
Stream 'VoIP-Call' added with priority 9
Stream 'Video-Conf' added with priority 7
Bandwidth allocated to: 'VoIP-Call' (priority 9)
Bandwidth allocated to: 'Video-Conf' (priority 7)

2.10 Screenshots
￼
<img width="713" height="711" alt="Screenshot 2026-06-16 at 2 32 42 AM" src="https://github.com/user-attachments/assets/eb9eee23-8064-44ec-98b9-48dc5782f37a" />



2.11 Results and Observations
* The AVL/Balanced BST (via std::map) provides consistent O(log n) router lookups, eliminating the slow/inconsistent retrieval problem.
* The Stack-based undo correctly reverses the last token action in O(1), solving the irreversible revocation problem.
* The Queue ensures strict FIFO access request processing — no computer is skipped or served out of order.
* Linear Search correctly locates channels in unsorted lists — simple and reliable for this use case.
* Merge Sort successfully ranks all links by quality in O(n log n), enabling reliable routing decisions.
* Dijkstra's algorithm correctly finds the minimum cost path across the network (HQ → Branch-B costs 6 via Branch-A, not 8 directly).
* The Max-Heap allocates bandwidth to VoIP (priority 9) before Video (priority 7) before File Backup (priority 2) — exactly as required.


2.12 Conclusion
This project successfully implements all 8 required features of the TokenNet system using carefully chosen data structures. Each choice was justified by both theoretical complexity analysis and real-world enterprise networking parallels (OSPF uses Dijkstra, Cisco IOS uses rollback stacks, 802.1X uses FIFO queues). The modular class-based design makes each component independently testable and extensible.
