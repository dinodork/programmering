//#include <bits/stdc++.h>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#undef DBUG
#define DBUG
#ifdef DBUG
#define debug_print(...) printf(__VA_ARGS__)
#else
#define debug_print(...)
#endif

using namespace std;

vector<string> split_string(string);

int leftChildIndex(int n, size_t s) { return 2 * n - s - 1; }

int rightChildIndex(int n, size_t s) { return 2 * n - s; }

void heapify(vector<int> &v) {
  if (v.size() < 2)
    return;
  debug_print("before heapify: ");
  for (int i : v)
    debug_print("%i ", i);
  debug_print("\n");
  debug_print("heap height = %lu\n", (v.size() >> 1) + 1);

  for (unsigned int i = v.size() - 1; leftChildIndex(i, v.size()) >= 0; --i) {
    int lci = leftChildIndex(i, v.size());

    debug_print("v[%i] = %i > v[%i] = %i ?\n", i, v[i], lci, v[lci]);

    if (v[i] > v[lci]) {
      debug_print("yes\n");
      swap(v[i], v[lci]);
    }

    int rci = rightChildIndex(i, v.size());

    debug_print("v[%i] = %i > v[%i] = %i ?\n", i, v[i], rci, v[rci]);

    if (v[i] > v[rci]) {
      debug_print("yes\n");
      swap(v[i], v[rci]);
    }
  }
  debug_print("after heapify: ");
  for (int i : v)
    debug_print("%i ", i);
  debug_print("\n");
}

int getMinValue(vector<int> &heap) {
  if (heap.empty())
    return -1;
  int v = heap[heap.size() - 1];
  debug_print("getMinValue(");
  for (int n : heap)
    debug_print("%i ", n);
  debug_print(")\n");
  heap.pop_back();
  heapify(heap);
  debug_print("getMinValue = %i\n", v);
  return v;
}

/*
 * Complete the getMoneySpent function below.
 */
int getMoneySpent(vector<int> keyboards, vector<int> drives, int b) {

  heapify(keyboards);
  heapify(drives);
  const auto drivesCopy = drives;
  debug_print("--------------\n");
  int maxMoneySpent = -1;
  int keyboard = -1;
  int drive = -1;
  int chosenKeyboard = -1;
  int chosenDrive = -1;

  while ((keyboard = getMinValue(keyboards)) != -1) {
    drives = drivesCopy;
    while ((drive = getMinValue(drives)) != -1 && (drive + keyboard) <= b) {
      if (drive + keyboard > maxMoneySpent) {
        chosenKeyboard = keyboard;
        chosenDrive = drive;
        maxMoneySpent = drive + keyboard;
      }
    }
  }

  printf("Answer: %i + %i = %i\n", chosenKeyboard, chosenDrive, maxMoneySpent);
  return maxMoneySpent;
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string bnm_temp;
  getline(cin, bnm_temp);

  vector<string> bnm = split_string(bnm_temp);

  int b = stoi(bnm[0]);

  int n = stoi(bnm[1]);

  int m = stoi(bnm[2]);

  string keyboards_temp_temp;
  getline(cin, keyboards_temp_temp);

  vector<string> keyboards_temp = split_string(keyboards_temp_temp);

  vector<int> keyboards(n);

  for (int keyboards_itr = 0; keyboards_itr < n; keyboards_itr++) {
    int keyboards_item = stoi(keyboards_temp[keyboards_itr]);

    keyboards[keyboards_itr] = keyboards_item;
  }

  string drives_temp_temp;
  getline(cin, drives_temp_temp);

  vector<string> drives_temp = split_string(drives_temp_temp);

  vector<int> drives(m);

  for (int drives_itr = 0; drives_itr < m; drives_itr++) {
    int drives_item = stoi(drives_temp[drives_itr]);

    drives[drives_itr] = drives_item;
  }

  /*
   * The maximum amount of money she can spend on a keyboard and USB drive, or
   * -1 if she can't purchase both items
   */

  int moneySpent = getMoneySpent(keyboards, drives, b);

  fout << moneySpent << "\n";

  fout.close();

  return 0;
}

vector<string> split_string(string input_string) {
  string::iterator new_end =
      unique(input_string.begin(), input_string.end(),
             [](const char &x, const char &y) { return x == y and x == ' '; });

  input_string.erase(new_end, input_string.end());

  while (input_string[input_string.length() - 1] == ' ') {
    input_string.pop_back();
  }

  vector<string> splits;
  char delimiter = ' ';

  size_t i = 0;
  size_t pos = input_string.find(delimiter);

  while (pos != string::npos) {
    splits.push_back(input_string.substr(i, pos - i));

    i = pos + 1;
    pos = input_string.find(delimiter, i);
  }

  splits.push_back(
      input_string.substr(i, min(pos, input_string.length()) - i + 1));

  return splits;
}
