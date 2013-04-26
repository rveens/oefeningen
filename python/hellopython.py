import sys

def hello(name):
    """Dit is een test"""
    if name == 'wewt':
        name = 'derp'
    print "Dit is een"

# Definieer een main methode en zeg hello world.
def main():
    """main functie"""
    hello(sys.argv[1])

# Boilerplate voor de main methode.
if __name__ == '__main__':
    main()
