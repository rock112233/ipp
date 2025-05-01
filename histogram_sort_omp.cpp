#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

void histogram_sort_parallel(std::vector<int>& data, int num_bins) {
    int n = data.size();
    int max_val = *std::max_element(data.begin(), data.end());
    int min_val = *std::min_element(data.begin(), data.end());

    int range = max_val - min_val + 1;
    int bin_size = (range + num_bins - 1) / num_bins;

    // Create bins
    std::vector<std::vector<int>> bins(num_bins);

    // Step 1: Assign elements to bins in parallel
    #pragma omp parallel
    {
        std::vector<std::vector<int>> local_bins(num_bins);

        #pragma omp for nowait
        for (int i = 0; i < n; ++i) {
            int bin_index = (data[i] - min_val) / bin_size;
            local_bins[bin_index].push_back(data[i]);
        }

        // Merge local bins into global bins
        #pragma omp critical
        {
            for (int i = 0; i < num_bins; ++i) {
                bins[i].insert(bins[i].end(), local_bins[i].begin(), local_bins[i].end());
            }
        }
    }

    // Step 2: Sort each bin in parallel
    #pragma omp parallel for
    for (int i = 0; i < num_bins; ++i) {
        std::sort(bins[i].begin(), bins[i].end());
    }

    // Step 3: Merge sorted bins into original array
    int index = 0;
    for (int i = 0; i < num_bins; ++i) {
        for (int val : bins[i]) {
            data[index++] = val;
        }
    }
}

int main() {
    std::vector<int> data = {35, 12, 43, 8, 51, 27, 3, 66, 23, 18};

    std::cout << "Original: ";
    for (int num : data) std::cout << num << " ";
    std::cout << "\n";

    int num_bins = 4; // Can be set based on data or thread count
    histogram_sort_parallel(data, num_bins);

    std::cout << "Sorted:   ";
    for (int num : data) std::cout << num << " ";
    std::cout << "\n";

    return 0;
}