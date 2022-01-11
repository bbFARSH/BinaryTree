#include <iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;
#define tab "\t"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pleft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pleft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element() { cout << "EDestructor:\t" << this << endl; }
		friend class Tree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	~Tree() { cout << "TDestructor:\t" << this << endl; }
	void insert(int Data) { insert(Data, this->Root); }
	int minValue()const { return minValue(this->Root); }
	int maxValue()const { return maxValue(this->Root); }
	int Count()const { return Count(this->Root); }
	int Sum()const { return Sum(this->Root); }
	double Avg()const { return Avg(this->Root); }
	void Clear(){ return Clear(this->Root);}
	void print()const { print(this->Root); cout << endl; }

private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) // Если есть мето для добавления элемента
				Root->pLeft = new Element(Data); // добавляем элемент прямо сюда
			else (insert(Data, Root->pLeft)); // в против случае идём налево и ищем место, куда добавить элемент
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	int minValue(Element* Root)const
	{
		if (Root->pLeft == nullptr)
			return Root->Data;
		return minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)
			return Root->Data;
		return maxValue(Root->pRight);*/
		//return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int Count(Element* Root)const
	{

		if (Root == NULL)
			return 0;

		else
		{
			return Count(Root->pLeft) + Count(Root->pRight) + 1;
		}

	}
	int Sum(Element* Root)const
	{
		if (Root == 0) return 0;
		return Root->Data + Sum(Root->pLeft) + Sum(Root->pRight);

	}
	double Avg(Element* Root)const
	{
		return (double)Sum(Root) / Count(Root);
	}
	void Clear(Element*& Root)
	{
		if (Root->pLeft != nullptr)
		{
			Clear(Root->pLeft);
		}
		if (Root->pRight != nullptr)
		{
			Clear(Root->pRight);
		}
		delete Root;
		Root = nullptr;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};
void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите колиечство элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве:  " << tree.Count() << endl;
	cout << "Сумма элементов в дереве: " << tree.Sum() << endl;
	cout << "Среднее арифметическое элементов в дереве:" << tree.Avg() << endl;
	tree.Clear();
	tree.print();
}