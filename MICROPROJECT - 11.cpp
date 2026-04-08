#include<stdio.h>
#include<stdlib.h>

#define MAX 20

int adj[MAX][MAX];
int visited[MAX];
int parent[MAX];

// Add connection
void addEdge(int u, int v){
    adj[u][v] = adj[v][u] = 1;
}

// Remove connection
void removeEdge(int u, int v){
    adj[u][v] = adj[v][u] = 0;
}

// Remove router (node)
void removeNode(int n, int node){
    for(int i=1;i<=n;i++){
        adj[node][i] = 0;
        adj[i][node] = 0;
    }
    printf("Router R%d removed\n", node);
}

// BFS shortest path
void bfsPath(int start, int end, int n){
    int queue[MAX], front=0, rear=0;

    for(int i=1;i<=n;i++){
        visited[i]=0;
        parent[i]=-1;
    }

    queue[rear++] = start;
    visited[start]=1;

    while(front < rear){
        int node = queue[front++];

        for(int i=1;i<=n;i++){
            if(adj[node][i] && !visited[i]){
                visited[i]=1;
                parent[i]=node;
                queue[rear++] = i;
            }
        }
    }

    if(!visited[end]){
        printf("No path found\n");
        return;
    }

    // Print path
    int path[MAX], count=0;
    for(int v=end; v!=-1; v=parent[v])
        path[count++] = v;

    printf("Shortest Path: ");
    for(int i=count-1;i>=0;i--)
        printf("R%d ", path[i]);
    printf("\n");
}

// DFS for loop detection
int dfsCycle(int node, int parentNode, int n){
    visited[node]=1;

    for(int i=1;i<=n;i++){
        if(adj[node][i]){
            if(!visited[i]){
                if(dfsCycle(i,node,n))
                    return 1;
            }
            else if(i != parentNode){
                return 1; // cycle found
            }
        }
    }
    return 0;
}

// Connected components
void dfs(int node, int n){
    visited[node]=1;
    printf("R%d ", node);

    for(int i=1;i<=n;i++){
        if(adj[node][i] && !visited[i])
            dfs(i,n);
    }
}

void components(int n){
    for(int i=1;i<=n;i++) visited[i]=0;

    printf("Connected Components:\n");

    for(int i=1;i<=n;i++){
        if(!visited[i]){
            printf("Component: ");
            dfs(i,n);
            printf("\n");
        }
    }
}

// Check isolated nodes
void isolated(int n){
    for(int i=1;i<=n;i++){
        int flag=0;
        for(int j=1;j<=n;j++){
            if(adj[i][j]){
                flag=1;
                break;
            }
        }
        if(flag==0)
            printf("R%d is isolated\n", i);
    }
}

int main(){
    int n, choice, u, v;

    printf("Enter number of routers: ");
    scanf("%d",&n);

    while(1){
        printf("\n--- MENU ---\n");
        printf("1. Connect Routers\n");
        printf("2. Disconnect Routers\n");
        printf("3. Remove Router\n");
        printf("4. BFS Shortest Path\n");
        printf("5. DFS Loop Detection\n");
        printf("6. Connected Components\n");
        printf("7. Isolated Routers\n");
        printf("8. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("Enter u v: ");
                scanf("%d %d",&u,&v);
                addEdge(u,v);
                break;

            case 2:
                printf("Enter u v: ");
                scanf("%d %d",&u,&v);
                removeEdge(u,v);
                break;

            case 3:
                printf("Enter router to remove: ");
                scanf("%d",&u);
                removeNode(n,u);
                break;

            case 4:
                printf("Enter start and end: ");
                scanf("%d %d",&u,&v);
                bfsPath(u,v,n);
                break;

            case 5:
                for(int i=1;i<=n;i++) visited[i]=0;
                if(dfsCycle(1,-1,n))
                    printf("Loop detected\n");
                else
                    printf("No loop\n");
                break;

            case 6:
                components(n);
                break;

            case 7:
                isolated(n);
                break;

            case 8:
                exit(0);
        }
    }
}
