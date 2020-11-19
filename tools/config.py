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


# TODO: clean this up
def mk_struct(d, indentlevel=1):
    indent = "\t" * indentlevel
    if isinstance(d, list) or isinstance(d, map):
        s = f", \\\n{indent}".join(mk_struct(v, indentlevel=indentlevel) for v in d)
        return f"{{ \\\n{s} \\\n}}" 
    if isinstance(d, dict):
        s = f", \\\n{indent}".join(f".{k} = {mk_struct(v,indentlevel=indentlevel+1)}" for k, v in d.items())
        return f"{{ \\\n{indent}{s} \\\n{indent}}}" 
    return f"0x{d:02x}"

def mk_header(defines):
    lines = list()
    lines.append("/* Generated file */")
    lines.append("#ifndef KSK_CONFIG_H")
    lines.append("#define KSK_CONFIG_H")
    lines.extend(f"#define {k} {v}" for k, v in defines.items())
    lines.append("#endif")
    return '\n'.join(lines)

def mk_pmp(proc_id, pmp_confs):
    pmp = dict()
    pmp['cfg0'] = 0
    for i, pmp_conf in enumerate(pmp_confs):
        rwx = pmp_conf['rwx']
        base = pmp_conf['base']
        lg_size = pmp_conf['lg_size']
        assert (lg_size > 1), \
            f"process {proc_id+1}, pmp {i+1}: lg_size must be greater than 1."

        cfg = 0
        if "r" in rwx:
            cfg |= 1
        if "w" in rwx:
            cfg |= 2
        if "x" in rwx:
            cfg |= 4

        if lg_size == 2:
            cfg |= 2 << 3
            na_mask = 0
        else:
            cfg |= 3 << 3
            na_mask = int("1"*lg_size, 2)
            na_mask >>= 3
            assert (base % (2**lg_size) == 0), \
                (f"process {proc_id+1}, pmp {i+1}: base (0x{base:x}) must "
                 f"be a multiple of 2^lg_size (0x{2**lg_size:x}).")
        
        pmp['cfg0'] |= (cfg << (8 * i))
        pmp[f'addr{i}'] = base >> 2 | na_mask
    return pmp

def mk_defines(data):
    defines = data['constants']
    procs = data['processes']
    for i, proc in enumerate(procs):
        proc['id'] = i
        proc['pmp'] = mk_pmp(i, proc['pmp'])
    defines['__PROCS__'] = mk_struct(procs)
    defines['NR_PROCS'] = len(procs)
    return defines



if __name__ == "__main__":
    args = get_args()
    data = get_config_data(args.conf_file)
    print(mk_header(mk_defines(data)))
