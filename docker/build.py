#!/usr/bin/python

import os
import sys
import subprocess
import getpass
import pwd

def read_template(filename='Dockerfile.tpl'):
    dockerfile = None
    with open(filename) as f:
        dockerfile = f.read()
    return dockerfile

def fill_template(contents):
    username = getpass.getuser()
    pw_entry = pwd.getpwnam(username)
    uid = pw_entry.pw_uid
    gid = pw_entry.pw_gid
    return contents.format(username=username, uid=uid, gid=gid)

def write_docker_file(contents, filename='Dockerfile'):
    with open(filename, 'w') as f:
        f.writelines(contents)

def build_image(tag='arwmar/images:base'):
    subprocess.call("docker build -t %s ./" % tag, shell=True)

def main():
    template = read_template()
    if not template:
        raise RuntimeError("Dockerfile template not available")

    template = fill_template(template)

    write_docker_file(template, filename='Dockerfile')

    try:
        build_image()
    finally:
        os.unlink('Dockerfile')

if __name__ == '__main__':
    sys.exit(main())
