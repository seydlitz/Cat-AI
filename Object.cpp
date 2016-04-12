//contains the definitions for the Object class.

#include "Object.hpp"
#include "Settings.hpp"

unsigned int Object::GlobalId = 0;
std::list<Object> Object::Objects = std::list<Object>();

Object::Object()
{
	//Id = GlobalId++; //don't want to do this, methinks...we're not using this anyway, and if we eventually rely on ID iterators for tasks, we're iterating dead objects.
	Name = "NULL";
	Sentient = false;
}

Object::Object(const std::string name, const bool sentient, const std::string imgname)
{
	Id = GlobalId++;
	Name = name;
	Sentient = sentient;
	//make sure imgpath is valid...
	sf::Image * img = new sf::Image;
	if(!img->loadFromFile("./db/img/" + imgname))
	{
		std::cout << "error loading image file " << imgname << std::endl;
		ImgName = "NULL";
	}
	else {ImgName = imgname;}
	delete img;

	HasPrey = false;
	HasPredator = false;
}

bool Object::InitializeObjects(void)
{
	GlobalId = 0;

	//hardcoded values for now
	Object Corn("Corn", false, "Corn.bmp");
	Corn.SetPredator("Rooster");
	Object Hen("Rooster", true, "Rooster.bmp");
	Hen.SetPredator("Cat");
	Hen.SetPrey("Corn");
	Object Cat("Cat", true, "Cat.bmp");
	Cat.SetPrey("Rooster");
	Cat.SetPredator("Dog");
	Object Dog("Dog", true, "Dog.bmp");
	Dog.SetPrey("Cat");

	Objects.push_back(Hen);
	Objects.push_back(Corn);
	Objects.push_back(Cat);
	Objects.push_back(Dog);

	return true;
}

int Object::GetId(void) const
{return Id;}
std::string Object::GetName(void) const
{return Name;}
bool Object::IsSentient(void) const
{return Sentient;}
std::string Object::GetImageName(void) const
{return ImgName;}

sf::Vector2u Object::GetPosition(void) const
{return MyPosition;}

bool Object::GetHasPredator(void) const
{return HasPredator;}
bool Object::GetHasPrey(void) const
{return HasPrey;}
std::string Object::GetPredator(void) const
{return PredatorName;}
std::string Object::GetPrey(void) const
{return PreyName;}

void Object::SetPrey(const std::string name)
{
	HasPrey = true;
	PreyName = name;
}
void Object::SetPredator(const std::string name)
{
	HasPredator = true;
	PredatorName = name;
}
void Object::SetPosition(const sf::Vector2u & NewPosition)
{MyPosition = NewPosition;}

sf::Vector2u Object::MovePrey(const sf::Vector2u & preyPosition)
{
	//basic move - close the bigger of the gaps, x or y.
	int x = MyPosition.x - preyPosition.x;
	int y = MyPosition.y - preyPosition.y;
	sf::Vector2u MyNewPosition = MyPosition;
	//tie goes to the width
	if(abs(x) >= abs(y))
	{
		//deciding whether to move left or right
		if(x < 0 && (MyNewPosition.x + 1 < Settings::BoardSizeX))
			MyNewPosition = sf::Vector2u(MyPosition.x + 1, MyPosition.y);
		else if (MyPosition.x - 1 >= 0)
			MyNewPosition = sf::Vector2u(MyPosition.x - 1, MyPosition.y);
	}
	else //u/d
	{
		//deciding whether to move up or down
		if(y < 0 && (MyPosition.y + 1 < Settings::BoardSizeY))
			MyNewPosition = sf::Vector2u(MyPosition.x, MyPosition.y + 1);
		else if(MyPosition.y - 1 >= 0)
			MyNewPosition = sf::Vector2u(MyPosition.x, MyPosition.y - 1);
	}

	return MyNewPosition;
}

sf::Vector2u Object::MovePredator(const sf::Vector2u & predatorPosition)
{
	//basic move - widen the smaller of the gaps, x or y.
	int x = MyPosition.x - predatorPosition.x;
	int y = MyPosition.y - predatorPosition.y;
	sf::Vector2u MyNewPosition = MyPosition;
	//basic move - widen the smaller of the gaps, x or y.
	//tie goes to the width - l/r
	if(abs(x) >= abs(y))
	{
		//deciding whether to move left or right
		if(x > 0)
			MyNewPosition = sf::Vector2u(MyPosition.x + 1, MyPosition.y);
		else if (MyPosition.x - 1 >= 0)
			MyNewPosition = sf::Vector2u(MyPosition.x - 1, MyPosition.y);
	}
	else //u/d
	{
		//deciding whether to move up or down
		if(y > 0 && (MyPosition.y + 1 < Settings::BoardSizeY))
			MyNewPosition = sf::Vector2u(MyPosition.x, MyPosition.y + 1);
		else if (MyPosition.y - 1 >= 0)
			MyNewPosition = sf::Vector2u(MyPosition.x, MyPosition.y - 1);
	}

	return MyNewPosition;
}

sf::Vector2u Object::Move(const sf::Vector2u & preyPosition, const sf::Vector2u & predatorPosition)
{
	//if the prey is closer, close on prey. If predator is closer, run from predator.

	int PreyX = MyPosition.x - preyPosition.x;
	int PreyY = MyPosition.y - preyPosition.y;
	int PredX = MyPosition.x - predatorPosition.x;
	int PredY = MyPosition.y - predatorPosition.y;
	sf::Vector2u MyNewPosition = MyPosition;
	//if the predator is closer than the prey, evade the predator
	if((abs(PreyX) + abs(PreyY)) <= (abs(PredX) + abs(PredY)))
	{
		//basic move - close the bigger of the gaps, x or y.
		//tie goes to the width - l/r
		if(abs(PreyX) >= abs(PreyY))
		{
			//deciding whether to move left or right
			if(PreyX < 0 && (MyNewPosition.x + 1 < Settings::BoardSizeX))
				MyNewPosition = sf::Vector2u(MyPosition.x + 1, MyPosition.y);
			else if (MyPosition.x - 1 >= 0)
				MyNewPosition = sf::Vector2u(MyPosition.x - 1, MyPosition.y);
		}
		else //u/d
		{
			//deciding whether to move up or down
			if(PreyY < 0 && (MyPosition.y + 1 < Settings::BoardSizeY))
				MyNewPosition = sf::Vector2u(MyPosition.x, MyPosition.y + 1);
			else if(MyPosition.y - 1 >= 0)
				MyNewPosition = sf::Vector2u(MyPosition.x, MyPosition.y - 1);
		}
	}
	//else chase the prey
	else
	{
		//basic move - widen the smaller of the gaps, x or y.
		//tie goes to the width - l/r
		if(abs(PredX) >= abs(PredY))
		{
			//deciding whether to move left or right
			if(PredX > 0)
				MyNewPosition = sf::Vector2u(MyPosition.x + 1, MyPosition.y);
			else if (MyPosition.x - 1 >= 0)
				MyNewPosition = sf::Vector2u(MyPosition.x - 1, MyPosition.y);
		}
		else //u/d
		{
			//deciding whether to move up or down
			if(PredY > 0 && (MyPosition.y + 1 < Settings::BoardSizeY))
				MyNewPosition = sf::Vector2u(MyPosition.x, MyPosition.y + 1);
			else if (MyPosition.y - 1 >= 0)
				MyNewPosition = sf::Vector2u(MyPosition.x, MyPosition.y - 1);
		}
	}
	return MyNewPosition;
}