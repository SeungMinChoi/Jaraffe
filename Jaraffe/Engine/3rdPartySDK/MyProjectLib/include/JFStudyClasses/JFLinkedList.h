#pragma once

namespace JF
{
	namespace JFStudy
	{
		template<typename TData>
		struct DLLNode
		{
			TData pData;
			DLLNode* pPrevNode = nullptr;
			DLLNode* pNextNode = nullptr;
		};

		template<typename TData>
		class JFLinkedList
		{
		private:
			DLLNode<TData>* CreateNode(TData p_Data);
			void Destroy(DLLNode<TData>* p_Node);

		public:
			void Push_Front(TData p_Data);
			void Push_Back(TData p_Data);
			void Remove(DLLNode<TData>* p_Node);

			int GetCount();
			DLLNode<TData>* BeginNode();

		private:
			DLLNode<TData>* m_pHead = nullptr;
			DLLNode<TData>* m_pTail = nullptr;
		};

		class Iterator
		{
			// 이후 심심할때 구현해보자.
		};

		template<typename TData>
		DLLNode<TData>* JF::JFStudy::JFLinkedList<TData>::CreateNode(TData p_Data)
		{
			DLLNode<TData>* newNode = (DLLNode<TData>*)malloc(sizeof(DLLNode<TData>));
			newNode->pData = p_Data;
			newNode->pNextNode = nullptr;
			newNode->pPrevNode = nullptr;

			return newNode;
		};

		template<typename TData>
		void JF::JFStudy::JFLinkedList<TData>::Destroy(DLLNode<TData>* p_Node)
		{
			free(p_Node);
		}

		template<typename TData>
		void JF::JFStudy::JFLinkedList<TData>::Push_Front(TData p_Data)
		{
			if (m_pHead == nullptr && m_pTail == nullptr)
			{
				m_pHead = CreateNode(p_Data);
				m_pTail = m_pHead;
			}
			else
			{
				if (m_pHead->pNextNode != nullptr)
					m_pHead->pNextNode = CreateNode(p_Data);

				if (m_pHead == m_pTail)
					m_pTail = m_pHead->pNextNode;
			}
		}

		template<typename TData>
		void JF::JFStudy::JFLinkedList<TData>::Push_Back(TData p_Data)
		{
			if (m_pHead == nullptr && m_pTail == nullptr)
			{
				m_pHead = CreateNode(p_Data);
				m_pTail = m_pHead;
			}
			else
			{
				m_pTail->pNextNode = CreateNode(p_Data);
				m_pTail->pNextNode->pPrevNode = m_pTail;
				m_pTail = m_pTail->pNextNode;
			}
		}

		template<typename TData>
		void JF::JFStudy::JFLinkedList<TData>::Remove(DLLNode<TData>* p_Node)
		{
			DLLNode<TData>* prevNode = p_Node->pPrevNode;
			DLLNode<TData>* nextNode = p_Node->pNextNode;

			if (prevNode == nullptr)
				m_pHead = nextNode;
			else
				prevNode->pNextNode = nextNode;

			if (nextNode == nullptr)
				m_pTail = prevNode;
			else
				nextNode->pPrevNode = prevNode;

			Destroy(p_Node);
		}

		template<typename TData>
		int JF::JFStudy::JFLinkedList<TData>::GetCount()
		{
			int nCount = 0;

			auto iterBegin = m_pHead;
			while (iterBegin != nullptr)
			{
				iterBegin = iterBegin->pNextNode;
				++nCount;
			}

			return nCount;
		}

		template<typename TData>
		DLLNode<TData>* JF::JFStudy::JFLinkedList<TData>::BeginNode()
		{
			return m_pHead;
		}
	}
}

