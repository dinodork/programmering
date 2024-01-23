#include <catch2/catch.hpp>

#include <cstdint>

#include "heapsort.hpp"

using namespace std;

uint32_t factorial(uint32_t number) {
  return number <= 1 ? number : factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(factorial(1) == 1);
  REQUIRE(factorial(2) == 2);
  REQUIRE(factorial(3) == 6);
  REQUIRE(factorial(10) == 3'628'800);
}

TEST_CASE("Heapify", "[heapify]") {
  {
    vector<int> v = {1, 2, 3};
    heapify(v, 0);
    REQUIRE(v == vector({3, 2, 1}));
  }
  {
    vector<int> v = {1, 2, 3, 4, 5};
    heapify(v, 0);
    REQUIRE(v == vector({3, 2, 1, 4, 5}));
  }
}

TEST_CASE("Building the heap", "[buildHeap]") {
  {
    vector<int> v = {1, 2, 3};
    buildHeap(v);
    REQUIRE(v == vector({3, 2, 1}));
  }
  {
    vector<int> v = {1, 2, 3, 4};
    heapify(v, 0);
    REQUIRE(v == vector({3, 2, 1, 4}));
  }
  {
    vector<int> v = {1, 2, 3, 4, 5};
    heapify(v, 0);
    REQUIRE(v == vector({3, 2, 1, 4, 5}));
  }
}


TEST_CASE("Extract the max", "[extractMax]") {
  {
    vector<int> v = {3, 2, 1};
    Heap heap(v);
    REQUIRE(heap.size() == 3);
    REQUIRE(heap.extractMax() == 3);
    REQUIRE(heap.size() == 2);
  }
}
