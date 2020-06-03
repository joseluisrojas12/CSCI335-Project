#pragma once

#include<cstdint>

uint64_t MurmurHash64(const void * key, int len, unsigned int seed);
unsigned int MurmurHash32(const void * key, int len, unsigned int seed);

// Hash functor for MurmurHash64 hashing
template<class T>
struct MurmurHasher64
{
	MurmurHasher64(unsigned int seed)
		:_seed(seed)
	{}

	MurmurHasher64()
		:_seed(0)
	{}

	uint64_t operator()(T& key)
	{
		return MurmurHash64(reinterpret_cast<void*>(&key), sizeof(key), _seed);
	}

private:
	unsigned int _seed;
};

// Hash functor for MurmurHash32 hashing
template<class T>
struct MurmurHasher32
{
	MurmurHasher32(unsigned int seed)
		:_seed(seed)
	{}

	MurmurHasher32()
		:_seed(0)
	{}

	uint64_t operator()(T& key)
	{
		return MurmurHash32(reinterpret_cast<void*>(&key), sizeof(key), _seed);
	}

private:
	unsigned int _seed;
};
