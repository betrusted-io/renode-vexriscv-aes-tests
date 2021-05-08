# VexRiscv Test for Renode

This repository contains VexRiscv test vectors for adding custom AES instructions to Renode.

You will most likely be modifying `vexriscv-aes.py`.

## Usage

To use, load `test-aes.resc` in Renode. You may find it comfortable to use the console, due to increased display performance:

```bash
$ renode test-aes.resc --console
```

Begin emulation:

```
(vexriscv-aes-test) start
```

You will see output on the uart analyzer, and debug messages on the terminal.

## Hacking

If you make modifications to `vexriscv-aes.py`, you will need to restart emulation:

```
(vexriscv-aes-test) machine Reset
```
