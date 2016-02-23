cmake_minimum_required(VERSION 3.0)
project ("LeetCodePlayground")

if(MSVC)
else()
	SET(CMAKE_CXX_FLAGS "-std=c++11")
endif(MSVC)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:20971520")

add_executable(runLeetCode 	
	Solution.h
	LeetCodeSolutions.cpp
	MaxDepth.h
	BuyStock.h
	SearchInsertPosition.h
	PascalTree.h
	ReverseInteger.h
	IsSameTree.h
	SingleNumber.h
	AddTwoNumbers.h
	Sudoku.h
	LongestParenthese.h
    MissingNumber.h
    UniqueBST.h
    ArrayToBST.h
    FindMinInRotateSortedArray.h
    RotateImage.h
    UniquePaths.h
    Permutation.h
    NextRightNode.h
	RegexMatch.h
	GrayCode.h
	SampleHeader.h
	MaxXor.h
	SwapNodes.h
	HuffmanDecode.h
	SimilarPair.h
	TwoEqualSubArrays.h
	MaxSumModuleSubarray.h
	SumMinInterval.h
	ScalarProduct.h
	TwoRobots.h
	FixTheCircle.h
	InsertSort.h
	CountSort.h
	ExtraLongFactorials.h
	QuickSort.h
	MatrixRotation.h
	SearchGrid.h
	TimeConversion.h
	KthSmallest.h
)

install(TARGETS runLeetCode DESTINATION bin)
