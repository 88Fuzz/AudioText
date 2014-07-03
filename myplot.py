from pylab import plot as py_plot
from pylab import show as py_plot_show

array=[]
count=0

with open("points.txt") as f:
    for line in f:
        line=line.rstrip()
        array.append(line)

py_plot(array)
py_plot_show()
