#pragma once

namespace JF
{
	namespace JFStudy
	{
		enum class RBTColor
		{
			RED,
			BLACK
		};

		template<typename TData>
		struct RBTNode
		{
		public:
			RBTNode<TData>* pParent;
			RBTNode<TData>* pLeft;
			RBTNode<TData>* pRight;

			RBTColor Color;

			TData Data;
		};

		template<typename TData>
		class RedBlackTree
		{
		public:
			RedBlackTree()
			{
				m_pNil = new RBTNode<TData>();
				m_pNil->Color = RBTColor::BLACK;
			}

		public:
			bool InsertNode(_In_ TData _data)
			{
				if (m_pRootNode == nullptr)
				{
					m_pRootNode = _CreateNode(_data);
					m_pRootNode->Color	= RBTColor::BLACK;
					m_pRootNode->pLeft	= m_pNil;
					m_pRootNode->pRight = m_pNil;
				}
				else
				{
					auto isFind = _SearchNode(m_pRootNode, _data);
					if (isFind != nullptr)
						return false;

					_InsertNode(&m_pRootNode, _CreateNode(_data));
				}

				return true;
			}

			bool RemoveNode(_In_ TData _data)
			{
				if (m_pRootNode == nullptr)
					return false;

				RBTNode<TData>* removeNode = _RemoveNode(&m_pRootNode, _data);
				if (removeNode == nullptr)
					return false;

				_DestroyNode(removeNode);

				return true;
			}

			void PrintTree(int _Depth, int _BlackCount)
			{
				_PrintTree(m_pRootNode, _Depth, _BlackCount);
			}

		private:
			RBTNode<TData>* _CreateNode(_In_ TData _NewData)
			{
				RBTNode<TData>* pNewNode = (RBTNode<TData>*)malloc(sizeof(RBTNode<TData>));
				pNewNode->pParent	= nullptr;
				pNewNode->pLeft		= nullptr;
				pNewNode->pRight	= nullptr;
				pNewNode->Data		= _NewData;
				pNewNode->Color		= RBTColor::BLACK;

				return pNewNode;
			}

			void _DestroyNode(_In_ RBTNode<TData>* _pNode)
			{
				free(_pNode);
			}

			void _DestroyTree(_In_ RBTNode<TData>* _pNode)
			{
				if (_pNode->pRight != m_pNil)
					_DestroyTree(_pNode->pRight);

				if (_pNode->pLeft != m_pNil)
					_DestroyTree(_pNode->pLeft);

				_pNode->pRight	= m_pNil;
				_pNode->pLeft	= m_pNil;

				_DestroyNode(_pNode);
			}

			RBTNode<TData>* _SearchNode(_In_ RBTNode<TData>* _pNode, _In_ TData _Target)
			{
				if (_pNode == m_pNil)
					return nullptr;

				if (_pNode->Data > _Target)
					return _SearchNode(_pNode->pLeft, _Target);
				else if (_pNode->Data < _Target)
					return _SearchNode(_pNode->pRight, _Target);
				else
					return _pNode;
			}

			RBTNode<TData>* _SearchMinNode(_In_ RBTNode<TData>* _pNode)
			{
				if (_pNode == m_pNil)
					return m_pNil;

				if (_pNode->pLeft == m_pNil)
					return _pNode;
				else
					return _SearchMinNode(_pNode->pLeft);
			}

			void _InsertNode(_Inout_ RBTNode<TData>** _ppNode, _In_ RBTNode<TData>* _NewNode)
			{
				_InsertNodeHelper(_ppNode, _NewNode);

				_NewNode->Color		= RBTColor::RED;
				_NewNode->pLeft		= m_pNil;
				_NewNode->pRight	= m_pNil;

				_RebuildAfterInsert(_ppNode, _NewNode);
			}

			void _InsertNodeHelper(_Inout_ RBTNode<TData>** _ppNode, _In_ RBTNode<TData>* _pNewNode)
			{
				if ((*_ppNode) == nullptr)
					(*_ppNode) = _pNewNode;

				if ((*_ppNode)->Data < _pNewNode->Data)
				{
					if ((*_ppNode)->pRight == m_pNil)
					{
						(*_ppNode)->pRight = _pNewNode;
						_pNewNode->pParent = (*_ppNode);
					}
					else
						_InsertNodeHelper(&(*_ppNode)->pRight, _pNewNode);
				}
				else if ((*_ppNode)->Data > _pNewNode->Data)
				{
					if ((*_ppNode)->pLeft == m_pNil)
					{
						(*_ppNode)->pLeft	= _pNewNode;
						_pNewNode->pParent	= (*_ppNode);
					}
					else
						_InsertNodeHelper(&(*_ppNode)->pLeft, _pNewNode);
				}
			}

			void _RotateRight(_Inout_ RBTNode<TData>** _ppRoot, _In_ RBTNode<TData>* _pParent)
			{
				RBTNode<TData>* pLeftChild = _pParent->pLeft;

				_pParent->pLeft = pLeftChild->pRight;

				if (pLeftChild->pRight != m_pNil)
					pLeftChild->pRight->pParent = _pParent;

				pLeftChild->pParent = _pParent->pParent;

				if (_pParent->pParent == nullptr)
					(*_ppRoot) = pLeftChild;
				else
				{
					if (_pParent == _pParent->pParent->pLeft)
						_pParent->pParent->pLeft = pLeftChild;
					else
						_pParent->pParent->pRight = pLeftChild;
				}

				pLeftChild->pRight	= _pParent;
				_pParent->pParent	= pLeftChild;
			}

			void _RotateLeft(_Inout_ RBTNode<TData>** _ppRoot, _In_ RBTNode<TData>* _pParent)
			{
				RBTNode<TData>* pRightChild = _pParent->pRight;

				_pParent->pRight = pRightChild->pLeft;

				if (pRightChild->pLeft != m_pNil)
					pRightChild->pLeft->pParent = _pParent;

				pRightChild->pParent = _pParent->pParent;

				if (_pParent->pParent == nullptr)
					(*_ppRoot) = pRightChild;
				else
				{
					if (_pParent == _pParent->pParent->pLeft)
						_pParent->pParent->pLeft = pRightChild;
					else
						_pParent->pParent->pRight = pRightChild;
				}

				pRightChild->pLeft	= _pParent;
				_pParent->pParent	= pRightChild;
			}

			void _RebuildAfterInsert(_Inout_ RBTNode<TData>** _ppRoot, _In_ RBTNode<TData>* _pNode)
			{
				while (_pNode != (*_ppRoot) && _pNode->pParent->Color == RBTColor::RED)
				{
					if (_pNode->pParent == _pNode->pParent->pParent->pLeft)
					{
						RBTNode<TData>* pUncle = _pNode->pParent->pParent->pRight;
						if (pUncle->Color == RBTColor::RED)
						{
							_pNode->pParent->Color			= RBTColor::BLACK;
							pUncle->Color					= RBTColor::BLACK;
							_pNode->pParent->pParent->Color = RBTColor::RED;

							_pNode = _pNode->pParent->pParent;
						}
						else
						{
							if (_pNode == _pNode->pParent->pRight)
							{
								_pNode = _pNode->pParent;
								_RotateLeft(_ppRoot, _pNode);
							}

							_pNode->pParent->Color			= RBTColor::BLACK;
							_pNode->pParent->pParent->Color = RBTColor::RED;

							_RotateRight(_ppRoot, _pNode->pParent->pParent);
						}
					}
					else
					{
						RBTNode<TData>* pUncle = _pNode->pParent->pParent->pLeft;
						if (pUncle->Color == RBTColor::RED)
						{
							_pNode->pParent->Color			= RBTColor::BLACK;
							pUncle->Color					= RBTColor::BLACK;
							_pNode->pParent->pParent->Color = RBTColor::RED;

							_pNode = _pNode->pParent->pParent;
						}
						else
						{
							if (_pNode == _pNode->pParent->pLeft)
							{
								_pNode = _pNode->pParent;
								_RotateRight(_ppRoot, _pNode);
							}

							_pNode->pParent->Color			= RBTColor::BLACK;
							_pNode->pParent->pParent->Color = RBTColor::RED;
							_RotateLeft(_ppRoot, _pNode->pParent->pParent);
						}
					}
				}

				(*_ppRoot)->Color = RBTColor::BLACK;
			}

			RBTNode<TData>* _RemoveNode(_Inout_ RBTNode<TData>** _ppRoot, _In_ TData _Data)
			{
				RBTNode<TData>* pRemoved	= nullptr;
				RBTNode<TData>* pSuccessor	= nullptr;
				RBTNode<TData>* pTarget		= _SearchNode( (*_ppRoot), _Data );

				if (pTarget == nullptr)
					return nullptr;

				if (pTarget->pLeft == m_pNil || pTarget->pRight == m_pNil)
					pRemoved = pTarget;
				else
				{
					pRemoved		= _SearchMinNode(pTarget->pRight);
					pTarget->Data	= pRemoved->Data;
				}

				if (pRemoved->pLeft != m_pNil)
					pSuccessor = pRemoved->pLeft;
				else
					pSuccessor = pRemoved->pRight;

				pSuccessor->pParent = pRemoved->pParent;

				if (pRemoved->pParent == nullptr)
					(*_ppRoot) = pSuccessor;
				else
				{
					if (pRemoved == pRemoved->pParent->pLeft)
						pRemoved->pParent->pLeft = pSuccessor;
					else
						pRemoved->pParent->pRight = pSuccessor;
				}

				if (pRemoved->Color == RBTColor::BLACK)
					_RebuildAfterRemove(_ppRoot, pSuccessor);

				return pRemoved;
			}

			void _RebuildAfterRemove(_Inout_ RBTNode<TData>** _ppRoot, _Inout_ RBTNode<TData>* _pSuccessor)
			{
				RBTNode<TData>* pSibling = nullptr;

				while (_pSuccessor->pParent != nullptr && _pSuccessor->Color == RBTColor::BLACK)
				{
					if (_pSuccessor == _pSuccessor->pParent->pLeft)
					{
						pSibling = _pSuccessor->pParent->pRight;

						if (pSibling->Color == RBTColor::RED)
						{
							pSibling->Color = RBTColor::BLACK;
							_pSuccessor->pParent->Color = RBTColor::RED;
							_RotateLeft(_ppRoot, _pSuccessor->pParent);
						}
						else
						{
							if (pSibling->pLeft->Color	== RBTColor::BLACK &&
								pSibling->pRight->Color == RBTColor::BLACK)
							{
								pSibling->Color = RBTColor::RED;
								_pSuccessor		= _pSuccessor->pParent;
							}
							else
							{
								if (pSibling->pLeft->Color == RBTColor::RED)
								{
									pSibling->pLeft->Color	= RBTColor::BLACK;
									pSibling->Color			= RBTColor::RED;

									_RotateRight(_ppRoot, pSibling);
									pSibling = _pSuccessor->pParent->pRight;
								}

								pSibling->Color				= _pSuccessor->pParent->Color;
								_pSuccessor->pParent->Color = RBTColor::BLACK;
								pSibling->pRight->Color		= RBTColor::BLACK;
								_RotateLeft(_ppRoot, _pSuccessor->pParent);
								_pSuccessor = (*_ppRoot);
							}
						}
					}
					else
					{
						pSibling = _pSuccessor->pParent->pLeft;

						if (pSibling->Color == RBTColor::RED)
						{
							pSibling->Color				= RBTColor::BLACK;
							_pSuccessor->pParent->Color = RBTColor::RED;
							_RotateRight(_ppRoot, _pSuccessor->pParent);
						}
						else
						{
							if (pSibling->pRight->Color == RBTColor::BLACK &&
								pSibling->pLeft->Color	== RBTColor::BLACK)
							{
								pSibling->Color = RBTColor::RED;
								_pSuccessor		= _pSuccessor->pParent;
							}
							else
							{
								if (pSibling->pRight->Color == RBTColor::RED)
								{
									pSibling->pRight->Color = RBTColor::BLACK;
									pSibling->Color			= RBTColor::RED;

									_RotateLeft(_ppRoot, pSibling);
									pSibling = _pSuccessor->pParent->pLeft;
								}

								pSibling->Color				= _pSuccessor->pParent->Color;
								_pSuccessor->pParent->Color = RBTColor::BLACK;
								pSibling->pLeft->Color		= RBTColor::BLACK;

								_RotateRight(_ppRoot, _pSuccessor->pParent);
								_pSuccessor = (*_ppRoot);
							}
						}
					}
				}

				_pSuccessor->Color = RBTColor::BLACK;
			}

			void _PrintTree(_In_ RBTNode<TData>* _pNode, _In_ int _nDepth, _In_ int _nBlackCount)
			{
				int i	= 0;
				int v	= -1;
				char c	= 'X';
				char cnt[100];

				if (_pNode == nullptr || _pNode == m_pNil)
					return;

				if (_pNode->Color == RBTColor::BLACK)
					++_nBlackCount;

				if (_pNode->pParent != nullptr)
				{
					v = _pNode->pParent->Data;

					if (_pNode->pParent->pLeft == _pNode)
						c = 'L';
					else
						c = 'R';
				}

				if (_pNode->pLeft == m_pNil && _pNode->pRight == m_pNil)
					sprintf_s(cnt, "----------- %d", _nBlackCount);
				else
					sprintf_s(cnt ,"");

				for (i = 0; i < _nDepth; ++i)
					printf("  ");

				printf("%d %s [%c,%d] %s\n", _pNode->Data, (_pNode->Color == RBTColor::RED) ? "RED" : "BLACK", c, v, cnt);

				_PrintTree(_pNode->pLeft, _nDepth + 1, _nBlackCount);
				_PrintTree(_pNode->pRight, _nDepth + 1, _nBlackCount);
			}

		private:
			RBTNode<TData>* m_pRootNode = nullptr;
			RBTNode<TData>* m_pNil		= nullptr;
		};
	}
}