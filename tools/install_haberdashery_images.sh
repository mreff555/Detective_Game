#!/bin/bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SESSION="/Users/mreff555/.grok/sessions/%2FUsers%2Fmreff555%2F.grok%2Fworktrees%2Fsrc-detective-game%2Fdetective-game/019edda2-97be-7b63-9a61-52f0e9332303/images"

install_icon() {
  local src="$1"
  local dest="$2"
  sips -s format png -z 256 256 "$SESSION/$src" --out "$ROOT/resources/icons/$dest" >/dev/null
}

install_examine() {
  local src="$1"
  local dest="$2"
  sips -s format png -z 832 1248 "$SESSION/$src" --out "$ROOT/resources/images/$dest" >/dev/null
}

# Icons
install_icon 58.jpg mens_cologne_icon.png
install_icon 61.jpg straight_razor_icon.png
install_icon 59.jpg hair_tonic_icon.png
install_icon 60.jpg shaving_brush_icon.png
install_icon 56.jpg cuff_links_icon.png
install_icon 57.jpg bow_tie_icon.png
install_icon 62.jpg custom_shirt_icon.png
install_icon 63.jpg custom_trousers_icon.png
install_icon 64.jpg custom_jacket_icon.png
install_icon 65.jpg mens_pea_coat_icon.png
install_icon 66.jpg mens_duster_icon.png
install_icon 67.jpg wool_fabric_sample_icon.png

# Examine images
install_examine 70.jpg mens_cologne_examine.png
install_examine 72.jpg straight_razor_examine.png
install_examine 71.jpg hair_tonic_examine.png
install_examine 73.jpg shaving_brush_examine.png
install_examine 69.jpg cuff_links_examine.png
install_examine 68.jpg bow_tie_examine.png
install_examine 78.jpg custom_shirt_examine.png
install_examine 75.jpg custom_trousers_examine.png
install_examine 79.jpg custom_jacket_examine.png
install_examine 77.jpg mens_pea_coat_examine.png
install_examine 76.jpg mens_duster_examine.png
install_examine 74.jpg wool_fabric_sample_examine.png

cd "$ROOT"
python3 tools/compress_images.py resources/icons --remove-source
python3 tools/compress_images.py resources/images/mens_cologne_examine.png resources/images/straight_razor_examine.png resources/images/hair_tonic_examine.png resources/images/shaving_brush_examine.png resources/images/cuff_links_examine.png resources/images/bow_tie_examine.png resources/images/custom_shirt_examine.png resources/images/custom_trousers_examine.png resources/images/custom_jacket_examine.png resources/images/mens_pea_coat_examine.png resources/images/mens_duster_examine.png resources/images/wool_fabric_sample_examine.png --remove-source

echo "Installed haberdashery images"