## 给出bash脚本的位置


   ## This line doesn't resolve symlink.
   DIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" && pwd )"

   ## This line resolve symlink.
   DIR="$(cd -P "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))" && pwd)"
