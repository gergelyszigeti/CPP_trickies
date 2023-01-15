#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using bar_type = int;
int randstate = 19790327;

template<typename T>
std::vector<T> GenerateRandomBars(int minlength = 20, int maxlength = 40,
                 int tallestBar = 10, int tallThres = 6, int tallBarCount = 3,
                 int maxSpaceLength = 4)
{
    // Unfortunately rand() was quite crappy on my MacBook Air, let me use
    // a simple but at least own rand (will be exactly the same on any platform)
    auto myRand = [] { randstate *= 65357; randstate ^= randstate >> 8;
                                 return randstate; };

    const int length = minlength + myRand() % (maxlength - minlength);
    std::vector<T> bars(length); // note, initially all values are 0 (space)
    for (int i = 0; i < length; i++) {
        // totally random bars look bad, therefore I limit the number of tall bars
        bars[i] = myRand() % ( tallBarCount ? tallestBar : tallThres );
        tallBarCount -= static_cast<int>(bars[i] > tallThres);

        i += myRand() % maxSpaceLength;
    }
    // Note, sometimes the vector ends with 0 (no bar), while the very first
    // element is always a bar; no problem, the algorithm can handle it B)
    // ( see "else branch here:" comment in PourWaterOnBars() )
    return bars;
}

template <typename T>
void ShowBarsWithoutAndWithWater(const std::vector<T>& bars,
		                 const std::vector<T>& water)
{
    auto width = bars.size();
    auto height = *std::max_element(bars.begin(), bars.end()); // tallest bar
    auto y = height; while (y --> 0) {          // y goes down (top to bottom)
	for(bool showWithWater: {false, true}) {
            for(auto x = 0; x < width; ++x) {   // x goes from left to right
	        std::cout <<                    // show one line
                    ( y <  bars[x] ? "|" :
    (showWithWater && y < water[x])? "o" :      // sorry if you find this line ugly
                            /*else*/ " " );     // for me it is more readable this way B)
	    }
	    std::cout << (showWithWater ? "\n" : "\t\t");
	}
    }
}

template<typename T>
std::vector<T> PourWaterOnBars(const std::vector<T>& bars)
{
    std::vector<T> water(bars.size());  // this will be our return,
                                        // water level for each position

    // Sort bars by height (tall -> short), sort with their places (indices)
    // COMPLEXITY: this part is O(log(b)), where b is the number of bars
    std::vector<std::pair<int, T>> barsWithPlaces; barsWithPlaces.reserve(bars.size());
    for (int i = 0; i < bars.size(); ++i) {
        // note: bars[] also have the spaces between bars, bars[i] = 0 there
        if (bars[i]) { barsWithPlaces.emplace_back(i, bars[i]); };
    }
    std::sort(barsWithPlaces.begin(), barsWithPlaces.end(),
              [](auto& a, auto& b) { return a.second > b.second; });

    // From now on, we only need the places (indices) of sorted bars
    // NOTE: this vector below is not really needed, the vector above
    // could have been used, with its first item of each pair only
    std::vector<T> orderedBarPlaces; orderedBarPlaces.reserve(bars.size());
    for (auto& barWithPlace: barsWithPlaces) {
        orderedBarPlaces.emplace_back(barWithPlace.first);
    }

    // Let's take all the bars in decreasing size order!
    // COMPLEXITY: this part is O(n), n is a bit less then all the bars and spaces -
    // places where water will be poured (each place is visited only once)
    for (auto& barPlace: orderedBarPlaces) {
        // If there is no already water to the right, we can pour it there
        // To guess the water level, let's find the tallest bar to the right
        if (barPlace != bars.size() - 1 && water[barPlace + 1] == 0) {
            // We can find the place (r) of the tallest bar to the right easily
            // with a very short while loop
            int r = 0;
            while(   r < orderedBarPlaces.size()
                  && orderedBarPlaces[r] <= barPlace) { r++; }
            if (r != orderedBarPlaces.size()) {
                // Water level is either the height of our bar
                // or the height of the tallest neighbor to the right
                T waterLevel = std::min(bars[barPlace], bars[orderedBarPlaces[r]]);
                // Pour water to the right as long as possible
                for (int i = barPlace + 1; i < orderedBarPlaces[r]; i++) {
                    if (bars[i] > waterLevel) { break; }
                    water[i] = waterLevel;
                }
            } // else branch here: for the last bar, there is no neighbor to the right
        }
    }
    return water;
}

int main(int argc, char* argv[])
{
    int count = 10;
    if (argc == 2) { count = std::stoi(argv[1]); }

    for (int i = 0; i < count; i++) {
        auto bars  = GenerateRandomBars<bar_type>();
        auto water = PourWaterOnBars(bars);
        ShowBarsWithoutAndWithWater(bars, water);

        std::cout << "\n--------------------------------------------"
                  << "------------------------------------------\n\n";
    }
}

