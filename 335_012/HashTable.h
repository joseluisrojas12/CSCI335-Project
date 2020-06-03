#ifndef HASHTABLE_H
#define HASHTABLE_H


#include <array>
#include <limits>
#include <functional>

namespace GarrettCSCI335
{
 //Functor for linear probing
 struct LinearProber
 {
   LinearProber()
         :_inc(0)
         {}
   
         size_t operator() () { return _inc++;}
   
   private:
         size_t _inc;
 };
  
 template<
          class Key,
          class Value,
          size_t N=1024,
          class Prober = LinearProber,
          class Hasher = std::hash<Key>
 >
          class HashTable
 {
          //Hash record is specified by Key and Value 
          typedef std::pair<Key, Value> bundle_type;
          
          //Number of inserted records
          size_t _count;
          
          std::array<bundle_type, N> _table;
          
          //Default value for empty records
          static bundle_type _invalid;
          
 public:
          enum { Size=N }; 
          
          HashTable();
          
          bool insert(const Key& k, const Value& v);
          std::pair<bool, Value> retrieve(const Key& k) const;
          bool erase(const Key& k);
 };

 template<class Key, class Value, size_t N, class Prober, class Hasher >
 HashTable<Key, Value, N, Prober, Hasher>::HashTable()
        :_count (0)
 { //constructor fill the array by default value
   bundle_type invalid = std::make_pair(std::numeric_limits<Key>::max(),std::numeric_limits<Value>::max());
   _table.fill(invalid);
 }
  
 template<class Key, class Value, size_t N, class Prober, class Hasher>
 bool HashTable<Key, Value, N, Prober, Hasher>::insert(const Key& k, const Value& v)
 {
   //array is full already
   if (_count == Size) return false;
   
   bundle_type invalid=std::make_pair(std::numeric_limits<Key>::max(),std::numeric_limits<Value>::max());
   bundle_type tmp=std::make_pair(k,v);
   Prober p;
   Key local =k;
   size_t hash = Hasher{}(local); //compute the hash
   size_t index =0;
   
   do
   {
     index=(hash+p()) % Size; //probe the index
     if (_table[index].first==k)  return false; //if key already exist in hashTable
   } while (_table[index]!=invalid);
   _table[index]=tmp; //insert into empty call
   ++_count; //increment the number of the records
   return true;
 }
  
 template<class Key,class Value, size_t N, class Prober, class Hasher>
 std::pair<bool, Value> HashTable<Key, Value, N, Prober, Hasher>::retrieve(const Key& k) const
 {
   bundle_type invalid=std::make_pair(std::numeric_limits<Key>::max(),std::numeric_limits<Value>::max());
   std::pair<bool, Value> tmp=std::make_pair(false, std::numeric_limits<Value>::max());
   size_t increment =0;
   Prober p;
   Key local = k;
   size_t hash = Hasher{}(local); //compute the hash
   size_t index =0;
   
   do
   {
     if(increment++ >= Size)  return tmp;  //key doesn't exist in the full hash table
     index=(hash + p())% Size; //probe the index
     if(_table[index] == invalid) return tmp; //key doesn't exist
   }while(_table[index].first !=k);
   
   tmp.first = true;
   tmp.second=_table[index].second;
   return tmp;  //return the value
 }
 template<class Key, class Value, size_t N, class Prober, class Hasher>
 bool HashTable<Key, Value, N, Prober, Hasher>::erase(const Key& k)
 {
   bundle_type invalid = std::make_pair (std::numeric_limits<Key>::max(), std::numeric_limits<Value>::max());
   size_t increment=0;
   Prober p;
   Key local = k;
   size_t hash = Hasher{}(local);
   size_t index = 0;
   
   do
   {
     if(increment++>= Size)  return false;  //key doesn't exist in the full hash table
     index=(hash+p()) % Size;  //probe the index
     if (_table[index] == invalid)  return false;  //key doesn't exist
   }while(_table[index].first!=k);
   _table[index]=invalid;  //erase record
   --_count;  //dencrement the number of the records
   return true;
 }
}
   
#endif 
    
   
   

   

    
   
  

