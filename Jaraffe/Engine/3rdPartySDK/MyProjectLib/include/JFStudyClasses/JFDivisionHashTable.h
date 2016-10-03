#pragma once

namespace JF
{
	namespace JFStudy
	{
		template<typename TValue>
		struct DHTNode
		{
			int Key;
			TValue Value;
		};

		template<typename TValue>
		class JFDHashTable
		{
		public:
			JFDHashTable(_In_ int _nTableSize)
			{
				m_pTable		= (DHTNode<TValue>*)malloc(sizeof(DHTNode<TValue>) * _nTableSize);
				m_nTableSize	= _nTableSize;
			}

		public:
			void Insert(_In_ int _nKey, _In_ TValue _Value)
			{
				int nindex = DivisionHash(_nKey);

				m_pTable[nindex].Key	= _nKey;
				m_pTable[nindex].Value	= _Value;
			}

			TValue* GetData(_In_ int _nKey)
			{
				int nindex = DivisionHash(_nKey);

				return &m_pTable[nindex].Value;
			}

		private:
			int DivisionHash(_In_ int _nKey)
			{
				return _nKey % m_nTableSize;
			}

		private:
			int					m_nTableSize;
			DHTNode<TValue>*	m_pTable;
		};
	}
}