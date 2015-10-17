#!/usr/bin/env python

import os
import sys
import docker
import getpass
import subprocess

def get_facts():
    script_path = os.path.dirname(os.path.realpath(__file__))
    return dict(
        script_path = script_path,
        project_path = os.path.join(script_path, '..'),
        docker_workspace_path = os.path.join(script_path, 'home'),
        username = getpass.getuser(),
        display = os.environ.get('DISPLAY'),
    )

def is_docker_running():
    return subprocess.call('service docker status >/dev/null 2>&1', shell=True) == 0

def main():
    facts = get_facts()

    if not is_docker_running():
        subprocess.check_call('sudo service docker start', shell=True)

    if not os.path.exists(facts['docker_workspace_path']):
        os.mkdir(facts['docker_workspace_path'])

    print "FIXME: disabling x access control"
    os.system('xhost +')

    docker.DockerContainerBuilder() \
        .with_image('arwmar/images:base') \
        .with_volume(host_path = facts['project_path'], docker_path = '/opt/sources/base') \
        .with_volume(host_path = '/tmp/.X11-unix', docker_path = '/tmp/.X11-unix') \
        .with_volume(host_path = facts['docker_workspace_path'], docker_path = os.path.join('/home', facts['username'])) \
        .with_env(name = 'DISPLAY', value = facts['display']) \
        .with_tty() \
        .with_interactive() \
        .run()

if __name__ == '__main__':
    sys.exit(main())
