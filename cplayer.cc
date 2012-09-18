#include "cplayer.h"
#include <cstdlib>
#include <algorithm>
#include <limits>

namespace reversi
{
	CPlayer::CPlayer(){}

	void CPlayer::Initialize(bool pFirst,const CDeadline &pDue)
	{
		srand(CDeadline::Now());
		
		std::for_each(valueMatrix.begin(), valueMatrix.end(), [](std::array<int, 8> & row){
			std::fill(row.begin(), row.end(), 0);
		});
		std::array<std::array<int, 8>,8> tmp = {
		10, -10, 0, 0, 0, 0, -10, 10,
		-10, -10, 0, 0, 0, 0, -10, -10,
		0, 0, 0, 0, 0, 0,  0,  0,
		0, 0, 0, 0, 0, 0,  0,  0,
		0, 0, 0, 0, 0, 0,  0,  0,
		0, 0, 0, 0, 0, 0,  0,  0,
		-10, -10, 0, 0, 0, 0, -10, -10,		
		10, -10, 0, 0, 0, 0, -10, 10,
		};
		valueMatrix = tmp;
		/*
		valueMatrix[0][0] = 10;
		valueMatrix[0][7] = 10;
		valueMatrix[7][7] = 10;
		valueMatrix[7][0] = 10;

		valueMatrix[1][1] = -2;
		valueMatrix[0][1] = -2;
		valueMatrix[1][0] = -2;

		valueMatrix[0][6] = -2;
		valueMatrix[1][6] = -2;
		valueMatrix[1][7] = -2;

		valueMatrix[6][6] = -2;
		valueMatrix[6][7] = -2;
		valueMatrix[7][6] = -2;

		valueMatrix[6][0] = -2;
		valueMatrix[6][1] = -2;
		valueMatrix[7][1] = -2;
		*/
		//printValueMatrix();
		//You can use this function to perform initialization tasks for your program. It is
		//perfectly ok to leave it as is
	}
    
	CMove CPlayer::Play(const CBoard &pBoard,const CDeadline &pDue)
	{
		//Use the commented version if your system supports ANSI color (linux does)
		//pBoard.PrintNoColor();
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
		//std::cout << "Start : " << pDue.Now() << std::endl;
		updateValueMatrix(pBoard);
		//printValueMatrix();

		std::vector<Node> nodes;
		nodes.resize(lMoves.size());
		for(size_t i = 0; i < nodes.size(); ++i)
		{
			nodes[i].moveId = i;
		}

		accessDenied(pBoard, lMoves, nodes);
		std::sort(nodes.begin(), nodes.end());
		//std::cout << "Stop : " << pDue.Now() << std::endl;

		//std::cout << "FINAL MOVE" << std::endl;
		//std::cout << "Player Moves : " << nodes[nodes.size() - 1].playerMoves << std::endl;
		//std::cout << "Opponent Moves : " << nodes[nodes.size() - 1].oppMoves << std::endl;
		//std::cout << "Blank : " << nodes[nodes.size() - 1].adjacentBlank << std::endl;
		//std::cout << "Total value : " << nodes[nodes.size() - 1].totalValue << std::endl;

		//return lMoves[rand()%lMoves.size()];
		return lMoves[nodes[nodes.size() - 1].moveId];
	}


	void CPlayer::accessDenied(const CBoard &pBoard, const std::vector<CMove> & moves, std::vector<Node> & nodes)
	{
		for(size_t i = 0; i < nodes.size(); ++i)
		{
			int row = moves[nodes[i].moveId].Row();
			int col = moves[nodes[i].moveId].Col();
			//std::cout << "Row : " << row << std::endl;
			//std::cout << "Col : " << col << std::endl;

			nodes[i].positionValue = valueMatrix[row][col];
			//std::cout << "Pos value : " << nodes[i].positionValue << std::endl;

			CBoard newBoard(pBoard, moves[nodes[i].moveId]);

			evaluateFunction(newBoard, nodes[i]);
			nodes[i].calculateTotalValue();
			//std::cout << "MOVE : " << i << std::endl;
			//std::cout << "Player Moves : " << nodes[i].playerMoves << std::endl;
			//std::cout << "Opponent Moves : " << nodes[i].oppMoves << std::endl;
			//std::cout << "Blank : " << nodes[i].adjacentBlank << std::endl;
			//std::cout << "Total : " << nodes[i].totalValue << std::endl;
		}
	}

	void CPlayer::evaluateFunction(CBoard & board, Node & node)
	{
		std::vector<CMove> oppMoves;
		std::vector<CMove> playerMoves;
		board.FindPossibleMoves(oppMoves,OTHER);
		board.FindPossibleMoves(playerMoves,OWN);
		node.oppMoves = oppMoves.size();
		node.playerMoves = playerMoves.size();
		node.adjacentBlank = checkEmptySquares(board);
		node.evaluated = true;
	}

	int CPlayer::checkEmptySquares(CBoard & board)
	{
		int count = 0;
		for(int i = 1; i < 7; ++i)
		{
			for(int j = 1; j < 7; ++j)
			{
				if(board.At(j, i) == 1)
				{
					if(board.At(j+1, i) == 0)
						++count; 
					if(board.At(j-1, i) == 0)
						++count;
					if(board.At(j, i+1) == 0)
						++count;
					if(board.At(j, i-1) == 0)
						++count;
				}
			}
		}
		return count;
	}

	void CPlayer::printValueMatrix() const
	{
		std::cout << "########" << std::endl;
		std::for_each(valueMatrix.begin(), valueMatrix.end(), [](const std::array<int, 8> & row){
			std::for_each(row.begin(), row.end(),[](const int & value){
				std::cout << value;
			});
			std::cout << std::endl;
		});
		std::cout << "########" << std::endl;
	}

	void CPlayer::updateValueMatrix(const CBoard & board)
	{
		if(board.At(0,0) == 1)
		{
			valueMatrix[0][1] = 5;	
			valueMatrix[1][0] = 5;
			valueMatrix[1][1] = 5;
		}
		if(board.At(0,7) == 1)
		{
			valueMatrix[0][6] = 5;	
			valueMatrix[1][6] = 5;
			valueMatrix[1][7] = 5;
		}			
		if(board.At(7,0) == 1)
		{
			valueMatrix[6][0] = 5;
			valueMatrix[6][1] = 5;	
			valueMatrix[7][1] = 5;
		}
		if(board.At(7,7) == 1)
		{
			valueMatrix[6][6] = 5;	
			valueMatrix[6][7] = 5;
			valueMatrix[7][6] = 5;
		}
	}
/*namespace reversi*/}
