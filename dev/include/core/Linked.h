#pragma once

namespace ldserver
{
	template <typename T>
	class Linked
	{
	public:
		typedef boost::shared_ptr<T>				LinkedNodePtr;

		Linked(){}
		virtual ~Linked(){}

		LinkedNodePtr								Next()
		{
			return m_next;
		}
		LinkedNodePtr								Prev()
		{
			return m_prev;
		}

		// insert after me
		static void									Insert(LinkedNodePtr pPos, LinkedNodePtr pNode)
		{
			if(pNode == NULL || pPos == NULL)
				return;

			pNode->Unlink();

			if(pPos->m_next != NULL)
			{
				pPos->m_next->m_prev = pNode;
			}

			pNode->m_next = pPos->m_next;

			pPos->m_next = pNode;
			pNode->m_prev = pPos;
		}

		void										Unlink()
		{
			if(m_next != NULL)
			{
				m_next->m_prev = m_prev;
			}
			if(m_prev != NULL)
			{
				m_prev->m_next = m_next;
			}

			m_next.reset();
			m_prev.reset();

		}

	private:

		LinkedNodePtr										m_prev;
		LinkedNodePtr										m_next;

	};
}
