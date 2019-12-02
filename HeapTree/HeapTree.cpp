#include <iostream>
#include <vector>
using T = int;


class Predicate
{
public:
	bool operator()(const T& Lhs, const T& Rhs)
	{
		return Lhs <= Rhs;
	}
};

class HeapTree
{
public:
	using THeap = std::vector<T>;
	THeap Heap;
	Predicate Pred;
	HeapTree(int Size)
	{
		Heap.reserve(Size);
	}
	T Data = 0;
	int CurIndex = 0;

	inline int GetLeftChildIDX(int IDX)
	{
		return IDX * 2;
	}
	inline int GetRightChildIDX(int IDX)
	{
		return IDX * 2 + 1;
	}
	inline int GetParentIndex(int IDX)
	{
		if (IDX == NULL) return NULL;
		else
			return IDX / 2;
	}
	void Delete()
	{
		int RootIDX = 1;
		T Leaf = Heap[CurIndex];
		Heap[RootIDX] = Leaf;


		int PriorChildIdx = GetPriorChildIDX(RootIDX);
		std::swap(Heap[RootIDX], Heap[PriorChildIdx]);
	};

	int GetPriorChildIDX(int RootIDX)
	{
		int LeftChild = GetLeftChildIDX(RootIDX);
		int RightChild = GetRightChildIDX(RootIDX);

		if (Pred(LeftChild, RightChild))
		{
			return LeftChild;
		}
		else
			return RightChild;
	}

	void Push(T Data)
	{
		Heap[++CurIndex];
		if (CurIndex == 2) return;
		int ParentIndex = GetParentIndex(CurIndex);
		Update(CurIndex, ParentIndex);
	}
	void Update(int LhsIDX, int RhsIDX)
	{
		if (LhsIDX == 1 || RhsIDX == 1) return;

		if (Pred(Heap[LhsIDX], Heap[RhsIDX]))
		{
			std::swap(Heap[LhsIDX], Heap[RhsIDX]);
			LhsIDX = GetParentIndex(LhsIDX);
			RhsIDX = LhsIDX;
			Update(LhsIDX, RhsIDX);
		};
	}

};







