#pragma once

namespace JF
{
	namespace JFStudy
	{
		template<typename TKey, typename TValue>
		struct PQNode
		{
		public:
			PQNode(){}

			PQNode(_In_ TKey _key, _In_ TValue _value)
			{
				Key		= _key;
				Value	= _value;
			}

		public:
			TKey	Key;
			TValue	Value;
		};

		template<typename TKey, typename TValue>
		class PriorityQueue
		{
		public:
			PriorityQueue(_In_ int _ninitSize)
			{
				if (_ninitSize > 0)
				{
					m_pNodes	= (PQNode<TKey, TValue>*)malloc(sizeof(PQNode<TKey, TValue>) * _ninitSize);
					m_nCapactiy = _ninitSize;
					m_nUsedSize = 0;
				}
				else
				{
					m_pNodes	= nullptr;
					m_nCapactiy = 0;
					m_nUsedSize = 0;
				}
			}

			virtual ~PriorityQueue()
			{
				free(m_pNodes);
				m_pNodes = nullptr;
			}

		public:
			void Enqueue(_In_ PQNode<TKey, TValue> _NewNode)
			{
				int nCurrIndex		= m_nUsedSize;
				int nParentIndex	= _GetParentIndex(nCurrIndex);

				// if max Capactiy, m_nCapactiy * 2
				if (m_nUsedSize == m_nCapactiy)
				{
					if (m_nCapactiy <= 0)
						m_nCapactiy = 1;

					m_nCapactiy *= 2;
					m_pNodes	= (PQNode<TKey, TValue>*)realloc(m_pNodes, sizeof(PQNode<TKey, TValue>) * m_nCapactiy);
				}

				// Add NewNode 
				m_pNodes[nCurrIndex] = _NewNode;

				// Refresh
				while (m_nUsedSize > 0 && m_pNodes[nCurrIndex].Key < m_pNodes[nParentIndex].Key)
				{
					_SwapNodes(nCurrIndex, nParentIndex);

					nCurrIndex		= nParentIndex;
					nParentIndex	= _GetParentIndex(nCurrIndex);
				}

				// offset
				++m_nUsedSize;
			}

			void Dequeue()
			{
				int nDataSize		= sizeof(PQNode<TKey, TValue>);
				int nParentIndex	= 0;
				int nLeftIndex		= 0;
				int nRightIndex		= 0;

				// offset
				--m_nUsedSize;

				_SwapNodes(0, m_nUsedSize);

				// Get Index ( LeftChild + 1 == RightChild )
				nLeftIndex	= _GetLeftChild(0);
				nRightIndex = nLeftIndex + 1;

				while (true)
				{
					int nSelectedChild = 0;

					if(nLeftIndex >= m_nUsedSize)
						break;

					if (nRightIndex >= m_nUsedSize)
					{
						nSelectedChild = nLeftIndex;
					}
					else
					{
						if (m_pNodes[nLeftIndex].Key > m_pNodes[nRightIndex].Key)
							nSelectedChild = nRightIndex;
						else
							nSelectedChild = nLeftIndex;
					}

					if (m_pNodes[nSelectedChild].Key < m_pNodes[nParentIndex].Key)
					{
						_SwapNodes(nParentIndex, nSelectedChild);
						nParentIndex = nSelectedChild;
					}
					else
						break;

					nLeftIndex	= _GetLeftChild(nParentIndex);
					nRightIndex = nLeftIndex + 1;
				}

				if (m_nUsedSize < (m_nCapactiy / 2))
				{
					m_nCapactiy /= 2;
					m_pNodes	= (PQNode<TKey, TValue>*)realloc(m_pNodes, sizeof(PQNode<TKey, TValue>) * m_nCapactiy);
				}
			}

			PQNode<TKey, TValue>* GetMinData()
			{
				if (m_nUsedSize > 0)
					return &m_pNodes[0];
				else
					return nullptr;
			}

			int GetUsedSize()
			{
				return m_nUsedSize;
			}

		private:
			PQNode<TKey, TValue>* _CreateHeap(_In_ PQNode<TKey, TValue> _newData)
			{
				PQNode<TKey, TValue>* pNewNode = new PQNode<TKey, TValue>();
				pNewNode = _newData;

				return pNewNode;
			}

			void _DestroyNodes()
			{
				delete pNewNode;
				pNewNode = nullptr;
			}

			void _SwapNodes(_In_ int _nIndex1, _In_ int _nIndex2)
			{
				int nCopySize = sizeof(PQNode<TKey, TValue>);
				PQNode<TKey, TValue>* pTemp = (PQNode<TKey, TValue>*)malloc(nCopySize);

				memcpy(pTemp,				&m_pNodes[_nIndex1],	nCopySize);
				memcpy(&m_pNodes[_nIndex1], &m_pNodes[_nIndex2],	nCopySize);
				memcpy(&m_pNodes[_nIndex2], pTemp,					nCopySize);

				free(pTemp);
			}

			int _GetParentIndex(_In_ int _nIndex)
			{
				return (int)((_nIndex - 1) / 2);
			}

			int _GetLeftChild(_In_ int _nIndex)
			{
				return (2 * _nIndex) + 1;
			}

			int _GetRightChild(_In_ int _nIndex)
			{
				return (2 * _nIndex) + 2;
			}

		private:
			PQNode<TKey, TValue>* m_pNodes;
			int m_nCapactiy;
			int m_nUsedSize;
		};
	}
}