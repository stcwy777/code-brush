/* 015_3sum.cc
 *
 * leetcode problem 015:
 * Given an array S of n integers, are there elements a, b, c in S such that
 * a + b + c = 0? Find all unique triplets in the array which gives the sum of
 * zero.
 *
 * History: 
 *  03/13/2017: file created
 *  03/19/2017: dp for finding combination, though overkill for this problem
 *  04/05/2017: added two pointers solution
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"
#include <algorithm>
#include <numeric>
typedef vector< vector<int> > Comb;
typedef vector< vector<int> >* CombPt;

bool ascend (int i, int j) { return (i<j); }

/*
 * Find n combinations gieven a list of numbers. 
 * Implemented with dynamic programming.
 */
vector< vector<int> > find_comb(vector<int> nums, int n) {
    int size = nums.size();
    vector< vector<int> > rslt;

    if (size < n) { // Invalid input (n > numbers in the list)
        return rslt;
    }
    // "solution" is a 2D array where each entry (x, y) indicates y combinations
    // of the first x numbers in the input. 
    CombPt*  solution;
    solution = new CombPt[size+1];

    for (size_t i = 0; i <= size; i++) {
        solution[i] = new Comb[n+1];
    }

    // Boundary conditions:
    // 1) 0 combinations of first i numbers;
    // 2) 1 combinations of first i numbers.
    for (size_t i = 1; i <= size; i++) {
        vector<int> empty;
        solution[i][0].push_back(empty);
        for (size_t j = 1; j <= i; j++) {
            vector<int> single(1, nums[j-1]);
            solution[i][1].push_back(single);
        }
    }

    // DP: solution(x, y) = solution(x-1, y) + [solution(x, y-1) and x]
    for (size_t i = 2; i <= size; i++) {
        for (size_t j = 2; j <= i && j <= n; j++) {

            if (i > j) {
                solution[i][j] = solution[i-1][j];
            }
            for (size_t k = 0; k < solution[i-1][j-1].size(); k++) {
                vector<int>  sub_solution = solution[i-1][j-1][k];
                sub_solution.push_back(nums[i-1]);
                solution[i][j].push_back(sub_solution);
            }
        }
    }
    rslt = solution[size][n];
    // delete solution;
    return rslt;
}

/*
 * Find triplets of which the sum equals to 0. Find all combinations and
 * remove duplicates using hash tables.
 */
vector< vector<int> > three_sum_dp(vector<int>& nums) {
    vector< vector<int> > rslt;
    vector<int> r_nums;
    unordered_map <int, int> input_map;    
    unordered_map <string, bool> unique_comp;

    if (nums.size() >= 3) {
        for (auto num : nums) {
            if (input_map.find(num) == input_map.end()) {
                input_map.insert(make_pair(num, 1));
            } else if (num != 0 && input_map[num] < 2) {
                input_map[num]++;
            } else if (num == 0 && input_map[num] < 3) {
                input_map[num]++;
            }
        }
        for (pair<int, int> elem : input_map) {
            for (size_t i = 0;i < elem.second; i++) {
                r_nums.push_back(elem.first);
            }
        }

        vector< vector<int> > combs = find_comb(nums, 3);
        for (auto comb:combs) {
            stringstream ss;
            int sum = 0;
            for (size_t i = 0; i < comb.size(); i++) {
                sum += comb[i];
                ss << comb[i] << " ";
            }
            if ( sum == 0 && unique_comp.find(ss.str()) == unique_comp.end()) {
                unique_comp.insert(make_pair(ss.str(), true));
                rslt.push_back(comb);
            }
        }
    }
    return rslt;
}

/*
 * Find triplets of which the sum equals to 0. Use two pointers to travse the 
 * array.
 */
vector< vector<int> > three_sum_light(vector<int>& nums) {
    vector< vector<int> > rslt;

    sort(nums.begin(), nums.end());
    size_t tot_nums = nums.size();

    if (nums.size() < 3) {
        return rslt;
    }
    for (size_t i = 0; i < tot_nums - 2; i++) {
        if (i && nums[i-1] == nums[i]) { // skip same numbers
            continue;
        } 
        size_t lpt = i + 1;
        size_t rpt = tot_nums - 1;
        int tar = -nums[i];        
        while (lpt < rpt) {
            int two_sum = nums[lpt] + nums[rpt];
            cout << '\t' << i << " " << two_sum << " " << tar << endl;

            if (two_sum == tar) {
                vector<int> solution;                
                solution.push_back(nums[i]);
                solution.push_back(nums[lpt]);
                solution.push_back(nums[rpt]);
                rslt.push_back(solution);
                lpt++;
                rpt--;
                while (lpt < rpt && nums[lpt-1] == nums[lpt]){
                    lpt++;
                }            
                while (lpt < rpt && nums[rpt+1] == nums[rpt]) {
                    rpt--;         
                }
            } else if (two_sum < tar) {
                lpt++;
            } else {
                rpt--;
            }
        }

    }
    return rslt;
}

int main(int argc, char *argv[]) {
    // Test: Initialize two number lists
    // -4, -1, -1, 0, 1, 2
    const int arrs[] = {-1, 0, 1, 2, -1, -4};
    // const int arrs[] = {1, 2,-2,-1};
    // const int arrs[] = {1, 1,1};
    // const int arrs[] = {-2, 0, 0, 2, 2};
    vector< vector<int> > rslt;
    vector<int> nums(arrs, arrs + sizeof(arrs)/sizeof(arrs[0]));

    rslt = three_sum_light(nums);
    // rslt = find_comb_dp(nums, 3);
    cout << rslt.size() << endl;
    for (auto comb:rslt) {
        if (1) {
            for (auto num:comb) {
                cout << num << " ";
            }
            cout << endl;
        }
    }
    return 0;
}

