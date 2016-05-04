//contains the Board class definitions

#include "Board.hpp"
#include "Settings.hpp"

bool Board::AnyBoardExists = false;
Board Board::GameBoard = Board();

Board::Board(void)
{
	SizeX = 0;
	SizeY = 0;
}

Board::Board(unsigned int sizeX, unsigned int sizeY)
{
	SizeX = sizeX;
	SizeY = sizeY;
	Tile::InitializeTiles(PlayingBoard, SizeX, SizeY);
}

bool Board::InitializeBoard(void)
{
	//create board
	if(!AnyBoardExists)
	{
		GameBoard = Board(Settings::BoardSizeX, Settings::BoardSizeY);
		AnyBoardExists = true;
	}
	else return false;

	//place objects
	for(auto pObject = Object::Objects.begin();pObject != Object::Objects.end();pObject++)
	{
		int RandX = rand() % GameBoard.SizeX + 1;
		int RandY = rand() % GameBoard.SizeY + 1;
		for(auto pTile = GameBoard.PlayingBoard.begin();pTile != GameBoard.PlayingBoard.end();pTile++)
		{
			if(pTile->GetPosition().x == RandX && pTile->GetPosition().y == RandY)
			{
				pTile->AddObject(&*pObject);
			}
		}
	}

	//set timer...
	GameBoard.Timer = GameBoard.MyClock.getElapsedTime();

	return true;
}

bool Board::ProcessTick(void)
{
	//more than 1 second has elapsed.
	if(GameBoard.MyClock.getElapsedTime().asMilliseconds() >= GameBoard.Timer.asMilliseconds() + 1000)
	{
		//go through each object, assemble the location of their prey/predators
		for(auto pObject = Object::Objects.begin();pObject != Object::Objects.end();pObject++)
		{
			//but not if they're inanimate
			if(pObject->IsSentient())
			{
				bool CannotMove = false;
				sf::Vector2u PredatorPosition;
				sf::Vector2u PreyPosition;
				if(pObject->GetHasPredator())
				{
					for(auto pObject2 = Object::Objects.begin();pObject2 != Object::Objects.end();pObject2++)
					{
						if(pObject2->GetName() == pObject->GetPredator())
							PredatorPosition = pObject2->GetPosition();
					}
				}
				if(pObject->GetHasPrey())
				{
					for(auto pObject2 = Object::Objects.begin();pObject2 != Object::Objects.end();pObject2++)
					{
						if(pObject2->GetName() == pObject->GetPrey())
							PreyPosition = pObject2->GetPosition();
					}
				}

				//save old and new locations (so we can update the tiles)
				sf::Vector2u OldPosition = pObject->GetPosition();
				sf::Vector2u NewPosition;
				//pass off locations to let the object AI move, and get new position.
				if(!pObject->GetHasPrey())
				{
					NewPosition = pObject->MovePredator(PredatorPosition);
				}
				else if (!pObject->GetHasPredator())
				{
					NewPosition = pObject->MovePrey(PreyPosition);
				}
				else
				{
					NewPosition = pObject->Move(PreyPosition, PredatorPosition);
				}

				//now cycle through tiles and update old tile as empty and new tile as occupied
				for(auto pTile = GameBoard.PlayingBoard.begin();pTile != GameBoard.PlayingBoard.end();pTile++)
				{
					if(pTile->GetPosition() == OldPosition)
					{
						pTile->RemoveObject();
					}
					if(pTile->GetPosition() == NewPosition)
					{
						//checking to see if tile is already occupied, then... 

						//...if occupied, check...
						if(!pTile->AddObject(&*pObject))
						{
							//...if the occupied is prey...
							if(pTile->GetObject()->GetName() == pObject->GetPrey())
							{
								std::cout << pObject->GetName() << " has captured the " << pTile->GetObject()->GetName() << "!\n";
								std::cout << "Game Over!";
								return false;
							}
							//...or else stay in old position
							else
							{CannotMove = true;}
						}
					}
				}

				//running a second time if CannotMove == true, to reset piece to original square.
				if(CannotMove)
				{
					for(auto pTile = GameBoard.PlayingBoard.begin();pTile != GameBoard.PlayingBoard.end();pTile++)
					{
						if(pTile->GetPosition() == OldPosition)
						{
							pTile->AddObject(&*pObject);
						}
					}
				}
			}
		}

		Timer = GameBoard.MyClock.getElapsedTime();
		std::cout << "Tick...\n";
		return true;
	}

}

void Board::DrawBoard(sf::RenderWindow & Window) const
{

	//draw lines at far left and top (bottom and right are done by border tiles)
	sf::VertexArray XLine(sf::PrimitiveType::Lines, 2);
	XLine[0].position = sf::Vector2f(0, 0);
	XLine[0].color = sf::Color::Red;
	XLine[1].position = sf::Vector2f(0 + Settings::BoardSizeX * 129, 0);
	XLine[1].color = sf::Color::Red;
	sf::VertexArray YLine(sf::PrimitiveType::Lines, 2);
	YLine[0].position = sf::Vector2f(0, 0);
	YLine[0].color = sf::Color::Red;
	YLine[1].position = sf::Vector2f(0, 0 + Settings::BoardSizeY * 129);
	YLine[1].color = sf::Color::Red;
	Window.draw(XLine);
	Window.draw(YLine);
	for(auto pTile = PlayingBoard.begin();pTile != PlayingBoard.end();pTile++)
	{
		pTile->DrawTile(Window);
	}
}
