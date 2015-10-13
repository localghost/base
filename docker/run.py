#!/usr/bin/python

import sys
import subprocess

def run_image(image, volumes=None):
    command = 'docker run -it --rm'
    if volumes:
        command += ''.join([' -v %s ' % volume for volume in volumes])
    command += ' %s' % image
    subprocess.call(command, shell=True)

def main():
    run_image('arwmar/images:base', ['/home/me/projects/base:/opt/sources/base'])

if __name__ == '__main__':
    sys.exit(main())
