#pragma once
#include "../Includes/LazyIncludes.h"
#include "../Memory/Handle.h"
namespace LE {
	template <class T>
	class LArray {

		Primitives::UInt32 m_size,m_numElements;
		Handle m_ptr;
	public:
		LArray<T>():m_size(0),m_numElements(0) {};
		LArray<T>(Primitives::UInt32 size) : m_size(size),m_numElements(0) {
			m_ptr = new Handle(sizeof(T)*m_size);
			memset(m_ptr.getAddress(), 0, sizeof(T)*m_size);
		}
		Primitives::UInt32 getSize() { return m_numElements; }
		void setSize(Primitives::UInt32 size) {
			m_size = size;
			m_ptr = Handle(sizeof(T)*size);
			memset(m_ptr.getAddress(), 0, size);
		}

		void addElement(const T &ele) {
			if (m_numElements <= m_size) {
				m_ptr.getObject<T>()[m_numElements] = ele;
				m_numElements++;
			}
			else
			{
				LogManager::getInstance()->get()->Log("Index Out of bounds!!");
				exit(0);
			}
		}
		void setElement(const T &ele, Primitives::UInt32 index) {
			if (index <= m_numElements) {
				m_ptr.getObject<T>()[index] = ele;
			}
			else {
				LogManager::getInstance()->get()->Log("Index Out of bounds!!");
				exit(0);
			}
		}
		T getElement(Primitives::UInt32 index) {
			if (index <= m_numElements)
				return m_ptr.getObject<T>()[index];
			else {
				LogManager::getInstance()->get()->Log("Index Out of bounds!!");
				exit(0);
			}
		}
	};

};