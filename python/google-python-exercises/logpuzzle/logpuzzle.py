#!/usr/bin/python
"""Logpuzzle exercise
Given an apache logfile, find the puzzle urls and download the images.

Here's what a puzzle url looks like:
10.254.254.28 - - [06/Aug/2007:00:13:48 -0700] "GET /~foo/puzzle-bar-aaab.jpg HTTP/1.0" 302 528 "-" "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.6) Gecko/20070725 Firefox/2.0.0.6"
"""
# Copyright 2010 Google Inc.
# Licensed under the Apache License, Version 2.0
# http://www.apache.org/licenses/LICENSE-2.0

# Google's Python Class
# http://code.google.com/edu/languages/google-python-class/

import os
import re
import sys
import urllib



def read_urls(filename):
    """Returns a list of the puzzle urls from the given log file,
    extracting the hostname from the filename itself.
    Screens out duplicate urls and returns the urls sorted into
    increasing order."""
    # +++your code here+++
    if os.path.exists(os.path.join(os.getcwd(), filename)):
        urls = set()
        bestand = open(filename)
        for line in bestand:
            match = re.search('GET (.+puzzle.+) HTTP/1.0', line)
            if match:
                hostname = 'http://code.google.com'
                totalname = hostname + match.groups()[0]
                urls.add(totalname)
        urls = sorted(urls, key=descramble_sort)
    return urls

def descramble_sort(element):
    match = re.search(r'-\w+-(\w+)\..+', element)
    if match:
        return match.groups()[0]
    else:
        return element


def download_images(img_urls, dest_dir):
    """Given the urls already in the correct order, downloads
    each image into the given directory.
    Gives the images local filenames img0, img1, and so on.
    Creates an index.html in the directory
    with an img tag to show each local image file.
    Creates the directory if necessary.
    """
    # +++your code here+++
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)
    number = 0
    for url in img_urls:
        print url
        #print os.path.join(os.path.abspath(dest_dir), 'img' + str(number))
        urllib.urlretrieve(url, os.path.join(os.path.abspath(dest_dir), 'img' + str(number)))
        number += 1
    sys.exit()
    indexfile = open(os.path.join(os.path.abspath(dest_dir), 'index.html'), 'w')
    indexfile.write('<html>')
    index = 0
    while index <= number:
        indexfile.write('<img src="' + 'img' + str(index) + '"/>')
        index += 1
    indexfile.write('</html>')
    indexfile.close()

def main():
    args = sys.argv[1:]

    if not args:
        print 'usage: [--todir dir] logfile '
        sys.exit(1)

    todir = ''
    if args[0] == '--todir':
        todir = args[1]
        del args[0:2]

    img_urls = read_urls(args[0])

    if todir:
        download_images(img_urls, todir)
    else:
        print '\n'.join(img_urls)

if __name__ == '__main__':
    main()
