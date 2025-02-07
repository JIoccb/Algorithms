#include <iostream>
#include <queue>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

struct Aho_Corasick {
    static constexpr int al = 26; // Алфавит: буквы 'a'-'z'
    struct Node {
        Node* to[al]{};
        Node* go[al]{};
        Node* link = nullptr;
        pmr::vector<int> output; // Индексы строк, заканчивающихся в этой вершине
        char pred_ch;
        Node* pred = nullptr;
        Node(char _pred_ch, Node* _pred) : pred_ch(_pred_ch), pred(_pred) {
            memset(to, 0, sizeof(to));
            memset(go, 0, sizeof(go));
        }
    };

    Node* root = new Node(0, nullptr);

    void add(const string& s, int index) const {
        Node* cur = root;
        for (char ch : s) {
            if (ch < 'a' || ch > 'z') {
                cerr << "Invalid character in input string: " << ch << endl;
                exit(1);
            }
            if (!cur->to[ch - 'a']) {
                cur->to[ch - 'a'] = new Node(ch, cur);
            }
            cur = cur->to[ch - 'a'];
        }
        cur->output.push_back(index); // Строка заканчивается в этой вершине
    }

    void build_links() const {
        queue<Node*> q;
        root->link = root; // Суффиксная ссылка корня на сам корень
        for (int i = 0; i < al; i++) {
            if (root->to[i]) {
                root->to[i]->link = root;
                q.push(root->to[i]);
            } else {
                root->go[i] = root;
            }
        }
        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();
            for (int i = 0; i < al; i++) {
                if (cur->to[i]) {
                    Node* next = cur->to[i];
                    Node* fail = cur->link;
                    while (fail != root && !fail->to[i]) {
                        fail = fail->link;
                    }
                    if (fail->to[i]) {
                        fail = fail->to[i];
                    }
                    next->link = fail;
                    next->output.insert(next->output.end(), fail->output.begin(), fail->output.end());
                    q.push(next);
                } else {
                    cur->go[i] = cur->link->go[i];
                }
            }
        }
    }

    void search(const string& t, vector<bool>& found) const {
        Node* cur = root;
        for (char ch : t) {
            if (ch < 'a' || ch > 'z') {
                cerr << "Invalid character in text: " << ch << endl;
                exit(1);
            }
            cur = cur->go[ch - 'a'];
            for (int index : cur->output) {
                found[index] = true;
            }
        }
    }

    ~Aho_Corasick() {
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();
            for (auto & i : cur->to) {
                if (i) {
                    q.push(i);
                }
            }
            delete cur;
        }
    }
};

int main() {
    string t;
    cin >> t;

    int n;
    cin >> n;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    Aho_Corasick ac;

    // Добавление строк в автомат
    for (int i = 0; i < n; i++) {
        ac.add(s[i], i);
    }

    // Построение ссылок
    ac.build_links();

    // Результаты
    vector found(n, false);

    // Поиск
    ac.search(t, found);

    // Вывод результатов
    for (int i = 0; i < n; i++) {
        cout << (found[i] ? "YES" : "NO") << endl;
    }

    return 0;
}