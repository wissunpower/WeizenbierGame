#pragma once


template < typename T >
class Singleton
{
public:
	using PtrType = T*;

	static PtrType Get()
	{
		return Instance();
	}

	static void releaseInstance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static PtrType m_pInstance;

	static PtrType Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new T{};
		}

		return m_pInstance;
	}
};

template <typename T>
typename Singleton<T>::PtrType Singleton<T>::m_pInstance;


class ResponseIntervalCollector;

extern ResponseIntervalCollector* ResponseIntervalCollectorInstance;
