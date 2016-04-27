/*
Abrahams, Thomas
CS A200
April 26, 2016

Lab #9 Comparing Sorting Algorithm

This code has been submitted to Professor Gabriela Ernsberger.
Use as a guide and remember to implement your own code.
Yes I will refactor later.
*/

/********************************************************************
Program tests number of comparisons performed
by Bubble sort (flagged version), Selection sort,
Insertion sort, and Merge Sort.

Testing can be performed on either a 6-length
array or a 1000-length random-numbers array.
********************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Declaration function bubbleSort
// Running time = O(n^2)
// Uses function swap
void bubbleSort(int a[], int & compBubble, int numberOfElements);


// Declaration function selectionSort
// Running time = O(n^2)
// Uses function swap
// Uses function minLocation
void selectionSort(int a[], int & compSelect, int numberOfElements);

// Declaration function minLocation
// Running time = O(n)
int minLocation(int a[],int beginIdx, int lastIdx, int & compSelect);

// Declaration function insertionSort
// Running time: O(n^2) 
void insertionSort(int a[], int& compInsert, int numberOfElements);

// Declaration function mergeSort
// Running time: O(n log n) => this includes the call to function merge
// Uses function merge
void mergeSort(int a[], int &compMerge, int numberOfElements);

// Declaration function merge
// Running time: O(n)
void merge(int a[], int* leftArray, int* rightArray, int leftMost, int rightMost, int &compMerge);

// Already implemented
void print(const int a[], int numOfElements);
void swap(int& n1, int& n2);
void testSmallArray(int a[], int numOfElements);  // testing cases
void testAllSmallArrays();
void testBigArray();

const int SMALL_CAP = 6;
const int BIG_CAP = 1000;

int main()
{
	testAllSmallArrays();

	testBigArray();

	cout << endl;
	system("Pause");
	return 0;
}

// Definition function bubbleSort
void bubbleSort(int a[], int & compBubble, int numberOfElements)
{
	bool swapFlag = true;

	for (int h = 1; (h <= numberOfElements) && swapFlag; h++)
	{
		swapFlag = false;
		for (int i = 0; i < numberOfElements - 1; i++)
		{
			compBubble++;
			if (a[i] > a[i + 1])
			{
				swapFlag = true;
				swap(a[i], a[i + 1]);
			}
		}
	}
}

// Definition function selectionSort
void selectionSort(int a[], int & compSelect, int numberOfElements)
{
	int temp = 0;
	int minIdx;
	for (int i = 0; i < numberOfElements - 1; i++)
	{
		minIdx = minLocation(a, i, numberOfElements, compSelect);
		swap(a[i], a[minIdx]);
	}

}

// Definition function minLocation
int minLocation(int a[], int beginIdx, int numberOfElements, int & compSelect)
{

	int minIdx = beginIdx;
	for (int j = beginIdx + 1; j < numberOfElements; j++)
	{
		compSelect++;
		if (a[j] < a[minIdx])
			minIdx = j;
	}
	return minIdx;
}

// Definition function insertionSort
void insertionSort(int a[], int& compInsert, int numberOfElements)
{
	int holder, idx;

	for (int i = 0; i < numberOfElements; i++)
	{
		compInsert++;
		idx = i;
		while (idx > 0 && a[idx] < a[idx - 1])
		{
			compInsert++;
			holder = a[idx];
			a[idx] = a[idx - 1];
			a[idx - 1] = holder;
			idx--;
		}
	}

}

// Definition function mergeSort
void mergeSort(int a[], int &compMerge, int numberOfElements)
{

	int middleIndex;

	if (numberOfElements >= 2)
	{
		//Find the middle Index
		middleIndex = (numberOfElements) / 2;

		int *leftArray = new int[middleIndex];
		int *rightArray = new int[numberOfElements - middleIndex];

		//For loop
		for (int i = 0; i < middleIndex; i++)
			leftArray[i] = a[i];
		for (int i = middleIndex; i < numberOfElements; i++)
			rightArray[i - middleIndex] = a[i];

		mergeSort(leftArray, compMerge, middleIndex);
		mergeSort(rightArray, compMerge, numberOfElements - middleIndex);
		//The values are re-merged.
		merge(a, leftArray, rightArray, middleIndex, numberOfElements - middleIndex, compMerge);

		//Memory clean up. This will fail depending on the array. Memory frees up, but it crashes at the delete function. It will run depending on the array.

		delete[] leftArray;
		leftArray = NULL;
		delete[] rightArray;
		rightArray = NULL;
	}

}

// Definition function merge
void merge(int a[], int* leftArray, int* rightArray, int leftMost, int rightMost, int &compMerge)
{
	//Starting for the indexes of the arrays, leftArray, rightArray, and merged array.
	int i = 0;
	int j = 0;
	int k = 0;
	//For the remerge
	//When both the lower index for the two arrays are less than the right most for the arrays.
	while (i < leftMost && j < rightMost)
	{
		compMerge++;
		if (leftArray[i] < rightArray[j])
			a[k++] = leftArray[i++];
		//Else increment j and k, and leave i for the next comparison
		else
			a[k++] = rightArray[j++];
	}
	while (i < leftMost)
	{
		compMerge++;
		a[k++] = leftArray[i++];
	}
	while (j < rightMost)
	{
		compMerge++;
		a[k++] = rightArray[j++];
	}


}

void print(const int a[], int numOfElements)
{
	for (int i = 0; i < numOfElements; ++i)
		cout << a[i] << " ";
}

void swap(int& n1, int& n2)
{
	int	temp = n1;
	n1 = n2;
	n2 = temp;
}

void testAllSmallArrays()
{
	int numOfElements = SMALL_CAP;

	int a1[] = { 5, 4, 3, 2, 1, 0 };
	testSmallArray(a1, numOfElements);

	int a2[] = { 0, 1, 2, 3, 4, 5 };
	testSmallArray(a2, numOfElements);

	int a3[] = { 3, 4, 5, 0, 1, 2 };
	testSmallArray(a3, numOfElements);

	int a4[] = { 2, 1, 0, 3, 4, 5 };
	testSmallArray(a4, numOfElements);

	int a5[] = { 0, 1, 2, 5, 4, 3 };
	testSmallArray(a5, numOfElements);
}

void testSmallArray(int a[], int numOfElements)
{
	cout << "Array is:\n\n";
	print(a, numOfElements);
	cout << endl;

	int aBubble[SMALL_CAP];
	int aSelection[SMALL_CAP];
	int aInsertion[SMALL_CAP];
	int aMerge[SMALL_CAP];

	//copy arrays
	for (int i = 0; i < numOfElements; ++i)
	{
		aBubble[i] = a[i];
		aSelection[i] = a[i];
		aInsertion[i] = a[i];
		aMerge[i] = a[i];
	}

	//TESTING BUBBLE SORT
	int compBubble = 0;
	bubbleSort(aBubble, compBubble, numOfElements);
	cout << "\nBubble sort:       ";
	print(aBubble, numOfElements);

	//TESTING SELECTION SORT
	int compSelection = 0;
	selectionSort(aSelection, compSelection, numOfElements);
	cout << "\nSelection sort is: ";
	print(aSelection, numOfElements); //Modified Main

	//TESTING INSERTION SORT
	int compInsertion = 0;
	insertionSort(aInsertion, compInsertion, numOfElements);
	cout << "\nInsertion Sort is: ";
	print(aInsertion, numOfElements);//Modified Main was printing a

	//TESTING MERGE SORT
	int compMergeSort = 0;
	mergeSort(aMerge, compMergeSort, numOfElements);
	cout << "\nMerge Sort is:     ";
	print(aMerge, numOfElements); //Modified Main was printing a

	cout << "\n\nResults: " << endl
		<< "    BUBBLE SORT    NUMBER OF COMPARISONS:   " << compBubble
		<< "\n    SELECTION SORT NUMBER OF COMPARISONS:   " << compSelection
		<< "\n    INSERTION SORT NUMBER OF COMPARISONS:   " << compInsertion
		<< "\n    MERGE SORT     NUMBER OF COMPARISONS:   " << compMergeSort
		<< endl;
	cout << "\n\n--------------------------------------------\n";
}

void bigArray(int a[], int& numOfElements)
{
	numOfElements = BIG_CAP;

	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < numOfElements; ++i)
		a[i] = 1 + rand() % (numOfElements * 10);
}

void testBigArray()
{
	int numOfElements = BIG_CAP;

	int a[BIG_CAP];

	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < numOfElements; ++i)
		a[i] = 1 + rand() % (numOfElements * 10);

	cout << "BIG ARRAY\n";
	//print(a, numOfElements);
	//cout << endl;

	//copy arrays to use with all functions
	int aBubble[BIG_CAP];
	int aSelection[BIG_CAP];
	int aInsertion[BIG_CAP];
	int aMerge[BIG_CAP];

	for (int i = 0; i < numOfElements; ++i)
	{
		aBubble[i] = a[i];
		aSelection[i] = a[i];
		aInsertion[i] = a[i];
		aMerge[i] = a[i];
	}

	////TESTING BUBBLE SORT
	int compBubble = 0;
	bubbleSort(aBubble, compBubble, numOfElements);
	//cout << "\nBubble sort:\n";
	//print(aBubble, numOfElements);

	//TESTING SELECTION SORT
	int compSelection = 0;
	selectionSort(aSelection, compSelection, numOfElements);
	//cout << "\nSelection sort is:\n";
	//print(aSelection, numOfElements);

	////TESTING INSERTION SORT
	int compInsertion = 0;
	insertionSort(aInsertion, compInsertion, numOfElements);
	//cout << "\nInsertion Sort is:\n";
	//print(aInsertion, numOfElements);

	////TESTING MERGE SORT
	int compMergeSort = 0;
	mergeSort(aMerge, compMergeSort, numOfElements);
	cout << "\nMerge Sort is:\n";
	print(aMerge, numOfElements);

	cout << "\nResults: " << endl
		<< "    BUBBLE SORT    NUMBER OF COMPARISONS:   " << compBubble
		<< "\n    SELECTION SORT NUMBER OF COMPARISONS:   " << compSelection
		<< "\n    INSERTION SORT NUMBER OF COMPARISONS:   " << compInsertion
		<< "\n    MERGE SORT     NUMBER OF COMPARISONS:   " << compMergeSort
		<< endl;
}

