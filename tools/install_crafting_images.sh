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

xz -dc "$ROOT/resources/icons/lamp_oil_icon.png.xz" > /tmp/lamp_oil.png

magick -size 256x256 canvas:'#121018' \
  \( -size 256x256 xc:none \
     -fill '#2a2218' -draw "rectangle 0,210 256,256" \
     -fill '#c49a3a' -draw "roundrectangle 84,142 172,206 12,12" \
     -fill none -stroke '#5a4630' -strokewidth 5 -draw "line 128,66 128,192" \
     -stroke '#6e5840' -strokewidth 2 -draw "line 124,66 124,192" \
     -stroke '#4a3828' -strokewidth 2 -draw "line 132,66 132,192" \
     -fill 'rgba(150,165,180,0.35)' -stroke '#b8c4d0' -strokewidth 3 -draw "roundrectangle 78,70 178,206 16,16" \
     -fill 'rgba(230,240,255,0.25)' -draw "roundrectangle 88,82 98,180 4,4" \
     -fill '#8a98a8' -stroke '#c0ccd8' -strokewidth 2 -draw "rectangle 104,52 152,70" \
     -fill '#9a7048' -stroke '#6e4e2c' -strokewidth 2 -draw "roundrectangle 100,36 156,52 6,6" \
     -fill '#2a2218' -draw "ellipse 124,40 6,6 0,360" \
     -stroke '#4a3828' -strokewidth 4 -draw "line 128,36 128,24" \
     -fill '#ffae42' -draw "ellipse 128,18 10,14 0,360" \
     -fill '#ffe48a' -draw "ellipse 128,20 5,7 0,360" \
  \) -composite \
  \( /tmp/lamp_oil.png -alpha set -channel A -evaluate multiply 0.22 +channel \) -gravity center -compose Overlay -composite \
  -modulate 105,118,100 \
  "$ROOT/resources/icons/crude_lantern_icon.png"

magick -size 1248x832 canvas:'#241c16' \
  \( -size 1248x832 xc:none \
     -fill '#3d2f24' -draw "rectangle 0,0 1248,832" \
     -fill '#4a382a' -draw "rectangle 0,680 1248,832" \
     -fill '#c49a3a' -draw "roundrectangle 514,470 734,760 28,28" \
     -fill none -stroke '#5a4630' -strokewidth 12 -draw "line 624,250 624,732" \
     -stroke '#7a6248' -strokewidth 5 -draw "line 612,250 612,732" \
     -stroke '#4a3828' -strokewidth 5 -draw "line 636,250 636,732" \
     -fill 'rgba(150,165,180,0.32)' -stroke '#d0dae4' -strokewidth 5 -draw "roundrectangle 500,300 748,760 34,34" \
     -fill 'rgba(235,245,255,0.28)' -draw "roundrectangle 530,340 560,700 8,8" \
     -fill '#8a98a8' -stroke '#c8d4de' -strokewidth 4 -draw "rectangle 560,220 688,300" \
     -fill '#9a7048' -stroke '#6e4e2c' -strokewidth 4 -draw "roundrectangle 548,176 700,220 12,12" \
     -fill '#2a2218' -draw "ellipse 612,190 10,10 0,360" \
     -stroke '#4a3828' -strokewidth 10 -draw "line 624,176 624,130" \
     -fill '#ffae42' -draw "ellipse 624,108 24,34 0,360" \
     -fill '#ffe48a' -draw "ellipse 624,114 12,16 0,360" \
     -fill 'rgba(255,180,80,0.18)' -draw "ellipse 560,700 300,120 0,360" \
  \) -composite \
  \( /tmp/lamp_oil.png -resize 430x430 -alpha set -channel A -evaluate multiply 0.18 +channel \) -gravity center -geometry +0+20 -compose Overlay -composite \
  -modulate 108,120,100 -gaussian-blur 0x0.3 \
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