#!/usr/bin/python
"""Copy Special exercise"""
# Copyright 2010 Google Inc.
# Licensed under the Apache License, Version 2.0
# http://www.apache.org/licenses/LICENSE-2.0

# Google's Python Class
# http://code.google.com/edu/languages/google-python-class/

import sys
import re
import os
import shutil
import commands


# +++your code here+++
# Write functions and modify main() to call them
def getspecialsathssir(directory):
    """return a list of special files within the given directory"""
    if os.path.exists(directory):
        specialfiles = []
        for filename in os.listdir(directory):
            match = re.search('__\w+__', filename)
            if match: 
                specialfiles.append(os.path.abspath(match.string))
        return specialfiles

def copy_to_dir(paths, directory):
    """copy the given list of files to a given directory"""
    if os.path.exists(directory):
        print 'dir exists'
        sys.exit()
    else:
        os.mkdir(directory)
        for path in paths:
            if os.path.exists(path):
                shutil.copy(path, directory)

def to_zip(paths, zippath):
    """zip the given list of files to the zippath"""
    if os.path.exists(zippath):
        print 'dir exists'
        sys.exit()
    else:
        if paths:
            command = 'zip -j ' + zippath + ' ' + ' '.join(paths)
            print 'i am going to execute: ' + command
            os.system(command)
        else:
            print 'no files!'
            sys.exit()

def main():
    """main method"""
    # This basic command line argument parsing code is provided.
    # Add code to call your functions below.

    # Make a list of command line arguments, omitting the [0] element
    # which is the script itself.
    args = sys.argv[1:]
    if not args:
        print "usage: [--todir dir][--tozip zipfile] dir [dir ...]"
        sys.exit(1)

    # todir and tozip are either set from command line
    # or left as the empty string.
    # The args array is left just containing the dirs.
    todir = ''
    if args[0] == '--todir':
        todir = args[1]
        del args[0:2]

    tozip = ''
    if args[0] == '--tozip':
        tozip = args[1]
        del args[0:2]

    if len(args) == 0:
        print "error: must specify one or more dirs"
        sys.exit(1)

    # +++your code here+++
    # Call your functions
    specialfiles = getspecialsathssir(args[0])
    if specialfiles:
        if todir:
            copy_to_dir(specialfiles, os.path.join(os.getcwd(), todir))
        if tozip:
            to_zip(specialfiles, tozip)
        else:
            for path in specialfiles:
                print path
    
if __name__ == "__main__":
    main()
