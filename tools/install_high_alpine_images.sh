#!/bin/bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SESSION="/Users/mreff555/.grok/sessions/%2FUsers%2Fmreff555%2F.grok%2Fworktrees%2Ftmp-detective-game%2Fgame-worker-2/019ef6e7-12d5-7b70-952d-2d56e4816fa2/images"

install_scene() {
  local src="$1"
  local dest="$2"
  sips -s format png -z 1117 750 "$SESSION/$src" --out "$ROOT/resources/images/$dest" >/dev/null
}

install_icon() {
  local src="$1"
  local dest="$2"
  sips -s format png -z 128 128 "$SESSION/$src" --out "$ROOT/resources/icons/$dest" >/dev/null
}

install_examine() {
  local src="$1"
  local dest="$2"
  sips -s format png -z 1117 750 "$SESSION/$src" --out "$ROOT/resources/images/$dest" >/dev/null
}

install_scene 22.jpg high_alpine_trail.png
install_scene 23.jpg alpine_summit.png
install_scene 24.jpg sawtooth_ridge_body.png
install_icon 21.jpg crampons_icon.png
install_examine 20.jpg crampons_examine.png

cd "$ROOT"
python3 tools/compress_images.py \
  resources/images/high_alpine_trail.png \
  resources/images/alpine_summit.png \
  resources/images/sawtooth_ridge_body.png \
  resources/images/crampons_examine.png \
  resources/icons/crampons_icon.png \
  --remove-source

echo "Installed high alpine trail, summit, ridge body, and crampons images"