set terminal postscript
set output 'orig.ps'
set xrange [0:256]
plot 'orig.dat' using 1 title "Input Signal" with lines linecolor rgb 'red'

set output 'wt.ps'
set logscale y
plot 'waveout.dat' using 1 title 'Wavelet Transform' with lines linecolor rgb 'red', \
	 'waveout.dat' using 2 title 'Filtered Transform' with lines linecolor rgb 'blue'
	 
set output 'revwt.ps'
unset logscale
set yrange [-1:1]
plot 'output2.dat' using 2 title 'Filtered Signal' with lines linecolor rgb 'red', \
	 'output2.dat' using 1 title '(5x) Signal Error' with lines linecolor rgb 'blue'
	 