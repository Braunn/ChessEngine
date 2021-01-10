#include "SearchNode.h"
#include "Move.h"
#include <tuple>

using namespace std;

SearchNode::SearchNode(SearchNode* parent, Move move) {

}

//GETTERS
Move SearchNode::getMove() {
	return this->move;
}

SearchNode* SearchNode::getParent() {
	return this->parent;
}

pair<SearchNode**, int> SearchNode::getChildren() {
	return { this->children, this->numOfChildren };
}

void SearchNode::makeChildren(Position current) {
	/*
	Type moves =current.getLegalMoves();
	this->numOfChildren = moves.length;
	// add + make children
	*/
}