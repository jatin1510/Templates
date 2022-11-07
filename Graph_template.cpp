#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

// typedefs
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
typedef long long ll;

// debug section
void debug()
{
    cerr << endl;
}
template <typename T1, typename... T2>
void debug(T1 var1, T2... var2)
{
    cerr << var1 << ' ';
    debug(var2...);
}

// print section
void print()
{
    cout << endl;
}
template <typename T1, typename... T2>
void print(T1 var1, T2... var2)
{
    cout << var1 << ' ';
    print(var2...);
}

// vector operator overload - input
template <typename T>
istream &operator>>(istream &os, vector<T> &v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        os >> v[i];
    }
    return os;
}

// vector operator overload - output
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        os << v[i];
        if (i != v.size() - 1)
            os << ' ';
    }
    return os;
}

class DSU
{
    vector<int> parent;
    vector<int> rank;

public:
    DSU() {}
    DSU(int n)
    {
        int N = 1e5 + 5;
        parent = vector<int>(N);
        rank = vector<int>(N, 0);
        init(n);
    }
    void init(int n)
    {
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }
    int findParent(int node)
    {
        if (node == parent[node])
            return node;

        // Path compression
        return parent[node] = findParent(parent[node]);
    }
    void unionn(int u, int v)
    {
        u = findParent(u);
        v = findParent(v);

        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[v] < rank[u])
            parent[v] = u;
        else
        {
            // Below two line is true independetly one at a time
            parent[v] = u, rank[u]++;
            // parent[u] = v, rank[v]++;
        }
    }
};

class Graph
{
private:
    // Node -> {{adjecent node, weight}, {adjecent node, weight}, ... }
    map<int, vector<int>> adj;

    // n - node
    // indexing -> (=0) if 1 based indexing and (=1) if 0 based indexing
    // initially it is 1 based indexing
    int n, indexing;

    // weight of the edges
    map<pair<int, int>, int> weight;

public:
    Graph(){};

    Graph(int nodes, int index = 1)
    {
        // nodes assigning
        n = nodes;

        // setting indexing
        if (index == 0)
            indexing = 1;
        else
            indexing = 0;
    };

    void addEdge(int u, int v, int weigh = 1)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
        weight[{u, v}] = weigh;
        weight[{v, u}] = weigh;
    };

    void addDirectionalEdge(int u, int v, int weigh = 1)
    {
        adj[u].push_back(v);
        weight[{u, v}] = weigh;
    };

    void printGraph(bool flag = false)
    {
        for (auto i : adj)
        {
            cout << i.first << ": ";
            for (auto j : i.second)
            {
                if (flag)
                    cout << "(";
                cout << j;

                if (flag)
                    cout << ", " << weight[{i.first, j}] << ") ";
                else
                    cout << ' ';
            }
            cout << endl;
        }
    }
    void BSF()
    {
        vector<int> visited(this->n + 1 - indexing, 0);
        for (int i = 1 - indexing; i <= this->n - indexing; i++)
        {
            if (!visited[i])
            {
                queue<int> q;
                q.push(i);
                visited[i] = 1;

                vector<int> bfsVector;
                while (!q.empty())
                {
                    int node = q.front();
                    q.pop();
                    cout << node << ' ';
                    bfsVector.push_back(node);

                    for (auto i : adj[node])
                        if (!visited[i])
                            q.push(i), visited[i] = 1;
                }
            }
        }
    }

    void DFSforNode(int n, vector<int> &visited, vector<int> &dfsVector)
    {
        dfsVector.push_back(n);
        visited[n] = true;
        for (auto i : adj[n])
            if (!visited[i])
                DFSforNode(i, visited, dfsVector);
    }
    void DFS()
    {
        vector<int> visited(this->n + 1);
        vector<int> dfsVector;
        for (int i = 1 - indexing; i <= this->n - indexing; i++)
            if (!visited[i])
                DFSforNode(i, visited, dfsVector);
        cout << dfsVector << endl;
    }

    bool bfs_detectCycle(int n, vector<int> &visited)
    {
        // node, parent = pair
        queue<pair<int, int>> q;
        q.push({n, -1});
        visited[n] = 1;

        while (!q.empty())
        {
            int node = q.front().first;
            int prev = q.front().second;
            q.pop();

            for (auto i : adj[node])
            {
                if (!visited[i])
                {
                    q.push({i, node});
                    visited[i] = true;
                }
                else if (i != prev)
                    return true;
            }
        }
        return false;
    }
    bool detectCycleusingBFS()
    {
        vector<int> visited(this->n + 1 - indexing);

        for (int i = 1 - indexing; i <= this->n - indexing; i++)
            if (!visited[i] && bfs_detectCycle(i, visited))
                return true;
        return false;
    }

    bool dfs_detectCycle(int node, int prev, vector<int> &visited)
    {
        visited[node] = true;
        for (auto i : adj[node])
        {
            if (!visited[i])
            {
                if (dfs_detectCycle(i, node, visited))
                    return true;
            }
            else if (i != prev)
                return true;
        }
        return false;
    }
    bool detectCycleusingDFS()
    {
        vector<int> visited(this->n + 1 - indexing);

        for (int i = 1 - indexing; i <= this->n - indexing; i++)
            if (!visited[i] && dfs_detectCycle(i, -1, visited))
                return true;
        return false;
    }

    bool bfs_bipartite(int n, vector<int> &color)
    {
        queue<int> q;
        q.push(1 - indexing);
        color[1 - indexing] = 0;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (auto i : adj[node])
            {
                if (color[i] == -1)
                {
                    color[i] = !color[node];
                    q.push(i);
                }
                else if (color[i] == color[node])
                    return false;
            }
        }
        return true;
    }
    bool isBipartiteusingBFS()
    {
        vector<int> color(this->n + 1 - indexing, -1);

        for (int i = 1 - indexing; i <= this->n - indexing; i++)
            if (color[i] == -1 && !bfs_bipartite(i, color))
                return false;
        return true;
    }

    bool dfs_bipartite(int n, vector<int> &color)
    {
        for (auto i : adj[n])
        {
            if (color[i] == -1)
            {
                color[i] = !color[n];
                if (!dfs_bipartite(i, color))
                    return false;
            }
            else
            {
                if (color[i] == color[n])
                    return false;
            }
        }
        return true;
    }
    bool isBipartiteusingDFS()
    {
        vector<int> color(this->n + 1 - indexing, -1);
        for (int i = 1 - indexing; i <= this->n - indexing; i++)
        {
            if (color[i] == -1)
            {
                color[i] = 0;
                if (!dfs_bipartite(i, color))
                    return false;
            }
        }
        return true;
    }

    bool detectCycleusingDFSinDirected(int n, vector<int> &visited, vector<int> &dfs_visited)
    {
        visited[n] = 1;
        dfs_visited[n] = 1;
        for (auto i : adj[n])
        {
            if (!visited[i] && detectCycleusingDFSinDirected(i, visited, dfs_visited))
                return true;
            else if (dfs_visited[i])
                return true;
        }
        dfs_visited[n] = 0;
        return false;
    }
    bool cycleDetectionDirectedGraphusingDFS()
    {
        vector<int> visited(this->n + 1 - indexing);
        vector<int> dfs_visited(this->n + 1 - indexing);

        for (int i = 1 - indexing; i <= this->n - indexing; i++)
            if (!visited[i])
                if (detectCycleusingDFSinDirected(i, visited, dfs_visited))
                    return true;

        return false;
    }

    // topological sorting is linear ordering of a vertices such that if there exist an edge between u -> v then u always appears before v in the linear ordering.
    // Graph should be DAG (Directed acyclic graph)
    void dfs_topological(int n, vector<int> &visited, stack<int> &ans)
    {
        visited[n] = 1;
        for (auto i : adj[n])
            if (!visited[i])
                dfs_topological(i, visited, ans);
        ans.push(n);
    }

    stack<int> topologicalSortingUSingdfs()
    {
        vector<int> visited(this->n + 1 - indexing);
        stack<int> ans;
        for (int i = 1 - indexing; i <= this->n - indexing; i++)
            if (!visited[i])
                dfs_topological(i, visited, ans);

        // if answer we want to return is in vector form then uncomment below four lines and change the return data type
        // vector<int> v;
        // while (!ans.empty())
        //     v.push_back(ans.top()), ans.pop();
        // return v;
        return ans;
    }

    // kahn's algorithm
    vector<int> topologicalSortingUSingbfs()
    {
        vector<int> indegree(this->n + 1 - indexing);
        for (auto i : adj)
            for (auto j : i.second)
                indegree[j]++;

        queue<int> q;
        for (int i = 1 - indexing; i <= this->n - indexing; i++)
            if (!indegree[i])
                q.push(i);

        vector<int> ans;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            ans.push_back(node);
            for (auto i : adj[node])
            {
                indegree[i]--;
                if (indegree[i] == 0)
                    q.push(i);
            }
        }
        return ans;
    }

    bool cycleDetectionDirectedGraphusingBFS()
    {
        vector<int> topological = topologicalSortingUSingbfs();
        if (topological.size() != this->n)
            return true;
        return false;
    }

    // Unfortunately, this is working as same as djikstra algorithm 😁
    int shortestPathInUndirectedGraph(int source, int destination)
    {
        vector<int> dist(this->n + 1 - indexing, INT_MAX);
        queue<int> q;
        q.push(source);
        dist[source] = 0;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            // till node minimal distance is "till"
            int till = dist[node];
            for (auto i : adj[node])
            {
                // weight of edge from "node" to "i"
                int w = weight[{node, i}];
                if (till + w < dist[i])
                {
                    dist[i] = till + w;
                    q.push(i);
                }
            }
        }
        // cout << dist << endl;
        return dist[destination];
    }

    int shortestPathInDirectedGraph(int source, int destination)
    {
        // idea is to use topological sort
        stack<int> topo = topologicalSortingUSingdfs();
        vector<int> dist(this->n + 1 - indexing, INT_MAX);
        dist[source] = 0;

        while (!topo.empty())
        {
            int node = topo.top();
            topo.pop();

            if (dist[node] != INT_MAX)
            {
                int till = dist[node];
                for (auto i : adj[node])
                {
                    int w = weight[{node, i}];
                    if (till + w < dist[i])
                    {
                        dist[i] = till + w;
                    }
                }
            }
        }
        // cout << dist << endl;
        return dist[destination];
    }

    int dijkstra(int source, int destination)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(this->n + 1 - indexing, INT_MAX);
        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty())
        {
            int dist_till_u = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            for (auto i : adj[u])
            {
                int v = i;
                int w = weight[{u, v}];
                if (dist_till_u + w < dist[v])
                {
                    dist[v] = dist_till_u + w;
                    pq.push({dist_till_u + w, v});
                }
            }
        }
        // cout << dist << endl;
        return dist[destination];
    }

    // Runs in O(n^2) because we will incrementing count till n and in every iteration we are finding minimal value to process further
    int mst_PRIMSalgo()
    {
        vector<int> key(this->n + 1 - indexing, INT_MAX);
        vector<int> MST(this->n + 1 - indexing, false);
        vector<int> parent(this->n + 1 - indexing, -1);

        // starting with zero(=0 based indexing) or one(=1 based indexing)
        key[1 - indexing] = 0;
        int cnt = 0;

        while (cnt != this->n)
        {
            int processNode, mn = INT_MAX;

            // finding which node to include in MST = (processNode = "u")
            for (int i = 1 - indexing; i <= this->n - indexing; i++)
                if (MST[i] == 0 && key[i] < mn)
                    processNode = i, mn = key[i];

            // Marking it as visited
            MST[processNode] = 1;
            cnt++;

            // Traveling through adjecant node
            // Pick it if it is not taken and current weight to reach that node is less than previous
            // Take i as "v"
            for (auto i : adj[processNode])
            {
                // weight[{processNode, i}] = "w"
                if (MST[i] == 0 && weight[{processNode, i}] < key[i])
                {
                    key[i] = weight[{processNode, i}];
                    parent[i] = processNode;
                }
            }
        }

        // Building MST through - parent array - if we need graph in answer uncomment below code
        // always iterate through second node
        // Graph graph(this->n, 1 - indexing);
        // for (int i = 1 - indexing + 1; i <= this->n - indexing; i++)
        //     graph.addEdge(i, parent[i], weight[{i, parent[i]}]);
        // graph.printGraph(1);

        int ans = 0;
        for (int i = 1 - indexing; i <= this->n - indexing; i++)
            ans += key[i];
        return ans;
    }

    // Above Algorithm runs in O(n^2) because we will incrementing count till n and in every iteration we are finding minimal value to process further
    // In this algorithm we'll use min-heap to get track of minimal value which runs in logN => Hence overall TC will be O(NlogN + (N+E)) ~ O(NlogN);
    int mst_PRIMSalgo_efficient()
    {
        vector<int> key(this->n + 1 - indexing, INT_MAX);
        vector<int> MST(this->n + 1 - indexing, false);
        vector<int> parent(this->n + 1 - indexing, -1);

        // starting with zero(=0 based indexing) or one(=1 based indexing)
        key[1 - indexing] = 0;
        int cnt = 0;

        // key[i], index=i
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 1 - indexing});

        // while (cnt != this->n) ==> this line is not working properly for {{4, 5, 9}, {3, 4, 5}, {3, 6, 8}, {2, 6, 7}, {1, 2, 2}, {1, 5, 4}, {1, 4, 1}, {2, 4, 3}, {2, 3, 3}} bcoz After all process 6 is not showing in MST.
        while (!pq.empty())
        {
            // finding which node to include in MST = (processNode = "u")
            int processNode = pq.top().second;
            pq.pop();

            // Marking it as visited
            MST[processNode] = 1;
            cnt++;

            // Traveling through adjecant node
            // Pick it if it is not taken and current weight to reach that node is less than previous
            // Take i as "v"
            for (auto i : adj[processNode])
            {
                // weight[{processNode, i}] = "w"
                if (MST[i] == 0 && weight[{processNode, i}] < key[i])
                {
                    key[i] = weight[{processNode, i}];
                    parent[i] = processNode;
                    pq.push({key[i], i});
                }
            }
        }

        // Building MST through - parent array - if we need graph in answer uncomment below code
        // always iterate through second node
        // Graph graph(this->n, 1 - indexing);
        // for (int i = 1 - indexing + 1; i <= this->n - indexing; i++)
        //     graph.addEdge(i, parent[i], weight[{i, parent[i]}]);
        // graph.printGraph(1);

        int ans = 0;
        for (int i = 1 - indexing; i <= this->n - indexing; i++)
            ans += key[i];
        return ans;
    }

    int mst_KRUSKALSalgo()
    {
        // sort according Data Structure into ascending order of weights
        vector<vector<int>> ds;
        map<pair<int, int>, int> mp;
        for (int i = 1 - indexing; i <= this->n - indexing; i++)
        {
            for (auto v : adj[i])
                if (!mp[{i, v}] && !mp[{v, i}])
                    ds.push_back({weight[{i, v}], i, v}), mp[{i, v}] = 1, mp[{v, i}] = 1;
        }
        sort(ds.begin(), ds.end());

        int ans = 0;
        vector<vector<int>> mst;
        DSU d(this->n);
        for (auto vec : ds)
        {
            int w = vec[0], u = vec[1], v = vec[2];
            if (d.findParent(u) != d.findParent(v))
            {
                d.unionn(u, v);
                ans += w;
                mst.push_back({u, v, w});
            }
        }

        // if we need graph in answer uncomment below code
        // Graph graph;
        // for (auto vec : mst)
        //     graph.addEdge(vec[0], vec[1], vec[2]);
        // graph.printGraph(1);

        return ans;
    }

    void dfs_bridges(int node, int parent, vector<int> &visited, vector<int> &t_insertion, vector<int> &low, int &timer, vector<vector<int>> &ans)
    {
        visited[node] = 1;
        t_insertion[node] = low[node] = timer++;
        for (auto it : adj[node])
        {
            if (it == parent)
                continue;

            if (!visited[it])
            {
                dfs_bridges(it, node, visited, t_insertion, low, timer, ans);
                low[node] = min(low[node], low[it]);
                if (low[it] > t_insertion[node])
                    ans.push_back({node, it});
            }
            else
            {
                low[node] = min(low[node], t_insertion[it]);
            }
        }
    }
    // Jenny's lectures
    vector<vector<int>> bridges()
    {
        vector<int> t_insertion(this->n - indexing, -1);
        vector<int> low(this->n - indexing, -1);
        vector<int> visited(this->n - indexing, 0);
        vector<vector<int>> ans;

        int timer = 0;
        for (int i = 1 - indexing; i <= this->n - indexing; i++)
            if (!visited[i])
                dfs_bridges(i, -1, visited, t_insertion, low, timer, ans);
        return ans;
    }

    void dfs_articulation_point(int node, int parent, vector<int> &visited, vector<int> &t_insertion, vector<int> &low, int &timer, vector<int> &ans)
    {
        visited[node] = 1;
        t_insertion[node] = low[node] = timer++;
        int child = 0;
        for (auto it : adj[node])
        {
            if (it == parent)
                continue;

            if (!visited[it])
            {
                dfs_articulation_point(it, node, visited, t_insertion, low, timer, ans);
                low[node] = min(low[node], low[it]);
                if (low[it] >= t_insertion[node] && parent != -1)
                    ans.push_back(node);
                child++;
            }
            else
            {
                low[node] = min(low[node], t_insertion[it]);
            }
        }
        if (parent == -1 && child > 1)
            ans.push_back(node);
    }
    // articulation point is the node which if we remove, graph will have more disconnected components
    vector<int> articulation_Point()
    {
        // simple solution on my point of view
        // If an edge is bridge then if we remove one of the node from the edge, that node will always be articulation point

        // ::: CODE :::
        /*
        vector<vector<int>> edges = bridges();
        unordered_map<int, int> mp;
        for (auto i : edges)
            mp[i[0]] = 1, mp[i[1]] = 1;
        vector<int> ans;
        for (auto i : mp)
            ans.push_back(i.first);
        return ans;
        */

        // Above case is wrong - I read it in the comment section - Here is the explanation why is it wrong ==> /* If there is a link between a node of a graph and a single node...the link will be a bridge which connects two different components but on the removal of the single node it won't divide the graph into two different components there will be only one component remained */
        vector<int> t_insertion(this->n - indexing, -1);
        vector<int> low(this->n - indexing, -1);
        vector<int> visited(this->n - indexing, 0);
        vector<int> ans;

        int timer = 0;
        for (int i = 1 - indexing; i <= this->n - indexing; i++)
            if (!visited[i])
                dfs_articulation_point(i, -1, visited, t_insertion, low, timer, ans);
        return ans;
    }

    // Kosaraju's Algorithm
    void strongly_connected_components_util(int node, vector<int> &vis, map<int, vector<int>> adjacency, vector<int> &ans)
    {
        vis[node] = 1;
        ans.push_back(node);

        for (auto i : adjacency[node])
            if (!vis[i])
                strongly_connected_components_util(i, vis, adjacency, ans);
    }
    // for directed graph
    vector<vector<int>> strongly_connected_components()
    {
        stack<int> s = topologicalSortingUSingdfs();
        
        map<int, vector<int>> adjacency;
        for (auto i : adj)
            for (auto j : i.second)
                adjacency[j].push_back(i.first);

        vector<vector<int>> ans;
        vector<int> vis(this->n + 1 - indexing);
        while (!s.empty())
        {
            int node = s.top();
            s.pop();

            if (!vis[node])
            {
                vector<int> subans;
                strongly_connected_components_util(node, vis, adjacency, subans);
                ans.push_back(subans);
            }
        }

        return ans;
    }

    // shortest path algorithm - works fine for directed graph (negative edge also)
    // -ve weighted cycle is not allowed
    // if we want to run this algorithm for undirected graph then we have to convert directed graph to undirected graph Eg. (1->2 with edge weight of 2) ==> (1-2 & 2-1 with both edge weight as 2) (Negative edge is not allowed)

    // 1. Relax all the edges N-1 times
    // At then end we'll get shortest distances

    // O(N-1 * E) ~ O(N * E)
    int bellman_ford_algo(int src, int destination)
    {
        const int inf = 1e7;
        vector<int> dist(this->n + 1 - indexing, inf);
        dist[src] = 0;
        int relaxation = this->n - 1;

        map<pair<int, int>, int> edges;

        for (auto i : adj)
            for (auto j : i.second)
                edges[{i.first, j}] = weight[{i.first, j}];

        while (relaxation--)
        {
            for (auto i : edges)
            {
                int u = i.first.first, v = i.first.second, w = i.second;
                if (dist[u] + w < dist[v])
                    dist[v] = dist[u] + w;
            }
        }
        return dist[destination];
    }
};

int main()
{
    // Graph g(6, 0);
    // vector<vector<int>> v = {{0, 1, 5}, {1, 2, -2}, {2, 4, 3}, {1, 5, -3}, {5, 3, 1}, {3, 2, 6}, {3, 4, -2}};

    // for (auto i : v)
    //     g.addDirectionalEdge(i[0], i[1], i[2]);

    // cout << g.bellman_ford_algo(0, 1) << endl;
    return 0;
}