// SDL_project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SDL_project.h"
#include "MainGame.h"

class CListNode
{
public:
	CListNode(int Value) { m_Value = Value;	};
	// Get and set Next node
	CListNode* getNext() { return m_Next; }
	CListNode* setNext(CListNode* next) { return m_Next = next; }
	// Get and Set Previous node
	CListNode* getPrev() { return m_Prev; }
	CListNode* setPrev(CListNode* prev) { return m_Prev = prev; }

private:
	// Next node in list
	CListNode* m_Next = nullptr;
	// Previous node in list
	CListNode* m_Prev = nullptr;
	int m_Value;
};

class CLinkedList
{
public:
	CLinkedList() {};
	CListNode* AddNode(int Value);
	bool DeleteNode(CListNode* Node);

	int FindMatchingParenthesis(char* String, int Index);
private:
	// Start ptr of linked list
	CListNode* m_Start = nullptr;
	// End ptr of linked list
	CListNode* m_end = nullptr;

};

CListNode* CLinkedList::AddNode(int Value)
{
	CListNode* newNode = new CListNode(Value);

	// Create start and end of list
	if (m_Start == nullptr)
	{
		m_Start = newNode;
		m_end = newNode;
	}
	else
	{
		// Set previous node for the new node
		newNode->setPrev(m_end);
		// Set previous node's next node to this new one
		m_end->setNext(newNode);
		// Update end node
		m_end = newNode;
	}

	return newNode;
}

// Delete node
bool CLinkedList::DeleteNode(CListNode* Node)
{
	if (Node != nullptr)
	{
		// Link Previous and next nodes together
		CListNode* prev = Node->getPrev();
		CListNode* next = Node->getNext();
		prev->setNext(next);

		// Remove node
		delete Node;
		return true;
	}
	else
		return false;
}

int CLinkedList::FindMatchingParenthesis(char* String, int Index)
{
	std::string str = String;
	int result = -1;
	int totLeft = 0, totRight = 0;

	// Create map of ID and index
	std::map<int, int> LParenthesis, RParenthesis;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == *"(")
		{
			LParenthesis[totLeft] = i;
			totLeft++;
		}
		else if (str[i] == *")")
		{
			RParenthesis[totRight] = i;
			totRight++;
		}
	}

	// IF there are unequal amounts of left and right brackets
	if (LParenthesis.size() != LParenthesis.size())
	{
		return -1;
	}

	result = RParenthesis[Index];

	return result;

}

struct MyStruct_t
{
public:
	MyStruct_t::MyStruct_t() { vec.push_back("TEST"); };
	int test = 0;
	std::vector<std::string> vec;
private:
	bool var = false;
};

int Calculate(int* x, int& y, int z)
{
	(*x)++;
	z = *x + y;
	y += z;
	return y;
}

int FindItemInListRec(int* list, int value, int index = 0)
{
	int found = -1;
	if (value == list[index])
	{
		return list[value];
	}
	else
	{
		index++;
		FindItemInListRec(list, value, index);
	}
}

typedef int TLength;

class CPoint
{
public:
	TLength X() const { return m_X; }
	TLength Y() const { return m_Y; }

	CPoint(TLength x = 0, TLength y = 0) { m_X = x; m_Y = y; }
	TLength Distance(const CPoint& point) const;

private:
	TLength m_X;
	TLength m_Y;
};

TLength CPoint::Distance(const CPoint& point) const
{
	TLength dx = X() - point.X();
	TLength dy = Y() - point.Y();
	TLength dist = 0.0;

	dist = pow(dx, 2) + pow(dy, 2);
	dist = sqrt(dist);

	return dist;
}

std::pair<CPoint*,CPoint*> FindNearest(CPoint* pointsA[], CPoint* pointsB[])
{
	int lowest = 20;
	std::pair<CPoint*, CPoint*> result;

	// Loop throuh both arrays to calcualte the two closest points
	for (int i = 0; pointsA[i] != nullptr; i++)
	{
		for (int j = 0; pointsB[j] != nullptr; j++)
		{
			int dist = pointsA[i]->Distance(*pointsB[j]);
			std::cout << dist << std::endl;
			// Set lowest value if not set
			if (lowest == 0)
				lowest = dist;
			// Set the closest two points
			if (dist < lowest)
			{
				std::cout << "Lowest: " << dist << std::endl;
				lowest = dist;
				result.first = pointsA[i];
				result.second = pointsB[j];
			}
		}
	}

	return result;


	// Find the nearest pair of points from the two null terminated arrays of points.
}
int CountDigits(std::string Text)
{
	int Count = 0;
	std::string Digits("1234567890");
	for (int Index = 0; Index < Text.length(); Index++)
	{
		if (Digits.find(Text[Index]) != std::string::npos)
		{
			Count++;
		}
	}
	return Count;
}
int main(int argc, char* args[])
{

	CountDigits("asd819238asdf");
	int numbers[] = { 2, 2, 3, 5, 6, 8, 14, 16, 22, 22, 30, 36 };
	FindItemInListRec(numbers, 22);

	CPoint PointsA(10,10);
	CPoint PointsB(20, 0);
	CPoint* arra[11];
	CPoint* arrb[11];
	for (int i = 9; i >= 0; i--)
	{
		CPoint* point = new CPoint(i, i * -1);
		arra[i] = point;
	}
	arra[10] = nullptr;
	for (int i = 0; i < 10; i++)
	{
		CPoint* point = new CPoint(i* -1 , 10);
		arrb[i] = point;
	}
	arrb[10] = nullptr;
	FindNearest(arra, arrb);
	int dista = PointsA.Distance(PointsB);


	CLinkedList MyList;
	CListNode* NodeA = MyList.AddNode(1);
	CListNode* NodeB = MyList.AddNode(2);
	CListNode* NodeC = MyList.AddNode(3);

	MyList.DeleteNode(NodeB);


	char* str = "When opening a door (for some reason (it could be any (real or imaginary) reason)) hold tight.";
	MyList.FindMatchingParenthesis(str,1);


	MyStruct_t FirstInfo;
	MyStruct_t* SecondInfo;
	SecondInfo = &FirstInfo;

	int f = sizeof(FirstInfo);
	int s = sizeof(*SecondInfo);
	
	memset(SecondInfo, 0, sizeof(*SecondInfo));


	int ForegroundRed = 156;
	int ForegroundGreen = 32;
	int ForegroundBlue = 193;

	int dimFactor = 10;
	// add implementation here to manipulate foreground colour elements
	// to produce a colour that appears dimmed on the screen relative
	// to something drawn in the original colour.


	// Calulcate luminance
	///Max
	double max = std::max(std::max(ForegroundRed, ForegroundGreen), ForegroundBlue);
	///Min
	double min = std::min(std::min(ForegroundRed, ForegroundGreen), ForegroundBlue);
	double l = ((max + min) / 2.0);

	int x = 0;
	int y = 0;

	if (x++ && y++)
	{
		y += 2;
	}

	std::cout << x + y << std::endl;



	int a = 1;
	int b = 2;
	int c = 3;

	int d = Calculate(&a, b, c);

	std::cout << a + b + c + d << std::endl;

	struct Shape
	{
		void name()
		{
			std::cout << "SHAPE" << std::endl;
		}
		virtual ~Shape() {}
	};

	struct Rectangle : public Shape
	{
		virtual void name()
		{
			std::cout << "RECTANGLE" << std::endl;
		}
	};

	struct Square : public Rectangle
	{
		void name()
		{
			std::cout << "SQUARE" << std::endl;
		}
	};

	Shape* s1 = new Square;

	s1->name();
	((Rectangle*)s1)->name();
	((Square*)s1)->name();

	delete s1;


	MainGame game;
	game.run();
	while (game.needsRestart)
	{
		MainGame game;
		game.run();
	}
	
	return 0;

}

