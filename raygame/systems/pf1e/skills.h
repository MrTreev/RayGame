#pragma once
#include "raygame/core/types.h"

namespace raygame::systems::pf1e {

class Skill {
    core::int32_t m_value{0};

public:
    constexpr Skill() = default;

    constexpr explicit Skill(core::int32_t val)
        : m_value(val) {}

    [[nodiscard]]
    constexpr decltype(m_value) val() const {
        return m_value;
    }
};

class Skills {
public:
    Skill m_acrobatics;
    Skill m_appraise;
    Skill m_bluff;
    Skill m_climb;

    struct {
        Skill m_alchemy;
        Skill m_armor;
        Skill m_baskets;
        Skill m_blacksmithing;
        Skill m_books;
        Skill m_bows;
        Skill m_calligraphy;
        Skill m_carpentry;
        Skill m_cloth;
        Skill m_clothing;
        Skill m_gemcutting;
        Skill m_glass;
        Skill m_jewelry;
        Skill m_leather;
        Skill m_locks;
        Skill m_paintings;
        Skill m_pottery;
        Skill m_sculptures;
        Skill m_ships;
        Skill m_shoes;
        Skill m_stonemasonry;
        Skill m_traps;
        Skill m_weapons;
        Skill m_untrained;
    } m_craft;

    Skill m_diplomacy;
    Skill m_disable_device;
    Skill m_disguise;
    Skill m_escape_artist;
    Skill m_fly;
    Skill m_handle_animal;
    Skill m_heal;
    Skill m_intimidate;

    struct {
        Skill m_arcana;
        Skill m_dungeoneering;
        Skill m_engineering;
        Skill m_geography;
        Skill m_history;
        Skill m_local;
        Skill m_nature;
        Skill m_nobility;
        Skill m_planes;
        Skill m_religion;
    } m_knowledge;

    Skill m_linguistics;
    Skill m_perception;

    struct {
        Skill m_act;
        Skill m_comedy;
        Skill m_dance;
        Skill m_keyboard_instruments;
        Skill m_oratory;
        Skill m_percussion_instruments;
        Skill m_sing;
        Skill m_string_instruments;
        Skill m_wind_instruments;
        Skill m_untrained;
    } m_perform;

    struct {
        Skill m_architect;
        Skill m_baker;
        Skill m_barrister;
        Skill m_brewer;
        Skill m_butcher;
        Skill m_clerk;
        Skill m_cook;
        Skill m_courtesan;
        Skill m_driver;
        Skill m_engineer;
        Skill m_farmer;
        Skill m_fisherman;
        Skill m_gambler;
        Skill m_gardener;
        Skill m_herbalist;
        Skill m_innkeeper;
        Skill m_librarian;
        Skill m_merchant;
        Skill m_midwife;
        Skill m_miller;
        Skill m_miner;
        Skill m_porter;
        Skill m_sailor;
        Skill m_scribe;
        Skill m_shepherd;
        Skill m_soldier;
        Skill m_soothsayer;
        Skill m_stable_master;
        Skill m_tanner;
        Skill m_trapper;
        Skill m_woodcutter;
    } m_profession;

    Skill m_ride;
    Skill m_sense_motive;
    Skill m_sleight_of_hand;
    Skill m_spellcraft;
    Skill m_stealth;
    Skill m_survival;
    Skill m_swim;
    Skill m_use_magic_device;
};
} // namespace raygame::systems::pf1e
