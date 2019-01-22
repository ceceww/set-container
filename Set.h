#ifndef MYSET_H_
#define MYSET_H_

#include <vector>
#include <fstream>
#include <algorithm>

using std::vector;

using std::cerr;

/* In this exercise you will use templates to implement a container
 * which represents a set of elements of some type T.
 * The type T is assumed to have copy constructors and assignment
 * operators implemented for it, and, furthermore, operator<, operator==,
 * operator<< and operator>> are overloaded for type T.
 *
 *
 * You are advised to use the STL containers for storing
 * information. This should help you implement this class.
 *
 * The container accepts objects of type T and stores them. 
 * It allows for searching for a value in the set, 
 * and if the value is not present, it returns a vector consisting
 * of the greatest K elements smaller than that value, followed by the
 * smallest K elements greater than that value. 
 * It also allows you to get a vector of all elements of the set
 * that are between a given start value and a given end value.
 * In either case, the elements in the returned vector should be sorted
 * in ascending order, according to the operator <.
 *
 * Details about each of the functions of Set are given below.
 */

template<class T>
class Set {
public:
	// Default constructor initializing an empty container
	Set();

	// Destructor
	~Set();

	// No need to implement copy and move constructors
	Set(const Set&) = delete;
	Set(Set&&) = delete;
	// No need to implement assignment operators
	Set& operator=(const Set& other) = delete;
	Set& operator=(Set&& other) = delete;

	// Populates the set from a file. We assume 
	// that operator>> is defined for the type T.
	// If the file cannot be open or there is an error
	// during reading, throws std::exception.
	// If the container already contains some elements,
	// they are all dropped before reading the file.
	void readFromFile(const std::string& file_name);

	
	// Searches for value val in the container. 
	// If val is found in container, returns a vector
	// of length 1 containing this single value. 
	// If val is not found in the container, returns a 
	// vector (l_1,...,l_i,g_1,...g_j), 
	// where l_1, ..., l_i are the largest K elements of the 
	// set that are smaller than val,
	// and g_1, ... g_j are the smallest K elements of the 
	// set that are greater than val.
	// If the container contains fewer than K elements smaller 
	// than val, then l_1, ..., l_i are all the elements
	// of the set that are smaller than val.
	// If the container contains fewer than K elements greater 
	// than val, then g_1, ..., g_j are all the elements
	// of the set that are greater than val.
	// Furthermore, the elements of the returned vector should
	// be ordered in ascending order according to <, that is:
	// l_1 < ...< l_i < g_1 < ... < g_j.
	std::vector<T> findClosest(const T& val, unsigned int K) const;

	
	// Returns all the elements of the set container that are greater
	// or equal to start_value and smaller or equal to end_value. 
	// The elements of the returned vector should be in ascending order 
	// according to <. That is, the returned vector is (e_1,...,e_n), where:
	// -- we have e_1 < e_2 < ...< e_n.
	// -- all elements of set that are greater or equal to start_value
	// AND are smaller or equal to end_value are among e_1,...,e_n.
	// If start_value > end_value, then the returned vector should be empty.
	// Note that start_value and end_value do not have to exist in the container.
	std::vector<T> getRange(const T& start_value,const T& end_value) const;


	// Inserts an element val in the container. 
	// If val is already in the container, does nothing and returns false,
	// otherwise adds val to the container and returns true.
	bool insert(const T& val);
	
	// Removes an element val from the container. 
	// If val is not in the container, does nothing and returns false,
	// otherwise, removes val from the container and returns true.
	bool remove(const T& val);

	// Removes from the container all elements greater or equal to val. 
	// If nothing is removed, returns false, otherwise returns true.
	// Note that even when val is not in the container, elements
	// greater than it have to be removed.
	bool removeGreaterOrEqual(const T& val);

	// Removes from the container all elements smaller or equal to val. 
	// If nothing is removed, returns false, otherwise returns true.
	// Note that even when val is not in the container, elements
	// smaller than it have to be removed.
	bool removeLessOrEqual(const T& val);

	// Returns true if the set is empty, and false otherwise.
	bool empty()const;

	// Returns the number of elements in the set.
	unsigned int size() const;

	// Removes all elements from the set container.
	// Leaves the set empty (with a size of 0).
	void clear();


	// Outputs all the elements of the container in ascending order according to <.
	// We assume that operator<< is overloaded for type T.
	template <class U>
	friend std::ostream& operator<<(std::ostream& o, const Set<U>& dict);


private:
	vector<T> vect;
};

template<class T> 
Set<T>::Set(){
}


template<class T> 
Set<T>::~Set(){
}

template<class T>
void Set<T>::readFromFile(const std::string& file_name){
	try{
		std::ifstream infile(file_name); 	// Open the file
		T elem;
		while ( infile >> elem ) {	// Read contents of file
			vect.push_back(elem);		// Add element to vect
		}
	} 
	catch (std::exception e) {
		cerr << e.what() << "Error with file" << std::endl;
	}
}	


template<class T> 
std::vector<T> Set<T>::findClosest(const T& val, unsigned int K) const{
	vector<T> new_vect; // new_vect is the vector returned
	if (std::find(vect.begin(), vect.end(), val) != vect.end()) { // If val is in vect
		new_vect.push_back(val); // Insert val into new_vect
		return new_vect; 
	}
	else { // If val is not in vect
		vector<T> orig_vect; 
		for (auto i = vect.begin(); i != vect.end(); i++) { 
			orig_vect.push_back(*i); // Add each element of vect to new vector object
		}
		vector<T> v_greater; // Store the K elements greater than val

		sort(orig_vect.begin(), orig_vect.end()); // Sort new_vect so elements are in ascending order

		// Look for elements greater than val
		for (auto i = orig_vect.begin(); i != orig_vect.end(); i++) {
			if (*i > val) {
				v_greater.push_back(*i); // Insert element into v_greater
				if (v_greater.size() == K) { // If number of elements in v_greater is K 
					break; // Exit loop
				}
			}
		}
		// Look for elements smaller than val
		for (auto i = orig_vect.begin(); i != orig_vect.end(); i++) {
			if (*i < val) {
				new_vect.push_back(*i); // Insert element into new_vect
			}
		}
		// Sort new_vect so elements are in descending order 
		sort(new_vect.begin(), new_vect.end());
		reverse(new_vect.begin(), new_vect.end());

		new_vect.resize(K); // Resize new_vect to only contain the first K elements
		sort(new_vect.begin(), new_vect.end()); // Sort the elements in ascending order

		new_vect.insert(new_vect.end(), v_greater.begin(), v_greater.end()); // Insert v_greater at the end of new_vect
	}
	
	return new_vect;
}


template<class T> 
std::vector<T> Set<T>::getRange(const T& start_value,const T& end_value) const{
	vector<T> new_vect; // The vector returned
	if (start_value > end_value) {
		return new_vect;
	}
	else {
		for (auto i = vect.begin(); i != vect.end(); i++) {
			// Check the criteria for i is met, for it to be included in new_vect
			if ((*i == start_value) || ((*i > start_value) && (*i < end_value))) {
				new_vect.push_back(*i); // Add it to new_vect
			}
		}
		// Sort new_vect in ascending order
		sort(new_vect.begin(), new_vect.end());
	}	
	return new_vect;
}

template<class T>
bool Set<T>::insert(const T& val){
	bool inserted = false;
	if (std::find(vect.begin(), vect.end(), val) != vect.end()) { // If found
		return inserted; // Returns false
	}
	vect.push_back(val); 	// Otherwise insert val into vect
	inserted = true;
	return inserted;	// Returns true
}


template<class T>
bool Set<T>::remove(const T& val){
	bool removed = false;
	if (std::find(vect.begin(), vect.end(), val) != vect.end()) { // If found
		// Then remove the element
		vect.erase(std::remove(vect.begin(), vect.end(), val), vect.end());
		removed = true;
	}
	return removed;

}


template<class T>
bool Set<T>::removeGreaterOrEqual(const T& val){
	vector<T> v_greater; // Store the elements of vect that are >= val
	bool removed = false; // Init removed to false; nothing removed yet
	// Look for elements >= than val
	for (auto i = vect.begin(); i != vect.end(); i++) {
		if (*i >= val) {
			v_greater.push_back(*i); // Insert element into v_greater
		}
	}
	for (auto i = v_greater.begin(); i != v_greater.end(); i++) { // Now iterate over v_greater
		if (std::find(vect.begin(), vect.end(), *i) != vect.end()) { // If element of v_greater is in vect
			removed = true; // It will be removed so set removed = true
		}
		vect.erase(std::remove(vect.begin(), vect.end(), *i), vect.end()); // Erase this element from vect
	}
	return removed;	
}

template<class T>
bool Set<T>::removeLessOrEqual(const T& val){
	vector<T> v_smaller; // Store the elements of vect that are <= val
	bool removed = false; // Init removed to false; nothing removed yet
 // Look for elements <= than val
	for (auto i = vect.begin(); i != vect.end(); i++) {
		if (*i <= val) {
			v_smaller.push_back(*i); // Insert element into v_smaller
		}
	}
	for (auto i = v_smaller.begin(); i != v_smaller.end(); i++) { // Now iterate over v_smaller
		if (std::find(vect.begin(), vect.end(), *i) != vect.end()) { // If element of v_smaller is in vect
			removed = true; // It will be removed so set removed = true
		}
		vect.erase(std::remove(vect.begin(), vect.end(), *i), vect.end()); // Erase this element from vect
	}
	return removed;
}

template<class T>	
bool Set<T>::empty()const{
	return vect.empty();
}

template<class T>
unsigned int Set<T>::size() const{
	return vect.size();
}

template<class T>
void Set<T>::clear(){
	vect.clear();
}

template<class T>
std::ostream& operator<<(std::ostream& o, const Set<T>& s){
	for (auto i = s.vect.begin(); i != s.vect.end(); ++i) {
    	o << *i << ' ';
	}
	return o;
}

#endif /* MYSET_H_ */
