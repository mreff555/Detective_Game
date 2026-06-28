#!/usr/bin/env python3
"""Merge alpine hardware shopkeeper conversation into conversations.json."""

from __future__ import annotations

import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from shop_utils import ShopDialogConfig, build_shop_conversation  # noqa: E402

COMPLIMENT_CHOICE = {
    "id": "compliment_building",
    "label": "Impressive building (looking around a bit)",
    "response": (
        "You take in the post-and-beam bones of the room: timbers joined "
        "with a joiner's patience, braces cut true, the whole frame standing "
        "with the quiet confidence of work done by someone who did not need "
        "to hurry.\n\n\"Impressive building,\" you say.\n\n"
        "For the first time, something like pleasure enters his face.\n\n"
        "\"I built it myself,\" he says. \"Every beam, every brace, every "
        "peg. My father ran a mill in Pennsylvania. I learned timber before "
        "I learned trade. Came up here in eighty-one when the High Line "
        "decided it was going to stay, not just camp. There was no proper "
        "hardware north of Graysmill that would make the climb worth a "
        "mule's temper, so I opened this room and stocked it for men who "
        "break ground in weather that kills carelessness.\" He taps the "
        "nearest post with his knuckle. \"She'll stand longer than most of "
        "the claims on this ridge.\""
    ),
    "consumeOnSelect": True,
    "persistConsumed": True,
    "resumeTopLevel": True,
    "closePhase": False,
}


def main() -> None:
    catalog = json.loads((ROOT / "tools" / "hardware_catalog.json").read_text())
    conversations_path = ROOT / "resources" / "conversations.json"
    data = json.loads(conversations_path.read_text())

    config = ShopDialogConfig(
        merchant_tone="hardware",
        phase_id="merchant",
        extra_top_level_choices=[COMPLIMENT_CHOICE],
    )

    data["alpine_hardware"] = build_shop_conversation([], config=config)
    merchant_phase = data["alpine_hardware"]["speakPhases"][0]
    catalog_choice = next(
        c for c in merchant_phase["choices"] if c["id"] == config.catalog_choice_id
    )
    catalog_choice["choices"] = catalog

    conversations_path.write_text(json.dumps(data, indent=2) + "\n")
    print("Updated alpine_hardware conversation")


if __name__ == "__main__":
    main()