### WaterOnBars.cpp

A quite interesting puzzle: what happens when you pour some water on a histogram?
As a former research engineer, who worked a lot with histograms, was pretty courios about it :D

I wrote a simple algorithm for this, that sorts the bars as a preparitory step from the tallest to the shortest.
It is `O(log(b))` in complexity, where `b` is the number of bars.
Then, I take each bar in this order, and if there is no water already to the right of the bar, I pour some until the tallest neighbor bar to the right. The water level is always the height of the smaller bar of the two. Sometimes it is so low, that even a taller bar can stop it before the tallest neigbor to the right. Then I stop the pouring at that bar.
It is `O(n - db)` in complexity, where `n` is the length of the histogram (number of bars with the number of spaces between bars), `db` is the number of 'dry' bars (bars are not under water). All places are visited only once.

After typing `make` on Linux, MacOs terminal, or Cygwin, the program can be used by typing `./WaterOnBars`. It will show you ten experiments with various looking histogram pairs, similars to this one:


```
  | |                                     |o|
  | |                                     |o|
  | |   |                                 |o|ooo|
  | |   |                                 |o|ooo|
  | |   |      |   |                      |o|ooo|oooooo|ooo|
  | |   |      |   | |                    |o|ooo|oooooo|ooo|o|
  | |   |     ||   | |                    |o|ooo|ooooo||ooo|o|
| | |   | |   ||  || |                  |o|o|ooo|o|ooo||oo||o|
| | |   | |   ||  || |  |               |o|o|ooo|o|ooo||oo||o|oo|
```

> Note: here in this example `b` is 11, `n` is 25, `db` is 8 as we have 3 bars under water.

##### (this part below is not yet implemented)

You can set the number of experiments by giving a number as the first argument:
`./WaterOnBars 10000 > bars.txt`

Note, that although you can get 10 000 histograms in a fraction of a second, it would flood your screen for long kilometers, that is why an output txt file is used. The example was shown above will also be found in the txt file.

