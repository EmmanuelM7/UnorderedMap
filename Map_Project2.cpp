#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept> 
#include<utility>
#include<list>
#include <iterator>


using namespace std;


unsigned int hashFunction(char const* key, int table_size) {
	unsigned int hashCode = 0;
	unsigned int b = 0; //temp variable
	unsigned int index = 0;


	for (int i = 0; key[i] != '\0'; i++)
	{
		unsigned int asciiVal = (int)key[i];
		if (i % 2 == 0)
		{
			b = (hashCode << 7) ^ asciiVal ^ (hashCode >> 3);
		}
		else
		{
			b = (hashCode << 11) ^ asciiVal ^ (hashCode >> 5);
			b = ~b;
		}

		hashCode = hashCode ^ b;
	}

	// implemented a strategy I found on this link https://www.geeksforgeeks.org/program-to-clear-k-th-bit-of-a-number-n/


	hashCode = hashCode & (~(1 << (31)));

	index = hashCode % table_size;

	return index;

}





class UnorderedMap
{
private:
	//define your data structure here
	vector <list<pair<string, string>>> table;

	//define other attributes e.g. bucket count, maximum load factor, size of table, etc. 
	unsigned int bCount;
	double maxLoadFactor;
	int numOfElements;
	//int tableSize;

public:
	class Iterator;
	UnorderedMap(unsigned int bucketCount, double loadFactor);
	~UnorderedMap();
	Iterator begin() const;
	Iterator end() const;
	std::string& operator[] (std::string const& key);
	void rehash();
	void remove(std::string const& key);
	unsigned int size();
	double loadFactor();

	//used similar iterator as professor

	    class Iterator
	    {
	    public:
			list<pair<string, string>>* bucketPointer;
			pair<string, string>* llPointer;
	        //this constructor does not need to be a default constructor;
	        //the parameters for this constructor are up to your discretion.
	        //hint: you may need to pass in an UnorderedMap object.
	        Iterator() 
			{

				UnorderedMap obj();
				list<pair<string, string>>* bucketPointer = nullptr;

				pair<string, string>* llPointer = nullptr;


				//UnorderedMap obj(bCount, loadFactor());

				
			}
	        Iterator& operator=(Iterator const& rhs) 
			{
				llPointer = rhs.llPointer;
				//auto it = obj.table[]
				return *this;
			}
	        Iterator& operator++() 
			{
				if (llPointer != nullptr)
				{
					llPointer = ++llPointer;
				}


				return *this;
			}
	        bool operator!=(Iterator const& rhs) 
			{
				if (llPointer != rhs.llPointer)
				{
					return true;
				}

				return false;
			}
	        
			bool operator==(Iterator const& rhs) 
			{
				if (llPointer == rhs.llPointer)
				{
					return true;
				}

				return false;

			}
	        std::pair<std::string, std::string> operator*() const 
			{
				pair<string, string>pair1;

				pair1.first = "";
				pair1.second = "";
			
				return pair1;
			}

	        friend class UnorderedMap;
	    };
};

UnorderedMap::UnorderedMap(unsigned int bucketCount, double loadFactor)
{

	bCount = bucketCount;
	maxLoadFactor = loadFactor;
	numOfElements = 0; //number of keys
	table.resize(bucketCount); //make sure to cite

}

UnorderedMap::~UnorderedMap()
{

}

UnorderedMap::Iterator UnorderedMap::begin() const
{
	Iterator it;
	return it;
}

UnorderedMap::Iterator UnorderedMap::end() const
{
	Iterator it;
	return it;
}

//not understanding 
//this could be an issue
std::string& UnorderedMap::operator[] (std::string const& key)
{
	//string hello = "Hello";
	//cout << table.capacity() << endl;
	int index = hashFunction(key.c_str(), bCount);
	string searchedVal = "";

	//cout << index << endl;
	string searchedKey = ""; //this could be wrong

	if (table[index].empty())
	{
		searchedKey == ""; // make it an empty string
	}
	else
	{
		for (auto it = table[index].begin(); it != table[index].end(); ++it)
		{
			if (it->first == key)
			{
				return it->second;
			}
		}

		searchedKey = "";

	}


	if (searchedKey != "")
	{
		//nothing should even get here
	}
	else
	{
		numOfElements++;
		index = hashFunction(key.c_str(), bCount);
		if (table[index].empty())
		{
			list<pair<string, string>> obj; // could cause a seg fault errir
			obj.push_front(make_pair(key, "")); // does this make sense
			table[index] = obj; // this could be the issue
		}
		else
		{
			table[index].push_back(make_pair(key, ""));
		}

		if (loadFactor() >= maxLoadFactor)
		{
			rehash();
			index = hashFunction(key.c_str(), bCount);
		}

		return table[index].back().second;
	}

}

//when rehasing we would also have to calculate the hashcode for the other nodes right?
//Rehash function to be used when the current load factor meets or exceeds the maximum load factor.
//Transfer data to new, larger hash table.
//Reset current load factorand capacity.
//Clean up the outdated hash table.

//used the pseudocode of TA Josh to better understand the thought process of the hash function
void UnorderedMap::rehash()
{
	unsigned int prevBCount = bCount;
	vector<list<pair<string, string>>> temp;
	temp.resize(bCount * 2);

	bCount = bCount * 2;
	numOfElements = 0;

	for (int i = 0; i < prevBCount; i++)
	{
		//if at the bucket it is empty then there is not a linkedlist to traverse
			if (table[i].empty())
			{
				continue;
			}
		for (auto iter = table[i].begin(); iter != table[i].end(); iter++)
		{
			numOfElements++;
			//should be using new bucket count
			int index = hashFunction(iter->first.c_str(), bCount);
			if (temp[index].empty())
			{
				list<pair<string, string>> obj; // could cause a seg fault errir
				obj.push_front(make_pair(iter->first, iter->second)); // does this make sense
				temp[index] = obj; // this could be the issue
			}
			else
			{
				temp[index].push_back(make_pair(iter->first, iter->second));
			}

		}
	}

	table.clear();
	table = temp;

}

void UnorderedMap::remove(std::string const& key)
{
	int index = hashFunction(key.c_str(), bCount);

	//LinkedList::Node* searchedKey = table[index]->Find(key); //this could be wrong

	if (!table[index].empty())
	{
		for (auto it = table[index].begin(); it != table[index].end(); ++it)
		{
			auto it2 = it;
			if (it2->first == key)
			{
				table[index].erase(it2);
				numOfElements--;
				break;
			}
		}
	}
	else
	{
		return; // possibly print to test
	}
}

unsigned int UnorderedMap::size()
{
	return numOfElements;
}

double UnorderedMap::loadFactor()
{
	//could cause an error 
	return (double)numOfElements / bCount;
}





//implement other operators in Iterator class


//Do not change main() 
int main()
{
	int lines = 0, buckets = 0;
	double maxLoadFactor = 0.0;
	std::string command = "", ufid = "", name = "", key = "";
	std::cin >> lines >> buckets >> maxLoadFactor;
	UnorderedMap myMap = UnorderedMap(buckets, maxLoadFactor);
	while (lines--)
	{
		std::cin >> command;
		if (command == "hash")
		{
			std::cin >> key;
			const char* convertedKey = key.c_str();
			std::cout << hashFunction(convertedKey, buckets) << "\n";
		}
		else if (command == "insert")
		{
			std::cin >> ufid >> name;
			myMap[ufid] = name;
		}
		else if (command == "size")
		{
			std::cout << myMap.size() << "\n";
		}
		else if (command == "load")
		{
			std::cout << std::fixed << std::setprecision(2) << myMap.loadFactor() << "\n";
		}
		else if (command == "search")
		{
			std::cin >> ufid;
			std::cout << myMap[ufid] << "\n";
		}
		else if (command == "traverse")
		{
			/*for (UnorderedMap::Iterator iter = myMap.begin(); iter != myMap.end(); ++iter)
			{
				std::cout << (*iter).first << " " << (*iter).second << "\n";
			}*/

			/* This should also work
				for (auto tableEntry: myMap)
				{
					std::cout << tableEntry.first << " " << tableEntry.second << "\n";
				}
			*/
		}
		else if (command == "remove")
		{
			std::cin >> ufid;
			myMap.remove(ufid);
		}
	}

	return 0;
}