#!/bin/bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SESSION="/Users/mreff555/.grok/sessions/%2FUsers%2Fmreff555%2F.grok%2Fworktrees%2Ftmp-detective-game%2Fgame-worker-2/019ef6e7-12d5-7b70-952d-2d56e4816fa2/images"

install_scene() {
  local src="$1"
  local dest="$2"
  sips -s format png -z 1117 750 "$SESSION/$src" --out "$ROOT/resources/images/$dest" >/dev/null
}

install_scene 16.jpg cellar_passage_shaft.png
install_scene 15.jpg cellar_passage_shaft_lit.png
install_scene 17.jpg cellar_passage_storage.png
install_scene 18.jpg cellar_passage_storage_lit.png
install_scene 19.jpg cellar_passage_storage_door_open.png

cd "$ROOT"
python3 tools/compress_images.py \
  resources/images/cellar_passage_shaft.png \
  resources/images/cellar_passage_shaft_lit.png \
  resources/images/cellar_passage_storage.png \
  resources/images/cellar_passage_storage_lit.png \
  resources/images/cellar_passage_storage_door_open.png \
  --remove-source

if [[ -f tools/hardware_sources/hector_letter_desk_source.jpg ]]; then
  python3 tools/generate_hector_letter.py
fi

echo "Installed cellar passage scene images"