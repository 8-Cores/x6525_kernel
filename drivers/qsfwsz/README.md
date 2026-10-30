# QSFWSZ kernel diagnostic interface

This directory contains the in-tree QSFWSZ driver for the UMS9230 kernel.

## Build

Enable `CONFIG_QSFWSZ=y`. The driver is built into the kernel and registers
a root-only miscdevice at `/dev/qsfwsz`.

## Current ABI

The first ABI version provides one query:

- `QSFWSZ_IOC_GET_INFO`: returns the ABI version, structure size and feature
  flags defined in `include/uapi/linux/qsfwsz.h`.

This initial implementation is metadata-only. It intentionally does not
read or modify memory belonging to other processes.

The source is tracked directly in this kernel repository. The CI workflow
does not clone or download a separate MemKernel repository to build it.
