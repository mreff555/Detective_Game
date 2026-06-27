#!/bin/bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SESSION="/Users/mreff555/.grok/sessions/%2FUsers%2Fmreff555%2F.grok%2Fworktrees%2Ftmp-detective-game%2Fgame-worker-2/019ef6e7-12d5-7b70-952d-2d56e4816fa2/images"

install_scene() {
  local src="$1"
  local dest="$2"
  sips -s format png -z 1117 750 "$SESSION/$src" --out "$ROOT/resources/images/$dest" >/dev/null
}

install_scene 13.jpg steep_mountain_trail.png
install_scene 10.jpg ridge_doctors_practice.png
install_scene 8.jpg ridge_cabin_main_room.png
install_scene 14.jpg ridge_cabin_bedroom.png

cd "$ROOT"
python3 tools/compress_images.py \
  resources/images/steep_mountain_trail.png \
  resources/images/ridge_doctors_practice.png \
  resources/images/ridge_cabin_main_room.png \
  resources/images/ridge_cabin_bedroom.png \
  --remove-source

echo "Installed ridge scene images"