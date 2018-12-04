#include <cmath>
#include <limits>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

class IntervalVector {
	struct Interval {
		double start, end;
		bool operator <(double d) const { return end < d; };
	};

	std::vector<Interval> intervals;
	
public:
	void insert(double start, double end) {
		std::cout << "insert: (" << start << "," << end << ")\n";
		
		// find the interval with the smallest end greater than or equal to the given start
		auto firstIt = lower_bound(intervals.begin(), intervals.end(), start);
		//std::cout << "firstIt:" << firstIt->start << "," << firstIt->end << std::endl;
		
        // no overlap
		if (firstIt == intervals.end() || end < firstIt->start) {
			intervals.insert(firstIt, {start, end});
			print();
			return;
		}

		// we have at least one overlapping interval
		// find the interval with the smallest end greater than or equal to the given end
		auto lastIt = lower_bound(intervals.begin(), intervals.end(), end);
		//if (lastIt == intervals.end()) std::cout << "lastIt:  end\n";
		//else std::cout << "lastIt: " << lastIt->start << "," << lastIt->end << std::endl;
	   
        // extend the first overlapping interval in place
		firstIt->start = std::min(start, firstIt->start);
		firstIt->end = std::max(end, firstIt->end);

		// if we overlap with the last interval, merge it and mark it for removal
		if (lastIt != intervals.end() && end >= lastIt->start) {
			firstIt->end = std::max(end, lastIt->end);
            ++lastIt;
		}
		
		// remove any overlapping intervals after the first
        intervals.erase(firstIt+1, lastIt);
		print();
	}

    bool contains(double x) {
          auto it = std::upper_bound(intervals.begin(), intervals.end(), Interval{x, x},
                [](const Interval &a, const Interval &b) { return a.start < b.start; });
          std::cout << "searching for " << x;
          if (it == intervals.begin()) {
              std::cout << ": goes before start of set ";
              return false;
          }
          if (it == intervals.end()) {
              std::cout << ": goes after end of set ";
          }
          --it;
          std::cout << ": found (" << it->start << ',' << it->end << ") ";
          return it->start <= x && it->end > x;
    }
	
	void print() {
        std::cout << "                ";
		for (auto &i : intervals) {
            std::cout << "(" << i.start << ',' << i.end << ") ";
		}
		std::cout << std::endl;
	}
};

class IntervalTree {
    enum Type {START, END};
	std::map<double, Type> intervals;

public:
	IntervalTree() {
		intervals[-std::numeric_limits<double>::infinity()] = END;
		intervals[std::numeric_limits<double>::infinity()] = START;
	}
	
	void insert(double start, double end) {
		std::cout << "insert: (" << start << "," << end << ")\n";

		auto firstIt = intervals.lower_bound(start);
		if (firstIt->second == START) intervals[start] = START;
	
		auto lastIt = intervals.upper_bound(end);
		if (firstIt->first < lastIt->first) intervals.erase(firstIt, lastIt);
	
		if (lastIt->second == START) intervals[end] = END;

		print();
	}

	void print() {
        std::cout << "                ";
		for (auto &b : intervals) {
			if (!std::isfinite(b.first)) continue;
            if (b.second == START) std::cout << "(" << b.first;
			else std::cout << ',' << b.first << ") ";
		}
		std::cout << std::endl;
	}

    bool contains(double d) {
        auto it = intervals.lower_bound(d);
        return it->first == d || it->second == END;
    }
};

int main() {
   // IntervalTree s;
    IntervalVector s;
	
	s.insert(10, 16);
	s.insert(-20, -18);
	s.insert(1, 4);

	s.insert(2, 3);
	s.insert(2, 4);
	s.insert(0, 5);
	s.insert(-1, 5);
	s.insert(6, 7);
	s.insert(-21, 8);
	s.insert(30, 32);
//	s.insert(8, 30);

    std::cout << std::boolalpha << "=============================================\n";
    s.print();
    
    std::cout << s.contains(-22) << "\n";
    std::cout << s.contains(3) << "\n";
    std::cout << s.contains(10) << "\n";
    std::cout << s.contains(16) << "\n";
    std::cout << s.contains(18) << "\n";
    std::cout << s.contains(31) << "\n";
    std::cout << s.contains(33) << "\n";
    std::cout << std::endl;
    return 0;
}
