#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */
class HCNodePtrComp {
public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        return *lhs < *rhs;
    }
};

/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class HCTree {
private:
    HCNode* root;
    vector<HCNode*> leaves;
    vector<string> encodings;

    /**
     * Recursive helper function for printTree
     */
    void printTreeHelper(HCNode * node, string indent = "") const;

    /**
     * Recursive helper for Destructor
     */
    void deleteTree(HCNode * subroot);

    /**
     * gets the binary encoding for for each symbol and 
     * loads then as char*'s in encodings 
     */
    void getEncodings();

    /**
     * gets the path up to the root recursivly and returns it as a 
     * string
     */
    string getPath(HCNode * leaf, HCNode * prev);

public:
    /** Constructor for HCTree
     */
    explicit HCTree() : root(0) {
        leaves = vector<HCNode*>(256, (HCNode*) 0);
        encodings = vector<string>(256, "");
    }

    /** Destructor for HCTree
     */
    ~HCTree();

    /** Use the Huffman algorithm to build a Huffman coding tree.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the tree,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void build(const vector<int>& freqs);

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encode(byte symbol, BitOutputStream& out) const;

    /** Write to the given ostream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encode(byte symbol, ostream& out) const;

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    byte decode(BitInputStream& in) const;

    /** Return the symbol coded in the next sequence of bits (represented as 
     *  ASCII text) from the istream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    byte decode(istream& in) const;

    /**
     * Print the contents of a tree
     */
    void printTree() const;
};

#endif // HCTREE_HPP
