class TreeAncestor {
public:
    vector<vector<int>> dp;
    int l;
    
    void dfs(int root, int parent, vector<vector<int>> &adj, int l) {
        if (root != parent)
            dp[root][0] = parent;
        
        for (int i = 1; i < l; i++) {
            if (dp[root][i-1] == -1)
                break;
            dp[root][i] = dp[dp[root][i-1]][i-1];
        }
    
        for (auto v: adj[root]) {
            if (v != parent)
                dfs(v, root, adj, l);
        }
    }
    
    
    TreeAncestor(int n, vector<int>& parent) {
        vector<vector<int>> adj(n);
        
        int root = -1;
        l = ceil(log2(n)) + 1;
       
        for (int i = 0; i < n; i++) {
            vector<int> jj;
            for (int j = 0; j < l; j++)
                jj.push_back(-1);
            dp.push_back(jj);
        }
        
        for (int i = 0; i < n; i++) {
            if (parent[i] == -1) {
                root = i;
            } else {
                adj[parent[i]].push_back(i);
            }
        }
        
        
        dfs(root, root, adj, l);
    }
    
    int getKthAncestor(int node, int k) {
       for (int i = 0; i <= l; i++)  {
           if (k & (1<<i)) {
               node = dp[node][i];
               if (node == -1)
                   break;
           }
       }
       return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */