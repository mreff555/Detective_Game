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

install_icon 100.jpg wick_icon.png
install_examine 100.jpg wick_examine.png

xz -dc "$ROOT/resources/icons/lamp_oil_icon.png.xz" > /tmp/lamp_oil_icon.png
xz -dc "$ROOT/resources/images/copper_wire_spool_examine.png.xz" > /tmp/wood_bg.png

magick /tmp/lamp_oil_icon.png \
  \( "$ROOT/resources/icons/wick_icon.png" -resize 72x72 \) \
  -gravity north -geometry +0+18 -composite \
  "$ROOT/resources/icons/crude_lantern_icon.png"

magick /tmp/wood_bg.png \
  \( /tmp/lamp_oil_icon.png -resize 520x520 -background none -gravity center -extent 520x520 \) \
  -gravity center -geometry +40-40 -composite \
  \( "$ROOT/resources/icons/wick_icon.png" -resize 180x120 \) \
  -gravity center -geometry +40-250 -composite \
  \( -size 40x55 xc:none -fill '#ffb347' -draw "ellipse 20,45 12,18 0,360" -blur 0x6 \) \
  -gravity center -geometry +40-300 -composite \
  "$ROOT/resources/images/crude_lantern_examine.png"

cd "$ROOT"
python3 tools/compress_images.py \
  resources/icons/wick_icon.png \
  resources/icons/crude_lantern_icon.png \
  --remove-source
python3 tools/compress_images.py \
  resources/images/wick_examine.png \
  resources/images/crude_lantern_examine.png \
  --remove-source

echo "Installed crafting item images"