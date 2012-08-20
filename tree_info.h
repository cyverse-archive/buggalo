/* 
 * File:   tree_info.h
 * Author: Dennis Roberts
 *
 * Header file for the tree information class.
 */

#ifndef TREE_INFO_H
#define	TREE_INFO_H

#include <string>

using namespace std;

/**
 * Stores only the information about trees that we care about, which is the name to assign to the tree along with
 * the actual Newick string.
 */
class tree_info {
public:

    /**
     * @param name the name of the tree.
     * @param newick the Newick string.
     */
    inline tree_info(string name, string newick) : _name(name), _newick(newick) {
    }

    /**
     * @return the name of the tree.
     */
    inline string get_name() {
        return _name;
    }

    /**
     * @return the Newick string.
     */
    inline string get_newick() {
        return _newick;
    }

private:
    string _name; /// The name of the tree.
    string _newick; /// The Newick string describing the tree.
};

#endif	/* TREE_INFO_H */
