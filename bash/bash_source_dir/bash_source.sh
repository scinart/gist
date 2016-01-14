#!/bin/bash

## This line doesn't resolve symlink.
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "called dir: ${DIR}"
## This line resolve symlink.
DIR="$(cd -P "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))" && pwd)"

echo "actual dir: ${DIR}"