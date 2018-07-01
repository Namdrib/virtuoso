#ifndef HELPERS_CPP
#define HELPERS_CPP

#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

#define all(c) (c).begin(), (c).end()


// Output for vector, space separated
template <typename T>
ostream& operator << (ostream& os, const vector<T> &v)
{
	for (size_t i=0; i<v.size(); i++)
	{
		os << v[i];
		if (i < v.size()-1) os << " ";
	}
	return os;
}

// Output for set, space separated
// Not sure how to not space on the last one
template <typename T>
ostream& operator << (ostream& os, const set<T> &s)
{
	for (auto it = s.begin(); it != s.end(); it++)
	{
		os << *it << " ";
	}
	return os;
}

template <typename T, typename S>
ostream & operator << (ostream &os, const pair<T, S> &p)
{
	os << "(" << p.first << ", " << p.second << ")";
	return os;
}

#endif // HELPERS_CPP
