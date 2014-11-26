#!/usr/bin/env python3

import numpy

def main():
	total = 0
	done = False
	x = list()
	y = list()
	for n in range(0,1000):
		x.append(n+1)
		y.append(1)
		for i in range(1,11):
			if i&1:
				y[n] -= pow(n+1,i)
			else:
				y[n] += pow(n+1,i)

	n = 0
	while not done:
		n += 1
		print("x: " + str(x[0:n]))
		print("y: " + str(y[0:n]))
		coeffs = numpy.polyfit(x[0:n], y[0:n], deg=n-1)
		print("coeffs: " + str(coeffs))
		for i in range(0,len(coeffs)):
			coeffs[i] = round(coeffs[i])
		p = numpy.poly1d(coeffs)
		print("coeffs: " + str(coeffs))
		#print(numpy.polyval(numpy.poly1d(p),x))
		i = 0
		while True:
			print("p(" + str(i+1) + ") = " + str(p(i+1)) + " y = " + str(y[i]))
			if p(i+1) != y[i]:
				total += p(i+1)
				print("diff: " + str(p(i+1) - y[i]))
				print("total: " + str(total))
				break
			i += 1
			if i > n+1:
				print("done!")
				print("total: " + str(total))
				done = True
				break

if __name__ == '__main__':
	main()
