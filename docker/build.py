#!/usr/bin/env python

import os
import sys
import docker

def main():
    try:
        docker.DockerfileBuilder() \
            .with_template('./Dockerfile.tpl') \
            .with_vars(docker.get_user_variables()) \
            .with_output('./Dockerfile') \
            .build()

        docker.Docker().build(path='./', tag='arwmar/images:base')
    finally:
        os.unlink('Dockerfile')

if __name__ == '__main__':
    sys.exit(main())
