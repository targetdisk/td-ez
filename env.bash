git submodule update --init --recursive -- "$(git rev-parse --show-toplevel)/modules/bash-util"
. modules/bash-util/env.bash
add_path "$PWD/var/bin"
