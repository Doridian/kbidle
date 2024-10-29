#!/bin/bash

set -euo pipefail

case "$1" in
    pre)
        sudo -u doridian openrgb -p Off
        ;;
    post)
        sudo -u doridian openrgb -p Default
        ;;
esac
