/* SuffixTree.h
 * 
 * Definition of Class SuffixTree. A definition of tree node structure is also 
 * given. Children of a tree node is stored in an array indexed by ASCII chars.
 * Therefore, in this version, we assume the string will contain only ASCII.
 * 
 * History: 
 * 05/08/2016: First version finished
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */


#ifndef SUFFIXTREE_H
#define SUFFIXTREE_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

// Constant Variable
const int   MAX_CHAR = 256;

/* struct: suffix_tree_node
 *  For non-root node, we use a pair of integer to store characters from this
 *  node's parent to it. In particular, index of last character on the edge is
 *  shared by all leaves. 
 */

typedef struct suffix_tree_node {
    int start;	    // Index of first char of the edge
    int* end;	    // Point to the index of last char of the edge
    int	suffix_index;   // Non-neg: index of suffix; -1: internal nodes
    suffix_tree_node*   children[MAX_CHAR]; // Links to children
    suffix_tree_node*   suffix_link;	    // Suffix link for internal nodes
    int	label;	    // Label of the node
} SuffixTreeNode, *SuffixTreeNodePtr;

/* class: SuffixTree          
 *  This class implements a string suffix tree data structure and Ukkonen's
 *  algorithm for builting suffix tree in O(n) complexity. Building a suffix 
 *  tree contains a N phase expansion where N equals to the number of chars.
 *  In each phase, a new character is added to the expansion from the input 
 *  string. Each phase contains M suffix to add. Ukkonen's algorithm contains 
 *  three rules for adding these suffixes. A good introduction of this algorithm
 *  can be found at http://www.geeksforgeeks.org/
 */
class SuffixTree {

private:
    // Private Attributes
    string str_;		// Store input string
    int  phase_;		// Current phase in tree extension
    int  remain_suffix_;	// Number of suffix to extend in a phase
    int  active_steps_;		// Walk down steps on the active edge
    int  active_char_idx_;	// Index of first char of the active edge
    SuffixTreeNodePtr   root_node_;	// Link to root node
    SuffixTreeNodePtr   active_node_;	// Link to the active node
    SuffixTreeNodePtr   last_node_;	// Link to last created internal node
    vector<SuffixTreeNodePtr>   all_nodes_; // Link to all nodes for cleaning
    

public:
     // CLass Methods
    SuffixTreeNodePtr add_node(int edge_start, int* edge_end);
    void expand_tree(string s);
    void dfs_traverse(SuffixTreeNodePtr node); 
    void print_tree();

    // Construction methods
    SuffixTree();
    //SuffixTree(string s);
    virtual ~SuffixTree();
};

#endif

