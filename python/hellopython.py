#!/usr/bin/python2.4

import sys

def Hello(name):
	if name == 'wewt':
		name = 'derp'
	print "Dit is een",name

# Definieer een main methode en zeg hello world.
def main():
	Hello(sys.argv[1])

# Boilerplate voor de main methode.
if __name__ == '__main__':
	main()