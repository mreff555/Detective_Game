#!/usr/bin/env python3
"""Merge haberdashery shopkeeper conversation into conversations.json."""

from __future__ import annotations

import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def main() -> None:
    catalog = json.loads((ROOT / "tools" / "haberdashery_catalog.json").read_text())
    conversations_path = ROOT / "resources" / "conversations.json"
    data = json.loads(conversations_path.read_text())

    data["ridge_haberdashery"] = {
        "speakPhases": [
            {
                "id": "shopkeeper",
                "type": "scripted",
                "resetOnSceneEnter": True,
                "intro": (
                    "The gentleman behind the counter sets down his pen and regards you with "
                    "practiced courtesy. His vest is pressed, his collar crisp, his hands clean "
                    "in the manner of a man who sells refinement at altitude.\n\n"
                    "\"Good day, sir. Is there anything I can help you find?\""
                ),
                "resumeIntro": (
                    "\"Now then, sir,\" he says, settling his hands on the counter. "
                    "\"What else may I help you find?\""
                ),
                "choices": [
                    {
                        "id": "what_on_offer",
                        "label": "Yes, what do you have on offer?",
                        "response": (
                            "\"Well... anything you see here.\" He sweeps one hand across the "
                            "shelves and counter with the easy pride of a man who knows his "
                            "stock by heart. \"We also do custom jackets, shirts, vests, and "
                            "trousers.\""
                        ),
                        "choices": catalog,
                    },
                    {
                        "id": "compliment_store",
                        "label": "This is an impressive store.",
                        "response": (
                            "You let your gaze travel the shelves, the bolt rolls, the glass "
                            "cases, the iron rack of ready-made coats, taking it in the way you "
                            "would a room that has been assembled with intention.\n\n"
                            "\"This is an impressive store,\" you say.\n\n"
                            "A modest smile crosses his face, pleased but not surprised—he has "
                            "heard the compliment before and still believes it.\n\n"
                            "\"You are kind to say so, sir.\" He rests his fingertips on the "
                            "counter. \"I trained on Savile Row before the mountains called. My "
                            "uncle kept a dry goods post on this ridge when the High Line was "
                            "only timber camps and prayer. I came up to visit, saw what men "
                            "lacked at altitude, and stayed. That was eighteen ninety-one. "
                            "Everything here is chosen so a man need not descend to Graysmill "
                            "merely to look as though he belongs in a room with money.\""
                        ),
                        "consumeOnSelect": True,
                        "persistConsumed": True,
                        "resumeTopLevel": True,
                        "closePhase": False,
                    },
                    {
                        "id": "just_browsing",
                        "label": "Just browsing at the moment.",
                        "response": (
                            "\"Of course, sir,\" he says warmly. \"Take your time. "
                            "I will be here if you need anything.\""
                        ),
                    },
                ],
            }
        ]
    }

    conversations_path.write_text(json.dumps(data, indent=2) + "\n")
    print("Updated ridge_haberdashery conversation")


if __name__ == "__main__":
    main()