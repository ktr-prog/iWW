#ifndef GFX_PATTERNTEXCACHE_H
#define GFX_PATTERNTEXCACHE_H

#include "types.h"
#include "save/Pattern.h"
#include "sys/RecordFile.h"


class PatternPaletteFile {
public:
    u8 *fileData;
    u8 *palettes[16];
    PatternPaletteFile();
    ~PatternPaletteFile();
    void unload();
    void load();
    void clear();
};

class PatternTexKeys {
public:
    u32 unk_00;
    PatternTexKeys();
    ~PatternTexKeys();
};

class PatternTexCache {
public:
    PatternTexKeys texKeys;
    PatternPaletteFile paletteFile;
    PatternTexCache();
    ~PatternTexCache();
    void reset();
    u8 *getPalette(s32 i);
    void load();
    void unload();
    void createTextures();
    void setAbleDirty(s32 bit);
    BOOL testAndClearAbleDirty(s32 bit);
    u8 *getAbleTexKey(s32 i);
    u8 *getPlayerTexKey(s32 a, s32 b);
};

struct ClothTexStorage {
    u32 v[0xb1];
};

class PatternPresetInfoFile {
public:
    RecordFile file;
    PatternPresetInfoFile();
    ~PatternPresetInfoFile();
};

class PresetPatternBuffer {
public:
    Pattern pattern;
    PresetPatternBuffer();
    ~PresetPatternBuffer();
    BOOL load(s32 n);
    Pattern *getPattern();
};

#endif
