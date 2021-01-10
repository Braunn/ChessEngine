#pragma once
#include <tuple>
#include "Position.h"

class SearchNode
{
public:

	SearchNode(SearchNode*, Move);
	
	bool checkCapturePromotionCastle();// how to handle this??
	
	Move getMove();
	SearchNode* getParent();
	pair<SearchNode**, int> getChildren();

	int depth;

	SearchNode* parent;
	SearchNode** children;
	int numOfChildren;

	Move move;

	void makeChildren(Position);

};

