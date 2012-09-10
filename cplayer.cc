#include "cplayer.h"
#include <cstdlib>
#include <algorithm>

namespace reversi
{

	CPlayer::CPlayer(){}

	void CPlayer::Initialize(bool pFirst,const CDeadline &pDue)
	{
		srand(CDeadline::Now());
		
		//You can use this function to perform initialization tasks for your program. It is
		//perfectly ok to leave it as is
	}
    
	CMove CPlayer::Play(const CBoard &pBoard,const CDeadline &pDue)
	{
		//Use the commented version if your system supports ANSI color (linux does)
		pBoard.PrintNoColor();
		//pBoard.Print();
    
		std::vector<CMove> lMoves;
		//this gets a list of our (OWN) possible moves
		pBoard.FindPossibleMoves(lMoves,OWN);
		
		///if the list of moves is empty, we must pass
		if(lMoves.empty()) return cPass;

		/*
		 * Here you should write your clever algorithms to get the best next move.
		 * This skeleton returns a random movement instead.
		 */
		int maxCount = 0;
		CMoce bestMove;
		std::for_each(lMoves.begin(), lMoves.end(), [](CMove & move)
		{
			int totalCount = 0;
			totalCount += CountEnemyDisksOnRow(move);
			//TODO: Count on col
			//TODO: Count on diagonal
			if(totalCount > maxCount)
			{
				maxCount = totalCount;
				bestMove = move;
			}
		};
    		//TODO: return bestMove;
		return lMoves[rand()%lMoves.size()];
	}

	int CPlayer::CountEnemyDisksOnRow(Move & move)
	{
		int rightCount = 0; 
		for(int i = move.Row(); i < pBoard.cSize; ++i)
		{
			if(pBoard.At(i, move.Col()) == 2)
			{
				++rightCount;
			}
			else if(pBoard.At(i, move.Col()) == 1)
			{
				break;
			}
			else if(pBoard.At(i, move.Col()) == 0)
			{
				rightCount = 0;
				break;
			}

			// Reset count if we don't reach our own disk on the right side this row
			if( i == (pBoard.cSize -1))
			{
				rightCount = 0;
				break;
			}
		}
		
		int leftCount = 0;
		for(int i = move.Row(); 0 =< i; --i)
		{
			if(pBoard.At(i, move.Col()) == 2)
			{
				++leftCount;
			}
			else if(pBoard.At(i, move.Col()) == 1)
			{
				break;
			}
			else if(pBoard.At(i, move.Col()) == 0)
			{
				leftCount = 0;
				break;
			}

			// Reset count if we don't reach our own disk on the left side of this row
			if( i == 0)
			{
				rightCount = 0;
				break;
			}
		}
		return leftCount + rightCount;
	}
/*namespace reversi*/}
