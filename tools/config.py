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

def get_args():
    parser = argparse.ArgumentParser(
        description = 'Generate KongligSK configuration header (config.h).')
    parser.add_argument('conf_file', help='Path to YAML configuration file.')
    return parser.parse_args()


def get_config_data(conf_file):
    with open(conf_file, 'r') as f:
        data = yaml.load(f)
    return data


def mk_struct(d):
    if isinstance(d, list) or isinstance(d, map):
        s = ",".join(mk_struct(v) for v in d)
        return f"{{{s}}}" 
    if isinstance(d, dict):
        s = ",".join(f".{k} = {mk_struct(v)}" for k, v in d.items())
        return f"{{{s}}}" 
    return f"0x{d:02x}"

def mk_header(defines):
    lines = list()
    lines.append("/* Generated file */")
    lines.append("#ifndef KSK_CONFIG_H")
    lines.append("#define KSK_CONFIG_H")
    lines.extend(f"#define {k} {v}" for k, v in defines.items())
    lines.append("#endif")
    return '\n'.join(lines)

def mk_pmp(pmp_cfgs):
    pmp = dict()
    pmp['cfg0'] = 0
    for i, pmp_cfg in enumerate(pmp_cfgs):
        rwx = pmp_cfg['rwx']
        base = pmp_cfg['base']
        size = pmp_cfg['size']
        assert (size > 1), \
            "PMP regions size must be at least 4 bytes"

        cfg = 0
        if "r" in rwx:
            cfg |= 1
        if "w" in rwx:
            cfg |= 2
        if "x" in rwx:
            cfg |= 4

        if size == 2:
            cfg |= 2 << 3
            na_mask = 0
        else:
            cfg |= 3 << 3
            na_mask = int("1" * size, 2)
            na_mask >>= 3
            assert (base % (2**size) == 0), \
                "PMP regions not aligned with the size"
        
        pmp['cfg0'] |= (cfg << (8 * i))
        pmp[f'addr{i}'] = base >> 2 | na_mask
    return pmp

def mk_defines(data):
    defines = data['constants']
    processes = data['processes']
    defines['NR_PROCS'] = len(processes)
    for proc in processes:
        proc['pmp'] = mk_pmp(proc['pmp'])
    defines['__PROCS__'] = mk_struct(processes)
    return defines



if __name__ == "__main__":
    args = get_args()
    data = get_config_data(args.conf_file)
    print(mk_header(mk_defines(data)))
