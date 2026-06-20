#include <ConversationManager.h>
#include <cstdlib>

namespace testgame
{

void ConversationManager::onEnterScene(const std::string& sceneId, const SceneSpeakConfig& config)
{
    currentSceneId = sceneId;

    for (const ConversationPhase& phase : config.phases)
    {
        if (phase.resetOnSceneEnter)
        {
            completedPhaseIds.erase(phase.id);
            clearConsumedScriptedChoices(phase.id);
            lastRandomLineIndex.erase(randomPoolKey(sceneId, phase));
        }
    }

    awaitingChoice = false;
    combatAttackAllowed = false;
    combatEncounterId.clear();
    activeScriptPhaseId.clear();
    activeParentChoiceId.clear();
    pendingChoices.clear();
}

void ConversationManager::clearPendingEncounter()
{
    if (!activeScriptPhaseId.empty())
        markPhaseComplete(activeScriptPhaseId);

    awaitingChoice = false;
    combatAttackAllowed = false;
    combatEncounterId.clear();
    activeScriptPhaseId.clear();
    activeParentChoiceId.clear();
    pendingChoices.clear();
}

bool ConversationManager::isPhaseComplete(const std::string& phaseId) const
{
    return completedPhaseIds.count(phaseId) > 0;
}

void ConversationManager::markPhaseComplete(const std::string& phaseId)
{
    completedPhaseIds.insert(phaseId);
}

bool ConversationManager::isPhaseRequirementMet(
    const ConversationPhase& phase,
    const std::set<std::string>& storyFlags) const
{
    if (!phase.requiresPhaseId.empty() && !isPhaseComplete(phase.requiresPhaseId))
        return false;

    if (!phase.requiresFlag.empty() && storyFlags.count(phase.requiresFlag) == 0)
        return false;

    return true;
}

const ConversationPhase* ConversationManager::findPhase(
    const SceneSpeakConfig& config,
    const std::string& phaseId) const
{
    for (const ConversationPhase& phase : config.phases)
    {
        if (phase.id == phaseId)
            return &phase;
    }

    return nullptr;
}

const ConversationPhase* ConversationManager::findActivePhase(
    const std::string& sceneId,
    const SceneSpeakConfig& config,
    const std::set<std::string>& storyFlags) const
{
    (void)sceneId;

    for (const ConversationPhase& phase : config.phases)
    {
        if (!isPhaseRequirementMet(phase, storyFlags))
            continue;

        if (phase.type == ConversationPhaseType::Once && !isPhaseComplete(phase.id))
            return &phase;

        if (phase.type == ConversationPhaseType::Scripted && !isPhaseComplete(phase.id))
            return &phase;

        if (phase.type == ConversationPhaseType::Random && !phase.lines.empty())
            return &phase;
    }

    return nullptr;
}

bool ConversationManager::canSpeak(
    const SceneSpeakConfig& config,
    bool baseSpeakEnabled,
    const std::set<std::string>& storyFlags) const
{
    if (!baseSpeakEnabled || config.phases.empty() || awaitingChoice)
        return false;

    return findActivePhase(currentSceneId, config, storyFlags) != nullptr;
}

SpeakResult ConversationManager::buildNarrativeResult(
    const std::string& text,
    const StatusEffect& status,
    const GrantedInventoryItemDef& grantItem) const
{
    SpeakResult result;
    if (text.empty() && !grantItem.isValid())
        return result;

    result.action = SpeakResult::Action::ShowNarrative;
    result.narrative = text;
    if (status.hasDelta())
        result.statusEffects.push_back(status);
    if (grantItem.isValid())
        result.grantItem = grantItem;
    return result;
}

std::string ConversationManager::scriptedChoiceKey(
    const std::string& phaseId,
    const std::string& choiceId) const
{
    return phaseId + ":" + choiceId;
}

bool ConversationManager::isScriptedChoiceConsumed(
    const std::string& phaseId,
    const std::string& choiceId) const
{
    return consumedScriptedChoiceIds.count(scriptedChoiceKey(phaseId, choiceId)) > 0;
}

void ConversationManager::markScriptedChoiceConsumed(
    const std::string& phaseId,
    const std::string& choiceId)
{
    consumedScriptedChoiceIds.insert(scriptedChoiceKey(phaseId, choiceId));
}

void ConversationManager::clearConsumedScriptedChoices(const std::string& phaseId)
{
    const std::string prefix = phaseId + ":";
    for (auto it = consumedScriptedChoiceIds.begin(); it != consumedScriptedChoiceIds.end();)
    {
        if (it->compare(0, prefix.size(), prefix) == 0)
            it = consumedScriptedChoiceIds.erase(it);
        else
            ++it;
    }
}

std::vector<ConversationChoiceDef> ConversationManager::remainingTopLevelChoices(
    const ConversationPhase& phase) const
{
    std::vector<ConversationChoiceDef> remaining;
    remaining.reserve(phase.choices.size());

    for (const ConversationChoiceDef& choice : phase.choices)
    {
        if (!isScriptedChoiceConsumed(phase.id, choice.id))
            remaining.push_back(choice);
    }

    return remaining;
}

bool ConversationManager::allTopLevelChoicesConsumed(const ConversationPhase& phase) const
{
    for (const ConversationChoiceDef& choice : phase.choices)
    {
        if (!isScriptedChoiceConsumed(phase.id, choice.id))
            return false;
    }

    return true;
}

SpeakResult ConversationManager::resumeScriptedPhase(
    const ConversationPhase& phase,
    const std::string& responseText,
    const StatusEffect& status) const
{
    const std::vector<ConversationChoiceDef> remaining = remainingTopLevelChoices(phase);
    if (remaining.empty())
        return buildNarrativeResult(responseText, status);

    SpeakResult result;
    result.action = SpeakResult::Action::ShowChoices;
    result.narrative = responseText;
    if (status.hasDelta())
        result.statusEffects.push_back(status);

    const std::string& resumeText = !phase.resumeIntro.empty() ? phase.resumeIntro : phase.intro;
    if (!resumeText.empty())
    {
        if (!result.narrative.empty())
            result.narrative += "\n\n";
        result.narrative += resumeText;
    }

    result.choices = remaining;
    return result;
}

const ConversationChoiceDef* ConversationManager::findChoiceInList(
    const std::vector<ConversationChoiceDef>& choices,
    const std::string& choiceId) const
{
    for (const ConversationChoiceDef& choice : choices)
    {
        if (choice.id == choiceId)
            return &choice;
    }

    return nullptr;
}

const ConversationChoiceDef* ConversationManager::findTopLevelChoiceForId(
    const ConversationPhase& phase,
    const std::string& choiceId) const
{
    if (const ConversationChoiceDef* topLevel = findChoiceInList(phase.choices, choiceId))
        return topLevel;

    for (const ConversationChoiceDef& topLevel : phase.choices)
    {
        if (findChoiceInList(topLevel.followUpChoices, choiceId))
            return &topLevel;
    }

    return nullptr;
}

std::string ConversationManager::randomPoolKey(
    const std::string& sceneId,
    const ConversationPhase& phase) const
{
    return sceneId + ":" + (phase.poolId.empty() ? phase.id : phase.poolId);
}

SpeakResult ConversationManager::pickRandomLine(
    const std::string& sceneId,
    const ConversationPhase& phase)
{
    if (phase.lines.empty())
        return SpeakResult();

    std::vector<size_t> eligibleIndices;
    eligibleIndices.reserve(phase.lines.size());
    for (size_t i = 0; i < phase.lines.size(); ++i)
    {
        const RandomConversationLine& line = phase.lines[i];
        if (line.once && !line.id.empty() && completedRandomLineIds.count(line.id) > 0)
            continue;

        eligibleIndices.push_back(i);
    }

    if (eligibleIndices.empty())
        return SpeakResult();

    int totalWeight = 0;
    for (size_t index : eligibleIndices)
        totalWeight += phase.lines[index].weight > 0 ? phase.lines[index].weight : 1;

    if (totalWeight <= 0)
        return SpeakResult();

    const std::string poolKey = randomPoolKey(sceneId, phase);
    int chosenIndex = 0;

    if (phase.avoidRepeat && eligibleIndices.size() > 1)
    {
        const int lastIndex = lastRandomLineIndex.count(poolKey) > 0
            ? lastRandomLineIndex.at(poolKey)
            : -1;

        int guard = 0;
        do
        {
            int roll = rand() % totalWeight;
            int cumulative = 0;
            for (size_t index : eligibleIndices)
            {
                cumulative += phase.lines[index].weight > 0 ? phase.lines[index].weight : 1;
                if (roll < cumulative)
                {
                    chosenIndex = (int)index;
                    break;
                }
            }
            ++guard;
        }
        while (chosenIndex == lastIndex && guard < 12);

        lastRandomLineIndex[poolKey] = chosenIndex;
    }
    else
    {
        int roll = rand() % totalWeight;
        int cumulative = 0;
        for (size_t index : eligibleIndices)
        {
            cumulative += phase.lines[index].weight > 0 ? phase.lines[index].weight : 1;
            if (roll < cumulative)
            {
                chosenIndex = (int)index;
                break;
            }
        }
        lastRandomLineIndex[poolKey] = chosenIndex;
    }

    const RandomConversationLine& line = phase.lines[(size_t)chosenIndex];

    if (line.once && !line.id.empty())
        completedRandomLineIds.insert(line.id);

    if (!line.choices.empty())
    {
        SpeakResult result;
        result.action = SpeakResult::Action::ShowChoices;
        result.narrative = line.text;
        result.choices = line.choices;
        awaitingChoice = true;
        activeScriptPhaseId = phase.id;
        pendingChoices = line.choices;
        combatAttackAllowed = line.allowAttack;
        combatEncounterId = line.attackEncounterId;
        return result;
    }

    return buildNarrativeResult(line.text, line.status);
}

SpeakResult ConversationManager::handleSpeak(
    const std::string& sceneId,
    const SceneSpeakConfig& config,
    const std::set<std::string>& storyFlags)
{
    if (awaitingChoice || config.phases.empty())
        return SpeakResult();

    const ConversationPhase* phase = findActivePhase(sceneId, config, storyFlags);
    if (!phase)
        return SpeakResult();

    if (phase->type == ConversationPhaseType::Once)
    {
        markPhaseComplete(phase->id);
        return buildNarrativeResult(phase->text, phase->status, phase->grantItem);
    }

    if (phase->type == ConversationPhaseType::Scripted)
    {
        SpeakResult result;
        result.action = SpeakResult::Action::ShowChoices;
        result.narrative = phase->intro;
        result.choices = phase->choices;
        awaitingChoice = true;
        activeScriptPhaseId = phase->id;
        pendingChoices = phase->choices;
        return result;
    }

    if (phase->type == ConversationPhaseType::Random)
        return pickRandomLine(sceneId, *phase);

    return SpeakResult();
}

SpeakResult ConversationManager::resolveScriptedChoice(
    const SceneSpeakConfig& /*config*/,
    const ConversationPhase& phase,
    const ConversationChoiceDef& choice,
    bool fromTopLevel)
{
    if (!choice.followUpChoices.empty())
    {
        if (fromTopLevel)
            activeParentChoiceId = choice.id;

        SpeakResult result;
        result.action = SpeakResult::Action::ShowChoices;
        result.narrative = choice.response;
        result.choices = choice.followUpChoices;
        awaitingChoice = true;
        activeScriptPhaseId = phase.id;
        pendingChoices = choice.followUpChoices;
        return result;
    }

    const std::string parentChoiceId = fromTopLevel ? choice.id : activeParentChoiceId;
    if (!parentChoiceId.empty())
        markScriptedChoiceConsumed(phase.id, parentChoiceId);

    activeParentChoiceId.clear();
    pendingChoices.clear();
    combatAttackAllowed = false;
    combatEncounterId.clear();

    if (allTopLevelChoicesConsumed(phase))
    {
        awaitingChoice = false;
        activeScriptPhaseId.clear();
        markPhaseComplete(phase.id);
        SpeakResult result = buildNarrativeResult(choice.response, choice.status);
        if (!choice.status.onZeroLucidity.empty())
            result.action = SpeakResult::Action::ShowNarrative;
        return result;
    }

    SpeakResult result = resumeScriptedPhase(phase, choice.response, choice.status);
    awaitingChoice = true;
    activeScriptPhaseId = phase.id;
    pendingChoices = result.choices;
    if (!choice.status.onZeroLucidity.empty())
        result.action = SpeakResult::Action::ShowNarrative;
    return result;
}

SpeakResult ConversationManager::resolveChoice(
    const SceneSpeakConfig& config,
    const std::string& choiceId)
{
    if (!awaitingChoice || activeScriptPhaseId.empty())
        return SpeakResult();

    const ConversationPhase* phase = findPhase(config, activeScriptPhaseId);
    if (!phase || phase->type != ConversationPhaseType::Scripted)
        return SpeakResult();

    const ConversationChoiceDef* chosen = findChoiceInList(pendingChoices, choiceId);
    if (!chosen)
        return SpeakResult();

    const bool fromTopLevel = activeParentChoiceId.empty();
    return resolveScriptedChoice(config, *phase, *chosen, fromTopLevel);
}

SpeakResult ConversationManager::resolveChoiceFromConfig(
    const SceneSpeakConfig& config,
    const std::string& choiceId)
{
    for (const ConversationPhase& phase : config.phases)
    {
        if (phase.type != ConversationPhaseType::Scripted)
            continue;

        const ConversationChoiceDef* topLevel = findTopLevelChoiceForId(phase, choiceId);
        if (!topLevel)
            continue;

        const bool fromTopLevel = topLevel->id == choiceId;
        const ConversationChoiceDef* chosen = fromTopLevel
            ? topLevel
            : findChoiceInList(topLevel->followUpChoices, choiceId);
        if (!chosen)
            continue;

        return resolveScriptedChoice(config, phase, *chosen, fromTopLevel);
    }

    return SpeakResult();
}

void ConversationManager::exportPersistState(ConversationPersistState& out) const
{
    out.completedPhaseIds = completedPhaseIds;
    out.completedRandomLineIds = completedRandomLineIds;
    out.consumedScriptedChoiceIds = consumedScriptedChoiceIds;
}

void ConversationManager::importPersistState(const ConversationPersistState& state)
{
    completedPhaseIds = state.completedPhaseIds;
    completedRandomLineIds = state.completedRandomLineIds;
    consumedScriptedChoiceIds = state.consumedScriptedChoiceIds;
    awaitingChoice = false;
    combatAttackAllowed = false;
    combatEncounterId.clear();
    activeScriptPhaseId.clear();
    activeParentChoiceId.clear();
    pendingChoices.clear();
}

}