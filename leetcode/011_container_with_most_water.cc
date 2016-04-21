/* 011_container_with_most_water.cc
 *
 * leetcode problem 011:
 * Given n non-negative integers a1, a2, ..., an, where each represents a point
 * at coordinate (i, ai). n vertical lines are drawn such that the two 
 * endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together 
 * with x-axis forms a container, such that the container contains the most 
 * water.
 *
 * History: 
 *  04/19/2016: file created
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"

int get_max_area(vector<int>& height) {
    
    int max_area = 0;
    int tmp_area = 0;
    size_t num_lines = height.size();
    size_t i = 0;
    size_t j = num_lines - 1;
    
    // Start from two ends of the lines. 
    // Each time, move of the lower line.
    while (i < j) {
        int width = j - i;
        
        if (height[i] < height[j]) {// Identify lower line
            tmp_area = height[i] * width;
            i++;
        } else {
            tmp_area = height[j] * width;
            j--;
        }

        if (max_area < area) {      // Update max area if found a larger area
            max_area = area;
        } 
    }
    
    return max_area;
}


int main(int argc, char *argv[]) {
    // Test
    vector<int> height = {1,2,4,3};
    cout << get_max_area(height) << endl;
    return 0;
}

