/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Operation.h
 * Author: benjamin
 *
 * Created on September 6, 2017, 11:01 PM
 */

#ifndef OPERATION_H
#define OPERATION_H

#include "HashTable.h"
#include "MurmurHash.h"

    #include<cstdint>
    #include<fstream>
    #include<iostream>
    #include<string.h>

    namespace GarrettCSCI335 {
        template<
		class Prober,
		template <typename> typename Hasher
	>
    
        class Operation {
        public:
            enum OppCodes
		{
			INSERT = 0,
			RETRIVE
		};

        bool operator()(int64_t type, int64_t key, int64_t value);
           
        private:
            
        // HashTable declared as 1024 sized array with key and value typed to int64_t
		// probing behavior and hashing function are specified by templates arguments
		typedef HashTable<int64_t, int64_t, 1024, Prober, Hasher<int64_t> > HashTableType;
		HashTableType _table;
    };

	// invoked for each record of the operation sequence
	// return boolean result of the operation
	template< class Prober, template <typename> typename Hasher >
	bool Operation<Prober, Hasher >::operator()(int64_t type, int64_t key, int64_t value)
	{
		bool result = false;
		switch (type)
		{
		case INSERT:
			result = _table.insert(key, value);
			break;
		case RETRIVE:
		{
			std::pair<bool, int64_t> a = _table.retrieve(key);
			result = a.first;
			break;
		}
		default:
			std::cerr << "Invalid operation type.\n";
			break;
		}
		return result;
	}
}

         
#endif /* OPERATION_H */

