#!/bin/bash

set -euo pipefail

setprofile() {
	sudo -u nobody /usr/local/bin/kbidle standby
}

case "$1" in
    pre)
	/usr/local/bin/kbidle standby
        ;;
    post)
	/usr/local/bin/kbidle wakeup
        ;;
esac
