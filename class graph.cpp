#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Graph {
    struct Edge {
        int weight;
        int index;
        Edge* next;
        Edge(int weight, int index, Edge* next = nullptr) : weight(weight), index(index), next(next) {}
    };
    struct Vertex {
        char name;
        Edge* edges;
        Vertex() :name(0), edges(nullptr) {}
        Vertex(char name, Edge* edges = nullptr) :name(name), edges(edges) {}
    };
    int count;
    Vertex* verts;
public:
    Graph() : count(0), verts(nullptr){}

    void add_vertex(char name) {
        for (size_t i = 0; i < count; ++i) {
            if (verts[i].name == name) throw logic_error("Vertex 'name' already exist");
        }
        Vertex* tmp = new Vertex[count + 1];
        for (size_t i = 0; i < count; ++i){
            tmp[i].name = verts[i].name;
        }
        tmp[count] = Vertex(name);
        delete[]verts;
        verts = tmp;
        ++count;
    }

    void del_vertex(char name) {
        int k = 0;
        while (verts[k].name != name && k!=count) {
            ++k;
        }
        if (k==count) throw logic_error("Vertex 'name' not exist");
        int index = find_index(name);
        Vertex* tmp = new Vertex[count-1];
        /*for (size_t i = index; i < count - 1; ++i) {
            verts[i].name = verts[i + 1].name;
            verts[i].edges = verts[i + 1].edges;
        }
        for (size_t i = 0; i < count - 1; ++i) {
            tmp[i].name = verts[i].name;
            tmp[i].edges = verts[i].edges;
        }*/
        for (size_t i = 0; i < index; ++i) {
            tmp[i].name = verts[i].name;
            tmp[i].edges= verts[i].edges;
        }
        for (int i = index; i < count-1; ++i) {
            tmp[i].name = verts[i+1].name;
            tmp[i].edges = verts[i+1].edges;
        }
        delete[]verts;
        verts = tmp;
        --count;
    }

    int find_index(char name) {
        for (size_t i = 0; i < count; ++i){
            if (verts[i].name == name) return i;
        }
        throw logic_error("Vertex 'name' not exist");
    }

    void add_edge(char src, char dst, int weight) {
        int ind_v1 = find_index(src);
        int ind_v2 = find_index(dst);
        if (weight<=0) throw logic_error("Weight < 0");
        verts[ind_v1].edges = new Edge(weight, ind_v2, verts[ind_v1].edges);
    }

    void del_edges(char src, char dst) {
        int ind_src = find_index(src);
        int ind_dst = find_index(dst);
        Edge* head = verts[ind_src].edges;
        if (ind_dst == head->index) { // если элемент первый в списке
            verts[ind_src].edges = verts[ind_src].edges->next;
            delete head;
        }
        else {
            while (head->next->index != ind_dst) {
                head = head->next;
            }
            Edge* tmp = head;
            head = head->next;
            tmp->next = head->next;
            delete head;
        }
    }

    void dfs(char name) {
        int index = find_index(name);
        bool* visited = new bool[count];
        for (size_t i = 0; i < count; ++i) {
            visited[i] = false;
        }
        stack<int> q;
        q.push(index);
        cout<< "dfs:" <<endl;
        while (!q.empty()) {
            int cur_id = q.top();
            q.pop();
            if (visited[cur_id] == true) {
                continue;
            }
            Edge* head = verts[cur_id].edges;
            while (head) {
                if (!visited[head->index]) {
                    q.push(head->index);
                }
                head = head->next;
            }
            cout << verts[cur_id].name << ' ';
            visited[cur_id] = true;
        }
        cout << endl;
    }

    void bfs(char name) {
        int index = find_index(name);
        bool* vis = new bool[count];
        for (size_t i = 0; i < count; ++i) {
            vis[i] = false;
        }
        queue<int> q;
        q.push(index);
        cout << "bfs:" << endl;
        while (!q.empty()) {
            int cur_id = q.front();
            q.pop();
            if (vis[cur_id] == true)
                continue;
            Edge* head = verts[cur_id].edges;
            while (head) {
                if (!vis[head->index]) {
                    q.push(head->index);
                }
                head = head->next;
            }
            cout << verts[cur_id].name << ' ';
            vis[cur_id] = true;
        }
        cout << endl;
    }

    void print() {
        cout << "Graph:" << endl;
        for (size_t i = 0; i < count; ++i){
            cout << verts[i].name << endl;
            Edge* head = verts[i].edges;
            while (head) {
                cout << "\t" << verts[head->index].name << " " << head->weight << endl;
                head = head->next;
            }
        }
    }

    ~Graph() {
        for (size_t i = 0; i < count; i++){
            Edge* head = verts[i].edges;
            while (head) {
                Edge* tmp = head;
                head = head->next;
                delete tmp;
            }
        }
        delete[]verts;
        count = 0;
    }
};

int main()
{
    Graph g;
    g.add_vertex('A');
    g.add_vertex('B');
    g.add_vertex('C');
    g.add_vertex('D');
    g.add_vertex('E');
    g.add_edge('A', 'B', 1);
    g.add_edge('A', 'C', 8);
    g.add_edge('C', 'A', 8);
    g.add_edge('B', 'D', 2);
    g.add_edge('B', 'E', 9);
    g.add_edge('E', 'D', 9);
    g.bfs('A');
    g.dfs('A');
    g.print();
    g.del_edges('A', 'C');
    g.del_vertex('C');
    g.print();
}

