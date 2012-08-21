/* 
 * File:   tree_parser.h
 * Author: Dennis Roberts
 *
 * Header file for the tree parser class.
 */

#ifndef TREE_PARSER_H
#define	TREE_PARSER_H

#include <string>
#include <vector>

#include "ncl/nxsmultiformat.h"
#include "ncl/nxstreesblock.h"

#include "tree_info.h"

using namespace std;

/**
 * A parser that attempts to extract trees from a file in a single format.
 */
class tree_parser {
public:

    /**
     * @param format the expected tree file format.
     */
    tree_parser(string format);

    /**
     * Needed to call the NCL cleanup methods.
     */
    ~tree_parser();

    /**
     * Attempts to parse the contents of a tree file.
     * 
     * @param in the input stream to read the tree file from.
     */
    void parse(istream &in);

    /**
     * Gets the list of trees were extracted from the tree file.
     * 
     * @return the list of trees.
     */
    vector<tree_info> get_trees();

private:
    MultiFormatReader _reader; /// Reads and parses the file contents.
    string _format; /// The expected tree file format.
    vector<tree_info> _trees; /// the list of trees in the file.

    /**
     * Loads all of the trees from the parsed file.
     */
    void load_all_trees();

    /**
     * Loads all of the trees from a single taxa block in a parsed file.
     * 
     * @param taxa_block the current taxa block.
     */
    void load_trees_in_taxa_block(NxsTaxaBlock *taxa_block);

    /**
     * Loads all of the trees from a single trees block in a parsed file.
     * 
     * @param taxa_block the current taxa block.
     * @param trees_block the current trees block.
     */
    void load_trees_in_trees_block(NxsTaxaBlock *taxa_block, NxsTreesBlock *trees_block);
};


#endif	/* TREE_PARSER_H */

