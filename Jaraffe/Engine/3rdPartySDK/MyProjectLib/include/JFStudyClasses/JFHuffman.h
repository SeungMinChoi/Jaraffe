#pragma once

#define MAX_CHAR	256
#define MAX_BIT		8

typedef unsigned int	UINT;
typedef unsigned char	UCHAR;

namespace JF
{
	namespace JFStudy
	{
		struct SymbolInfo
		{
			UCHAR	Symbol;
			int		Frequency;
		};

		struct HuffmanNode 
		{
			SymbolInfo		Data;
			HuffmanNode*	pLeft;
			HuffmanNode*	pRight;
		};

		struct BitBuffer
		{
			UCHAR*	pBuffer;
			UINT	nSize;
		};

		struct HuffmanCode 
		{
			UCHAR	Code[MAX_BIT];
			int		nSize;
		};

		HuffmanNode* CreateNode(SymbolInfo _NewData);
		void DestroyNode(HuffmanNode* _pNode);
		void DestroyTree(HuffmanNode* _pNode);

		void AddBit(BitBuffer* _pBuffer, char _Bit);
		void Encode(HuffmanNode** _ppTree, UCHAR* _pSource, BitBuffer* _pEncoded, HuffmanCode codeTable[MAX_CHAR]);
		void Decode(HuffmanNode* _ppTree, BitBuffer* _pEncoded, UCHAR* _pDecoded);

		void BuildPrefixTree(HuffmanNode** _ppTree, SymbolInfo _SymbolInfoTable[MAX_CHAR]);
		void BuildCodeTable(HuffmanNode* _pTree, HuffmanCode _CodeTable[MAX_CHAR], UCHAR _Code[MAX_BIT], int _nSize);
		void PrintBinary(BitBuffer* _pBuffer);
	}
}