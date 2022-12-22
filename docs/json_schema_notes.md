
# Rough summary of JSON schema

## Enabling output
Use the `-oj` argument to enable JSON output format

## Example output:
Invocation:`./gbtoolsid -oj test/zgb_template_2022.0.gb`

```
{
"file": "zgb_template_2022.0.gb",
"toolsName": "GBDK", "toolsVersion": "2020.4.1.0+",
"engineName": "ZGB", "engineVersion": "2022.0+",
"musicName": "hUGETracker", "musicVersion": "SuperDisk",
"soundfxName": null, "soundfxVersion": null
}
```

## Notes:
- For every Tool type there are matching `...Name` and `...Version` field names.
  - Possible Name fields: `["toolsName", "engineName", "musicName", "soundfxName"]`
  - Matching Version fields: `["toolsVersion", "engineVersion", "musicVersion", "soundfxVersion"]`
- If a Tool type is not detected then non-quoted `null` will be used for both the name and version field values.
- If a Tool type entry has been detected but lacks version data then an empty quoted string `""` will be used for the version field value.
- While multiple entries for each Tool type can be detected, only the first entry detected for each category will be rendered in the JSON format (the default console format will render all detected entries). This scenario is uncommon and mostly occurs for game ROMs which have crack-tros with additional music drivers appended to them.

## Current Possible Values
- Only Tool type Names are enumerated below.
- All possible Tool type Versions are not enumerated, however the values will all be quoted strings (when the value is not `null`)

```
{
    "file": [<string quoted filename>],
    "toolsName": [null, "GBDK", "Turbo Rascal Syntax Error"],
    "toolsVersion": [null, "", "Unknown", "<various>"],
    "engineName":  [null, "GBStudio", "ZGB"],
    "engineVersion": [null, "", "Unknown", "<various>"],
    "musicName": [null, "GHX", "DevSound", "DevSound", "Visual Impact", "MusyX", "Freaq", "LSDJ", "hUGETracker", "Trackerboy engine", "Black Box Music Box", "Lemon", "GBT Player", "Carillon Player", "MPlay", "GBSoundSystem", "MMLGB", "GBMC"],
    "musicVersion": [null, "", "Unknown", "<various>"],
    "soundfxName": [null, "FX Hammer", "CBT-FX", "VAL-FX", "VGM2GBSFX"],
    "soundfxVersion": [null, "", "Unknown", "<various>"],
}
```
