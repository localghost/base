#!/usr/bin/env python

import os
import sys
import facts
import docker

def main():
    if not docker.DockerService.is_running():
        docker.DockerService.start()

    try:
        docker.DockerfileBuilder() \
            .with_template('./Dockerfile.tpl') \
            .with_vars(facts.get_facts()['user']) \
            .with_output('./Dockerfile') \
            .build()

        docker.Docker().build(path='./', tag='arwmar/images:base')
    finally:
        if os.path.exists('Dockerfile'):
           os.unlink('Dockerfile')

if __name__ == '__main__':
    sys.exit(main())
