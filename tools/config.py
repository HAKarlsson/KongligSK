#!/bin/env python3    
# This file is part of KongligSK.
# Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.
#
# KongligSK is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# KongligSK is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with KongligSK.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import yaml

def get_arguments():
    parser = argparse.ArgumentParser(description='Generate KongligSK code from configuration file.')
    parser.add_argument('config', help='Path to configuration file (YAML).')
    parser.add_argument('inc', help='Path to header directory.')
    return parser.parse_args()

def parse_yaml(filename):
    with open(filename, 'r') as f:
        data = yaml.load(f, Loader=yaml.Loader)
    return data


def dict2cstruct(struct_dict):




class ConfigParser:
    def __init__(self, conf):
        self.defines = conf['DEFINES']
        self.defines['NR_PROCS'] = len(conf['PROCESSES'])


if __name__ == "__main__":
    args = get_arguments()
    conf = parse_yaml(args.config)
    parser = ConfigParser(conf)
    print(parser.defines)
