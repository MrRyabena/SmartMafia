#!/bin/bash

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"

show_help() {
    cat <<EOF
Usage: $(basename "$0") [options]

Options:
  -p, -pa, --prepare [app]  Prepare application files (app is the default)
  -h, --help                Show this help
EOF
}

prepare_app() {
    mkdir -p ./app/SmartMafia/ShsBuild

    # cp -r ./SmartMafia ./app/SmartMafia/ShsComponents
    rm -rf ./app/SmartMafia/ShsBuild/SHS_SmartSpot
    rm -rf ./app/SmartMafia/ShsBuild/SHS_Color
    rm -rf ./app/SmartMafia/ShsBuild/SHS_APIids
    rm -rf ./app/SmartMafia/ShsBuild/SHScore

    cp -r /mnt/s/repos/SmartSpot/src/SHS_SmartSpot ./app/SmartMafia/ShsBuild
    cp -r /mnt/s/repos/SmartHomeSystem/src/SHSlibrary/SHS_Color ./app/SmartMafia/ShsBuild
    cp -r /mnt/s/repos/SmartHomeSystem/src/SHSlibrary/SHS_APIids ./app/SmartMafia/ShsBuild
    cp -r /mnt/s/repos/SmartHomeSystem/src/SHScore ./app/SmartMafia/ShsBuild

}

while [[ $# -gt 0 ]]; do
    case "$1" in
        -h|--help)
            show_help
            exit 0
            ;;
        -p|-pa|--prepare)
            if [[ "$2" == "app" ]]; then
                shift
            elif [[ -n "$2" && "$2" != -* ]]; then
                echo "[ERROR] Unknown prepare option: $2" >&2
                show_help >&2
                exit 1
            fi
            prepare_app
            shift
            ;;
        -*)
            echo "[ERROR] Unknown option: $1" >&2
            show_help >&2
            exit 1
            ;;
        *)
            echo "[ERROR] Unknown argument: $1" >&2
            show_help >&2
            exit 1
            ;;
    esac
done
