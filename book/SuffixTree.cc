/* SuffixTree.cc
 * 
 * An implementation file of Class SuffixTree. Suffix tree expansion is 
 * implemented by Ukkonen's Suffix Tree algorithm.
 *
 * A detailed introduction of this algorithm can be found at
 * http://www.geeksforgeeks.org/
 * 
 * History:
 * 05/08/2016: First version finished
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */


#include "SuffixTree.h"


/* constructor
 *  Set default values of members and create a root node
 */
SuffixTree::SuffixTree() {
    
    // Initialize root node
    root_node_ = add_node(-1, NULL);
    
    // Initialize variables for tree extension
    phase_ = -1;
    remain_suffix_ = 0;
    active_steps_ = 0;
    active_char_idx_ = -1;
    active_node_ = root_node_;
    last_node_ = NULL;
}

/* destructor
 *   Delete all nodes in the tree. For internal node, its edge end variable 
 *   should also be deleted.
 */
SuffixTree::~SuffixTree() {
    for (int i = 0; i < all_nodes_.size(); i++) {
        SuffixTreeNodePtr& node = all_nodes_[i];
        if (node->end != NULL && node->end != &phase_) {
            delete node->end;
        }
        delete node;
    }
}

/* create_new_node
 *  Create a new suffix tree node and set members to default value
 * 
 * args:
 *  edge_start: index of first char of the edge ending at this node
 *
 * return:
 *  node: a pointer of newly allocated node
 */
SuffixTreeNodePtr SuffixTree::add_node(int edge_start, int* edge_end) {
    SuffixTreeNodePtr node = new SuffixTreeNode();
    
    node->start = edge_start;
    // For leaf nodes, their edge end value is shared
    // For internal nodes, set individual edge end
    node->end = edge_end;

    node->suffix_index = -1;
    node->suffix_link = NULL;
    
    for (int i = 0; i < MAX_CHAR; i++) {    // Set all children to NULL
        node->children[i] = NULL;
    }

    all_nodes_.push_back(node);       // Record this node
    node->label = all_nodes_.size();

    return node;
}

/* build_tree
 *  Build a suffix tree given an input string
 * 
 * args:
 *  s: input string with last character as '$'
 *
 */
void SuffixTree::expand_tree(string s) {
    str_ = s + '$';
    int s_len = str_.length();
    cout << "phases: " << s_len << endl;
    // Perform n phases expansion where n equals to string length
    for (int i = 0; i < s_len; i++) {
        ++phase_;               // Apply rule 1 extension
        ++remain_suffix_;       
        last_node_ = NULL;
        // Every phase contains extensions of suffix introduced by the new 
        // character. Extensions will be terminated when rule 3 is applied
        while (remain_suffix_) {
            // If the current extension is not performed on any edge
            // set the active char to the added character of the new phase
            if (active_steps_ == 0) { 
                active_char_idx_ = phase_;
            }
            
            // If no outgoing edges heading with active char
            // Apply rule 2: add new leadf node. Otherwise, walk down along 
            // the outgoing edge. An internal node will be created if the new 
            // char is not contained
            SuffixTreeNodePtr child_node = 
                active_node_->children[str_[active_char_idx_]]; 
            if (child_node == NULL) {
                active_node_->children[str_[active_char_idx_]] =
			add_node(active_char_idx_, &phase_); 
                
                // If there is a internal node created in last extension 
                // set its suffix link to this leaf node and reset 
                // last_node_ to NULL waiting for next internal node created
                if (last_node_) {
                    last_node_->suffix_link = active_node_;
                    last_node_ = NULL;
                }
            } else { 
                // How many chars on current edge
                int edge_length = *child_node->end - child_node->start + 1;
                
                // Walk down the entire edge and update active node
                if (edge_length <= active_steps_) {
                    active_steps_ -= edge_length;
                    active_char_idx_ += edge_length;
                    active_node_ = child_node;
		    child_node = active_node_->children[str_[active_char_idx_]];
                    continue;
                }
                
                // The new char to add in this phase already on the edge,
                if (str_[child_node->start + active_steps_] == str_[phase_]) {
                    if (last_node_) {
                        last_node_->suffix_link = active_node_;
                        last_node_ = NULL;
                    }
                    
                    // Apply rule 3: skip left extensions & move to next phase
                    ++active_steps_;
                    break;
                } else { 
                    // Add new internal node and leaf node
                    SuffixTreeNodePtr in_node = 
                         add_node(child_node->start, NULL);
		    active_node_->children[str_[active_char_idx_]] = in_node; 
		    in_node->end = new int;
                    *in_node->end = in_node->start + active_steps_ - 1;
        	    in_node->suffix_index = -1;

                    // Create leaf node for the new char
		    in_node->children[str_[phase_]] = add_node(phase_, &phase_);
		    child_node->start += active_steps_;
		    in_node->children[str_[child_node->start]] = child_node;
                        
        	    if (last_node_) {
                        last_node_->suffix_link = in_node;
                    }
        	    last_node_ = in_node;
                }
            }
	    // After add an new suffix, reduce remain_suffix_ by one. 
	    // Update active_node_ in two ways:
	    // (1) if active_node_ is root and active_steps_ > 0, reduce
	    // active_steps_ by one. The index of next active_node_ is 
	    // (phase_ - remain_suffix + 1)
	    --remain_suffix_;

	    if (active_node_ == root_node_ && active_steps_ > 0) {
		--active_steps_;
		active_char_idx_ = phase_ - remain_suffix_ + 1;
	    } else if (active_node_ != root_node_) {
		active_node_ = active_node_->suffix_link;
	    }
        }
    }
}

/* dfs_traverse
 *  Traverse the suffix tree by depth-first-search
 * 
 * args:
 *  node: a starting node could be root, internal node and leaf
 */
void SuffixTree::dfs_traverse(SuffixTreeNodePtr node) {

    if (node == NULL) {
        return;
    }
    
    if (node->start != -1) {
        size_t edge_length = *node->end - node->start + 1;
        cout << node->label << ":" << node->start << "," << *node->end << ":" 
	     << str_.substr(node->start, edge_length) << " ";
    }

    for (int i = 0; i < MAX_CHAR; i++) {
        if (node->children[i] != NULL) {
	    cout << char(i) << " > ";
            dfs_traverse(node->children[i]);
        }
    }
    cout << endl;
    return;
}

/* print_tree 
 *  print out characters along edges while dfs traverse the tree 
 */
void SuffixTree::print_tree() {
    dfs_traverse(root_node_);
    
    /* For Debug: display all nodes in tree
    cout<< all_nodes_.size() << endl;
    for (int i = 0; i < all_nodes_.size(); i++) {
	if (all_nodes_[i]->end != NULL) 
        for (int j = 0; j < MAX_CHAR; j++) {
	    if (all_nodes_[i]->children[j] != NULL) {
		cout << char(j) << " ";
	    }
	}
	cout << endl;
    }*/
}
