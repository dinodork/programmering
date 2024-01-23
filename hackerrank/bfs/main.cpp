#include <bits/stdc++.h>
#include <variant>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'bfs' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. 2D_INTEGER_ARRAY edges
 *  4. INTEGER s
 */

vector<int> bfs(int n, int m, vector<vector<int>> edges, int s) {
  struct Node {
    int id;
    int cost;
    vector<Node *> adjacent; // Two-way link
    bool visited{false};

    Node() = default;
    Node(int ida) : id(ida), cost(-1) {}
  };

  struct EndOfLayer {};

  using QueueElement = variant<Node *, EndOfLayer>;
  using Queue = deque<QueueElement>;

  const int w = 6;

  Node allNodes[n];
  for (int i = 0; i < n; ++i)
    new (allNodes + i) Node(i + 1);

  // Build graph
  for (const auto &edge : edges) {
    auto edgeStart = allNodes + edge[0] - 1;
    auto edgeEnd = allNodes + edge[1] - 1;
    edgeStart->adjacent.push_back(edgeEnd);
    edgeEnd->adjacent.push_back(edgeStart);
  }

  cout << "All nodes:\n";
  for (int i = 0; i < n; ++i) {
    Node &node = allNodes[i];
    cout << "Node( id=" << node.id << " adjacent={ ";
    for (auto node : node.adjacent)
      cout << node - allNodes + 1 << " ";
    cout << "} )\n";
  }
  cout << "\n";

  Queue q;
  q.push_back(allNodes + s - 1);
  q.push_back(EndOfLayer());

  int currentCost = 0;

  while (!q.empty()) {
    auto elem = q.front();
    q.pop_front();

    if (holds_alternative<EndOfLayer>(elem)) {
      currentCost += w;
      cout << "Popped eol cc=" << currentCost << "\n";
      if (!q.empty())
        q.push_back(elem);

    } else {
      auto node = get<Node *>(elem);
      if (!node->visited) {
        node->visited = true;
        cout << "Popped node " << node->id << "\n";

        node->cost = currentCost;
        for (auto adjacentNode : node->adjacent) {
          cout << "q'ing #" << adjacentNode - allNodes << " : " << node->id
               << "\n";
          q.push_back(adjacentNode);
        }
      }
    }
  }

  vector<int> answer;
  answer.reserve(n - 1);

  for (int i = 0; i < n; ++i)
    if (i != s - 1) {
      cout << "pushing back answer\n";
      answer.push_back(allNodes[i].cost);
      cout << "answer size now = " << answer.size() << endl;
    }

  cout << "n = " << n << endl;
  cout << "answer size = " << answer.size() << endl;

  cout << "Answer: {";
  for (int cost : answer)
    cout << cost << " ";
  cout << "}\n----------\n";

  return answer;
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string q_temp;
  getline(cin, q_temp);

  int q = stoi(ltrim(rtrim(q_temp)));

  for (int q_itr = 0; q_itr < q; q_itr++) {
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input =
        split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<vector<int>> edges(m);

    for (int i = 0; i < m; i++) {
      edges[i].resize(2);

      string edges_row_temp_temp;
      getline(cin, edges_row_temp_temp);

      vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

      for (int j = 0; j < 2; j++) {
        int edges_row_item = stoi(edges_row_temp[j]);

        edges[i][j] = edges_row_item;
      }
    }

    string s_temp;
    getline(cin, s_temp);

    int s = stoi(ltrim(rtrim(s_temp)));

    vector<int> result = bfs(n, m, edges, s);

    for (size_t i = 0; i < result.size(); i++) {
      fout << result[i];

      if (i != result.size() - 1) {
        fout << " ";
      }
    }

    fout << "\n";
  }

  fout.close();

  return 0;
}

string ltrim(const string &str) {
  string s(str);

  s.erase(s.begin(),
          find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

  return s;
}

string rtrim(const string &str) {
  string s(str);

  s.erase(
      find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
      s.end());

  return s;
}

vector<string> split(const string &str) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(" ", start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));

    start = end + 1;
  }

  tokens.push_back(str.substr(start));

  return tokens;
}
