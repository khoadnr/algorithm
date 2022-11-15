#include <algorithm>
#include <cassert>
#include <vector>

#include "sorting_util.h"

namespace algorithm {
namespace sorting {

/**
 * Bubble Sort is mainly useful when sorting a large set of floating point
 * numbers which are in range [0, 1). It works by distributing elements to
 * buckets, then sorts each bucket and finally concatenates all sorted buckets.
 * @tparam T T array's class
 * @tparam N size of array
 * @param array unsorted array (non-negative floating point number array in
 * range [0, 1))
 *
 * Examples:
 *  - Giving an array [0.52, 0.12, 0.86, 0.29, 0.46, 0.4, 0.18, 0.6], 10 buckets
 * and assuming that we sort the array by ascending order.
 *  - Distributing all the elements to corresponding buckets by multiplying the
 * element and buckets' slots. Each bucket is a linked list. [0.52, 0.12, 0.86,
 * 0.29, 0.46, 0.4, 0.18, 0.6] -> array
 *    [[], [], [], [], [], [], [], [], [], []] -> buckets
 *    [0 []
 *     1 [] -> [0.12] -> [0.18]   0.12 * 10 = 1.2, 0.18 * 10 = 1.8
 *     2 [] -> [0.29]   0.29 * 10 = 2.9
 *     3 []
 *     4 [] -> [0.46] -> [0.4]   0.46 * 10 = 4.6, 0.4 * 10 = 4.0
 *     5 [] -> [0.52]   0.52 * 10 = 5.2
 *     6 [] -> [0.6]
 *     7 []
 *     8 [] -> [0.86]   0.86 * 10 = 8.6
 *     9 []
 *     ]
 *  - We sort each bucket using insertion sort.
 *    [[], [0.12, 0.18], [0.29], [], [0.4, 0.46], [0.52], [0.6], [], [0.86], []]
 *  - Concatenating all non-empty buckets, array is now sorted.
 */
template <class T, size_t N>
void BucketSort(T (&array)[N]) {
  if (!std::is_same<T, float>::value && !std::is_same<T, double>::value) {
    throw std::runtime_error("Only accept floating point number array.");
  }

  for (auto element : array) {
    if (element < 0 || element >= 1) {
      throw std::runtime_error(
          "Only accept non-negative floating point number array in range [0, "
          "1).");
    }
  }

  constexpr unsigned int slots = 10;
  std::vector<T> buckets[slots];
  for (auto i = 0; i < N; i++) {
    int bucket_index = slots * array[i];
    buckets[bucket_index].push_back(array[i]);
  }

  int index = 0;
  for (auto i = 0; i < slots; i++) {
    sort(buckets[i].begin(), buckets[i].end());
    for (auto j = 0; j < buckets[i].size(); j++) {
      array[index++] = buckets[i][j];
    }
  }
}

}  // namespace sorting
}  // namespace algorithm

int main() {
  float floats[8] = {0.52f, 0.44f, 0.68f, 0.95f, 0.1f, 0.12f, 0.32f, 0.59f};
  double doubles[8] = {0.52, 0.44, 0.68, 0.95, 0.1, 0.12, 0.32, 0.59};

  algorithm::sorting::BucketSort(floats);
  std::cout << "Sorted float array: ";
  algorithm::sorting::PrintArray(
      floats);  // 0.1 0.12 0.32 0.44 0.52 0.59 0.68 0.95

  algorithm::sorting::BucketSort(doubles);
  std::cout << "Sorted double array: ";
  algorithm::sorting::PrintArray(
      doubles);  // 0.1 0.12 0.32 0.44 0.52 0.59 0.68 0.95

  return 0;
}