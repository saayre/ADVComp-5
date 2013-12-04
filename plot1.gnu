set terminal postscript
set output 'wt.ps'
set logscale y
plot 'waveout.dat' using 1 with lines, \
	 'waveout.dat' using 2 with lines
	 