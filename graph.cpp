#include <vector>

using namespace std;

#define ALL(c) (c).begin(), (c).end()

const int INF = 1000 * 1000 * 1000;


template<typename T>
vector<T> dijkstra(int src, vector<vector<pair<int, T>>> &edges) {
    int n = edges.size();

    vector<T> d(n, INF);
    d[src] = 0;
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;
    q.push(make_pair(0, src));

    while(!q.empty()) {
        PII p = q.top(); q.pop();
        T du = p.first;
        int u = p.second;
        if(d[u] < du) continue;

        for(auto e: edges[u]) {
            int to = e.first;
            T cost = e.second;
            if(d[to] > d[u] + cost) {
                d[to] = d[u] + cost;
                q.push(make_pair(d[to], to));
            }
        }
    }

    return std::move(d);
}


/**
 * Minimum s-t cut
 */
template<typename T>
struct Graph {
    struct edge { int to; T cap; int rev; };

    int n_;
    vector<vector<edge>> edges_;

    void add_edge(int from, int to, T cap) {
        edges_[from].push_back((edge){to, cap, (int)edges_[to].size()});
        edges_[to].push_back((edge){from, 0, (int)edges_[from].size() - 1});
    }

    Graph(int n)
    : n_(n)
    {
        edges_.resize(n_);
    }

    Graph(vector<vector<pair<int, T>>> &edges) {
        n_ = edges.size();
        edges_.resize(n_);
        for(int i = 0; i < n_; i++) {
            for(int j = 0; j < edges[i].size(); j++) {
                add_edge(i, edges[i].first, edges[i].second);
            }
        }
    }

    T dfs(int v, int t, vector<bool> &used, T f=INF) {
        if(v == t) return f;
        used[v] = true;

        for(int i = 0; i < edges_[v].size(); i++) {
            edge &e = edges_[v][i];
            if(!used[e.to] && e.cap > 0) {
                T d = dfs(e.to, t, used, min(f, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    edges_[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    T max_flow(int s, int t) {
        vector<bool> used(n_);

        T flow = 0;
        while(true) {
            fill(ALL(used), false);
            T f = dfs(s, t, used);
            if(f == 0) return flow;
            flow += f;
        }
    }
};


/**
 * Minimum cost flow
 */ 
template<typename T>
struct CostGraph {
    struct edge { int to; T cap; T cost; int rev; };

    int n_;
    vector<vector<edge>> edges_;
    vector<T> h_, dist_;
    vector<int> prevv_, preve_;

    void add_edge(int from, int to, T cap, T cost) {
        edges_[from].push_back((edge){to, cap, cost, (int)edges_[to].size()});
        edges_[to].push_back((edge){from, 0, -cost, (int)edges_[from].size() - 1});
    }

    CostGraph(int n)
    : n_(n)
    {
        edges_.resize(n_);
        h_.resize(n_);
        dist_.resize(n_);
        prevv_.resize(n_);
        preve_.resize(n_);
    }

    T min_cost_flow(int s, int t, T f) {
        T res = 0;
        fill(ALL(h_), 0);

        while(f > 0) {
            priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> que;
            fill(ALL(dist_), INF);
            dist_[s] = 0;
            que.push(make_pair(T(0), s));
            while(!que.empty()) {
                auto p = que.top(); que.pop();
                int v = p.second;
                if(dist[v] < p.first) continue;
                for(int i = 0; i < edges_[v].size(); i++) {
                    edge &e = edges_[v][i];
                    if(e.cap > 0 && dist_[e.to] > dist_[v] + e.cost + h_[v] - h_[e.to]) {
                        dist_[e.to] = dist_[v] + e.cost + h_[v] - h_[e.to];
                        prevv_[e.to] = v;
                        preve_[e.to] = i;
                        que.push(make_pair(dist_[e.to], e.to));
                    }
                }
            }

            if(dist_[t] == INF) {
                return -1;
            }
            for(int v = 0; v < V; v++) h_[v] += dist_[v];

            T d = f;
            for(int v = t; v != s; v = prevv_[v]) {
                d = min(d, edges_[prevv_[v]][preve_[v]].cap);
            }
            f -= d;
            res += d * h_[t];
            for(int v = t; v != s; v = prevv_[v]) {
                edge &e = edges_[prevv_[v]][preve_[v]];
                e.cap -= d;
                edges_[v][e.rev].cap += d;
            }
        }
        
        return res;
    }
};




