#pragma once

namespace JF
{
	namespace JFStudy
	{
		template<typename TValue>
		struct JFDighitsFoldingNode
		{
			char* Key;
			TValue Value;
		};

		template<typename TValue>
		class JFDighitsFolding
		{
		public:
			JFDighitsFolding(_In_ int _nTableSize)
			{
				m_pTable = (JFDighitsFoldingNode<TValue>*)malloc(sizeof(JFDighitsFoldingNode<TValue>) * _nTableSize);
				m_nTableSize = _nTableSize;
			}

		public:
			void Insert(_In_ char* _nKey, _In_ int _nKeyLength, _In_ TValue _Value)
			{
				int nindex = DighitsFoldingHash(_nKey, _nKeyLength);

				m_pTable[nindex].Key = _nKey;
				m_pTable[nindex].Value = _Value;
			}

			TValue* GetData(_In_ char* _nKey, _In_ int _nKeyLength)
			{
				int nindex = DighitsFoldingHash(_nKey, _nKeyLength);

				return &m_pTable[nindex].Value;
			}

		private:
			int DighitsFoldingHash(_In_ char* _nKey, _In_ int _nKeyLength)
			{
				int nHashValue = 0;

				for (int i = 0; i < _nKeyLength; ++i)
					nHashValue = (nHashValue << 3) + _nKey[i];

				return nHashValue % m_nTableSize;
			}

		private:
			int								m_nTableSize;
			JFDighitsFoldingNode<TValue>*	m_pTable;
		};
	}
}