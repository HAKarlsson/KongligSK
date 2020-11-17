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
    return parser.parse_args()

def parse_yaml(filename):
    with open(filename, 'r') as f:
        data = yaml.load(f, Loader=yaml.Loader)
    return data


def print_defs(defs):
    for name, val in defs.items():
        print(f"#define {name:16} {val}")



if __name__ == "__main__":
    args = get_arguments()
    conf = parse_yaml(args.config)
    print("#ifndef _CONFIG_H")
    print("#define _CONFIG_H")
    conf["DEFINES"]["NR_PROCS"] = len(conf["PROCESSES"])
    print_defs(conf["DEFINES"])
    print("#endif /* _CONFIG_H */")
