#include <iostream>
#include <sstream>

#include "tree_info.h"
#include "tree_parser.h"

using namespace std;

tree_parser::tree_parser(string format) : _reader(-1), _trees(),  _trees_loaded(false) {
    _format = format;

    // Tell the reader not to throw an exception unless a fatal error occurs.
    _reader.SetWarningToErrorThreshold(NxsReader::FATAL_WARNING);
    
    // Tell the reader to allow augmented sequence symbols.
    NxsCharactersBlock *chars_block = _reader.GetCharactersBlockTemplate();
    NxsDataBlock *data_block = _reader.GetDataBlockTemplate();
    chars_block->SetAllowAugmentingOfSequenceSymbols(true);
    data_block->SetAllowAugmentingOfSequenceSymbols(true);
    
    // Allow implicit names in trees blocks.
    NxsTreesBlock *trees_block = _reader.GetTreesBlockTemplate();
    trees_block->SetAllowImplicitNames(true);
    
    // Allow unterminated blocks.
    NxsStoreTokensBlockReader *storer_block = _reader.GetUnknownBlockTemplate();
    storer_block->SetTolerateEOFInBlock(true);
}

tree_parser::~tree_parser() {
    _reader.DeleteBlocksFromFactories();
}

void tree_parser::parse(istream &in) {
    _reader.ReadStream(in, _format.c_str());
    _trees.clear();
    _trees_loaded = false;
}

vector<tree_info> tree_parser::get_trees() {
    if (!_trees_loaded) {
        load_all_trees();
        _trees_loaded = true;
    }
    return _trees;
}

void tree_parser::load_all_trees() {
    int num_taxa_blocks = _reader.GetNumTaxaBlocks();
    for (int i = 0; i < num_taxa_blocks; i++) {
        NxsTaxaBlock *taxa_block = _reader.GetTaxaBlock(i);
        load_trees_in_taxa_block(taxa_block);
    }
}

void tree_parser::load_trees_in_taxa_block(NxsTaxaBlock *taxa_block) {
    int num_trees_blocks = _reader.GetNumTreesBlocks(taxa_block);
    for (int i = 0; i < num_trees_blocks; i++) {
        NxsTreesBlock *trees_block = _reader.GetTreesBlock(taxa_block, i);
        load_trees_in_trees_block(taxa_block, trees_block);
    }
}

void tree_parser::load_trees_in_trees_block(NxsTaxaBlock *taxa_block, NxsTreesBlock *trees_block) {
    int num_trees = trees_block->GetNumTrees();
    for (int i = 0; i < num_trees; i++) {
        const NxsFullTreeDescription &desc = trees_block->GetFullTreeDescription(i);
        NxsSimpleTree tree(desc, 1, 1.0);
        ostringstream out;
        tree.WriteAsNewick(out, false, true, true, taxa_block);
        tree_info info(desc.GetName(), out.str());
        _trees.push_back(info);
    }
}
