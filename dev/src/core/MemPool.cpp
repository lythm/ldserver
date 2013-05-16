#include "core_pch.h"
#include "core/MemPool.h"

#ifndef CONTAINING_RECORD	
#define CONTAINING_RECORD(address, type, field) ((type *)( \
    (char *)(address) - \
    (ptrdiff_t)(&((type *)0)->field)))
#endif

namespace ldserver
{
	MemPool::MemPool(void)
	{
	}


	MemPool::~MemPool(void)
	{
		Release();
	}
	void MemPool::Update()
	{
		for(size_t i = 0; i < m_Slots.size(); ++i)
		{
			m_Slots[i].pSlot->Update();
		}
	}
	bool MemPool::slot_find(const Slot& s1, const Slot&s2)
	{
		return s1.blockBytes < s2.blockBytes;
	}
	void* MemPool::Alloc(uint64 bytes)
	{
		Slot s;
		s.blockBytes = bytes;

		std::vector<Slot>::iterator it = std::lower_bound(m_Slots.begin(), m_Slots.end(), s, slot_find);

		if(it == m_Slots.end())
		{
			return new char[bytes];
		}

		return it->pSlot->Alloc(bytes);
	}
	void MemPool::Free(void* mem)
	{
		if(mem == nullptr)
		{
			return;
		}
		MemSlot::_MemNode* pNode = CONTAINING_RECORD(mem, MemSlot::_MemNode, data);


		uint64 bytes = pNode->bytes;
		
		Slot s;
		s.blockBytes = bytes;

		std::vector<Slot>::iterator it = std::lower_bound(m_Slots.begin(), m_Slots.end(), s, slot_find);

		if(it == m_Slots.end())
		{
			delete mem;
			return;
		}

		it->pSlot->Free(mem);
	}

	bool MemPool::Initialize(int slotReservedCount, int slotShrinkStep)
	{
		uint64 v_list[] = 
		{
			8, 
			2 * 8,
			3 * 8,
			4 * 8,
			5 * 8,
			6 * 8,
			7 * 8,
			8 * 8,
			16 * 8,
			32 * 8,
			64 * 8,
			128 * 8,
			256 * 8,
			512 * 8,
			1024 * 8,
			2048 * 8,
			4096 * 8,
			8192 * 8,

		};

		for(size_t i = 0; i < sizeof(v_list) / sizeof(v_list[0]); ++i)
		{
			MemSlot* pSlot = new MemSlot;
			pSlot->Init(v_list[i], slotShrinkStep, slotReservedCount);

			Slot s;
			s.blockBytes = v_list[i];
			s.pSlot = pSlot;
			m_Slots.push_back(s);

		}

		return true;
	}
	
	void MemPool::Release()
	{
		for(size_t i = 0; i < m_Slots.size(); ++i)
		{
			Slot s = m_Slots[i];
			s.pSlot->Release();
			delete s.pSlot;
		}
		m_Slots.clear();
	}
}

namespace ldserver
{
	MemSlot::MemSlot()
	{
		m_blockBytes					= 0;
		m_totalBytes					= 0;

		m_blockCount					= 0;

		m_allocCount					= 0;
		m_freeCount						= 0;

		m_reservedBlockCount			= 0;
	}
	MemSlot::~MemSlot()
	{
	}

	bool MemSlot::Init(uint64 blockBytes, uint64 shrinkStep, uint64 reservedBlocks)
	{
		m_shrinkStep = shrinkStep;
		m_blockBytes = blockBytes;
		m_pHead = new _MemNode;

		m_pHead->next = NULL;

		ReserveBlocks(blockBytes, reservedBlocks);
		return true;
	}
	void MemSlot::Release()
	{
		_MemNode* pNode = m_pHead;

		while(pNode)
		{
			_MemNode* pTmp = pNode->next;
			delete pNode;
			pNode = pTmp;
		}
		
		m_pHead = NULL;
		m_blockBytes = 0;
		m_totalBytes = 0;
	}
	void* MemSlot::Alloc(uint64 bytes)
	{
		++m_allocCount;
		if(m_pHead->next == NULL)
		{
			_MemNode* pNode = (_MemNode*)new char[sizeof(_MemNode) + m_blockBytes];
			pNode->bytes = bytes;
			pNode->next = NULL;
			return pNode->data;
		}

		_MemNode* pNode = m_pHead->next;
		pNode->bytes = bytes;
		m_pHead->next = pNode->next;

		--m_blockCount;
		return pNode->data;
	}
	void MemSlot::Free(void* pData)
	{
		++m_freeCount;
		_MemNode* pNode = CONTAINING_RECORD(pData, _MemNode, data);

		pNode->next = m_pHead->next;
		m_pHead->next = pNode;

		++m_blockCount;
	}
	void MemSlot::Update()
	{
		if(m_blockCount - m_reservedBlockCount > m_shrinkStep)
		{
			Shrink(m_shrinkStep);
		}
	}
	void MemSlot::ReserveBlocks(uint64 blockBytes, uint64 blockCount)
	{
		std::vector<void*> list;

		for(uint64 i = 0; i < blockCount; ++i)
		{
			void* pBlock = Alloc(blockBytes);
			list.push_back(pBlock);

		}

		for(uint64 i = 0; i < blockCount; ++i)
		{
			void* pBlock = list[i];
			Free(pBlock);
		}
		list.clear();

		m_reservedBlockCount = blockCount;
	}
	void MemSlot::Shrink(uint64 count)
	{
		assert(m_blockCount - m_reservedBlockCount > count);

		for(int i = 0; i < count; ++i)
		{
			_MemNode* pNode = m_pHead;

			if(pNode == nullptr)
			{
				assert(0);
				return;
			}

			pNode = m_pHead;

			
			m_pHead = m_pHead->next;

			delete pNode;

			-- m_blockCount;

		}
	}
}
