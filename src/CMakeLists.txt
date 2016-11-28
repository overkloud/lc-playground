cmake_minimum_required(VERSION 3.0)
project ("LeetCodePlayground")

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:20971520")
else()
	SET(CMAKE_CXX_FLAGS "-std=c++14")
    ##SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl --stack 20971520")
endif(MSVC)

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
	Jeffreies.h
	strStr.h
	LongestCommonSubstring.h
	AQR.h
	LongestSubstringKRepeat.h
	LongestSubstringNoRepeat.h
	MinWindow.h
	WordLadder.h
	NQueen.h
	MinSizeSubarraySum.h
	LongestIncreasingSubSequence.h
	MinPathSum.h
	MiniParser.h
	Permutation2.h
	CourseSchedule2.h
	CourseSchedule.h
	UniquePath2.h
	UniqueBST2.h
	KPairsSmallestSum.h
	MinHeightTrees.h
	LowestCommonAncestor.h
	GroupAnagrams.h
	GasStation.h
	SearchRange.h
	HIndex.h
	SuperPow.h
	Triangle.h
	LargestDivisiveSubset.h
	AdditiveNumber.h
	LRUCache.h
	KCGTest.h
	MinAbsSum.h
	NumberSolitaire.h
	JumpGame.h
	DemandMoney.h
	LazySort.h
	FixedIncomeAlloc.h
	CurrencyArb.h
	MaxSubarray.h
	NoPrefixSet.h
	Trie.h
	MinWaitTime.h
	FindMedian.h
	QHeap1.h
	LongestChain.h
	FriendCircle.h
	Cipher.h
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

add_subdirectory(test)