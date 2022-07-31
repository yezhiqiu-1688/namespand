#include "iostream"
#include "queue"
#include "cstring"
using namespace std;

//
const int MaxVertexNum = 10;
typedef int VertexType;

//
typedef struct ArcNode {
    int adjvex;//该弧所指向的顶点的位置
    struct ArcNode* next;
}ArcNode;
typedef struct VNode {
    VertexType data;
    ArcNode* first;
}VNode, * AdjList;
typedef struct {
    AdjList ventices;
    int vexnum, arcnum;
}ALGraph;
void InitALGraph(ALGraph& G) {
    G.ventices = new VNode[MaxVertexNum];
    G.vexnum = 0; G.arcnum = 0;
}

int Locate(ALGraph G, VertexType x) {
    int i;
    if (G.vexnum <= 0)
        return -1;
    for (i = 0; i < G.vexnum; i++) {
        if (x == G.ventices[i].data)
            return i;
    }
    return -1;
}

//有向
void Create(ALGraph& G) {
    InitALGraph(G);
    cout << "input the vexnum and arcnum" << endl;
    cin >> G.vexnum >> G.arcnum;
    if (G.vexnum > MaxVertexNum) {
        cout << "vexnum is illegal" << endl;
        return;
    }

    cout << "input the ventices" << endl;
    for (int i = 0; i < G.vexnum; i++) {
        cin >> G.ventices[i].data;
        G.ventices[i].first = nullptr;
    }
    VertexType v1, v2;
    int i, j;
    cout << "input the arc's head and rear" << endl;
    for (int k = 0; k < G.arcnum; k++) {
        /*这里犯了一个错误，将i给当作循环变量，for语句内的i=Locate()导致for无法跳出，
        * 因为给出的i始终是不满足for的判断条件i<G.arcnum的*/
        cin >> v1 >> v2;
        i = Locate(G, v1);
        j = Locate(G, v2);
        
        ArcNode* node = new ArcNode;
        node->adjvex = j;
        node->next = G.ventices[i].first;
        G.ventices[i].first = node;
    }
}
//


//一个下标为v的顶点的第一个邻接点所指向的顶点下标
int FirstNeighbor(ALGraph G, int v) {
    if (G.ventices[v].first != nullptr)
        return G.ventices[v].first->adjvex;
    else
        return -1;
}
//w后面一个的adjvex值
int NextNeighbor(ALGraph G, int v, int w) {
    //    ArcNode *p;
    //    //先找到当前的顶点w的位置，再去找它的邻接点
    //    for(p=G.ventices[v].first;p!= nullptr;p=p->next)
    //        if(p->adjvex==w)
    //            break;
    //    if(p== nullptr||p->next== nullptr)
    //        return -1;
    //    return p->next->adjvex;//p的下一个邻接点的值
    if (v != -1) {
        ArcNode* p = G.ventices[v].first;
        while (p != nullptr && p->adjvex != w)
            p = p->next;
        if (p != nullptr && p->next != nullptr)
            return p->next->adjvex;
    }
    return -1;
}

//
int visited[MaxVertexNum];
int visited1[MaxVertexNum];
void DFS(ALGraph G, int i, int j, bool& can_reach) {
    //顶点v1到vj的路径
    if (i == j) {
        can_reach = true;
        return;
    }
    visited[i] = 1;
    for (int p = FirstNeighbor(G, i); p >= 0; p = NextNeighbor(G, i, p))
        if (!visited[p] && !can_reach)
            DFS(G, p, j, can_reach);
}

//基于下标的操作
int BFS(ALGraph G, int i, int j) {
    queue<int> q;
    int u;
    q.push(i);
    while (!q.empty()) {
        u = q.front();//访问队头
        q.pop();
        visited1[u] = 1;//标记访问
        if (u == j)
            return 1;

        for (int p = FirstNeighbor(G, u); p >= 0; p = NextNeighbor(G, u, p)) {
            //for 的判断条件p必须大于等于0，不能像书本那样只填个p，不然就一直循环
            if (p == j)    //查找成功
                return 1;
            if (!visited1[p]) {
                q.push(p);
                cout << p << endl;
                visited1[p] = 1;
            }
        }
    }
    return 0;
}
void Print(ALGraph G) {
    ArcNode* p;
    for (int i = 0; i < G.vexnum; i++) {
        cout << G.ventices[i].data;
        for (p = G.ventices[i].first; p != nullptr; p = p->next) {
            cout << "->" << p->adjvex;
        }
        cout << endl;
    }
    p = nullptr;

}
int main() {
    ALGraph G;
    Create(G);
    Print(G);
    memset(visited, 0, sizeof(visited));
    memset(visited1, 0, sizeof(visited1));
    VertexType vi, vj;
    cout << "input the vi and vj" << endl;
    cin >> vi >> vj;
    int i = Locate(G, vi);//下标操作
    int j = Locate(G, vj);

    int ret;
    ret = BFS(G, i, j);
    if (ret)
        cout << "yes" << endl;
    else
        cout << "no" << endl;

    bool can_reach = false;
    DFS(G, i, j, can_reach);
    if (can_reach)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
    return 0;
}