#!/bin/bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SESSION="/Users/mreff555/.grok/sessions/%2FUsers%2Fmreff555%2F.grok%2Fworktrees%2Ftmp-detective-game%2Fgame-worker-2/019ef6e7-12d5-7b70-952d-2d56e4816fa2/images"

sips -s format png -z 256 256 "$SESSION/2.jpg" --out "$ROOT/resources/icons/bent_nails_icon.png" >/dev/null
sips -s format png -z 832 1248 "$SESSION/3.jpg" --out "$ROOT/resources/images/bent_nails_examine.png" >/dev/null

cd "$ROOT"
python3 tools/compress_images.py \
  resources/icons/bent_nails_icon.png \
  resources/images/bent_nails_examine.png \
  --remove-source

echo "Installed bent nails images"