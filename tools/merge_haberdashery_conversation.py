#!/usr/bin/env python3
"""Merge haberdashery shopkeeper conversation into conversations.json."""

from __future__ import annotations

import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from shop_utils import ShopDialogConfig, build_shop_conversation  # noqa: E402

WALLET_GREETING_PHASE = {
    "id": "shopkeeper_wallet",
    "type": "scripted",
    "resetOnSceneEnter": False,
    "intro": (
        "The gentleman behind the counter sets down his pen and regards you with "
        "practiced courtesy. His vest is pressed, his collar crisp, his hands clean "
        "in the manner of a man who sells refinement at altitude.\n\n"
        "He pauses, studying your face as though sorting you into a ledger already written.\n\n"
        "\"Good day, Sir. How are you enjoying the new wallet?\""
    ),
    "choices": [
        {
            "id": "wallet_confused",
            "label": "Um, I don't follow. What wallet.",
            "response": (
                "\"My apologies, sir. You resemble another customer that visited my shop "
                "a few days ago.\"\n\n"
                "He recovers his composure with a small inclination of the head.\n\n"
                "\"Apologies for the confusion. Is there anything I can help you find?\""
            ),
            "grantStoryFlag": "ridge_haberdashery:greeting_done",
            "startPhase": "shopkeeper",
            "skipIntroOnStartPhase": True,
            "closePhase": True,
        },
        {
            "id": "wallet_great",
            "label": "Oh, uh. It's great...",
            "response": (
                "He studies you a moment longer than courtesy requires, confusion working "
                "behind his eyes.\n\n"
                "\"Hmmm... Let's move on. Is there anything I can help you find?\""
            ),
            "grantStoryFlag": "ridge_haberdashery:greeting_done",
            "startPhase": "shopkeeper",
            "skipIntroOnStartPhase": True,
            "closePhase": True,
        },
    ],
}

COMPLIMENT_CHOICE = {
    "id": "compliment_store",
    "label": "This is an impressive store.",
    "response": (
        "You let your gaze travel the shelves, the bolt rolls, the glass cases, the iron "
        "rack of ready-made coats, taking it in the way you would a room that has been "
        "assembled with intention.\n\n"
        "\"This is an impressive store,\" you say.\n\n"
        "A modest smile crosses his face, pleased but not surprised—he has heard the "
        "compliment before and still believes it.\n\n"
        "\"You are kind to say so, sir.\" He rests his fingertips on the counter. "
        "\"I trained on Savile Row before the mountains called. My uncle kept a dry goods "
        "post on this ridge when the High Line was only timber camps and prayer. I came up "
        "to visit, saw what men lacked at altitude, and stayed. That was eighteen "
        "ninety-one. Everything here is chosen so a man need not descend to Graysmill "
        "merely to look as though he belongs in a room with money.\""
    ),
    "consumeOnSelect": True,
    "persistConsumed": True,
    "resumeTopLevel": True,
    "closePhase": False,
}


def main() -> None:
    catalog = json.loads((ROOT / "tools" / "haberdashery_catalog.json").read_text())
    conversations_path = ROOT / "resources" / "conversations.json"
    data = json.loads(conversations_path.read_text())

    config = ShopDialogConfig(
        merchant_tone="haberdasher",
        phase_id="shopkeeper",
        extra_top_level_choices=[COMPLIMENT_CHOICE],
    )

    data["ridge_haberdashery"] = build_shop_conversation(
        [],
        config=config,
        greeting_phases=[WALLET_GREETING_PHASE],
        requires_flag="ridge_haberdashery:greeting_done",
    )

    shopkeeper_phase = data["ridge_haberdashery"]["speakPhases"][-1]
    catalog_choice = next(
        c for c in shopkeeper_phase["choices"] if c["id"] == config.catalog_choice_id
    )
    catalog_choice["choices"] = catalog

    conversations_path.write_text(json.dumps(data, indent=2) + "\n")
    print("Updated ridge_haberdashery conversation")


if __name__ == "__main__":
    main()