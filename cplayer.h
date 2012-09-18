#ifndef _REVERSI_CPLAYER_H_
#define _REVERSI_CPLAYER_H_

#include "cdeadline.h"
#include "cmove.h"
#include "cboard.h"
#include <vector>
#include <array>

namespace reversi {

class Node{
	public:
		int moveId;
		int oppMoves;
		int playerMoves;
		int adjacentBlank;
		int totalValue;
		int positionValue;
		bool evaluated;

		Node() : moveId(0), oppMoves(0), playerMoves(0), adjacentBlank(0), totalValue(0), positionValue(0), evaluated(false){}
		int moveDifference() const { return playerMoves - oppMoves; }
		void calculateTotalValue()
		{
			totalValue = moveDifference() + positionValue - adjacentBlank/2;
		}
		bool operator<(const Node & other) const
		{
			if(totalValue < other.totalValue)
			{
				return true;
			}
			else
			{
				return false;
			} 
		}
};

class CPlayer
{
public:
	///constructor
	///Shouldn't do much. Any expensive initialization should be in 
	///Initialize
	CPlayer();

	///perform initialization of the player

	///\param pFirst true if we will move first, false otherwise
	///\param pDue time before which we must have returned. To check how
	///much time we have left you can use \p pDue.TimeUntil(), which returns
	///the remaining time in milliseconds.
	///That's the only safe way to use the pDue parameter.
	void Initialize(bool pFirst,const CDeadline &pDue);

	///perform a move

	///\param pBoard the current state of the board
	///\param pDue time before which we must have returned. To check how
	///much time we have left you can use \p pDue.TimeUntil(), which returns
	///the remaining time in milliseconds.
	///That's the only safe way to use the pDue parameter.
	///\return the move we make
	CMove Play(const CBoard &pBoard,const CDeadline &pDue);

	void accessDenied(const CBoard &pBoard, const std::vector<CMove> & moves, std::vector<Node> & nodes);

	void evaluateFunction(CBoard & board, Node & node);

	int checkEmptySquares(CBoard & board);

	void printValueMatrix() const;

	void updateValueMatrix(const CBoard & board);
private:
	std::array<std::array<int, 8>,8> valueMatrix;
};

/*namespace reversi*/ }

#endif
