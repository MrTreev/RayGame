#include "raygame/core/base/types.h"

namespace raygame::systems::pf1e {
struct Skills {
    int32_t acrobatics;
    int32_t appraise;
    int32_t bluff;
    int32_t climb;

    struct {
        int32_t alchemy;
        int32_t armor;
        int32_t baskets;
        int32_t blacksmithing;
        int32_t books;
        int32_t bows;
        int32_t calligraphy;
        int32_t carpentry;
        int32_t cloth;
        int32_t clothing;
        int32_t gemcutting;
        int32_t glass;
        int32_t jewelry;
        int32_t leather;
        int32_t locks;
        int32_t paintings;
        int32_t pottery;
        int32_t sculptures;
        int32_t ships;
        int32_t shoes;
        int32_t stonemasonry;
        int32_t traps;
        int32_t weapons;
        int32_t untrained;
    } craft;

    int32_t diplomacy;
    int32_t disable_device;
    int32_t disguise;
    int32_t escape_artist;
    int32_t fly;
    int32_t handle_animal;
    int32_t heal;
    int32_t intimidate;

    struct {
        int32_t arcana;
        int32_t dungeoneering;
        int32_t engineering;
        int32_t geography;
        int32_t history;
        int32_t local;
        int32_t nature;
        int32_t nobility;
        int32_t planes;
        int32_t religion;
    } knowledge;

    int32_t linguistics;
    int32_t perception;

    struct {
        int32_t act;
        int32_t comedy;
        int32_t dance;
        int32_t keyboard_instruments;
        int32_t oratory;
        int32_t percussion_instruments;
        int32_t sing;
        int32_t string_instruments;
        int32_t wind_instruments;
        int32_t untrained;
    } perform;

    struct {
        int32_t architect;
        int32_t baker;
        int32_t barrister;
        int32_t brewer;
        int32_t butcher;
        int32_t clerk;
        int32_t cook;
        int32_t courtesan;
        int32_t driver;
        int32_t engineer;
        int32_t farmer;
        int32_t fisherman;
        int32_t gambler;
        int32_t gardener;
        int32_t herbalist;
        int32_t innkeeper;
        int32_t librarian;
        int32_t merchant;
        int32_t midwife;
        int32_t miller;
        int32_t miner;
        int32_t porter;
        int32_t sailor;
        int32_t scribe;
        int32_t shepherd;
        int32_t soldier;
        int32_t soothsayer;
        int32_t stable_master;
        int32_t tanner;
        int32_t trapper;
        int32_t woodcutter;
    } profession;

    int32_t ride;
    int32_t sense_motive;
    int32_t sleight_of_hand;
    int32_t spellcraft;
    int32_t stealth;
    int32_t survival;
    int32_t swim;
    int32_t use_magic_device;
};
} // namespace raygame::systems::pf1e
