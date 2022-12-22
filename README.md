gbtoolsid - Game Boy Toolchain ID
=================================

A command line app for identifying tools used to build Game Boy ROMs

For the web version see:
https://bbbbbr.github.io/gbtoolsid_web/
https://github.com/bbbbbr/gbtoolsid_web


It attempts to identify the toolchain and engine through binary fingerprints:

Toolchains:
- GBDK 2.x and GBDK-2020
- Turbo Rascal Syntax Error

Game Engines:
- ZGB
- GBStudio

Audio Drivers:
- Carillon Player, [DevSound](https://github.com/DevEd2/DevSound) & [DevSoundLite](https://github.com/DevEd2/DevSoundLite), Freaq, GHX, GB Sound System, [GBT Player](https://github.com/AntonioND/gbt-player), [hUGETracker](https://github.com/SuperDisk/hUGETracker) & [fortISSimO](https://github.com/ISSOtm/fortISSimO), Lemon, LSDJ, MPlay, Music Box Black Box, MusyX, [Trackerboy](https://github.com/stoneface86/tbengine), Visual Impact's, [MMLGB](https://github.com/SimonLarsen/mmlgb), [GBMC](http://mydocuments.g2.xrea.com/html/gb/sounddriver.html)

Sound FX Drivers:
- FX Hammer, [CBT-FX](https://github.com/datguywitha3ds/CBT-FX), [VAL-FX](https://github.com/ISSOtm/val-fx), [VGM2GBSFX](https://github.com/untoxa/VGM2GBSFX)


Output is available in several formats:
- standard text (only this mode shows multiple entries for a given category if found)
- json (`-oj`)
- csv row (`-oc` and `-oC`)


```
gbtoolsid [options] infile.gb[c]

Use: Try to identify the toolchain used to build a
     Game Boy game the result is printed to stdout.

Options
-h   : Show this help screen
-oj  : json style output
-oc  : csv style output
-oC  : Bare csv style output (no field names)
-s   : Strict mode: require GBDK match before testing ZGB or GBStudio
-pF  : Show full path to file in output (default: filename only)

Example: "gbtoolchainid petris.gbc"

```


Some example output:
```
File: deadeus.gb
Tools: GBDK, Version: 2.x - 2020-3.2.0
Engine: GBStudio, Version: 1.0.0 - 1.2.1
Music: GBT Player


File: POWA! DEMO.gbc
Tools: GBDK, Version: 2.x - 2020-3.2.0
Engine: ZGB, Version: 2020.1 - 2021.0
Music: GBT Player


File: IndestructoTankGB.gb
Tools: GBDK, Version: 2020.4.0.2
Music: GBT Player


File: Super_JetPak_DX_DMG-SJPD-UKV.gbc
Tools: GBDK, Version: 2.x - 2020-3.2.0
Music: GHX


File: Tuff.gb
Tools: <unknown>


File: Last Crown Warriors (Demo) 1.1.1.gb
Tools: <unknown>
Music: Carillon Player
SoundFX: FX Hammer

```

To scan in bulk, it can be combined with other tools, for example:
```
find path/to/some/ROMs/* -iname "*.gb*" -type f -print0 | xargs -0 -n1 path/to/gbtoolsid
```
Or, scan in bulk and dump to csv:
```
find path/to/some/ROMs/* -iname "*.gb" -type f | xargs -I {} path/to/gbtoolsid -pF -oC "{}" > path/to/someoutputfile.csv
```
