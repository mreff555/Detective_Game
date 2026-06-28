#!/usr/bin/env python3
"""Install the desk-letter focus scene image for cellar_passage_storage#desk_letter.

The source art is a photo-real scene render resized to the game's portrait scene
format (750x1117). Regenerate with your image pipeline, then run this script or
tools/install_cellar_passage_images.sh to compress into resources/images/.
"""

from __future__ import annotations

import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DEFAULT_SOURCE = (
    ROOT
    / "tools"
    / "hardware_sources"
    / "hector_letter_desk_source.jpg"
)
OUT = ROOT / "resources" / "images" / "hector_letter_desk.png"


def main() -> None:
    source = Path(sys.argv[1]) if len(sys.argv) > 1 else DEFAULT_SOURCE
    if not source.exists():
        print(
            f"Source image not found: {source}\n"
            "Place a photo-real desk/letter render at that path, or pass a path "
            "as the first argument.",
            file=sys.stderr,
        )
        sys.exit(1)

    OUT.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        [
            "sips",
            "-s",
            "format",
            "png",
            "-z",
            "1117",
            "750",
            str(source),
            "--out",
            str(OUT),
        ],
        check=True,
        stdout=subprocess.DEVNULL,
    )

    subprocess.run(
        [
            sys.executable,
            str(ROOT / "tools" / "compress_images.py"),
            str(OUT),
            "--remove-source",
        ],
        check=True,
        cwd=ROOT,
    )
    print(f"Installed {OUT.with_suffix('.png.xz')}")


if __name__ == "__main__":
    main()