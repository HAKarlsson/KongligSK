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


def get_args():
    import argparse
    parser = argparse.ArgumentParser(description='Generate KongligSK configuration header (config.h).')
    parser.add_argument('conf_file', help='Path to YAML configuration file.')
    return parser.parse_args()


def get_config_data(conf_file):
    import yaml
    with open(conf_file, 'r') as f:
        data = yaml.load(f, Loader=yaml.Loader)
    return data


class Config:
    def __init__(self, config):
        self.constants = config['constants']
        self._processes(config['processes'])

    def _processes(self, procs):
        self.constants['NR_PROCS'] = len(procs)

    def __repr__(self):
        lines = list()
        lines.append("/* Generated file */")
        lines.append("#ifndef KSK_CONFIG_H")
        lines.append("#define KSK_CONFIG_H")
        lines.extend(f"#define {k} {v}" for k, v in self.constants.items())
        lines.append("#endif /* KSK_CONFIG_H */")
        return '\n'.join(lines)

if __name__ == "__main__":
    args = get_args()
    data = get_config_data(args.conf_file)
    config = Config(data)
    print(config)
