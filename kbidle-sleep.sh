#!/bin/bash

set -euo pipefail

kbidle() {
	sudo -u nobody /usr/local/bin/kbidle "$1"
}

case "$1" in
    pre)
	    kbidle standby
        ;;
    post)
	    kbidle wakeup
        ;;
esac
